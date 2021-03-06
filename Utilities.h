/* 
===============================================================================
SOURCE FILE:    Utilities.h 
                    Header file for the shared functions of the Client and
                    Server programs.

PROGRAM:        Client / Server

FUNCTIONS:      int ReadMessage(int queue, Mesg* msg, long msg_type)
                int SendMessage(int queue, Mesg* msg)
                int SendFinalMessage(int queue, Mesg* msg)
                int OpenQueue(void)
                FILE* OpenFile(const char* fileName)
                void sig_handler(int sig)


DATE:           January 30, 2016

REVISIONS:      January 31, 2016        (Tyler Trepanier-Bracken)
                    Splitting the old "ClientServer" functionality into
                    the Client files and the Server files. In addition, 
                    worked on Prompt-User Input for bug fixing and formatting
                    the desired message.
                
                Febuary 2, 2016         (Tyler Trepanier-Bracken)
                    Both Client and Server files have been split from each
                    other and any shared functionality has been included
                    inside of the Utilities files. NOTE: Both Server and
                    Client has their own definitions of the sig_handler
                    with their own implementations.

DESIGNGER:      Tyler Trepanier-Bracken

PROGRAMMER:     Tyler Trepanier-Bracken

NOTES:
The Utilities filess do not perform any stand-alone function but instead
provide both the Client and the Server similar functionality to the message
queue. 
===============================================================================
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#include "mesg.h"

#define MSGPERM                 0644    // Message queue permissions
#define BUFF                    256     // Small array of character buffer
#define CLIENT_TO_SERVER        100     // Message type directed to the Server

/* Global variables */
int msgQueue;               // The message queue, used for signal handling
int rc;                     // Error message handler.

struct sigaction sa;        // The new signal handler structure.
struct sigaction oldint;    /* Old signal handler structure which will be 
                                restored. */

/*
===============================================================================
FUNCTION:       Read Message 

DATE:           January 28, 2016

REVISIONS:      January 30, 2016    (Tyler Trepanier-Bracken)
                    No longer hardcoding the values of the msg_type and
                    the message itself.
                Febuary 1, 2016     (Tyler Trepanier-Bracken)
                    Removed debug statements. 

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int ReadMessage(int queue, 
                                Mesg* msg, 
                                long msg_type)

PARAMETERS:     int queue
                    Message queue to which all messages are sent to.
                Mesg* msg
                    Destination message structure which will be filled with
                    the accompanying message from the message queue.
                long msg_type
                    Type of message, used to differiante messages meant for
                    different processes.

RETURNS:        -Returns -1 on failure to read a message.      
                -Returns 0 on received message success.

NOTES:
Reads a message from an existing linux message queue. Uses the IPC_NOWAIT to
allow this function to immediately return -1 if there are no current messages
of a mentioned type in the queue.
===============================================================================
*/
int ReadMessage(int queue, Mesg* msg, long msg_type);

/*
===============================================================================
FUNCTION:       Send Message

DATE:           January 28, 2016

REVISIONS:      January 30, 2016    (Tyler Trepanier-Bracken)
                    No longer hardcoding the values of the msg_type and
                    the message itself.
                Febuary 1, 2016     (Tyler Trepanier-Bracken)
                    Inserted the message length calculation inside and 
                    removed all debug statements.

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int SendMessage(int queue, Mesg* msg)

PARAMETERS:     Mesg* msg
                    Source message structure which will place its message contents
                    onto the message queue.
                long msg_type
                    Type of message, used to differiante messages meant for
                    different processes.

RETURNS:        -Returns -1 on failure to send a message.      
                -Returns 0 on received message success.

NOTES:
Sends a message from an existing linux message queue. Uses no flags to allow 
this function to wait on the message queue to free messages to be send if
there is an excess of messages already inside of the message queue.
===============================================================================
*/
int SendMessage(int queue, Mesg* msg);

/*
===============================================================================
FUNCTION:       Send Final Message 

DATE:           Feb 1, 2016

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int SendFinalMessage(int queue, Mesg* msg)

PARAMETERS:     Mesg* msg
                    Source message structure which will place its message contents
                    onto the message queue.
                long msg_type
                    Type of message, used to differiante messages meant for
                    different processes.

RETURNS:        -Returns -1 on failure to send a message.      
                -Returns 0 on received message success.

NOTES:
Sends a message from an existing linux message queue. Makes use of the 
pre-existing SendMessage function to send an empty message to a client to 
CONFIRM a completed message.
===============================================================================
*/
int SendFinalMessage(int queue, Mesg* msg);

/*
===============================================================================
FUNCTION:       Remove Queue 

DATE:           January 28, 2016

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int RemoveQueue(int queue)

PARAMETERS:     int queue
                    Message queue to be removed from the linux message.

RETURNS:        -Returns -1 if there is a failure to remove the message queue.
                Usually occurs if the message queue has been previously
                removed.          
                -Returns 0 on successful removal of the message queue.

NOTES:
Wrapper function that removes the message queue from the linux machine.
===============================================================================
*/
int RemoveQueue(int queue);

/*
===============================================================================
FUNCTION:       Open Queue 

DATE:           January 28, 2016

REVISIONS:      Febuary 1, 2016 (Tyler Trepanier-Bracken)
                    Removed the previous function OpenNewQueue and instead
                    used only the IPC_CREAT flag for opening an existing queue
                    or creating a new queue.

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int OpenQueue(void)

PARAMETERS:     void

RETURNS:        -Returns -1 on failure to open or create a message queue.
                -Return 0 on successfully opening or creating a message queue.

NOTES:
Creates or opens a message queue which will allow interprocess communication
between the server and clients.
===============================================================================
*/
int OpenQueue(void);

/*
===============================================================================
FUNCTION:       sig_handler 

DATE:           January 9, 2016

REVISIONS:      January 30th, 2016      (Tyler Trepanier-Bracken)
                    Repurposed from Aman's signal lab example.

DESIGNER:       Aman Abdulla

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void sig_handler(int sig)

PARAMETERS:     int sig
                    The sent signal is caught here.

RETURNS:        void

NOTES:
Each the Client and the Server both implement their own version of this
function but the general purpose is the same. They both catch any available
signals and terminate the program.

The Server catches the SIGINT and sets the quit flag. This quit flag stops all
reading, sends whatever is in its buffer to the Clients and sends a final
message to its Client before terminating itself.

The Client catches this SIGINT and simply flushes all output before restored
normal signal action and exiting.
===============================================================================
*/
void sig_handler(int sig);

/*
===============================================================================
FUNCTION:       Open File 

DATE:           January 28, 2016

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      FILE* OpenFile(const char* fileName)

PARAMETERS:     const char* fileName

RETURNS:        -Returns the null pointer if the file could not be opened
                -Returns the file pointer if the file was opened successfully

NOTES:
Simple wrapper function that attempts to open a file for reading. 
===============================================================================
*/
FILE* OpenFile(const char* fileName);