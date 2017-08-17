/*	EP1 - MAC0422 
	Shell + Gerenciados de processos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct {
  char **text;
  int qnt;
} input;


void mysplit(char *in, input *inp) {
  int i, n = 0;
  for (i = 0; i<strlen(in) ; i++) {
    if(in[i] == 32)  {
      n++; //32 == " "
    }
  }
  inp->qnt = n+1;
  inp->text = malloc (n+1 * sizeof(char *));
  inp->text[0] = malloc (50 * sizeof(char));
  inp->text[0] = strtok(in, " ");
  for(i = 1; i < n+1; i++) {
    inp->text[i] = malloc (50 * sizeof(char));
    inp->text[i] = strtok(NULL, " ");
  }
  return;
}

void calls (input *inp) {
  if (strcmp(inp->text[0],"/bin/ping") == 0 || strcmp(inp->text[0],"/usr/bin/cal") == 0 || strcmp(inp->text[0],"./ep1") == 0) {
    execve(inp->text[0], inp->text, NULL);
  }
  else {
    printf("Command not found");
  } 
}

int main ()
{
  input *inp;
  inp = malloc (sizeof (input));
  char *in; 
  int ret;
  while(1) {
    in = readline("\n[./]$ ");
    mysplit(in, inp);
    ret = fork();
    if(ret == 0)
    {
      //child process
      calls(inp);
      //system(strcat("kill -9",ret));
    }
    else
    {
       //you will come here only if fork() fails.
       printf("forkFailed\n");
    }
  }
  return 0;
}
