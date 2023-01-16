// Gerardo Wibmer U2890-7597
#include "Directory.h"
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

// Purpose: Program that lists files in the given directory.
// Inputs: none, -l flag or a directory
// Assumptions: a directory is input
// Post condition: All the file names will be printed
int main(int argc, char **argv) {

  int count = 0;
  // getting the amount parameters in the command line
  while (argv[++count] != NULL)
    ;
  // Declating the structures
  struct dirent *dir_struct;
  DIR *dir;
  dir = opendir(".");

  // Checking the user input to decide what to do
  if (count > 1 && strcmp(argv[1], "-l") != 0) {
    dir = opendir(argv[1]);
  } else if (count > 2) {

    dir = opendir(argv[2]);
  }
  // reading the directory
  dir_struct = readdir(dir);
  // reading the entire directory
  for (; dir_struct != NULL; dir_struct = readdir(dir)) {
    // if -l print all the infromations about the files inside the directory
    if (count > 1 && strcmp(argv[1], "-l") == 0) {
	
      struct stat dirInfo;
      stat(dir_struct->d_name, &dirInfo);
	if (!strcmp(dir_struct->d_name, ".") || !strcmp(dir_struct->d_name, ".."))
            continue;

      printf("\nFile infortmation of %s\n", dir_struct->d_name);
      printf("File Size:: %ld Bytes \n", dirInfo.st_size);
      printf("Number of Blocks Allocated: %ld  \n", dirInfo.st_blocks);
      printf("Number of Links: %ld  \n", dirInfo.st_nlink);
      printf("The owner ID is: %d \n", dirInfo.st_uid);
      printf("The group ID is: %d \n", dirInfo.st_gid);
      printf("File Permissions: ");
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
    } else {
	if (!strcmp(dir_struct->d_name, ".") || !strcmp(dir_struct->d_name, ".."))
            continue;
      // if not just print the name of the files in the given directory
      printf("%s\n", dir_struct->d_name);
    }
  }
  // close the directory
  closedir(dir);
}