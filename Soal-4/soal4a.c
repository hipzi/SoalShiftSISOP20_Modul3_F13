# include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int matrix1[10][10];
int matrix2[10][10];
int matrix3[10][10];

int main()
{
    key_t key = 1234;
    int *value;
    int arr[10][10];

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    int iCount,jCount,kCount;

    int matrix1[4][2] = { {1, 2} ,   
                        {3, 4} ,
                        {5, 6} ,   
                        {7, 8}};
    
    int matrix2[2][5] = { {9, 10, 11, 12, 13} ,   
                        {14, 15, 16, 17, 18} };
    
    int matrix3[4][5] = {0};
    
    if(2!=2)
    {
        printf("Multipication of Matrix not Possible");
    }
    else
    {           
        for(iCount=0;iCount<4;iCount++)
        {
            for(jCount=0;jCount<5;jCount++)
            {
                for(kCount=0;kCount<2;kCount++)
                {
                    matrix3[iCount][jCount]+=matrix1[iCount][kCount] * matrix2[kCount][jCount];
                }
            }
        }
    }  
    
    printf("Multipication of Matrix\n");
    
    for(iCount=0;iCount<4;iCount++)
    {
        for(jCount=0;jCount<5;jCount++)
        {
            printf("%d \t",matrix3[iCount][jCount]);
            *value = matrix3[iCount][jCount];
            sleep(5);
        }
        printf("\n");
    }    
    return 0;
}