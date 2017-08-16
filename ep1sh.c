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

int main ()
{
  input *inp;
  inp = malloc (sizeof (input));
  char *in; 
  in = readline("\n[./]$ ");
  mysplit(in, inp);
  int ret = fork();
	if(ret==0)
    {
       //child process
       execve(inp->text[0], inp->text, NULL);
       printf("\nEXECV Failed from child\n");
    }
    else if(ret>0)
    {
       //parent process
       printf("\nOi2\n");
       //execve("./faz2");
       printf("\nEXECV Failed from parent\n");
    }
    else
    {
       //you will come here only if fork() fails.
       printf("forkFailed\n");
    }
    return 0;
}
