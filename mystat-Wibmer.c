// Gerardo Wibmer U2890-7597
#include "Directory.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Purpose: Print information of a given file or directory
// Inputs: file or directory
// Assumptions: a directory is input
// Post condition: All the file infromation is printed
int main(int argc, char *argv[]) {
  // Declaring variables
  int count = 0;
  char name[100];
  struct stat dirInfo;
  // getting the amount of parameters
  while (argv[++count] != NULL)
    ;
  // Defining the name of the directory depending on the command line
  if (count == 1) {
    stat(".", &dirInfo);
    strcpy(name, ".");
  } else if (count == 2) {
    stat(argv[1], &dirInfo);
    strcpy(name, argv[1]);
  } else {
    printf("Invalid amounts of arguments");
    return 1;
  }
  // Printing all the needed information from the file.
  printf("\nFile infortmation of %s\n", name);
  printf("File Size: %ld Bytes \n", dirInfo.st_size);
  printf("Number of Blocks Allocated: %ld  \n", dirInfo.st_blocks);
  printf("Number of Links: %ld  \n", dirInfo.st_nlink);
  printf("File Permissions:  ");
  // all of this if's are made with the purpose of gettingthe permission of
  // the files.
  if (S_ISDIR(dirInfo.st_mode)) {
    printf("d");
  } else {
    printf("-");
  }
  if (dirInfo.st_mode & S_IRUSR) {
    printf("r");
  } else {
    printf("-");
  }
  if (dirInfo.st_mode & S_IWUSR) {
    printf("w");
  } else {
    printf("-");
  }
  if (dirInfo.st_mode & S_IXUSR) {
    printf("x");
  } else {
    printf("-");
  }
  if (dirInfo.st_mode & S_IRGRP) {
    printf("r");
  } else {
    printf("-");
  }
  if (dirInfo.st_mode & S_IWGRP) {
    printf("w");
  } else {
    printf("-");
  }
  if (dirInfo.st_mode & S_IXGRP) {
    printf("x");
  } else {
    printf("-");
  }
  if (dirInfo.st_mode & S_IROTH) {
    printf("r");
  } else {
    printf("-");
  }
  if (dirInfo.st_mode & S_IWOTH) {
    printf("w");
  } else {
    printf("-");
  }
  if (dirInfo.st_mode & S_IXOTH) {
    printf("x");

  } else {
    printf("-");
  }
  printf("\nFile Inode: %ld  \n", dirInfo.st_ino);
}