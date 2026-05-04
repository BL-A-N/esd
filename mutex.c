#include <stdio.h>
#include <pthread.h>
#define max 10
pthread_mutex_t mutex;

int i=0;
void *up(void *arg){
for (i=0;i<max;++i){
pthread_mutex_lock(&mutex);
counter++;
printf("upcount: %d\n",counter);
pthread_mutex_unlock(&mutex);
}
pthread_exit(NULL);
}

void *down(void *arg){
for(i=0; i<max;++i){
pthread_mutex_lock(&mutex);
counter--;
printf("downcount: %d\n",counter);
pthread_mutex_unlock(&mutex);
}
pthread_exit(NULL);
}

int main(){
pthread_t tup,tdown;
pthread_mutex_init(&mutex,NULL);
pthread_create(&tup,NULL,up,NULL);
pthread_create(&tdown,NULL,down,NULL);

pthread_join(tup,NULL);
pthread_join(tdown,NULL);

pthread_mutex_destroy(&mutex);
return 0;
}
