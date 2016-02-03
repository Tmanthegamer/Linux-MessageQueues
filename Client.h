/* 
===============================================================================
SOURCE FILE:    Client.h 
                    Header file 

PROGRAM:        Client Server

FUNCTIONS:      void* OutputFunction(void *message)
				int DisplayMessage(const char* message)
				int PromptUserInput(char* input)
				int ReadInput(void)
				int ReadServerResponse(void)
				int TerminateClient(void)


DATE:           January 9, 2016

REVISIONS:

DESIGNGER:      Tyler Trepanier-Bracken

PROGRAMMER:     Tyler Trepanier-Bracken

NOTES:
Standard Notes go here.
===============================================================================
*/

#include <pthread.h>
#include "Utilities.h"

int done;

/*
===============================================================================
FUNCTION:       Main 

DATE:           January 28, 2016

REVISIONS:      January 30, 2016    (Tyler Trepanier-Bracken)
                    Moved existing code for sending test messages into Server
                    function.
                Febuary 30, 2016     (Tyler Trepanier-Bracken)
                    Create the functionality to split the server and client
                    components via command-line arguments.

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int main(int argc,
                         char **argv)

PARAMETERS:     int argc,
                    Number of command-line arguments. Used to verify the
                    correctness of program calling.
                char **argv
                    Command-line arguments. Only second argument is taken
                    into consideration for this program.
RETURNS:        -Returns 1 on improper program exit.
                -Returns 0 on normal program termination.

NOTES:
Main entry point into the program. Divides program functionality based on the 
command-line arguments into client and server functionality. 

Server will start when the Program is called with the 's' character.

Client will start when the Program is called with the 'c' character.
===============================================================================
*/
int main(int argc,char **argv);

/*
===============================================================================
FUNCTION:       Client

DATE:           January 30, 2016

REVISIONS:      Febuary 1, 2016 (Tyler Trepanier-Bracken)
                    Implemented threads to read from a server.

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int Client(void)

PARAMETERS:     void

RETURNS:        -Returns 1 if the Client was unable to open a message queue.
                -Returns 0 on proper program termination

NOTES:
Separate functionality from the Server side, the purpose of this function 
is to allow user requests for files. First it opens the message queue (if it 
cannot open the message queue, this will exit the application). The request 
will be padded with the PID of the current process and the optional priority. 

Afterwards the server will respond with the contents of the file inside of a
series of messages. If the server cannot open the file, the server will 
respond with an error.

The program will continually asked for user input until user enters "quit" 
or ctrl-c has been hit.
===============================================================================
*/
int Client(void);

/*
===============================================================================
FUNCTION:       Main 

DATE:           January 9, 2016

REVISIONS:      (Date and Description)

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken
                Harvey Dent

INTERFACE:      int main (char *process)

PARAMETERS:     char *process: 
                    the name of the process to be validated. 

RETURNS:        -Returns the PID of process specified if the process
                exists.          
                -Returns 0 if the process was not found in the process table.

NOTES:
Standard Notes go here. 
===============================================================================
*/
void* ReadServerResponse(void *queue);

/*
===============================================================================
FUNCTION:       Main 

DATE:           January 9, 2016

REVISIONS:      (Date and Description)

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken
                Harvey Dent

INTERFACE:      int main (char *process)

PARAMETERS:     char *process: 
                    the name of the process to be validated. 

RETURNS:        -Returns the PID of process specified if the process
                exists.          
                -Returns 0 if the process was not found in the process table.

NOTES:
Standard Notes go here. 
===============================================================================
*/
int PromptUserInput(char* input);

/*
===============================================================================
FUNCTION:       Main 

DATE:           January 9, 2016

REVISIONS:      (Date and Description)

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken
                Harvey Dent

INTERFACE:      int main (char *process)

PARAMETERS:     char *process: 
                    the name of the process to be validated. 

RETURNS:        -Returns the PID of process specified if the process
                exists.          
                -Returns 0 if the process was not found in the process table.

NOTES:
Standard Notes go here. 
===============================================================================
*/
int ReadInput(void);

/*
===============================================================================
FUNCTION:       Main 

DATE:           January 9, 2016

REVISIONS:      (Date and Description)

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken
                Harvey Dent

INTERFACE:      int main (char *process)

PARAMETERS:     char *process: 
                    the name of the process to be validated. 

RETURNS:        -Returns the PID of process specified if the process
                exists.          
                -Returns 0 if the process was not found in the process table.

NOTES:
Standard Notes go here. 
===============================================================================
*/
int CreateReadThread();