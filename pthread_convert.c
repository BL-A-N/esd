#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#define buf 1024
char buffer[buf];

void *read (void *arg){
  while(strncmp("stop",buffer,4)!=0)
  {
printf("Enter text: ");
fgets(buffer,buf,stdin);
sleep(1);
  }
pthread_exit("read thread exit succesful");
}

void *convert (){
  int i;
while (strncmp("stop",buffer,4)!=0){
sleep(1);
printf("Converted text: ");
for(i=0,i<strlen(buffer),i++)
  printf("%c",toupper(buffer[i]));
}
pthread_exit("convert thread exit successful");
}

int main(){
int result;
pthread_t rt,ct;
void *thread_result;
printf("Enter text, the program will convert it into upper case, \n To stop enter 'stop' \n");
pthread_create(&rt,NULL,read,NULL);
pthread_create(&ct,NULL,convert,NULL);

pthread_join(rt,&thread_result);
printf("read thread joined, %s\n", (char)thread_result);
pthread_join(ct,&thread_result);
printf("convert thread joined, %s\n", (char)thread_result);
return (0);
}
