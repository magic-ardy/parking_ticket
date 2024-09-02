#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_MASUK "kendaraan_masuk.txt"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void masuk();
void keluar();
int main(int argc, char *argv[]) {
	int mode;
	do{
		printf("\n\nketik: \n 1. kendaraan  masuk\n 2. kendaraan keluar \n 0. exit aplikasi\n  input anda: ");
		mode=getche();
		if(mode=='1'){
			masuk();
		}else if(mode=='2'){
			keluar();
		}
		
	}while(mode=='1' || mode=='2');
	return 0;
}
void input_data(char nopol[10],int *jam, int *menit){

	printf("\nmasukkan no pol : ");
	scanf("%s",nopol);
	
	printf("Jam : ");
	scanf("%d",jam);
	
	printf("Menit : ");
	scanf("%d",menit);

}
void simpan_data_masuk(char no_pol[10],int jam, int mnt){
	FILE * fp;
	fp= fopen(FILE_MASUK,"a");
	fprintf(fp,"%s %d %d \n",no_pol,jam,mnt);
	fclose(fp);
}
int baca_jam_masuk(char no_pol[10],int *jam,int *mnt){
	FILE * fp;
	char no_pol_masuk[10];
	fp= fopen(FILE_MASUK,"r");

	while(fscanf(fp,"%s %d %d",no_pol_masuk,jam,mnt)==3){
		printf("%s %d %d\n",no_pol_masuk,*jam,*mnt);
//		printf("%d",strcmp(no_pol,no_pol_masuk));
		if(strcmp(no_pol,no_pol_masuk)==0) {
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}
void simpan_info_parkir(char no_pol[10],int jam_masuk, int mnt_masuk,int jam_keluar, int mnt_keluar,int biaya){
	FILE * fp;
	fp= fopen("info_parkir.txt","a");
	fprintf(fp,"%s %d %d %d %d %d\n",no_pol,jam_masuk, mnt_masuk, jam_keluar, mnt_keluar, biaya);
	fclose(fp);
}
int hitung_parkir(int jam_masuk, int mnt_masuk,int jam_keluar, int mnt_keluar){
	int total_masuk,total_keluar;
	int lama_parkir,sisa_dibulatkan;
	total_masuk = jam_masuk*60+mnt_masuk;
	total_keluar= jam_keluar*60+mnt_keluar;
	lama_parkir= total_keluar-total_masuk;
	if(lama_parkir%60==0)
		sisa_dibulatkan=0;
	else
		sisa_dibulatkan=1;
	return (2000* (sisa_dibulatkan + lama_parkir/60));
}
void masuk(){
	char nopol[10];
	int jam_masuk,menit_masuk;

 	printf("\n\nMasukkan no pol dan jam masuk kendaraan\n");

	input_data(nopol,&jam_masuk,&menit_masuk);
	printf("*****************\n** No Pol: ");
	puts(nopol);
	printf("\nWaktu:   %d:%d",jam_masuk,menit_masuk);
	simpan_data_masuk(nopol,jam_masuk,menit_masuk);
}
void keluar(){
	char nopol[10];
	int jam_masuk,menit_masuk;
	int jam_keluar,menit_keluar;
	int biaya;
	printf("\n\nMasukkan no pol dan jam keluar kendaraan\n");	
	input_data(nopol,&jam_keluar,&menit_keluar);
	if(baca_jam_masuk(nopol,&jam_masuk,&menit_masuk)){
	
		biaya=hitung_parkir( jam_masuk,menit_masuk,jam_keluar,menit_keluar);
		simpan_info_parkir(nopol,jam_masuk, menit_masuk, jam_keluar,  menit_keluar, biaya);
		printf("\n\n****************************\n");
		printf("*No Pol: %s\n",nopol);
		printf("*Jam Masuk: %d:%d\n",jam_masuk, menit_masuk);
		printf("*Jam Keluar: %d:%d\n",jam_keluar,  menit_keluar);
		printf("\n**  BIAYA PARKIR %d rupiah   **\n",biaya);
		printf("\n****************************\n");
	}else{
		printf("\n\n****************************\n");
		printf("No pol tidak ada di file\n");
		printf("****************************\n");
	}
}