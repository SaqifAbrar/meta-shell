#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// gcc -std=c99 -o -Wall myShell myShell.c
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --read-var-info=yes  -v ./myShell
// ./myShell

void freeString(char *string) {
  free(string);
}

char* append(char *string1, char *string2){
  char *path = (char *) malloc(sizeof(char) * strlen(string1) + sizeof(char) * strlen(string2) + 1); // \0 character
  strcpy(path, string1);
  strcat(path, string2);
  return path;
}

int readInput(){
  return 0;
}

int prompt() {

}

int main(int argc, char **argv) {
  char *test = append("/user/bin/", "ls");
  printf("%s\n", test);
  freeString(test);
  return 0;
}