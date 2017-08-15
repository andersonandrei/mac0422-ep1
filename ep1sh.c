/*	EP1 - MAC0422 
	Shell + Gerenciados de processos
*/

#include <stdio.h>
#include <unistd.h>

int main ()
{
	char *args[2];
    int ret = fork();
    char *const parmList[] = {"/bin/ping", "-c", "10", "www.google.com.br", NULL};
    if(ret==0)
    {
       //child process
       printf("Oi1\n");
       //execve("./faz1"); // GIVE ADDRESS OF 2nd element as starting point to skip source.txt
       execve(parmList[0], parmList, NULL);
       printf("EXECV Failed from child\n");
    }
    else if(ret>0)
    {
       //parent process
       printf("Oi2\n");
       //execve("./faz2");
       printf("EXECV Failed from parent\n");
    }
    else
    {
       //you will come here only if fork() fails.
       printf("forkFailed\n");
    }
    return 0;
}