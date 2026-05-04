#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define max 512
struct msg{
long int msg_type;
char some_text[max];};

int main(){
int running=1;
int msgid;
struct msg some_data;
char buffer[50];
msgid=msgget((key_t)12345,0666|IPC_CREAT);
if (msgid==-1){
printf("Error in creating queue\n");
exit(0);}

while(running){
printf("Enter some text: \n");
fgets(buffer,50,stdin);
some_data.mgs_type=1;
strcpy(some_data.some_text,buffer);
if(msgsnd(msgid,(void*)&some_data,max,0)==-1){
printf("msg not sent\n");
}
if(strncmp(buffer,"end",3)==0){
running=0;
}
}
}
