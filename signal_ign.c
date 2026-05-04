#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(){

(void) signal (SIGINT,SIG_IGN);
while(1){
printf("%d \n", getpid());
sleep(1);
}
}
