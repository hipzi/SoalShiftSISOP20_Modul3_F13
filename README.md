# MODUL 3

 - Soal 2 :
	 * <a href="#soal-2">soal 2</a>
 - Soal 3 :
	 * <a href="#soal-3">soal 3</a>
 - Soal 4 :
	 * <a href="#soal-4">soal 4</a>


<a id="soal-2"> </a> 
## SOAL 2
<justify>
1. TapTap Game adalah game online berbasis text console. Terdapat 2 program yaitu
tapserver.c dan tapplayer.c
<p></p>
Syarat :</br>
- Menggunakan Socket, dan Thread </br>
Hint :</br>
- fwrite, fread
<p></p>

<p></p>
a. Pada screen 1 kalian dapat menginputkan “login”, setelah menekan enter
anda diminta untuk menginputkan username dan password seperti berikut
<p></p>
b. Jika login berhasil maka akan menampilkan pesan “login success”, jika gagal
akan menampilkan pesan “login failed” (pengecekan login hanya mengecek
username dan password, maka dapat multi autentikasi dengan username dan
password yang sama)
<p></p>
c. Pada screen 1 kalian juga dapat menginputkan “register”, setelah menekan
enter anda diminta untuk menginputkan username dan password sama
halnya seperti login
<p></p>
d. Setelah login berhasil maka anda berpindah ke screen 2 dimana
menampilkan 2 fitur seperti berikut.
<p></p>

    ...
    void screen1(int sock){

    printf("1. Login\n");
    printf("2. Register\n");
    printf("Choices : ");

    bzero(pilih, sizeof(pilih)); 
    bzero(username, sizeof(username));
    bzero(password, sizeof(password));
    bzero(cek_username, sizeof(cek_username));
    bzero(cek_password, sizeof(cek_password));
 
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
    ...
<p></p>

Keterangan : </br>
<p></p> 
- <code>bzero</code> untuk memset agar isi string tersebut 0 </br>
- <code>fgets(pilih, MAX, stdin) </code> mengambil input yang diberikan lalu mamasukkannya pada string pilih</br>
- <code>send(sock, pilih , strlen(pilih), 0)</code> mengirim isi dari string pilih ke server</br>
- <code>if (strncmp("login", pilih, 5) == 0)</code> jika isi string pilih adalah login maka bernilai true</br>
- <code>fgets(cek_username, MAX, stdin)</code> mengambil input yang diberikan lalu mamasukkannya pada string cek_username, <code>send(sock , cek_username , strlen(cek_username)-1, 0)</code> mengirin string cek_username ke server </br>
- <code>fgets(cek_password, MAX, stdin)</code> mengambil input yang diberikan lalu mamasukkannya pada string cek_password, <code>send(sock , cek_password , strlen(cek_password)-1, 0)</code> </br>
- <code>read(sock , auth, MAX)</code> membaca string auth yang dikirim oleh server</br>
- <code>if (strncmp("Auth Success", auth, 12) == 0)</code> jika isi string auth adalah Auth Success maka pindah ke <code>screen2(sock)</code></br>
- <code>printf("%s\n", auth)</code> jika login berhasil menampilkan pesan “Auth Success”, jika gagal
akan menampilkan pesan “Auth Failed”</br>

<p></p>
e. Pada register tidak ada pengecekan unique username, maka setelah register
akan langsung menampilkan pesan “register success” dan dapat terjadi
double account

    ...
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
    ...

Keterangan : </br>
<p></p> 
- <code>if (strncmp("register", pilih, 8) == 0)</code> jika isi string pilih adalah register maka bernilai true</br>
- <code>read(sock , stop, MAX)</code> membaca string stop yang dikirim oleh server</br>
- <code>if(strncmp("false", stop, 5) == 0)</code> jika isi string stop adalah false maka bernilai true</br>
- <code>fgets(username, MAX, stdin)</code> mengambil input yang diberikan lalu mamasukkannya pada string username</br>
- <code>fgets(password, MAX, stdin)</code> mengambil input yang diberikan lalu mamasukkannya pada string password</br>
- <code>if((int)strlen(username) > 1 && (int)strlen(password) > 1)</code> jika isi string username dan password ada isinya maka di <code>send</code> ke server</br>

<p></p>
f. Setelah login berhasil maka anda berpindah ke screen 2 dimana
menampilkan 2 fitur seperti berikut.
<p></p>
g. Pada screen 2 anda dapat menginputkan “logout” setelah logout anda akan
kembali ke screen 1
<p></p>
h. Pada screen 2 anda dapat menginputkan “find”, setelah itu akan
menampilkan pesan “Waiting for player ...” print terus sampai menemukan
lawan

    ...
    void screen2(int sock){
        printf("1. Find Match\n");
        printf("2. Logout\n");
        printf("Choices : ");

        bzero(pilih, sizeof(pilih));
        bzero(wait, sizeof(wait));  
        bzero(s_total_client, sizeof(s_total_client));

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
    ...
Keterangan : </br>
<p></p> 

- <code>bzero</code> untuk memset agar isi string tersebut 0 </br>
- <code>fgets(pilih, MAX, stdin) </code> mengambil input yang diberikan lalu mamasukkannya pada string pilih</br>
- <code>send(sock, pilih , strlen(pilih), 0)</code> mengirim isi dari string pilih ke server</br>
- <code>if (strncmp("logout", pilih, 6) == 0)</code> jika isi string pilih adalah logout maka pindah ke <code>screen1(sock)</code></br>
- <code>if (strncmp("find", pilih, 4) == 0)</code> jika isi string pilih adalah find maka bernilai true</br>
- <code>read(sock , s_total_client, MAX)</code> membaca isi string s_total_client kemudian <code>total_client = atoi(s_total_client)</code>mengkonversi isi string menjadi int</br>
- <code>while(total_client < 2)</code> jika total_client kurang dari 2 maka <code>printf("Waiting for player...\n")</code></br>
- <code>read(sock , play_game, MAX)</code> membaca isi string play_game

<p></p>
h. Pada saat program pertama kali dijalankan maka program akan membuat file
akun.txt jika file tersebut tidak ada. File tersebut digunakan untuk menyimpan
username dan password

    ...
    if(strncmp("register", pilih, 8) == 0){

            sprintf(stop, "%s\n", "false");
            send(sock , stop , strlen(stop), 0);

            read(sock , username, MAX);
            read(sock , password, MAX);

            fp = fopen("akun.txt", "a");
            fputs(username, fp);
            fputs(password, fp);
            fclose(fp);
            ...
        }
    ...

Keterangan : </br>
<p></p>
- <code>if (strncmp("register", pilih, 8) == 0)</code> jika isi string pilih adalah register maka bernilai true</br>
- <code>send(sock , stop , strlen(stop), 0)</code>mengirim string stop ke client</br>
- <code>read(sock , username, MAX)</code>membaca string username yang dikirim oleh client</br>
- <code>read(sock , password, MAX)</code>membaca string password yang dikirim oleh client</br>
- <code>fp = fopen("akun.txt", "a")</code>membuat file <code>akun.txt</code> kemudian menulis isi dari <code>username</code>dan<code>password</code> setelah itu di <code>close</code></br>

<p></p>
i. Pada saat user berhasil login maka akan menampilkan pesan “Auth success” jika
gagal “Auth Failed”

    ...
    if(strncmp("login", pilih, 5) == 0){

            read(sock, cek_username, MAX);
            read(sock, cek_password, MAX);

Keterangan : </br>
<p></p> 
- <code>if (strncmp("login", pilih, 5) == 0)</code> jika isi string pilih adalah login maka bernilai true</br>
- <code>read(sock , cek_username, MAX)</code>membaca string username yang dikirim oleh client</br>
- <code>read(sock , cek_password, MAX)</code>membaca string password yang dikirim oleh client</br>

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
    ...
Keterangan : </br>
<p></p> 
- <code>fp = fopen("akun.txt", "r")</code> membaca isi file akun.txt lalu menyimpan perbaris isi dari file dengan loop <code>while(fgets(line[i], sizeof(line[i]), fp))</code></br>
- <code>for(i = 0; i < total; i++)</code>loop untuk mencocokkan baris apakah jika baris pertama ini dari array line[i] sama dengan <code>cek_username</code> jika sama maka cek baris selanjutnya apakah sama dengan isi array cek_password kalau sama masukkan <code>"Auth Success"</code> pada string auth jika tidak masukkan <code>"Auth Failed"</code> pada string auth</br>
- <code>send(sock, auth, strlen(auth), 0)</code> mengirim string auth ke server lalu <code>fclose(fp)</code></br>

<p></p>
j. Pada saat user sukses meregister maka akan menampilkan List account yang
terdaftar (username dan password harus terlihat)

    ...
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
    ...
Keterangan : </br>
<p></p> 
- <code>printf("%s\n", line[i])</code> untuk menampilkan List account yang
terdaftar</br>
<p></p>

Code main pada client :

    int main(int argc, char const *argv[]) {

    ...

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

Keterangan : </br>
<p></p> 
- <code>sock = socket(AF_INET, SOCK_STREAM, 0)</code> untuk menyambungkan ke socket dengan parameter <code>AF_INET</code> yang berarti IPv4 dan <code>SOCK_STREAM</code> menggunakan protokol TCP</br>
- <code>serv_addr.sin_family = AF_INET</code> setting familynya IPv4 dan <code>htons(PORT)</code> untuk setting port</br>
- <code>inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)</code> untuk mengkonversi alamat yang berupa string ke network addres </br>
- <code>connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)</code> untuk connect ke server</br>
<p></p>
Code main pada server :

    int main(int argc, char const *argv[]) {

    ...

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

            if((child = fork()) == 0){
                    file(new_socket); 
                    play(new_socket);
            }
        }
    }

Keterangan : </br>
<p></p> 
- <code>server_fd = socket(AF_INET, SOCK_STREAM, 0)</code> untuk menyambungkan ke socket dengan parameter <code>AF_INET</code> yang berarti IPv4 dan <code>SOCK_STREAM</code> menggunakan protokol TCP</br>
- <code>setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))</code> set socket berdasarkan option dengan level <code>SOL_SOCKET</code> agar bisa <code>SO_REUSEADDR | SO_REUSEPORT</code></br>
- <code>serv_addr.sin_family = AF_INET</code> setting familynya IPv4, <code>address.sin_addr.s_addr = INADDR_ANY</code> dapat menerima dari mana saja dan <code>htons(PORT)</code> untuk setting port</br>
- <code>bind(server_fd, (struct sockaddr *)&address, sizeof(address))</code> untuk mengikat address </br>
- <code>listen(server_fd, 3)</code> untuk mempersiapkan menerima client <code>3</code> merupakan maksimal client yang bisa di listen</br>
- <code>new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)</code> untuk menerima client</br>
<p></p>
 
<a id="soal-3"></a> 
## SOAL 3
<justify>
3. Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan
memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah
sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working
directory ketika program kategori tersebut dijalankan.
<p></p>

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
            strcpy(ekstensi, dot + 1);
            return ekstensi;
        }
    }
Keterangan :</br>
<p></p>
- merupakan fungsi untuk mengambil ekstensi dari suatu file</br>
  
    bool isdir(const char* path) {
        struct stat statbuf; 
        if (stat(path, &statbuf) == -1)
            return 0;
            return S_ISDIR(statbuf.st_mode);
    }

Keterangan :</br>
<p></p>
- merupakan fungsi untuk mengetahui directory atau bukan</br>
<p>a. Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa
dikategorikan sebanyak yang user inginkan seperti contoh di atas. </p>

    else if (argv[1][1] == 'f') 
    {
        for (int i= 3; i < argc+1; i++)
        {
            strcpy(fullpath, argv[i-1]);

Keterangan :</br>
<p></p>
- <code>if (argv[1][1] == 'f') </code> membaca kalau parameter yang di inputkan adalah <code>f</code> lalu melakukan looping dari selelah argumen parameter sampai argumen selesai <code>for (int i= 3; i < argc+1; i++)</code></br>
- <code>strcpy(fullpath, argv[i-1])</code>untuk mengcopy path dari file tersebut ke dalam string fullpath</br>

<p>b. Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual,
melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi,
maka dia akan disimpan dalam folder “Unknown”. </p>

    ...
    if (strcmp(ekstensi,"") == 0)
    {
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        strcat(cwd, "Unknown");
        mkdir(cwd, 0777);
        strcat(cwd, eval_filename);
        rename(fullpath, cwd);
    }
Keterangan :</br>
<p></p>
- <code>(strcmp(ekstensi,"") == 0)</code> kalau ekstensi tidak ada isinya maka bernilai true</br>
- <code>getcwd(cwd, sizeof(cwd))</code> untuk megambil pwd kemudian di strcat dengan "Unknown" untuk <code>mkdir</code> membuat folder Unknown</br>
- <code>rename(fullpath, cwd)</code> memindahkan file dari path awalnya kedalam folder Unknown</br>
  
    ...
    else
    {
        for(int i = 0; ekstensi[i]; i++){
            simpan_ekstensi[hitung][i] = tolower(ekstensi[i]);
        }
Keterangan :</br>
<p></p>
- <code>tolower(ekstensi[i])</code> mengecilkan nama ekstensi untuk menjadi nama foldernya</br>

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

Keterangan :</br>
<p></p>
- untuk membandingkan apakah ekstensinya sama seperti ekstensi sebelumnya atau tidak agar tidak terjadi duplikat pada folder</br>
  
    for (int i = 1; i <= n; i++) {
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        strcat(cwd, simpan_ekstensi[i]);
        mkdir(cwd, 0777);
    }

Keterangan :</br>
<p></p>
- <code>(int i = 1; i <= n; i++)</code> melakukan looping sampai jumlah file pada direktori habis</br>
- <code>getcwd(cwd, sizeof(cwd))</code> untuk megambil pwd kemudian di strcat dengan nama folder pada array <code>simpan_ekstensi</code> untuk <code>mkdir</code> membuat folder <code>simpan_ekstensi</code> dengan file permission <code>0777</code></br>

    for (int i = 1; i <= hitung; i++) {
        pthread_create(&threads[i], NULL, move, NULL);
    }

    for (int i = 1; i <= hitung; i++) {
        pthread_join(threads[i], NULL); 
    }   
Keterangan :</br>
<p></p>
- <code>pthread_create(&threads[i], NULL, move, NULL)</code> mengkategorikan setiap 1 file dioperasikan oleh 1 thread agar bisa berjalan secara paralel</br>
- <code>pthread_join(threads[i], NULL)</code> membuat <code>pthread_join</code>menunggu thread berjalan agar memberi tahu program jika nanti threadnya sudah selesai</br>      
<p></p>
<p>c. Program kategori ini juga menerima perintah (*). Artinya mengkategori seluruh file yang ada di working directory ketika
menjalankan program C tersebut. </p>
<p></p>
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
                ....
            }
            closedir(d);
        }

    }
Keterangan :</br>
<p></p>
- <code>(!strcmp(argv[1], "*"))</code> jika argumen pertama adalah <code>*</code> maka <code>d = opendir(".")</code>membuka working directory</br>
- <code>while ((dir = readdir(d)) != NULL)</code> membaca isi dari directori sampai directory habis lalu <code>closedir(d)</code></br>      
<p></p>
<p>d. Selain hal itu program C ini juga menerima opsi -d untuk melakukan kategori
pada suatu directory. Untuk opsi -d ini, user hanya bisa menginput 1 directory
saja, tidak seperti file yang bebas menginput file sebanyak mungkin. Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan
hasilnya akan disimpan di working directory di mana program C tersebut
berjalan (hasil kategori filenya bukan di /path/to/​ directory​ ). </p>

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
                ....
            }
            closedir(d);
        }
<p></p>
Keterangan :</br>
<p></p>
- <code>else if (argv[1][1] == 'd')</code> membaca kalau parameter yang di inputkan adalah <code>d</code></br>
- <code>while ((dir = readdir(d)) != NULL)</code> membaca isi dari directori sampai directory habis lalu <code>closedir(d)</code></br>      
<p></p>
<p>e. Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau
menggunakan (*) terdapat folder yang berisi file, maka file dalam folder
tersebut tidak dihiraukan, cukup file pada 1 level saja.. </p>
<p></p>
<p>f. Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan
secara paralel sehingga proses kategori bisa berjalan lebih cepat. ​ Dilarang
juga menggunakan fork-exec dan system. </p>
<p></p>

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

Keterangan : </br>
<p></p> 
- <code>if(strcasecmp(simpan_ekstensi[i], ekstensi) == 0)</code> jika ekstensi file sama dengan nama forder ekstensi maka memindahkan file tersebut ke dalam folder ekstensi dengan cara <code>rename</code> path yang lama diubah menjadi nama path yang baru</br>

<a id="soal-4"></a>
## SOAL 4
<justify>
1. Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat
mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di
pilar tersebut. Norland menghampiri setiap pilar secara bergantian.
<p></p>
a. Batu mulia pertama. Buatlah program C dengan nama "​ 4a.c​ ", yang berisi program untuk
melakukan perkalian matriks. Ukuran matriks pertama adalah ​ 4x2​ , dan
matriks kedua ​ 2x5​ . Isi dari matriks didefinisikan ​ di dalam kodingan. Matriks
nantinya akan berisi angka 1-20.Tampilkan matriks hasil perkalian tadi ke layar.
<p></p>

int main()
{
    key_t key = 1234;
    int *value;
    ...

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

Keterangan : </br>
<p></p> 
- <code>shmid</code> untuk mengidentifikasi id share memory yang di dapat dari <code>shmget(key, sizeof(int), IPC_CREAT | 0666)</code></br>
- <code>shmat(shmid, NULL, 0)</code> </br>
- <code>sleep(5)</code> agar proses selanjutnya dilakukan setelah menunggu selama 5 detik</br>

    ...
         
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

Keterangan : </br>
<p></p> 
- melakukan perkalian matriks lalu hasil dari perkalian matriks tersebut di passing ke alamat dari variabel value</br>
<p></p> 
b. Batu kedua adalah Amethyst. Buatlah program C kedua dengan nama "​ 4b.c​ ". Program ini akan
mengambil variabel ​ hasil perkalian matriks dari program "4a.c" (program
sebelumnya), dan tampilkan hasil matriks tersebut ke layar.
(​ Catatan!​ : gunakan shared memory).Setelah ditampilkan, berikutnya untuk setiap angka dari matriks
tersebut, carilah nilai ​ faktorialnya​ , dan tampilkan hasilnya ke layar dengan
format seperti matriks.
<p></p>
long double fact(int n){
    if(n==0 || n==1)
    return 1;
    else 
    return n+fact(n-1);
}
Keterangan : </br>
<p></p> 
- fungsi untuk melakukan pertambahan dari n sampai 1</br>
<p></p> 
void *factorial(void* arg) 
{ 
    int *n = (int *)arg;
    int a = *n;

    int *res = (int*)malloc(sizeof(int));
    *res = fact(a);
    
    pthread_exit(res);
}
Keterangan : </br>
<p></p> 
- <code>pthread</code> thread agar melakukan perhitungan secara paralel <code>dengan passing isi dari pointer ke variabel lalu mengeksekusinya dengan memanggil fungsi <code>fact</code> lalu menyimpannya kembali pada pointer</code></br>

int main(){

    ...

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

Keterangan : </br>
<p></p> 
- mengambil hasil dari share memory dan passing dalam array <code>faktorial[iCount][jCount]</code> kemudian passing alamat dari <code>faktorial[iCount][jCount]</code> ke <code>n</code></br>
- <code>pthread_create(&threads[count], NULL, factorial, (void*)(n))</code> membuat thread dengan passing pointer <code>n</code></br>

    for(int i=0;i<20;i++){
        void *k;
        pthread_join(threads[i], &k);

        int *p = (int *)k;
        printf("%d\t", *p);
        if ((i + 1) % 5 == 0){
            printf("\n");
        }
    }
Keterangan : </br>
<p></p> 
- <code>pthread_join(threads[i], &k)</code> melakukan pthread_join, mengambil isi pointer dari thread kemudian di print hasil pertambahan berbentuk matriks</br>

c. Batu ketiga adalah Onyx.Buatlah program C ketiga dengan nama "​ 4c.c​ ". Program ini tidak memiliki hubungan terhadap program yang lalu.Pada program ini, Norland diminta mengetahui jumlah file dan folder di direktori saat ini dengan command "​ ls | wc -l​ ". menggunakan
IPC
<p></p>

    int main()
    {
        if (pipe(fd1) == -1){
            exit(1);
        }

        pid_t child = fork();
        if (child == 0) 
        {
            dup2(fd1[1], STDOUT_FILENO);

            close(fd1[0]);
            close(fd1[1]);

            char *argv[] = {"ls", NULL};
                execv("/bin/ls", argv);
        } else {
            dup2(fd1[0], STDIN_FILENO);

            close(fd1[0]);
            close(fd1[1]);

            char *argv[] = {"wc", "-l", NULL};
                execv("/usr/bin/wc", argv);
        }
    }

Keterangan : </br>
<p></p> 
- <code> dup2(fd1[1], STDOUT_FILENO)</code> menduplikasi isi dari output hasil eksekusi <code>execv("/bin/ls", argv)</code> ke pipe[1] <code>1</code>karena write</br>
- <code>close(fd1[0])</code> close pipe <code>0</code> karena tidak dipakai <code>close(fd1[1])</code>karena sudah dipakai</br>
- <code> dup2(fd1[0], STDIN_FILENO)</code> menduplikasi isi dari pipe sebelumnya agar bisa menjadi inputan pada command setelahnya yaitu <code>execv("/usr/bin/wc", argv)</code></br>
- <code>close(fd1[0])</code> close pipe <code>0</code> karena telah dipakai <code>close(fd1[1])</code>karena tidak dipakai</br>

# Kendala

Entah kenapa minggu ini terasa berat, oleh karena itu saya kurang bisa fokus ke sisop


