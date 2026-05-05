#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(void){
pid_t pid;
char *message;
int no,no1=1;
int i,l;
printf("calling fork \n");
pid= fork();

switch(pid){
case -1:
printf("fork failed \n");
exit(1);
case 0:
i=1;
message="child process";
no=gepid();
no1=getppid();
break;
default:
i=1;
message="parent process";
no=getpid();
no1=getppid();
break;
}

if(pid!=0){
printf("Hello from parent\n");
wait(NULL);
printf("Child has terminated\n");
}

for(l=i;l>0;l--){
puts(message);
printf("My ID is %d \n",no);
printf("My parent ID is %d \n",no1);
}
return 0;
}

