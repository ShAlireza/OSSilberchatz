
#ifndef UTILS_HEADER_H
#define UTILS_HEADER_H

typedef struct {
  char *key;
  char *value;
} token;

unsigned char numbers[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14, 15, 16};

token *test = (token *)numbers;

#endif
