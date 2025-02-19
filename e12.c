#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
  printf("pid: %d\n", getpid());
  
  for(int i=0;i<4;i++){
    fork();
    printf("hehe\n");
    
  }
  
  return (0);
}
