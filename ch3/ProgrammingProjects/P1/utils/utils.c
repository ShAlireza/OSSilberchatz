#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#include <time.h>

#include "utils.h"

/* 
 * Creates a null terminated list of tokens
 * */

char **split(char *str, int *ret_size) {
  char * temp = str;
  int tokens_count = 1;

  while (*temp != '\0') {
    if (*temp == ' ') {
      tokens_count++;
      // while (*temp == ' ')
        // temp++;
    }
    temp++;
  }

  *ret_size = tokens_count;

  char **tokens = (char **)malloc(sizeof(char *) * (tokens_count + 1));
  char *token = strtok(str, " ");

  tokens[0] = token;
  int i = 1;
  while (token != NULL) {
    token = strtok(NULL, " ");
    tokens[i++] = token;
  }
  tokens[tokens_count] = NULL;

  return tokens;
}


char *read_env(char *name, char *def) {
  char *value = getenv(name);

  if (value == NULL) {
    return def;
  }

  return value;
}

char *concat_strings(char *first, char *second) {
  int target_len = strlen(first) + strlen(second);
  char *target = (char *)malloc(target_len + 1);
  target[target_len] = '\0';

  int i = 0;
  while (*first != '\0') {
    target[i++] = *first;
    first++;
  }
  while (*second != '\0') {
    target[i++] = *second;
    second++;
  }

  return target;
}


bool file_exists(char *dir_path, char *file_name) {
  char *dir_with_slash = concat_strings(dir_path, "/");
  char *absolute_path = concat_strings(dir_with_slash, file_name);

  int result = access(absolute_path, F_OK | X_OK);

  return !result ? true : false;
}

char *sub_string(const char *str, int start, int end) {
  int length = end - start;

  char *target = (char *)malloc(length + 1);
  target[length] = '\0';

  strncpy(target, str + start, length);

  return target;
}

char *find_binary(char *paths, char *file_name) {
  int start = 0;
  int end = 0;

  paths = concat_strings(".:", paths);

  while (paths[end] != '\0') {
    if (paths[end] == ':') {
      char *path = sub_string(paths, start, end);
      bool exists = file_exists(path, file_name);
      if (exists) {
        char *path_with_slash = concat_strings(path, "/");
        return concat_strings(path_with_slash, file_name);
      }
      start = end + 1;
    }
    end++;
  }

  return NULL;
}

void replace_substring(char *source, const char *target, const char *replacement) {
    char buffer[1024];
    char *insert_point = buffer;
    const char *tmp = source; 
    size_t target_len = strlen(target);
    size_t repl_len = strlen(replacement);

    while (1) {
        const char *p = strstr(tmp, target);

        if (p == NULL) {
            strcpy(insert_point, tmp);
            insert_point += strlen(tmp);
            break;
        }

        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;

        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;

        tmp = p + target_len;
    }

    *insert_point = '\0';
    strcpy(source, buffer);
}


char *get_current_time() {
  time_t now;
  struct tm *local_time;

  now = time(NULL);
  local_time = localtime(&now);

  char *time_str = (char *)malloc(9);
  strftime(time_str, 9, "%H:%M:%S", local_time);


  return time_str; 
}


char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}
