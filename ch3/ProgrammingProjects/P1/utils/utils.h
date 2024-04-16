#ifndef UTILS_HEADER_H
#define UTILS_HEADER_H

#include <stdbool.h>



char **split(char *str, int *ret_size);

char *read_env(char *name, char *def);

char *concat_strings(char *first, char *second);

bool file_exists(char *dir_path, char *file_name);

char *sub_string(const char *str, int start, int end);

char *find_binary(char *paths, char *file_name);

void replace_substring(char *source, const char *target, const char *replacement);

char *get_current_time();

char *ltrim(char *s);

char *rtrim(char *s);

char *trim(char *s);

#endif
