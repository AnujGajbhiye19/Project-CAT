#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <pthread.h>

struct msgbuf {
    long type;
    char data[100];
} msend, mrecv;

int end = 0; 
key_t key;
int msqid;

void* sender(void* arg) {
    msend.type = 111;

    while (1) {
        fgets(msend.data, sizeof(msend.data), stdin);

        msgsnd(msqid, &msend, sizeof(msend.data), 0);
        printf("You: %s",msend.data);

        if ((strcmp(msend.data, "-1\n") == 0) || (end==1)) {
            end = 1;
            break;
        }
    }

    return NULL;
}

void* receiver(void* arg) {
    mrecv.type = 11;

    while (1) {
        msgrcv(msqid, &mrecv, sizeof(mrecv.data), 11, 0);

        if ((strcmp(mrecv.data, "-1\n") == 0) || (end==1)) {
            end = 1;
            break;
        }

        printf("Anuj: %s", mrecv.data);
    }

    return NULL;
}

void print_date_time() {

    time_t curTime;
    
    struct tm* localTime;

    curTime = time(NULL);

    localTime = localtime(&curTime);

    printf("\n\n%s", asctime(localTime));
    
}

int main() {
    pthread_t thd1, thd2;
    FILE* chat;
    char ch;

    key = ftok("chat", '0');
    msqid = msgget(key, 0666 | IPC_CREAT);
    printf("Message Queue created/accessed with id %d\n\n", msqid);
    
    chat = fopen("conversation.txt", "r");
    printf("Getting Your previous Converison...\n\n");
    sleep(1);
    while ((ch = fgetc(chat)) != EOF) {
        printf("%c",ch);
    }
    fclose(chat);
    
    printf("Now you can chat with your friend!!!\n\n");
    printf("To end the conversation one of you should say bye and both  of you should send -1 to each other\n\n");
    
    print_date_time();

    pthread_create(&thd1, NULL, sender, NULL);
    pthread_create(&thd2, NULL, receiver, NULL);

    pthread_join(thd1, NULL);
    //pthread_join(thd2, NULL);

    printf("This conversation Ended Here!!!\n");

    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}

