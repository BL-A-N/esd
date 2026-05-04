#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void my_handler(int signal){
printf("Problem encountered %d n", signal);
}

int main(){
(void) signal (SIGINT.my_handler);
while(1){
printf("Hello \n");
sleep(2);
}
}
