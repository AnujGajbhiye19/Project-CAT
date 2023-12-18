# Task: Chat Application using 2 Process (Using Message Queue IPC).

INDEX:
	1) chatApplication Overview
	2) Technologies Used
	3) Message Queues (IPC)
	4) File handeling
	5) Thread Management
	6) Program Overview


1) chatApplication Overview
	: This application uses 2 saperate process for its complete working.
	It has 3 main Functionalities:
		i) Sending Message
		ii) Recieving Message
		iii) Storing the conversation into a saperate text file with current date and time.
	i) Sending and recieving of messages is done by IPC protocol. Here we have used Message Queues as an IPC.
	ii) To get and print current date and time, we have used time function.
	iii) And Finally, to save the conversation within the chat application we have used File handelling.
	


2) Technologies Used
	: we have used several technologies in chatApplication as follows,
		i) C-Programming - as coding language
		ii) Structures in C - to store type and data of sending and recieving messages
		iii) Multi-Process - 2 saperate processes for chatApplication
		iv) Multi-Threading - to send and recieve parallely
		v) IPC (MessageQ) - As InterProcessCommunication Protocol, for communication between process.
		vi) File Handelling - To save the conversation in saperate file.



3) Message Queues(IPC)
	: Message Queue is a Full Duplex IPC protocol.
	: It is Nothing but Linked List of Messages in Kernel Space based on their Message Types.
	: Each MessageQ is identified by its MessageQ-ID (msqid).
	: In MessageQ, Each message is a stucture which contains 2 entities.(type and data).
	: "type" is a long datatype variable which is going to differ linked list and decides where to send a message.
	: "data" is a string datatype variable which is actual message that is sent over the system.
	: MessageQ uses 2 saperate functions to send and recieve messages respectively. i)msgsnd(); & ii) msgrcv();
	: i) msgsend() has 4 arguments: messageQ-ID, address of message structure, size of buffer, flags.
	: ii) msgrcv() has 5 arguments: messageQ-ID, address of message structure, size of buffer, type of message to recieve from, flags.



4) File Handelling
	: We have used File handellingto store output of the code, ie. chat.
	: In this we are using <stdlib.h> header file for using file handelling functions like fopen(), fclose(), fprintf(), fgets(), fgetc(), etc.
	: To open a file, we have to use a FILE datatype pointer first to store the address of file and access it.
	: we can open a file with different flags having individual functionalities. They are given as follows,
		i) w - creates a new file for writting
		ii) r - opens an existing file for reading
		iii) a - opens an existing file for appending
		iv) w+ - creates an empty file for reading and writting
		v) r+ - opens already existing file for reading and writting
		vi) a+ - opens a file for reading and appending



5) Thread Management
	: A Thread is a parallel context of execution, means it runs/execute parallel to execution of its process (while process runs concurrently).
	: Threads are light weight as compared to process.
	: It uses less memory and takes less time to execute.
	: To create/use thread, we need to use POSIX Library (Portable Operating System Interface).
	: pthread.h is the header files which has predefined functions used for creation, joining, detaching, execute threads.
	: In our program, we have used pthread_create() and pthread_join().
	: pthread_create() has 4 arguments - address of thread_ID, thread Attributes, thread function, arguments to function.
	: pthread_join() has 2 arguments - thread_ID and return value. 



6) Program Overview
	:We are going to see our program overview in terms of which function does exacty what !
	: First we have included libraries that are going to provide predefined functions for IPC, Thread Management, File Handelling, etc.
	: main() is the start of the execution. It first initialize thread variables, file pointer and others.
	: It then creates key for messageQ and then creates a MessageQ with that key having unique msqID and prints msqid.
	: Now it search for previous conversation file of chat and prints it.
	: Now program prints terms and conditions for chat and then invokes print_date_time() which prints current date and time in terminal and conversation file also.
	: Now main() creates 2 threads from functions sender() and reciever() so that user can parallely use both of them.
	: The whole conversation is saved in a saperate "conversation.txt" file.
	: later we join one of the thread which invokes the execution of both threads.
	: conversation will end if one of process sends "-1" to other process which tends to termination of program and Removing MessageQ from the system.  

	
	
	
