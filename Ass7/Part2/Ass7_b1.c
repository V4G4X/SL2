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
  int fd = open("pipe", O_WRONLY);
	printf("Enter a set of sentences.\n");
	fgets(string, 32767, stdin);
	write(fd, string, strlen(string));
	close(fd);
	fd = open("pipe",O_RDONLY);
	char *chars=(char*)calloc(32767,sizeof(char));
	char *words=(char*)calloc(32767,sizeof(char));
	char *lines=(char*)calloc(32767,sizeof(char));
	read(fd,(char*)chars,32767);
	read(fd,(char*)words,32767);
	read(fd,(char*)lines,32767);
	printf("\n%s",chars);
	printf("%s",words);
	printf("%s",lines);
	close(fd);
	while (1) {}
	return 0;
}
