#include "message_temp.h"
using namespace std;



int open_queue(key_t i)
{
	int msgid;
	if((msgid=msgget(i,IPC_CREAT | 0666))==-1)
	{
		cout <<"Queue failed or it already exists "<< endl;
	}
	return msgid;
}
int send_msg(int msgid,struct mymsgbuf* mbuf)
{
	int length,result;
	length=sizeof(mymsgbuf)-sizeof(long)+1;
	result=msgsnd(msgid,mbuf,length,0);
	if(result==-1)
	{
		cout << "Message sending Failed\n";
	}
	return result;

}
int rec_msg(int msgid,struct mymsgbuf* mbuf,long type)
{
	int length,result;
	length=sizeof(mymsgbuf)-sizeof(long)+1;
	result=msgrcv(msgid,mbuf,length,type,0);
	if(result==-1)
	{	cout << "Message Not recieved"<< endl;}
	
	return result;
}
