// Gerardo Wibmer U2890-7597
#include "Directory.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>


// Purpose: Print the couple lines of a ttext file in a efficient way
// Inputs: text file and n (number of lines)
// Assumptions: a directory is input
// Post condition: All the file infromation is printed
int main(int argc, char *argv[]) {
  //Declaring variables
   int counter = 0,n=0,f;
   char name[100];
   // getting the amount of parameters
  while (argv[++counter] != NULL)
    ;
  //if there is no number of lines specified return only the last one
  if(counter==2){
    strcpy(name, argv[1]);
    f = open(argv[1], O_RDONLY);
    n=1;
  }
  else if(counter==3){
    strcpy(name, argv[2]);
    f = open(argv[2], O_RDONLY);
    n = atoi(argv[1]);
    }
  //printf("%d",n);
  char ch;
  int count=0,r;
  //Seek to the end
  int pos = lseek(f, -2, SEEK_END);
  //Go until the needed position
  while (pos != -1) {
    //printf("%d",pos);
    r = read(f, &ch, 1);
    pos--;
    pos = lseek(f, pos, SEEK_SET);
    //check for next line char
    if (ch == '\n') {
      count++;
      //if we reach the amount of lines needed break
      if (count == n) {
        break;
      }
	
    }
  }
  printf("These are the last %d lines of %s:", n ,argv[2]);
  int i = read(f, &ch, 1);
  //count = 0;
  //Prin the last couple lines of the file
  while (i != 0) {
    i = read(f, &ch, 1);
    printf("%c", ch);
  }
  printf("\n");
  return 0;
  //close file
  close(f);
}