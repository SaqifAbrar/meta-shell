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

char* readInput(){
  char *input = (char *) malloc(sizeof(char) * 10);
  printf("> ");
  //scanf("%s", input);
  fgets(input, 100, stdin);
  input = (char *)realloc(input, sizeof(char) * strlen(input) + 1);
  //printf("size of input, %s, is: %lu\n", input, strlen(input));
  return input;
}

void commands(char *input) {
  if(strcmp(input, "ls") == 0){
    //printf("%s\n", test);
    printf("/usr/bin/ls -> test\n");
  } else if(strcmp(input, "exit") == 0) {
    //running = 0;
    // exits loop to exit
  } else {
    printf("--> %s: command not found\n", input);
  }
}

void printCommands(char **commands) {
  int x = 0;
  while(commands[x] != NULL){
    printf("arg[%d]: %s\n", x, commands[x]);
    x++;
  }
}

char** interpretCommands(char *commands) {
  int size = 0;

  for(int x=0; x<strlen(commands); x++) {
    if(commands[x] == '|' || commands[x] == ' ' || commands[x] == '\n'){
      size++;
    }
  }
  
  if(size == 0) {
    return NULL;
  }

  char** allCommands = (char**) malloc(sizeof(char*) * size);
  int argNum = 0, startIndex = 0, endIndex = 0;
  //printf("length of %s is: %lu\n", commands, strlen(commands));
  for (unsigned long int y = 0; y < strlen(commands); y++)
  {
    //printf("%lu - ", y);
    if (commands[y] == '|' || commands[y] == ' ' || commands[y] == '\n')
    {
      endIndex = y - 1;

      //printf("\n<- %lu\n", y);

      if(commands[y] == '|'){
        //printf("arg %d ", argNum);
        allCommands[argNum] = (char *)malloc(sizeof(char) * 2);
        allCommands[argNum] = "|\0";
        //printf("----> %s\n", allCommands[argNum]);
      } else {
        //printf("arg %d ", argNum);
        allCommands[argNum] = (char *) malloc(sizeof(char) * (endIndex - startIndex + 1));
        memcpy(allCommands[argNum], &commands[startIndex], endIndex - startIndex + 1);
        //printf("----> %s\n", allCommands[argNum]);
      }

      //printf("start: %d - end: %d >> current character at index %lu: %c< \n", startIndex, endIndex, y, commands[y]);
      
      while(commands[y+1] == ' '){
        //printf("space found\n");
        y++;
      }

      //printf("-> %lu\n", y);

      startIndex = y + 1;
      //printf("new starting index: %d\n ------------- \n", startIndex);
      argNum++;
    }
  }

  return allCommands;
  //return NULL;
}

void prompt() {
  int running = 1;
  //int pipes = 0;

  while(running) {
    char *input = readInput();
    //printf("%s\n", input);
    char **commands = interpretCommands(input);
    printCommands(commands);
    //char *test = append("/user/bin/", "ls");
    //commands(input);
    freeString(input);
    //freeString(test);
  }

  exit(1);
}

int main(int argc, char **argv) {
  prompt();
  return 0;
}


/*  
int size = 0;

for(int x=0; x<strlen(commands); x++) {
  if(commands[x] == 'l' || commands[x] == ' '){
    size++;
  }
}

char** allCommands = (char**) malloc(sizeof(char*) * size);
int argNum = 1, startIndex = 0, endIndex = 0;

for(int y=0; y<strlen(commands); y++){
  if(commands[y] == '|' || commands[y] == ' ' || commands[y] == '\n'){
    endIndex--;
    allCommands[argNum] = (char *) malloc(sizeof(char) * (endIndex - startIndex));
    startIndex = y + 1;
    argNum++;
  }
}

return allCommands;*/
