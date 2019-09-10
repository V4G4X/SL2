#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  printf("This is a Process no. 1\n");
  char string[32767];
  int fd = open("b1_to_b2", O_WRONLY);
  printf("Enter a set of sentences.\n");
  fgets(string, 32767, stdin);
  write(fd, string, strlen(string));
  while (1) {
  }
  close(fd);
  return 0;
}
