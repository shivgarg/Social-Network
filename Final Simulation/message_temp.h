/*
 * message_temp.h
 *
 *  Created on: 16 Nov 2013
 *      Author: cs1120252
 */

#ifndef MESSAGE_TEMP_H_
#define MESSAGE_TEMP_H_

#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/*! \file message_temp.h
\brief A Documented file.
Details.
*/

/** @struct mymsgbuf
 *  @brief This structure stores messgae struct for message queue*/
 /**  @var studnode::mtype 
 *  Member 'mtype' contains message type*/
 /**  @var  studnode::thdid 
 *  Member 'thdid' contains the id of thread whose concerning the thread is*/
 /** 	@var	studnode::waketime
 * 	Member 'waketime' contains the waketime when that thread is to be waken up*/
 
struct mymsgbuf{
	long mtype;
	int thdid;
	int waketime;
};
//! A function taking one arguments and returning an integer value.
/*!
 \param t Used as a key for message queue.
 \return id of the message queue.

*/

int open_queue(key_t t);
//! A function taking two arguments and returning an integer value.
/*!
 \param t queue id to identify the message queue
 \param s struct pointer which has to be sent over queue
 \return 1 if message sending is successful

*/
int send_msg(int t,struct mymsgbuf*  s);
//! A function taking two arguments and returning an integer value.
/*!
 \param t queue id to identify the message queue
 \param s struct pointer in which message is to recieved
 \return integer

*/
int rec_msg(int ,struct mymsgbuf* ,long );

#endif /* MESSAGE_TEMP_H_ */
