#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

int faktorial[10][10];
long double hasil_faktorial[10][10];
int iCount,jCount,kCount;

long double fact(int n){
    if(n==0 || n==1)
    return 1;
    else 
    return n+fact(n-1);
}

void *factorial(void* arg) 
{ 
    int *n = (int *)arg;
    int a = *n;

    int *res = (int*)malloc(sizeof(int));
    *res = fact(a);
    
    pthread_exit(res);
}

int main(){
    key_t key = 1234;
    int iCount,jCount;
    int *value;
    int count;
    int *n = NULL;

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

                n = (int *)malloc(sizeof(int));

                n = &faktorial[iCount][jCount];
                pthread_create(&threads[count], NULL, factorial, (void*)(n));
                count++;

                sleep(5);
            }
            printf("\n");
        }

    for(int i=0;i<20;i++){
        void *k;
        pthread_join(threads[i], &k);

        int *p = (int *)k;
        printf("%d\t", *p);
        if ((i + 1) % 5 == 0){
            printf("\n");
        }
    }
  
}

