/* 
===============================================================================
SOURCE FILE:    Client.h 
                    Header file 

PROGRAM:        Client

FUNCTIONS:      int main(void)
                int Client(void)
        		int PromptUserInput(char* input)
        		int CreateReadThread(void)
        		void* ReadServerResponse(void *queue)
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

                Febuary 3, 2016         (Tyler Trepanier-Bracken)
                    Removing Prompt User functionality and replacing it
                    with  

DESIGNGER:      Tyler Trepanier-Bracken

PROGRAMMER:     Tyler Trepanier-Bracken

NOTES:
Client is a stand-alone program which allows the user to ask for files to read
and displayed onto the stdout of this process. This client may have multiple
instances at once and they work in unison with only one Server. 

Each individual Client requests the user to enter in the filename and, if
they so please, the priority and another client's process id. This request
gets bundled into a message which gets sent to the server where the server
processes this file opening request. Afterwards, the server responds which
either an error message or the contents of the file.

This is the main file that holds all of the unique functionality of the Client
program. There are some shared functionality with the Server that is defined
inside of the Utilities files.
===============================================================================
*/

#include <pthread.h>
#include "Utilities.h"

int done, running = 1;

/*
===============================================================================
FUNCTION:       Main 

DATE:           January 28, 2016

REVISIONS:      January 30, 2016    (Tyler Trepanier-Bracken)
                    Moved existing code for sending test messages into Server
                    function.
                Febuary 1, 2016     (Tyler Trepanier-Bracken)
                    Create the functionality to split the server and client
                    components via command-line arguments.
                Febuary 2, 2016     (Tyler Trepanier-Bracken)
                    Split this function into separate files: Client and 
                    Server.
                Febuary 3, 2016     (Tyler Trepanier-Bracken)
                    Removing user input functionality on all ends and instead
                    parsing command-line arguments.

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int main(void)

PARAMETERS:     int argc 
                    The number of arguments received from command-line.
                char** argv
                    The arguments received from the command-line to be parsed.

RETURNS:        -Returns 1 on improper program exit.
                -Returns 0 on normal program termination.

NOTES:
Main entry point into the program. Divides program functionality based on the 
command-line arguments into client and server functionality. 
===============================================================================
*/
int main(int argc, char** argv);

/*
===============================================================================
FUNCTION:       Client

DATE:           January 30, 2016

REVISIONS:      Febuary 1, 2016 (Tyler Trepanier-Bracken)
                    Implemented threads to read from a server.
                Febuary 3, 2016     (Tyler Trepanier-Bracken)
                    Removing user input functionality on all ends and instead
                    parsing command-line arguments.

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int Client(int argc, char** argv)

PARAMETERS:     int argc 
                    The number of arguments received from command-line.
                char** argv
                    The arguments received from the command-line to be parsed.

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
int Client(int argc, char** argv);

/*
===============================================================================
FUNCTION:       Read Server Response 

DATE:           Febuary 1, 2016

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void* ReadServerResponse(void *queue)

PARAMETERS:     void *queue
                    Pointer to an integer which is the message queue that
                    the server reads on.

RETURNS:        -Returns the PID of process specified if the process
                exists.          
                -Returns 0 if the process was not found in the process table.

NOTES:
This is a thread function that contiuously reads the message queue for any 
messages in the queue that are meant for this Client.
===============================================================================
*/
void* ReadServerResponse(void *queue);

/*
===============================================================================
FUNCTION:       Read Arguments

DATE:           January 31, 2016

REVISIONS:      Febuary 2, 2016 (Tyler Trepanier-Bracken)
                    Implemented help messages and normal termination via 
                    requesting a program quit.

                Febuary 3, 2016 (Tyler Trepanier-Bracken)
                    Repurposed this Prompt User Input (this function) to 
                    parsing command-line arguments.

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int ReadArguments(int argc, char** argv)

PARAMETERS:     char* request
                    The field which will be populated with the user's
                    request and message arguments.
                int argc 
                    The number of arguments received from command-line.
                char** argv
                    The arguments received from the command-line to be parsed.

RETURNS:        -Returns -1 on a improper argument formatting.
                -Returns 0 on succesful user input

NOTES:
This function grabs filenames from the command-line. Whenever there are no
arguments when the program is instiated, this program will display the usage
instructions on how this program operates and terminates.
===============================================================================
*/
int ReadArguments(char* request, int argc, char** argv);

/*
===============================================================================
FUNCTION:       Create Read Thread 

DATE:           January 30, 2016

REVISIONS:      Feb 1, 2016     (Tyler Trepanier-Bracken)
                    Set the parameter to be the message queue which is passed
                    to the Read Server Response function

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      int CreateReadThread(void)

PARAMETERS:     void

RETURNS:        -Returns -1 if unable to create the read thread. 
                -Returns 0 if the read thread creation succeeded.

NOTES:
Creates a thread which has the sole purpose of reading all messages from the
message queue for aimed at this process.
===============================================================================
*/
int CreateReadThread(void);

/*
===============================================================================
FUNCTION:       Client Help

DATE:           Febuary 2, 2016            

DESIGNER:       Tyler Trepanier-Bracken

PROGRAMMER(S):  Tyler Trepanier-Bracken

INTERFACE:      void ClientHelp(void);

PARAMETERS:     void

NOTES:
Displays a help message to standard output that displays how to use this
Client application.
===============================================================================
*/
void ClientHelp(void);
