/*	EP1 - MAC0422 
	Shell + Gerenciados de processos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

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
  inp->qnt = n+2;
  inp->text = malloc ((n+2) * sizeof(char *));
  inp->text[0] = strtok(in, " ");
  for(i = 1; i < n+1; i++) {
    inp->text[i] = strtok(NULL, " ");
  }
  inp->text[n+1] = 0; 
  return;
}

void calls (input inp) {
  int i;
  if (strcmp(inp.text[0],"/bin/ping") == 0 || strcmp(inp.text[0],"/usr/bin/cal") == 0 || strcmp(inp.text[0],"./ep1") == 0) {
    printf("%d",execv(inp.text[0], inp.text));
  }
  else {
    printf("Command not found");
  } 
}

int main ()
{
  input inp;
  char *in; 
  int ret, i;
  while(1) {
    in = malloc (sizeof (char *));
    in = readline("\n[./]$ ");
    mysplit(in, &inp);
    ret = fork();
    if(ret == 0)
    {
      //child process
      calls(inp);
    }
    else if (ret == -1) {
      printf("forkFailed\n");
    }
    else
    {
       waitpid(ret, NULL, 0);
    }
    free(inp.text);
    free(in);
  }
  return 0;
}
