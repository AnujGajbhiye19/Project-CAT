# Task: Chat Application using 2 Process (Using Socket Programming).

INDEX:
	1) chatApplication Overview
	2) Technologies Used
	3) Socket Programming
	4) File handeling
	5) Thread Management
	6) Program Overview


1) chatApplication Overview
	: This application uses 2 saperate process for its complete working.
	It has 3 main Functionalities:
		i) Sending Message
		ii) Recieving Message
		iii) Storing the conversation into a saperate text file with current date and time.
	i) Sending and recieving of messages is done over Internet. Here we have used Socket Programming.
	ii) To get and print current date and time, we have used time function.
	iii) And Finally, to save the conversation within the chat application we have used File handelling.
	


2) Technologies Used
	: we have used several technologies in chatApplication as follows,
		i) C-Programming - as coding language
		ii) Structures in C - to store type and data of sending and recieving messages
		iii) Multi-Process - 2 saperate processes for chatApplication
		iv) Multi-Threading - to send and recieve parallely
		v) Socket Programming - Socket Programing Used to send and recieve data over Internet sockets with the help of IPV4/V6 addresses.
		vi) File Handelling - To save the conversation in saperate file.



3) Socket Programming
	: Socket Programming is a Full Duplex protocol.
	: Socket programming is a way to connect two nodes on a network so they can communicate with each other.
	: The processes that use a socket can reside on the same system or different systems on different networks.
	: Sockets are useful for both stand-alone and network applications.
	: Sockets allow you to exchange information between processes on the same machine or across a network, distribute work to the most efficient machine, and they easily allow access to centralized data.
	: Socket application program interfaces (APIs) are the network standard for TCP/IP. A wide range of operating systems support socket APIs.



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
	: We are going to see our program overview in terms of which function does exacty what !
	: First we have included libraries that are going to provide predefined functions for IPC, Thread Management, File Handelling, etc.
	: main() is the start of the execution. It first initialize thread variables, file pointer and others.
	: receive_messages Function: It listens to what the other person (server) says, writes it down in our chat log, and understands when the conversation is over.
	: send_messages Function: It asks us what we want to say, tells the other person (server) our message, writes it in our chat log, and lets the other person know if we decide to stop talking.
	
	
	
	
