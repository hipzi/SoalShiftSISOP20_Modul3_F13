#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1000 

char pilih[MAX]; 
char stop[MAX]; 
char username[MAX]; 
char password[MAX]; 
char cek_username[MAX]; 
char cek_password[MAX];
char line[MAX][MAX];
char auth[MAX];
char wait[MAX];
char play_game[MAX]; 
char s_total_client[MAX];
char address_client[MAX]; 

int valread;
int total_client;

void play(int sock){
    sprintf(play_game, "%s\n", "Play Game !");
    send(sock , play_game , strlen(play_game), 0);
}

void file(int sock) 
{ 
    int i, total;
    FILE *fp;
    for (;;) { 
        bzero(pilih, sizeof(pilih)); 
        bzero(username, sizeof(username));
        bzero(password, sizeof(password));
        bzero(cek_username, sizeof(cek_username));
        bzero(cek_password, sizeof(cek_password));
        bzero(s_total_client, sizeof(s_total_client));

        read(sock , pilih, MAX);
        if(strncmp("find", pilih, 4) == 0){
            sprintf(s_total_client, "%d\n", total_client);
            send(sock , s_total_client , strlen(s_total_client), 0);

            if (total_client > 1){
                play(sock);
                break;
            }
                
        }
        if(strncmp("login", pilih, 5) == 0){

            read(sock, cek_username, MAX);
            read(sock, cek_password, MAX);

            fp = fopen("akun.txt", "r");
            while(fgets(line[i], sizeof(line[i]), fp)) 
            {
                line[i][strlen(line[i]) - 1] = '\0';
                i++;
            }
            total = i;
            for(i = 0; i < total; i++)
            {
                if(i%2==0 && strcmp(line[i], cek_username) == 0){
                    if(strcmp(line[i+1], cek_password) == 0){
                        sprintf(auth, "%s\n", "Auth Success");
                        break;
                    }
                } 
                else{
                    sprintf(auth, "%s\n", "Auth Failed");
                }
            }
            send(sock, auth, strlen(auth), 0);
            fclose(fp);
        }
        if(strncmp("register", pilih, 8) == 0){

            sprintf(stop, "%s\n", "false");
            send(sock , stop , strlen(stop), 0);

            read(sock , username, MAX);
            read(sock , password, MAX);

            fp = fopen("akun.txt", "a");
            fputs(username, fp);
            fputs(password, fp);
            fclose(fp);

            fp = fopen("akun.txt", "r");
            while(fgets(line[i], sizeof(line[i]), fp)) 
            {
                line[i][strlen(line[i]) - 1] = '\0';
                i++;
            }
            total = i;
            for(i = 0; i < total; i++)
            {
                    printf("%s\n", line[i]);
            }

            fclose(fp);
            sprintf(stop, "%s\n", "true");
            send(sock , stop , strlen(stop), 0);
            break;
        }
    }
}
int main(int argc, char const *argv[]) {

    int max_clients = 2;
    int client_socket[3];
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int count = 0;
    int addrlen = sizeof(address);
    pid_t child;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
  
    while (1)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        total_client++;
        // printf("Connection accepted from %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        // address_client[total_client]= address.sin_port;

        if((child = fork()) == 0){
                file(new_socket); 
                play(new_socket);
		}
    }
}