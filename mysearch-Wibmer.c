// Gerardo Wibmer U2890-7597
#include "Directory.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

// Declaring global variables
DIR *dir;
char *name;
char buffer[1024];
struct dirent *dir_struct;
struct stat stat_stuct;
char all_dir[50000];

//recursive function to look into all the files and directories
int recursive(char *name, char buffer) {
  //redeclaring all needed variables
  DIR *dir;
  dir = opendir(name);
  struct stat stat_stuct;
  struct dirent *dir_struct;
  stat(dir_struct->d_name, &stat_stuct);
  //checking if directory was open correctly
  if (!dir) {
    return 1;
  }
  //reading the driectory
  dir_struct = readdir(dir);
  //lopping through the directoryS
  for (; dir_struct != NULL; dir_struct = readdir(dir)) {
    if (strcmp(dir_struct->d_name, "..") != 0 &&
        strcmp(dir_struct->d_name, ".") != 0) {
	if (!strcmp(dir_struct->d_name, ".") || !strcmp(dir_struct->d_name, ".."))
            continue;
      printf("Filename: %s\n", dir_struct->d_name);
      if (dir_struct->d_type == DT_DIR) {
        //creating directory path
        sprintf(all_dir, "%s", name);
        snprintf(all_dir, sizeof(all_dir), "%s", "/");
        snprintf(all_dir, sizeof(all_dir), "%s", dir_struct->d_name);
        printf("Dirname: %s \n", all_dir);
        recursive(all_dir, buffer);
      }
    }
  }
  closedir(dir);
  return 0;
}


// Purpose: Search for all files in a given directory or current directory
// Inputs: directory
// Assumptions: a directory is input
// Post condition: All the file infromation is printed
int main(int argc, char **argv) {
  int count = 0;
    // getting the amount of parameters
  while (argv[++count] != NULL)
    ;
  //checking amount of parametrs passed
  if (count == 1) {
    // getting current directory
    if (getcwd(buffer, 1024) == NULL) {
      printf("Get current working directory failed");
    }
    printf("Current Path %s\n", buffer);
    name = ".";
  } else if (count == 2) {
    // getting current directory
    if (getcwd(buffer, 1024) == NULL) {
      printf("Get current working directory failed");
    }
    //prinitng the current directory
    printf("Current Path %s\n", buffer);
    name = argv[1];
  } else {
    printf("Invalid amount of arguments");
    return 1;
  }
  //open the given directory 
  dir = opendir(name);
  //checking if directory was open correctly
  if (!dir) {
    return 1;
  }
  //reading the directory
  dir_struct = readdir(dir);
  //looping through the directory
  for (; dir_struct != NULL; dir_struct = readdir(dir)) {
    //printing the information requested of the directory
    printf("Filename: %s\n", dir_struct->d_name);
    stat(dir_struct->d_name, &stat_stuct);
    if (dir_struct->d_type == DT_DIR && strcmp(dir_struct->d_name, ".") != 0 &&
        strcmp(dir_struct->d_name, "..") != 0) {
	if (!strcmp(dir_struct->d_name, ".") || !strcmp(dir_struct->d_name, ".."))
            continue;
      //creating directory path
      sprintf(all_dir, "%s", name);
      snprintf(all_dir, sizeof(all_dir), "%s", "/");
      snprintf(all_dir, sizeof(all_dir), "%s", dir_struct->d_name);
      recursive(all_dir, buffer[100]);
    }
  }

  printf("Dirname: %s\n", name);
  printf("Search has finished! \n");
  closedir(dir);
}