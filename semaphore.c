#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>
#define buf 1024
sem_t sem;
char buffer[buf];

void *read_t (void *arg){
  while(strncmp("stop",buffer,4)!=0)
  {
printf("Enter text: ");
fgets(buffer,buf,stdin);
sem_post(&sem);
sleep(1);
  }
pthread_exit("read thread exit succesful");
}

void *convert_t (){
  int i;
  sem_wait(&sem);
while (strncmp("stop",buffer,4)!=0){
printf("Converted text: ");
for(i=0;i<strlen(buffer);i++)
  printf("%c",toupper(buffer[i]));
  sem_wait(&sem);
}
pthread_exit("convert thread exit successful");
}

int main(){
int result;
pthread_t rt,ct;
void *thread_result;
sem_init(&sem,0,0);
printf("Enter text, the program will convert it into upper case, \n To stop enter 'stop' \n");
pthread_create(&rt,NULL,read_t,NULL);
pthread_create(&ct,NULL,convert_t,NULL);

pthread_join(rt,&thread_result);
printf("read thread joined, %s\n", (char *)thread_result);
pthread_join(ct,&thread_result);
printf("convert thread joined, %s\n", (char *)thread_result);
sem_destroy(&sem);
exit(0);
}
