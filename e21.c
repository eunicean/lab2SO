#include <stdio.h>
#include <time.h>

int main(){
  clock_t v1;
  clock_t v2;
  double total;
  
  v1 = clock();
  for(int i=0;i<1000000;i++){}
  for(int j=0;j<1000000;j++){}
  for(int k=0;k<1000000;k++){}
  v2 = clock();
  
  total = (double)v2 - (double)v1;
  
  printf("Duracion %f\n", total);
  
  return(0);
}
