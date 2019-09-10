#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define FILENAME "file.txt"

int main(int argc, char const *argv[]) {
  int fldes[2];
  int fldes2[2];
  int stat = pipe(fldes);
  int stat2 = pipe(fldes2);
  if (stat == -1 || stat2 == -1) {
    perror("Piping Error\n");
    EXIT_FAILURE;
  }
  int forkId = fork();
  if (forkId == 0) {
    // Child Process
    char address[30];
    read(fldes[0], address, sizeof(address));
    close(fldes[0]);
    FILE *fp = fopen(address, "r");
    char message[1024];
    fgets(message, sizeof(message), fp);
    write(fldes2[1], message, sizeof(message));
  } else {
    // Parent Process
    write(fldes[1], FILENAME, sizeof(FILENAME));
    char message[1024];
    read(fldes2[0], message, sizeof(message));
    close(fldes[1]);
    printf("%s\n", message);
  }
  return 0;
}
