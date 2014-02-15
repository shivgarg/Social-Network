

#include "Semaphore.h"
int open_sem( key_t keyval, int numsems )
{
        int     sid;
		sid = semget( keyval, numsems, IPC_CREAT | 0660 );
		if(sid==-1)
		{
			printf("Semaphore creation falied\n");
		}
		
		return(sid);
}    

void getSem(int id)
{
	
	sembuf *getlck=new sembuf;
	getlck->sem_num=0;
	getlck->sem_op=-1;
	getlck->sem_flg=0;
	if(semop ( id, getlck,1)==-1)
	{
		//printf("lock failed\n");
	}
	delete(getlck);
}

void relSem(int id)
{sembuf *relLck=new sembuf;

	relLck->sem_num=0;
	relLck->sem_op=1;
	relLck->sem_flg=0;
	if(semop(id,relLck,1)==-1)
	{
		//printf("release failed\n");
	}
	delete(relLck);
}
