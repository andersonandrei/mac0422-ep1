/*	EP1 - MAC0422 - Anderson Andrei da Silva
	Shell + Gerenciador de processos */

#include "ep1sh.h"

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

void externalCalls (input inp) {
  int ret;
  ret = fork();
  if(ret == 0) {
    execv(inp.text[0], inp.text);
  }
  else if (ret == -1) {
    printf("forkFailed\n");
  }
  else {
    waitpid(ret, NULL, 0);
  }
}

void myChown (input inp) {
  int uid = getuid();
  struct group *gr;

  gr = getgrnam(inp.text[1]+1);
  chown(inp.text[2], uid, gr->gr_gid);
}

void myDate (input inp) {
  time_t t = time(NULL);
  char dateBuffer[80];
  struct tm *tm = localtime(&t);
  time(&t);
  tm = localtime(&t);

  strftime(dateBuffer,80,"%a %b %d %I:%M:%S %Z %Y", tm);
  printf("%s\n", dateBuffer);
}

void internCalls (input inp) {
  if (strcmp(inp.text[0],"chown") == 0) {
    myChown(inp);
  }
  else if (strcmp(inp.text[0],"date") == 0) {
    myDate(inp);
  }
}

void calls (input inp) {
  if (strcmp(inp.text[0],"/bin/ping") == 0 || strcmp(inp.text[0],"/usr/bin/cal") == 0 || strcmp(inp.text[0],"./ep1") == 0) {
    externalCalls(inp);
  }
  else if ((strcmp(inp.text[0],"chown") == 0) || (strcmp(inp.text[0],"date") == 0)) {
    internCalls(inp);
  }
  else {
    printf("Command not found\n");
  } 
}

int main (){
  using_history();
  input inp;
  char *in;
  char inPrompt[100];
  while(1) {
    sprintf(inPrompt, "[%s] $ ", getcwd (NULL, 1024));
    in = malloc (sizeof (char *));
    in = readline(inPrompt);
    add_history(in);
    mysplit(in, &inp);
    calls(inp);
    free(inp.text);
    free(in);
  }
  clear_history();
  return 0;
}
