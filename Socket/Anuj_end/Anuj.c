#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 12345
#define MAX_MSG_LEN 1024
#define CHAT_LOG_FILE "chat_Anuj_end.txt"

int server_socket;
int client_socket;
FILE* chat_log;
int terminate_flag = 0; // Flag to indicate if the conversation should be terminated

void print_and_save_time() {
    time_t rawtime;
    struct tm* timeinfo;
    char time_buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    printf("Conversation started at: %s\n", time_buffer);
    fprintf(chat_log, "Conversation started at: %s\n", time_buffer);
    fflush(chat_log);
}

void* receive_messages(void* arg) {
    char message[MAX_MSG_LEN];
    int n;

    while (1) {
        n = read(client_socket, message, sizeof(message));
        if (n <= 0) {
            printf("Connection closed by the client.\n");
            break;
        }
        message[n] = '\0';
        printf("Received: %s", message);

        if (strcmp(message, "-1\n") == 0) {
            printf("Conversation terminated by the client.\n");
            terminate_flag = 1;
            break;
        }

        // Append the received message to the chat log file
        fprintf(chat_log, "Received: %s", message);
        fflush(chat_log);
    }

    pthread_exit(NULL);
}

void* send_messages(void* arg) {
    char message[MAX_MSG_LEN];

    while (1) {
        fgets(message, MAX_MSG_LEN, stdin);
        write(client_socket, message, strlen(message));

        if (strcmp(message, "-1\n") == 0) {
            printf("Conversation terminated by the server.\n");
            terminate_flag = 1;
            break;
        }

        // Append the sent message to the chat log file
        fprintf(chat_log, "Sent: %s", message);
        fflush(chat_log);
    }

    pthread_exit(NULL);
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t tid_send, tid_recv;

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    

    // Prepare the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 1) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    // Open the chat log file for appending
    chat_log = fopen(CHAT_LOG_FILE, "a");
    

    print_and_save_time();

    printf("Waiting for a connection...\n");

    // Accept a connection from the client
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    

    printf("Connected to the client.\n");

    // Create threads for sending and receiving messages
    pthread_create(&tid_send, NULL, send_messages, NULL);
    pthread_create(&tid_recv, NULL, receive_messages, NULL);

    // Wait for both threads to finish
    pthread_join(tid_send, NULL);
    pthread_join(tid_recv, NULL);

    // Close sockets and the chat log file
    fclose(chat_log);
    close(client_socket);
    close(server_socket);

    return 0;
}

