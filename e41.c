#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t p = fork();
  
  if(p==0) printf("pid %d\n", getpid());
  else while(1);
  
  return(0);
}
