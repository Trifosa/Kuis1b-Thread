//Library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int countWord(char line[]){
	int i;
	int jml = 0;
	for(i=0;i<strlen(line);i++){
		if(((line[i] == ' ')&&(line[i+1] != ' '))||(line[i] == '\n')){
				jml++;
		}
	}
	return jml;
}

void baca(char dir[]){
	FILE *text; //untuk membaca file

	text = fopen(dir, "r"); //membaca file

	char temp[1000][1000]; //penampung kata

	int n = 0;
	while(fgets(temp[n], 1000, text) != NULL){
		n++;
	}

	fclose(text);

	int i;
	int jml = 0;
	for(i=0;i<n;i++){
		jml += countWord(temp[i]);
	}

	printf("Jumlah kata dari %s = %d\n",dir, jml);
}

void gabungKata(char *hasil, char kata1[], char kata2[], int awal){
	int n = 0;
	int i;
	for(i=0;i<strlen(kata1);i++){
		hasil[n] = kata1[i];
		n++;
	}

	if(awal == 1){
		hasil[n] = '/';
		n++;
	}

	for(i=0;i<strlen(kata2);i++){
		hasil[n] = kata2[i];
		n++;
	}

	if(awal == 1){
		n = n-1;
	}
	hasil[n] = '\0';
}

int main(){
	char dir[100]; //untuk directory file
	printf("Masukkan alamat direktori: ");
	scanf("%s", dir); //meminta masukan directory file
	char cmd[1000];
	char tmp1[4], tmp2[7];

	strcpy(tmp1,"ls ");
	strcpy(tmp2," *.txt");

	int n;
	int i;

	gabungKata(cmd, tmp1, dir, 0);
	gabungKata(cmd, cmd, tmp2, 0);

	FILE *fp;
	char data[1000][1000];
	fp = popen(cmd, "r");

	n = 0;
	while(fgets(data[n], 1000, fp) != NULL){
		n++;
	}

	pclose(fp);
	i = 0;
	while(strlen(data[i]) != 1){
		printf("%s", data[i]);
		i++;
	}

	int total = i;
	char bener[total][1000];
	for(i=0; i<total; i++){
			gabungKata(bener[i], dir, data[i], 1);
	}

	pthread_t thread1, thread2;
	int iret1, iret2;

	iret1 = pthread_create( &thread1, NULL, baca, (void*) bener[0]);
	iret2 = pthread_create( &thread2, NULL, baca, (void*) bener[1]);

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	return 0;
}
