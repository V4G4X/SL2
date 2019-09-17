#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct count 
{
  int chararcters;  // incremented when character not ' ' nor '.'
  int words;        // incremented when character is ' ' and when character is '.'
  int lines;        // incremented when character is '.'
} count;

  int main(int argc, char const *argv[]) {
  	printf("This is a Process no. 2\n");
  	char string[32767];
  	int fd = open("pipe", O_RDONLY);
  	char message[32767];
  	read(fd, string, 32767);
  	printf("Now Recieved String\n");
  //   printf("%s\n", string);
	  int i = 0;
	  count counter;
	  for (i = 0; i < strlen(string); i++) {
	    if (string[i] == ' ' || string[i] == '.') {
	      counter.words++;
	      counter.chararcters--;
	    }
	    if (string[i] == '.') {
	      counter.chararcters--;
	      counter.lines++;
	    }
	    counter.chararcters++;
	  }
	  printf("Now counted String\n");
	  FILE *file = fopen("file.txt", "w");
	  if (file == NULL) {
	    printf("Error Opening File!");
	    exit(1);
	  }
	  fprintf(file, "Character Count: %d\nWord Count: %d\nLine Count: %d\n", counter.chararcters, counter.words, counter.lines);
	  printf("Now Wrote to file\n");
	  fclose(file);
	  close(fd);
	  file = fopen("file.txt", "r");
	  fd =  open("pipe",O_WRONLY);
		while(file){
			fgets(message,32767,file);
			write(fd,message,32767);
	  }
  	  close(fd);
  	  fclose(file);
	  while(1){sleep(1);}
	  return 0;
}
