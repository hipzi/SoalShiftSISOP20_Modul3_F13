#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <dirent.h>
#include <stdbool.h> 
#include <ctype.h> 
#include <sys/stat.h> 
#include <pthread.h>

int hitung = 0;
char cwd[1000];
char ekstensi[50];
char low_ekstensi[50];
char simpan_ekstensi[50][50];
char eval_filename[1000];
char fullpath[1000] = {"/home/hipzi/Documents/Sisop/Modul-3/Soal3/"};

void *move(void *p){
        for (int i = 1; i <= hitung; i++) {
            if(strcasecmp(simpan_ekstensi[i], ekstensi) == 0){
                getcwd(cwd, sizeof(cwd));
                strcat(cwd, "/");
                strcat(cwd, simpan_ekstensi[i]);
                strcat(cwd, eval_filename);
                rename(fullpath, cwd);
            }
        }

    pthread_exit(0);
}

bool ceknumber(char s[]) 
{ 
    for (int i = 1; i < strlen(s); i++){ 
        if (isdigit(s[i]) == false && s[i]!='*'){
            return false; 
        } 
    }
    return true;
} 

const char *get_filename_ext(const char *filename) {
    char number[1000];

    const char *path = strrchr(filename, '/');
    if(!path || path == filename) return 0;
    else{
        strcpy(eval_filename,path);
    }
    const char *dot = strrchr(eval_filename, '.');
    if(!dot || dot == eval_filename){
        strcpy(ekstensi, "\0");
        return ekstensi;
    }
    else{
        strcpy(number,dot);
        if(ceknumber(number)>0){
            strcpy(ekstensi, "\0");
            return ekstensi;
        }
        else {
                strcpy(ekstensi, dot + 1);
                return ekstensi;
        }
    }
}

bool isdir(const char* path) {
    struct stat statbuf; 
    if (stat(path, &statbuf) == -1)
        return 0;
        return S_ISDIR(statbuf.st_mode);
}

int main(int argc, char **argv) 
{
    DIR *d;
    struct dirent *dir;
    

    pthread_t threads[1000+1];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd() error");
    }

    if (!strcmp(argv[1], "*")) 
    {
        
        d = opendir(".");

        if(argc>2){
            perror("error");
            exit(0);
        }

        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                getcwd(cwd, sizeof(cwd));
                strcpy(fullpath, cwd);
                strcat(fullpath, "/");
                strcat(fullpath, dir->d_name);
                
                if(isdir(fullpath)){
                    continue;
                }
                hitung++;
                get_filename_ext(fullpath);
                if (strcmp(ekstensi,"") == 0)
                {
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, "/");
                    strcat(cwd, "Unknown");
                    mkdir(cwd, 0777);
                    strcat(cwd, eval_filename);
                    rename(fullpath, cwd);
                }
                else
                {
                    for(int i = 0; ekstensi[i]; i++){
                        simpan_ekstensi[hitung][i] = tolower(ekstensi[i]);
                    }
                    int n = hitung;
                    for (int i = 0; i < n; i++) {
                        for (int j = i + 1; j <= n; j++) {
                                if (strcmp(simpan_ekstensi[i], simpan_ekstensi[j]) == 0) {
                                        for (int k = j; k < n; k++) {
                                                strcpy(simpan_ekstensi[k], simpan_ekstensi[k + 1]);
                                        }
                                        n--, j--;
                                }
                        }
                    }
                    for (int i = 1; i <= n; i++) {
                        getcwd(cwd, sizeof(cwd));
                        strcat(cwd, "/");
                        strcat(cwd, simpan_ekstensi[i]);
                        printf("%s %s\n", cwd, simpan_ekstensi[i]);
                        mkdir(cwd, 0777);
                    }
                    for (int i = 1; i <= hitung; i++) {
                        pthread_create(&threads[i], NULL, move, NULL);
                    }

                    for (int i = 1; i <= hitung; i++) {
                        pthread_join(threads[i], NULL); 
                    }
                }
            }
            closedir(d);
        }

    }
    else if (argv[1][1] == 'f') 
    {
        for (int i= 3; i < argc+1; i++)
        {
            strcpy(fullpath, argv[i-1]);

            if(isdir(fullpath)){
                continue;
            }
            hitung++;
            get_filename_ext(fullpath);
            if (strcmp(ekstensi,"") == 0)
            {
                getcwd(cwd, sizeof(cwd));
                strcat(cwd, "/");
                strcat(cwd, "Unknown");
                mkdir(cwd, 0777);
                strcat(cwd, eval_filename);
                rename(fullpath, cwd);
                printf("%s\n", eval_filename);
                printf("%s %s\n", fullpath, cwd);
            }
            else
            {
                for(int i = 0; ekstensi[i]; i++){
		            simpan_ekstensi[hitung][i] = tolower(ekstensi[i]);
	            }
                int n = hitung;
                for (int i = 0; i < n; i++) {
                    for (int j = i + 1; j <= n; j++) {
                            if (strcmp(simpan_ekstensi[i], simpan_ekstensi[j]) == 0) {
                                    for (int k = j; k < n; k++) {
                                            strcpy(simpan_ekstensi[k], simpan_ekstensi[k + 1]);
                                    }
                                    n--, j--;
                            }
                    }
                }
                for (int i = 1; i <= n; i++) {
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, "/");
                    strcat(cwd, simpan_ekstensi[i]);
                    printf("%s %s\n", cwd, simpan_ekstensi[i]);
                    mkdir(cwd, 0777);
                }
                for (int i = 1; i <= hitung; i++) {
                    pthread_create(&threads[i], NULL, move, NULL);
                }

                for (int i = 1; i <= hitung; i++) {
                    pthread_join(threads[i], NULL); 
                }
            }
        }        
    }
    else if (argv[1][1] == 'd') 
    {
        DIR *d;
        struct dirent *dir;
        d = opendir(argv[2]);

        if(argc>3){
            perror("error");
            exit(0);
        }

        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {
                strcpy(fullpath, argv[2]);
                strcat(fullpath, "/");
                strcat(fullpath, dir->d_name);

                if(isdir(fullpath)){
                    continue;
                }
                hitung++;
                get_filename_ext(fullpath);
                if (strcmp(ekstensi,"") == 0)
                {
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd, "/");
                    strcat(cwd, "Unknown");
                    mkdir(cwd, 0777);
                    strcat(cwd, eval_filename);
                    rename(fullpath, cwd);
                }
                else
                {
                    for(int i = 0; ekstensi[i]; i++){
                        simpan_ekstensi[hitung][i] = tolower(ekstensi[i]);
                    }
                    int n = hitung;
                    for (int i = 0; i < n; i++) {
                        for (int j = i + 1; j <= n; j++) {
                                if (strcmp(simpan_ekstensi[i], simpan_ekstensi[j]) == 0) {
                                        for (int k = j; k < n; k++) {
                                                strcpy(simpan_ekstensi[k], simpan_ekstensi[k + 1]);
                                        }
                                        n--, j--;
                                }
                        }
                    }
                    for (int i = 1; i <= n; i++) {
                        getcwd(cwd, sizeof(cwd));
                        strcat(cwd, "/");
                        strcat(cwd, simpan_ekstensi[i]);
                        printf("%s %s\n", cwd, simpan_ekstensi[i]);
                        mkdir(cwd, 0777);
                    }
                    for (int i = 1; i <= hitung; i++) {
                        pthread_create(&threads[i], NULL, move, NULL);
                    }

                    for (int i = 1; i <= hitung; i++) {
                        pthread_join(threads[i], NULL); 
                    }
                }
            }
            closedir(d);
        }
    }
    else if (argc==1 || (argv[1][1] != 'f' && argv[1][1] != 'd')) {
        printf("Masukan argumen * atau dengan menggunakan parameter f atau d\n");
    }
}