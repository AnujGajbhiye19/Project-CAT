#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 12345
#define MAX_MSG_LEN 1024
#define CHAT_LOG_FILE "chat_Friend_end.txt"

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
            printf("Connection closed by the server.\n");
            break;
        }
        message[n] = '\0';
        printf("Anuj: %s", message);

        if (strcmp(message, "-1\n") == 0) {
            printf("Conversation terminated by the server.\n");
            terminate_flag = 1;
            break;
        }

        // Append the received message to the chat log file
        fprintf(chat_log, "Anuj: %s", message);
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
            printf("Conversation terminated by the client.\n");
            terminate_flag = 1;
            break;
        }

        // Append the sent message to the chat log file
        fprintf(chat_log, "You: %s", message);
        fflush(chat_log);
    }

    pthread_exit(NULL);
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t tid_send, tid_recv;

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    // Open the chat log file for appending
    chat_log = fopen(CHAT_LOG_FILE, "a");
    

    print_and_save_time();

    printf("Connected to the server.\n");

    // Create threads for sending and receiving messages
    pthread_create(&tid_send, NULL, send_messages, NULL);
    pthread_create(&tid_recv, NULL, receive_messages, NULL);

    // Wait for both threads to finish
    pthread_join(tid_send, NULL);
    pthread_join(tid_recv, NULL);

    // Close the socket and the chat log file
    fclose(chat_log);
    close(client_socket);

    return 0;
}

