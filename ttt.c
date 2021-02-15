#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>

void menu();
void pilihMode(); //
void pilihPapan();
void caraBermain(); // sudah
void skorTertinggi(); // belum
void tentang(); // sudah
void inputNama();
void bermain();

typedef struct 
{
	char nama[20];
	int score;
}Player;

typedef struct
{
	bool status;
	char level[10];
	int score;
}Komputer;

typedef struct {
	int pola;
	char xy[9][9];
	int waktu;
} Kotak;

Player User[2];
Komputer bot = {};
Kotak papan = {};


int grid, 
	gameOver = 0,
	jumlahGiliran = 0,
	riwayatKotak[50] = {0};


void gotoxy(int x, int y) {
    COORD coord;
     
    coord.X = x;
    coord.Y = y;
     
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void menu(){
    system("CLS"); // clear screen
    system("COLOR F1");
    printf("        TicTacToe\n\n");
    printf("1. Main\n");
    printf("2. Cara Bermain\n");
    printf("3. Skor Tertinggi\n");
    printf("4. Tentang\n");
    printf("5. Keluar\n");
}

void inputNama(int index){
	system("CLS");
	gotoxy(0,1); printf("> Masukan Nama Pemain (Player ke-%d): ", index+1);
	scanf("%s", &User[index].nama);
}

int pilihLevel(){
	int pilihan;
	
	do{
		system("cls");
		gotoxy(15,0); printf("Pilih Kesulitan");
		gotoxy(0,2); printf("1. Mudah");
		gotoxy(0,3); printf("2. Sulit");
		gotoxy(0,4); printf(">  Pilih Tingkat Kesulitan : ");
		scanf("%d",&pilihan);
//		if(pilihan > 0 && pilihan < 3){
//			bot.active = true;
//		}
		if(pilihan > 2 || pilihan < 0){
			printf("\n  Masukan pilihan antara 1 - 2 !!!");
		}
	}while(pilihan > 2 || pilihan < 0);
}

void pilihMode(){
	int pilih;

	do{
		system("CLS");
		gotoxy(15,0); printf("Pilih Mode");
		gotoxy(0,2); printf("1. Lawan Player");
		gotoxy(0,3); printf("2. Lawan Komputer");
		gotoxy(0,4); printf(">  Pilih Mode : ");

		scanf("%d", &pilih);
		if (pilih == 1){
			inputNama(0);
			inputNama(1);
			bermain();
		}else if(pilih == 2){
			inputNama(0);
			pilihLevel();
			bermain();
		}

		if (pilih > 2){
			printf("> Pilih 1 - 2!!!\n");
			system("pause");
		}
		
	}while(pilih > 2);
	
	
}

void pilihPapan(){
	
	do{
		system("CLS");
		gotoxy(17,0); printf("PILIH PAPAN");
		//papan 3x3
		gotoxy(0,2); printf("1. 3x3");
		gotoxy(3,3); printf("X X X");
		gotoxy(3,4); printf("X X X");
		gotoxy(3,5); printf("X X X");
		
		//papan 5x5
		gotoxy(15,2); printf("2. 5x5");
		gotoxy(18,3); printf("X X X X X");
		gotoxy(18,4); printf("X X X X X");
		gotoxy(18,5); printf("X X X X X");
		gotoxy(18,6); printf("X X X X X");
		gotoxy(18,7); printf("X X X X X");
		
		//papan 7x7
		gotoxy(34,2); printf("3. 7x7");
		gotoxy(37,3); printf("X X X X X X X");
		gotoxy(37,4); printf("X X X X X X X");
		gotoxy(37,5); printf("X X X X X X X");
		gotoxy(37,6); printf("X X X X X X X");
		gotoxy(37,7); printf("X X X X X X X");
		gotoxy(37,8); printf("X X X X X X X");
		gotoxy(37,9); printf("X X X X X X X");
		
		
		gotoxy(0,12); printf("> Masukan Pilihan (1-3) : ");
		scanf("%d", &papan.pola);
		if (papan.pola > 3){
			printf("> Pilih 1 - 3 !!!\n");
			system("pause");
		}
		
	}while(papan.pola > 3);
	
}

int cekKotak(int pilih){
	int i;
	papan.pola = 3;
	
	for(i = 0; i < papan.pola*papan.pola; i++){
		if(riwayatKotak[i] == pilih){
			return 1;
			break;
		}
	}
	
	return 0;
}

void papan1(){
	
	char simbol;
	int player = 1,
		pilih;
	do{
		
		// tampil papan
		player = (player % 2) ? 1 : 2;
		simbol = (player == 1)	? 'X' : 'O';
		
		system("CLS");
		gotoxy(15,0); printf("Papan 3x3");
		gotoxy(10,2); printf("-------------------");
		gotoxy(10,3); printf("|1 %c	|2 %c  |3 %c  |", papan.xy[0][0], papan.xy[0][1], papan.xy[0][2]);
		gotoxy(10,4); printf("-------------------");
		gotoxy(10,5); printf("|4 %c	|5 %c  |6 %c  |", papan.xy[1][0], papan.xy[1][1], papan.xy[1][2]);
		gotoxy(10,6); printf("-------------------");
		gotoxy(10,7); printf("|7 %c	|8 %c  |9 %c  |",papan.xy[2][0], papan.xy[2][1], papan.xy[2][2]);
		gotoxy(10,8); printf("-------------------");
		
		// tampil lawan dan Score
		gotoxy(35,4); printf("Player 1 [X]\t: %d", User[0].score);
		if(bot.status == true){
			gotoxy(35,3); printf("Lawan\t: Komputer (%s)", bot.level );
			gotoxy(35,5); printf("Komputer [O]\t: %d", bot.score);
			
		}else{
			gotoxy(35,3); printf("Lawan\t: Player ");
			gotoxy(35,5); printf("Player 2 [O]\t: %d", User[1].score);
		}
		
		// input no Kotak
		gotoxy(0,9); printf(">  Player %d Masukan Nomor Kotak : ", player);
		scanf("%d", &pilih);
		// cek batas inputan
		if(pilih < 1 || pilih > 9 ){
			printf("\n > Masukan kotak 1 - 9 !");
			system("pause");
		// cek kotak
		}else{
			printf("%d", cekKotak(pilih));
			if(cekKotak(pilih) == 1){				
				printf("> Kotak yang dipilih sudah terisi, pilih kotak lain !");
				system("pause");
				}
		// input no kotak ke papan
			else{
				// cari no papan
				int i,j,k = 1;
				for(i = 0; i < 3; i++){
					for(j = 0; j < 3; j++){
						if(pilih == k){
							papan.xy[i][j] = simbol;
							riwayatKotak[jumlahGiliran] = pilih;
							jumlahGiliran++; player++;
							goto mng;
						}
						k++;					
					}
					mng : break;
				}
			}		
		// cek menang				
		}
	} while (gameOver == 0 || jumlahGiliran < 9);
	
}

void papan2(){
	system("CLS") ;
	gotoxy(15,0);   printf("Papan 5x5");
	gotoxy(10,3);   printf("|  1   |  2  |  3   |  4   |  5    |");
	gotoxy(10,4);   printf("------------------------------------");
	gotoxy(10,5);   printf("|  6   |  27 |  8   |  9   |  10   |");
	gotoxy(10,6);   printf("------------------------------------");
	gotoxy(10,7);   printf("|  11  |  12 |  13  |  14  |  15   |");
	gotoxy(10,8);   printf("------------------------------------");
	gotoxy(10,9);   printf("|  16  |  17 |  18  |  19  |  20   |");
	gotoxy(10,10);  printf("------------------------------------");
	gotoxy(10,11);  printf("|  21  |  22 |  23  |  24  |  25   |");
}

void papan3(){
	system("CLS") ;
	gotoxy(15,0);     printf("Papan 7x7");
	gotoxy(10,3);     printf("|  1    |  2   |  3    |  4    |  5     |  6   |  7   |");
	gotoxy(10,4);     printf("-------------------------------------------------------");
	gotoxy(10,5);     printf("|  8    |  9   |  10   |  11   |  12    |  13  |  14  |");
	gotoxy(10,6);     printf("-------------------------------------------------------");
	gotoxy(10,7);     printf("|  15   |  16  |  17   |  18   |  19    |  20  |  21  |");
	gotoxy(10,8);     printf("-------------------------------------------------------");
	gotoxy(10,9);     printf("|  22   |  23  |  24   |  25   |  26    |  27  |  28  |");
	gotoxy(10,10);    printf("-------------------------------------------------------");
	gotoxy(10,11);    printf("|  29   |  30  |  31   |  32   |  33    |  34  |  35  |");
	gotoxy(10,12);    printf("-------------------------------------------------------");
	gotoxy(10,13);    printf("|  36   |  37  |  38   |  39   |  40    |  41  |  42  |");
	gotoxy(10,14);    printf("-------------------------------------------------------");
	gotoxy(10,15);    printf("|  43   |  44  |  45   |  46   |  47    |  48  |  49  |");
}

void bermain(){
	system("CLS");

	do{
		switch(papan.pola){
			case 1 : papan1(); break;
//			case 2 : papan2(); break;
//			case 3 : papan3(); break;
		}
	}
	while(papan.pola < 3);
}

void caraBermain(){
	system("CLS");
	printf("                Cara Bermain\n") ;
	printf("1. Setelah Player menentukan papan dan nama, selanjutnya pemain menentukan mode permainan.\n") ;
	printf("2. Saat game berlansung player memasukan nomor kotak yang ingin diisi dengan syarat kotak yang diisi belum diisi oleh lawan. Setiap giliran hanya bisa menginput satu simbol.\n") ;
	printf("3. Teruslah bergiliran mengisi simbol masing masing sampai salah satu pemain telah menggambar tiga atau lebih simbol yang sama secara berderet atau dinyatakan seri apabila tidak ada simbol yang berderet namun semua kotak sudah penuh.\n");
	
}

void skorTertinggi(){

}

void tentang(){
	system("CLS");
	printf("Tic-tac-toe adalah sebuah permainan untuk dua pemain yang dilakukan diatas sebuah media dengan cara menulis simbol diatasnya\n");
	printf("Setiap pemain memilih simbol antara X dan O serta mengisi grid secara bergiliran\n");
	printf("Pemain yang berhasil menempatkan tiga simbol secara berurutan baik horizontal,vertikal, ataupun diagonal\n");
	printf("Pemain tersebut yang memenangkan pertandingannya.\n");
}


int main(){
    int pilih;
    char ulangi;

    do{
        menu();
        printf("\nPilih Menu dari [1-5] : ");
        scanf("%d", &pilih);

        switch (pilih){
            case 1 : papan1(); break;
            case 2 : caraBermain(); break;
            case 3 : skorTertinggi(); break;
            case 4 : tentang(); break;
            case 5 : return 0; break;

            default: printf("Pilihan Tidak ada !\n"); break;
        }
        
        printf("\nKembali ke menu (y/n) ? : ");
        scanf("%s", &ulangi);
    }while (ulangi == 'y' || ulangi == 'Y');
}
