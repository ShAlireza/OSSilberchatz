#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[]) {
  
  int server_socket;
  int client_socket;
  char buffer[512];

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
    length_of_address = sizeof(connection_address);
    client_socket = accept(server_socket, (struct sockaddr *)&connection_address, &length_of_address);
    while (1) {
      int bytes = read(client_socket, buffer, sizeof(buffer));
      printf("Read message from client: %s\n", buffer);
      if (bytes == 0) {
        close(client_socket);
        printf("Client socket is closed!\n");
        break;
      }
      message = buffer;

      printf("Message from server: %s\n", message);
      write(client_socket, message, strlen(message));
    }
  }

  close(server_socket);

  return 0;
}
