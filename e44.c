#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(){
  pid_t p = fork();
  if(p==0) for(int i=0;i<50000000; i++) printf("%d\n",i);
  else while(1);
  
  return(0);
}
