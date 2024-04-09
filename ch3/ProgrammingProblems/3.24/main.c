#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"


struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len + 1);

  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }

  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);

  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }

  memcpy(s->ptr+s->len, ptr, size * nmemb);

  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size * nmemb;
}

char *get_quote() {
  CURL *curl;
  CURLcode response;
  struct string s;
  init_string(&s);
  const cJSON *quote;
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://zenquotes.io/api/random");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

    response = curl_easy_perform(curl);
    if (response != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(response));
    } else {
      cJSON *json = cJSON_Parse(s.ptr);
      if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
      } else {
        cJSON *json_array = json;
        const cJSON *json_object = NULL;

        cJSON_ArrayForEach(json_object, json_array) {
          quote = cJSON_GetObjectItemCaseSensitive(json_object, "q");
          if (cJSON_IsString(quote) && (quote->valuestring != NULL)) {
            printf("Received data: %s\n", quote->valuestring);
          }
          break;
        }
      }
    }
  }

  return quote->valuestring;
}

int main(int argc, char *argv[]) {
  
  int server_socket;
  int client_socket;

  int length_of_address;
  int option_value = 1;

  struct sockaddr_in server_address, connection_address;
  memset(&server_address, 0, sizeof(server_address));
  memset(&connection_address, 0, sizeof(connection_address));

  char *message; 

  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  int status = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value));

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(6017);
  server_address.sin_addr.s_addr = INADDR_ANY;

  status = bind(server_socket, (struct sockaddr *)&server_address, sizeof(struct sockaddr));

  status = listen(server_socket, 4);

  while (1) {
    message = get_quote();

    length_of_address = sizeof(connection_address);
    client_socket = accept(server_socket, (struct sockaddr *)&connection_address, &length_of_address);

    write(client_socket, message, strlen(message));
    write(client_socket, "\n", 1);
    write(client_socket, message, strlen(message));
    write(client_socket, "\n", 1);
    write(client_socket, message, strlen(message));
    write(client_socket, "\n", 1);
    close(client_socket);
  }

  close(server_socket);

  return 0;
}
