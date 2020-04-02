#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int faktorial[10][10];
long double hasil_faktorial[10][10];
int iCount,jCount,kCount;

long double fact(int n){
    if(n==0 || n==1)
    return 1;
    else 
    return n*fact(n-1);
}

void *factorial(void *p){

        for(iCount=0;iCount<4;iCount++)
        {
            for(jCount=0;jCount<5;jCount++)
            {                   
                hasil_faktorial[iCount][jCount] = fact(faktorial[iCount][jCount]);
            }
        }

    pthread_exit(0);
}

int main(){
    key_t key = 1234;
    int iCount,jCount;
    int *value;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    pthread_t threads[20+1];

    printf("Multipication of Matrix\n");

    for(iCount=0;iCount<4;iCount++)
        {
            for(jCount=0;jCount<5;jCount++)
            {
                printf("%d \t", *value);
                faktorial[iCount][jCount] = *value;
                sleep(3);
            }
            printf("\n");
        }

    for (int i = 0; i < 20; i++) {
        pthread_create(&threads[i], NULL, factorial, NULL);
    }

    for (int i = 0; i < 20; i++) {
        pthread_join(threads[i], NULL); 
    }

    for(iCount=0;iCount<4;iCount++)
    {
        for(jCount=0;jCount<5;jCount++)
        {
            printf("%0.Lf \t",hasil_faktorial[iCount][jCount]);
        }
        printf("\n");
    }   
}

