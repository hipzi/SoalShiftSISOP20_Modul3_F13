#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 80 

int n;
int total_client;

char pilih[MAX];
char lawan[MAX];
char stop[MAX]; 
char username[MAX]; 
char password[MAX]; 
char cek_username[MAX]; 
char cek_password[MAX];
char auth[MAX];
char play_game[MAX]; 
char s_total_client[MAX];
char wait[MAX];

void screen1(int sock);

void screen2(int sock){
    printf("1. Find Match\n");
    printf("2. Logout\n");
    printf("Choices : ");

    bzero(pilih, sizeof(pilih));
    bzero(wait, sizeof(wait));  
    bzero(s_total_client, sizeof(s_total_client));

    n = 0; 
    fgets(pilih, MAX, stdin);
    send(sock, pilih , strlen(pilih), 0);

    if (strncmp("logout", pilih, 6) == 0) { 
        screen1(sock);
    }
    if (strncmp("find", pilih, 4) == 0) { 
        read(sock , s_total_client, MAX);
        total_client = atoi(s_total_client);
        
        while(total_client < 2){
            printf("Waiting for player...\n");
        }
        read(sock , play_game, MAX);
        printf("%s\n", play_game);
    }
}

void screen1(int sock){

    printf("1. Login\n");
    printf("2. Register\n");
    printf("Choices : ");

    bzero(pilih, sizeof(pilih)); 
    bzero(username, sizeof(username));
    bzero(password, sizeof(password));
    bzero(cek_username, sizeof(cek_username));
    bzero(cek_password, sizeof(cek_password));

	n = 0; 
    fgets(pilih, MAX, stdin);
    send(sock, pilih , strlen(pilih), 0);
    
    if (strncmp("login", pilih, 5) == 0) { 
            printf("Username : ");
            fgets(cek_username, MAX, stdin);
            send(sock , cek_username , strlen(cek_username)-1, 0);
            printf("Password : ");
            fgets(cek_password, MAX, stdin);
            send(sock , cek_password , strlen(cek_password)-1, 0);

            read(sock , auth, MAX);
            printf("%s\n", auth);

            if (strncmp("Auth Success", auth, 12) == 0){
                screen2(sock);
            }    
    }
    if (strncmp("register", pilih, 8) == 0) { 
        read(sock , stop, MAX);
        if(strncmp("false", stop, 5) == 0){
           printf("Username : ");
           fgets(username, MAX, stdin);           
           printf("Password : "); 
           fgets(password, MAX, stdin);

           if((int)strlen(username) > 1 && (int)strlen(password) > 1){
               send(sock , username , strlen(username), 0);
               send(sock , password , strlen(password), 0);
           } 
           else{
               perror("Register Gagal : Username atau Password harap diisi!");
           }
        }
    }

}

int main(int argc, char const *argv[]) {

    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    screen1(sock);
    screen2(sock);
}