#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_commas(char* input) {
  int i = 0;
  int count = 0;
  while(input[i] != '\0') {
    if (input[i] == ',') count++;
    i++;
  }
  return count;
}

/**
 * Returns the length of the email address & the grades
 */
int email_len(char* input, int commas) {
  int i = 0;
  int count = 0;
  while (count < commas) {
    if (input[i] == ',') count++;
    i++;
  }
  return i;
}

char* remove_commas (char* input) {
  int commas = count_commas(input);
  int count = 0;
  int i = 0;
  while (count < 5) {
    if (input[i] == ',') count++;
    i++;
  }

  input += i;
  int len = email_len(input, commas - 5);
  char* clean = malloc(len);
  memcpy(clean, input, len-1);
  clean[len] = '\0';
  return clean;
}

void main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: trimmer infile outfile\n");
    return;
  }

  FILE* infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("%s: No such file or directory.\n", argv[1]);
    return;
  }

  /* FILE* outfile = fopen(argv[2], "w"); */
  char buf[256];
  while(fgets(buf, 255, infile) != NULL) {
    int i = 0;
    while (buf[i] != '\n') i++;
    buf[i] = '\0';
    if (count_commas(buf) != 0) {
      char* clean = remove_commas(buf);
      printf("%s\n", clean);
      free(clean);
    }
  }
  fclose(infile);
}
