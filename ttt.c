#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include<time.h>
#include <stdbool.h>

void menu();
	void game();
	
	//modul setting
	void pilihPapan();
	void pilihMode();
	void inputNama(int index);
	void pilihRonde();
	
	//modul game berlanggsung	
	void resetKotak(int nomor);
	void resetSkor();
	void tampilSkor();
	void tampilGiliran(int giliran);
	int isiAcak(int no);
	bool isiKotak(int giliran,int kotak, int pilihan);
	bool cekStatusKotak(int kotak);
	bool gantiGiliran(int giliran);
	bool cekGaris(int giliran,int grid);
	void showJuara();
	
	// modul papan
	void papan1();
	void papan2();
	void papan3();
	
	// modul waktu
	int StartTime();
	int EndTime();
	
	void gotoxy(int x, int y)
	
void caraBermain();
void skorTertinggi();
void tentang();



typedef struct 
{
	int kunci;
	char nama[20];
	int skor;
	bool status;
}Player;

typedef struct
{
	bool status;
	char level[10];
	int skor;
	bool active;
}Komputer;

typedef struct {
	int pola;
	char xy[9][9];
	int ordoDone[9][9];
	int ordoStatus[9][9];
	bool status;
	int waktu;
	int ronde;
} Kotak;

// variabel Global
Player User[2];
Komputer bot = {};
Kotak papan = {};

int i,j,
	pilihan;


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
	for (i = 0; i < index; i++){
		gotoxy(0,1+i); printf("> Masukan Nama Pemain (Player ke-%d): ", i+1);
		scanf("%s", &User[i].nama);
		User[i].kunci = i;
	}	
	User[1].kunci=1;
}

int pilihLevel(){
	bot.active = false;
	do{
		system("cls");
		gotoxy(15,0); printf("Pilih Mode");
		gotoxy(0,2); printf("1. Mudah");
		gotoxy(0,3); printf("2. Sedang");
		gotoxy(0,4); printf("3. Sulit");
		gotoxy(0,5); printf("4. Vs Player");
		gotoxy(0,7); printf(">  Pilih Tingkat Kesulitan : ");
		scanf("%d",&pilihan);
		if(pilihan > 0 && pilihan < 4){
			bot.active = true;
		}
		if(pilihan > 4 || pilihan < 0){
			printf("\n   Masukan pilihan antara 1 - 4 !!!\n");
			system("Pause");
		}
	}while(pilihan > 4 || pilihan < 0);

	return pilihan;
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

int pilih(){

	bot.active = false;
	
	do{
		system("cls");
		printf("||===========   Level   ===========||\n");
		printf("|| 1) Easy                         ||\n");
		printf("|| 2) Medium                       ||\n");
		printf("|| 3) Hard                         ||\n");
		printf("|| 4) VS Player                    ||\n");
		printf("||=================================||\n\n\n");
		printf("Masukan level : ");
		scanf("%d", &pilihan);
		if(pilihan != 4){
			bot.active = true;
		}
	}while(pilihan > 4 || pilihan < 0);
	
	return pilihan;
}

void resetKotak(int nomor){
	int i,j,noKotak=1;
	
	switch(nomor){
		case 1:
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){    
					papan.xy[i][j] = '-';
					papan.ordoDone[i][j] = noKotak;
					papan.ordoStatus[i][j] = 0;
					noKotak++;
				}
			}
			break;
			
		case 2:
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){    
					papan.xy[i][j] = '-';
					papan.ordoDone[i][j] = noKotak;
					papan.ordoStatus[i][j] = 0;
					noKotak++;
				}
			}
			break;
			
		case 3:
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){    
					papan.xy[i][j] = '-';
					papan.ordoDone[i][j] = noKotak;
					papan.ordoStatus[i][j] = 0;
					noKotak++;
				}
			}
			break;
	}
}

void pilihRonde(){
	bool salah=false;
	
	do{
		system("cls");
		gotoxy(15,0); printf(" Pilih Ronde \n");
		gotoxy(0,3); printf("1. 1 Ronde");
		gotoxy(0,4); printf("2. 3 Ronde");
		gotoxy(0,5); printf("3. 5 Ronde");

		if(salah==true){		
			gotoxy(0,7); printf("Pilih Ronde Dari Nomor 1 - 3 !\n");
		} 

		gotoxy(0,6); printf("> Pilih Nomor Ronde : ");
		scanf("%d",&papan.ronde);
		switch (papan.ronde){
			case 1 : papan.ronde = 1; break;
			case 2 : papan.ronde = 3; break;
			case 3 : papan.ronde = 5; break;
			default : break;
		}

		if(papan.ronde % 2 == 0 && papan.ronde < 6) 
			salah=true;

	}while(papan.ronde % 2 == 0 && papan.ronde < 6);
	
}

void resetSkor(){
	User[0].skor = 0;
	User[1].skor = 0;
}

void tampilSkor(){
	gotoxy(35,2); printf("Skor");
	if(bot.active == false){
		gotoxy(35,0); printf("%s", User[0].nama);
		gotoxy(45,0); printf(" [X] : %d", User[0].skor);
		gotoxy(35,1); printf("%s", User[1].nama);
		gotoxy(45,1); printf(" [O] : %d", User[1].skor);
	}else{
		gotoxy(35,0); printf("%s", User[0].nama);
		gotoxy(45,0); printf(" [X] : %d", User[0].skor);
		gotoxy(35,1); printf("Komputer");
		gotoxy(45,1); printf(" [O] : %d", User[1].skor);
	}
}

void tampilGiliran(int giliran){
	gotoxy(60,3); printf("Giliran %s", User[giliran].nama);
}

int isiAcak(int no){
	switch(no){
		case 1: return rand() % 9 + 1; break;		
		case 2: return rand() % 25 + 1; break;			
		case 3: return rand() % 49 + 1; break;			
	}
}

int StartTime() {
    clock_t startInput;
    startInput = clock();

    return startInput;
}

int EndTime() {
    clock_t endInput;
    endInput = clock();

    return endInput;
}

bool isiKotak(int giliran,int grid,int pilihan){
	int batasWaktuInput;
	int pilih,noGrid=1,t;
	bool errorPilih=false;
	double waktuInput = 0;
	
	if(pilihan == 1){
		batasWaktuInput = 10;
	} else if(pilihan == 2){
		batasWaktuInput = 5;
	} else if(pilihan == 3){
		batasWaktuInput = 3;
	} else {
		batasWaktuInput = 10;
	}
	
	
	if(bot.active == true && User[giliran].kunci == 1){
		pilih = isiAcak(grid);
	}else{
		
		t = StartTime();
		
		gotoxy(0,12); printf("Masukan nomor grid yang akan diisi : ");
		scanf("%d",&pilih);
		
		t = EndTime() - t;
		
		waktuInput = ((double) t)/CLOCKS_PER_SEC;
		
		if(waktuInput>batasWaktuInput){
			gotoxy(0,13); ("Anda Melebihi Batas Waktu Lebih Dari %d Detik, Giliran di Ganti",batasWaktuInput);
			gotoxy(0,14); printf("\nWaktu Anda Adalah %2.f Detik", waktuInput);			
			Sleep(3000);
			return errorPilih;
		}
	}

	switch(grid){
		case 1:
			if(pilih > 9 || pilih < 0){
				errorPilih = true;
			}else{
				errorPilih = false;
			}
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){			
					if(pilih == papan.ordoStatus[i][j]){
						errorPilih = true;
					}else if(pilih == papan.ordoDone[i][j] && User[giliran].kunci == 0){
						papan.xy[i][j] = 'X';
						papan.ordoDone[i][j] = 0;
						papan.ordoStatus[i][j] = pilih;
					}else if(pilih == papan.ordoDone[i][j] && User[giliran].kunci == 1){
						papan.xy[i][j] = 'O';
						papan.ordoDone[i][j] = 100;
						papan.ordoStatus[i][j] = pilih;
					}
				}
			}
			break;
			
		case 2:
			if(pilih > 25 || pilih < 0){
				errorPilih = true;
			}else{
				errorPilih = false;
			}
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){			
					if(pilih == papan.ordoStatus[i][j]){
						errorPilih = true;
					}else if(pilih == papan.ordoDone[i][j] && User[giliran].kunci == 0){
						papan.xy[i][j] = 'X';
						papan.ordoDone[i][j] = 0;
						papan.ordoStatus[i][j] = pilih;
					}else if(pilih == papan.ordoDone[i][j] && User[giliran].kunci == 1){
						papan.xy[i][j] = 'O';
						papan.ordoDone[i][j] = 100;
						papan.ordoStatus[i][j] = pilih;
					}
				}
			}
			break;
			
		case 3:
			if(pilih > 49 || pilih < 0){
				errorPilih = true;
			}else{
				errorPilih = false;
			}
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){			
					if(pilih == papan.ordoStatus[i][j]){
						errorPilih = true;
					}else if(pilih == papan.ordoDone[i][j] && User[giliran].kunci == 0){
						papan.xy[i][j] = 'X';
						papan.ordoDone[i][j] = 0;
						papan.ordoStatus[i][j] = pilih;
					}else if(pilih == papan.ordoDone[i][j] && User[giliran].kunci == 1){
						papan.xy[i][j] = 'O';
						papan.ordoDone[i][j] = 100;
						papan.ordoStatus[i][j] = pilih;
					}
				}
			}
			break;
	}
	
	

	return errorPilih;
}

bool cekStatusKotak(int kotak){
	int noKotak=1, hasil=0;
	
	switch(kotak){
		case 1:
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){					

					if(papan.ordoStatus[i][j] == noKotak) hasil++;
					noKotak++;					

				}
			}
			
			if(hasil == 9) return false;
				else return true;
			break;
			
		case 2:
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){
					
					if(papan.ordoStatus[i][j] == noKotak) hasil++;
					noKotak++;
					
				}
			}
			
			if(hasil == 25) return false;
				else return true;
			break;
			
		case 3:
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){
					
					if(papan.ordoStatus[i][j] == noKotak) hasil++;
					noKotak++;
					
				}
			}
			
			if(hasil == 49) return false;
				else return true;
			break;
	}
}

bool gantiGiliran(int giliran){
	if(giliran == 0){
		User[giliran].status = false;
		return true;
	}else{
		User[giliran].status = false;
		return false;
	}
}

bool cekGaris(int giliran,int grid){
	bool ronde=false;
	int putaran,miringkanan;
	
	switch(grid){
		case 1:
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){					
					if((papan.ordoDone[i][0] == papan.ordoDone[i][1] && papan.ordoDone[i][1] == papan.ordoDone[i][2]) ||
					(papan.ordoDone[0][j] == papan.ordoDone[1][j] && papan.ordoDone[1][j] == papan.ordoDone[2][j]) || 
					(papan.ordoDone[0][0] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][2]) ||
					(papan.ordoDone[0][2] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][0]) ){	
						ronde = true;
						if(User[giliran].kunci == 0) User[1].skor++;
							else User[0].skor++;
						resetKotak(1);
					}
				}
			}
			break;
			
		case 2:
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){					
					if((papan.ordoDone[i][0] == papan.ordoDone[i][1] && papan.ordoDone[i][1] == papan.ordoDone[i][2]) ||
					(papan.ordoDone[0][j] == papan.ordoDone[1][j] && papan.ordoDone[1][j] == papan.ordoDone[2][j]) || 
					(papan.ordoDone[0][0] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][2]) ||
					(papan.ordoDone[0][2] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][0]) ){	
						ronde = true;
						if(User[giliran].kunci == 0) User[1].skor++;
							else User[0].skor++;
						resetKotak(1);
					}
				}
			}
			break;
			
		case 3:
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){		
				
					for(putaran=0;putaran<3;putaran++){
						if(
						//horizontal
						(papan.ordoDone[i][0+putaran] == papan.ordoDone[i][1+putaran] && papan.ordoDone[i][1+putaran] == papan.ordoDone[i][2+putaran] &&
				 		papan.ordoDone[i][2+putaran] == papan.ordoDone[i][3+putaran] && papan.ordoDone[i][3+putaran] == papan.ordoDone[i][4+putaran])||
				 		
				 		//vertikal
						(papan.ordoDone[0+putaran][j] == papan.ordoDone[1+putaran][j] && papan.ordoDone[1+putaran][j] == papan.ordoDone[2+putaran][j] &&
						papan.ordoDone[2+putaran][j] == papan.ordoDone[3+putaran][j] && papan.ordoDone[3+putaran][j] == papan.ordoDone[4+putaran][j])|| 
						
						//miring
						(papan.ordoDone[0+putaran][0+putaran] == papan.ordoDone[1+putaran][1+putaran] && papan.ordoDone[1+putaran][1+putaran] == papan.ordoDone[2+putaran][2+putaran] &&
						papan.ordoDone[2+putaran][2+putaran] == papan.ordoDone[3+putaran][3+putaran] && papan.ordoDone[3+putaran][3+putaran] == papan.ordoDone[4+putaran][4+putaran]) ||
						
						(papan.ordoDone[0+putaran][6-putaran] == papan.ordoDone[1+putaran][5-putaran] && papan.ordoDone[1+putaran][5-putaran] == papan.ordoDone[2+putaran][4-putaran] &&
						papan.ordoDone[2+putaran][4-putaran] == papan.ordoDone[3+putaran][3-putaran] && papan.ordoDone[3+putaran][3-putaran] == papan.ordoDone[4+putaran][2-putaran])
						){	ronde = true;
							if(User[giliran].kunci == 0) User[1].skor++;
								else User[0].skor++;
							resetKotak(3);
						}			
					}
					
					for(putaran=0;putaran<2;putaran++){
						if(
						//miring 2 kali
						(papan.ordoDone[0+putaran][1+putaran] == papan.ordoDone[1+putaran][2+putaran] && papan.ordoDone[1+putaran][2+putaran] == papan.ordoDone[2+putaran][3+putaran] &&
						papan.ordoDone[2+putaran][3+putaran] == papan.ordoDone[3+putaran][4+putaran] && papan.ordoDone[3+putaran][4+putaran] == papan.ordoDone[4+putaran][5+putaran]) ||
						
						(papan.ordoDone[1+putaran][0+putaran] == papan.ordoDone[2+putaran][1+putaran] && papan.ordoDone[2+putaran][1+putaran] == papan.ordoDone[3+putaran][2+putaran] &&
						papan.ordoDone[3+putaran][2+putaran] == papan.ordoDone[4+putaran][3+putaran] && papan.ordoDone[4+putaran][3+putaran] == papan.ordoDone[5+putaran][4+putaran]) ||
						
						(papan.ordoDone[0+putaran][5-putaran] == papan.ordoDone[1+putaran][4-putaran] && papan.ordoDone[1+putaran][4-putaran] == papan.ordoDone[2+putaran][3-putaran] &&
						papan.ordoDone[2+putaran][3-putaran] == papan.ordoDone[3+putaran][2-putaran] && papan.ordoDone[3+putaran][2-putaran] == papan.ordoDone[4+putaran][1-putaran]) ||
						
						(papan.ordoDone[1+putaran][6-putaran] == papan.ordoDone[2+putaran][5-putaran] && papan.ordoDone[2+putaran][5-putaran] == papan.ordoDone[3+putaran][4-putaran] &&
						papan.ordoDone[3+putaran][4-putaran] == papan.ordoDone[4+putaran][3-putaran] && papan.ordoDone[4+putaran][3-putaran] == papan.ordoDone[5+putaran][2-putaran])
						){
						ronde = true;
							if(User[giliran].kunci == 0) User[1].skor++;
								else User[0].skor++;
							resetKotak(3);
						}
					}
					
					for(putaran=0;putaran<=2;putaran+=2){
						if(
						//miring 1 kali
						(papan.ordoDone[0+putaran][2-putaran] == papan.ordoDone[1+putaran][3-putaran] && papan.ordoDone[1+putaran][3-putaran] == papan.ordoDone[2+putaran][4-putaran] &&
						papan.ordoDone[2+putaran][4-putaran] == papan.ordoDone[3+putaran][5-putaran] && papan.ordoDone[3+putaran][5-putaran] == papan.ordoDone[4+putaran][6-putaran]) ||
						
						(papan.ordoDone[0+putaran][4+putaran] == papan.ordoDone[1+putaran][3+putaran] && papan.ordoDone[1+putaran][3+putaran] == papan.ordoDone[2+putaran][2+putaran] &&
						papan.ordoDone[2+putaran][2+putaran] == papan.ordoDone[3+putaran][1+putaran] && papan.ordoDone[3+putaran][1+putaran] == papan.ordoDone[4+putaran][0+putaran])
						){
						ronde = true;
							if(User[giliran].kunci == 0) User[1].skor++;
								else User[0].skor++;
							resetKotak(3);
						}
					}
					
				}
			}
			break;		
	}
	
	return ronde;
}

void showJuara(){
	char pilihan='N';

	system("cls");
	gotoxy(15,0); printf("Juara");
	
	if(bot.active == true && (User[1].skor > User[0].skor)){
		gotoxy(7,3); printf("Juaranya adalah : Komputer");
		gotoxy(7,4); printf("Score           : %d - %d",User[1].skor,User[0].skor);
	}else if(User[1].skor > User[0].skor){
		gotoxy(7,3); printf("Juaranya adalah : %s\n",User[1].nama);
		gotoxy(7,4); printf("Score           : %d - %d\n",User[1].skor,User[0].skor);
	}else{
		gotoxy(7,3); printf("Juaranya adalah : %s\n",User[0].nama);
		gotoxy(7,4); printf("Score           : %d - %d\n",User[0].skor,User[1].skor);
	}

}

void game(){
	int s,vsBot = 1;
	bool gameOver = false;
	pilihPapan();
	if(pilihLevel() == 4){
		vsBot = 2;
	}
	inputNama(vsBot);
	pilihRonde();
	
	system("cls");
	do{
		switch(papan.pola){
			case 1:
				papan1(); break;
			case 2:
				papan2(); break;
			case 3:
				papan3(); break;
			default: break;
		}
	}while(gameOver);
	
}

void papan1(){
	int giliran=0,ronde=0;
	bool errorPilih=false;

	resetKotak(1);
	resetSkor ();
	do{
		do{
			system("cls");
			tampilSkor();
			tampilGiliran(giliran);
			gotoxy(13,1); printf("Ronde   : %d\n",ronde+1);
			gotoxy(15,0); printf("Papan 3x3");
			gotoxy(10,2); printf("-------------------");
			gotoxy(10,3); printf("|1 %c	|2 %c  |3 %c  |", papan.xy[0][0], papan.xy[0][1], papan.xy[0][2]);
			gotoxy(10,4); printf("-------------------");
			gotoxy(10,5); printf("|4 %c	|5 %c  |6 %c  |", papan.xy[1][0], papan.xy[1][1], papan.xy[1][2]);
			gotoxy(10,6); printf("-------------------");
			gotoxy(10,7); printf("|7 %c	|8 %c  |9 %c  |", papan.xy[2][0], papan.xy[2][1], papan.xy[2][2]);
			gotoxy(10,8); printf("-------------------");
			if(errorPilih==true){
				gotoxy(0,11); printf("Nomor tidak ada atau sudah diisi! ");
			}
			errorPilih = isiKotak(giliran,1,pilihan);
		}while(errorPilih == true);
		
		if(cekStatusKotak(1) == false){
			resetKotak(1);
		}
		
		if(gantiGiliran(giliran) == true){
			giliran++;
		}else{
			giliran--;
		}
		
		if(cekGaris(giliran,1) == true)ronde++;
	}while(ronde < papan.ronde);
	showJuara(giliran);
}

void papan2(){
	int giliran=0,ronde=0;
	bool errorPilih=false;

	resetKotak(2);
	resetSkor();
	do{
		do{
			system("cls");
			tampilSkor();
			tampilGiliran(giliran);
			gotoxy(13,1); printf("Ronde   : %d\n",ronde+1);
			gotoxy(15,0); printf("Papan 5x5");		
			
			gotoxy(10,2); printf("---------------------------------");
			gotoxy(10,3); printf("|1 %c	|2 %c   |3 %c   |4 %c  |5 %c  |", papan.xy[0][0], papan.xy[0][1], papan.xy[0][2], papan.xy[0][3], papan.xy[0][4]);
			gotoxy(10,4); printf("|6 %c	|7 %c   |8 %c   |9 %c  |10 %c |",papan.xy[1][0], papan.xy[1][1], papan.xy[1][2], papan.xy[1][3], papan.xy[1][4]);
			gotoxy(10,5); printf("|11 %c	|12 %c  |13 %c  |14 %c |15 %c |",papan.xy[2][0], papan.xy[2][1], papan.xy[2][2], papan.xy[2][3], papan.xy[2][4]);
			gotoxy(10,6); printf("|16 %c	|17 %c  |18 %c  |19 %c |20 %c |",papan.xy[3][0], papan.xy[3][1], papan.xy[3][2], papan.xy[3][3], papan.xy[3][4]);
			gotoxy(10,7); printf("|21 %c	|22 %c  |23 %c  |24 %c |25 %c |",papan.xy[4][0], papan.xy[4][1], papan.xy[4][2], papan.xy[4][3], papan.xy[4][4]);
			gotoxy(10,8); printf("---------------------------------");
			
			if(errorPilih==true){
				gotoxy(0,11); gotoxy(0,11); printf("Nomor tidak ada atau sudah diisi! ");
			}
			errorPilih = isiKotak(giliran,2,pilihan);
			
		}while(errorPilih == true);
		if(cekStatusKotak(2) == false) resetKotak(2); 
		if(gantiGiliran(giliran) == true) giliran++;
			else giliran--;
		if(cekGaris(giliran,2) == true)ronde++;
	}while(ronde < papan.ronde);
	showJuara();
}

void papan3(){
	int giliran=0,ronde=0;
	bool errorPilih=false;

	resetKotak(3);
	resetSkor();
	do{
		do{
			system("cls");
			tampilSkor();
			tampilGiliran(giliran);
			gotoxy(13,1); printf("Ronde   : %d\n",ronde+1);
			gotoxy(15,0); printf("Papan 7x7");
			
			gotoxy(10,2); printf("---------------------------------------------");
			gotoxy(10,3); printf("|1 %c	|2 %c   |3 %c   |4 %c  |5 %c  |6 %c  |7 %c  |", papan.xy[0][0], papan.xy[0][1], papan.xy[0][2], papan.xy[0][3], papan.xy[0][4],papan.xy[0][5], papan.xy[0][6]);
			gotoxy(10,4); printf("|8 %c	|9 %c   |10 %c  |11 %c |12 %c |13 %c |14 %c |", papan.xy[1][0], papan.xy[1][1], papan.xy[1][2], papan.xy[1][3], papan.xy[1][4],papan.xy[1][5], papan.xy[1][6]);
			gotoxy(10,5); printf("|15 %c	|16 %c  |17 %c  |18 %c |19 %c |20 %c |21 %c |", papan.xy[2][0], papan.xy[2][1], papan.xy[2][2], papan.xy[2][3], papan.xy[2][4],papan.xy[2][5], papan.xy[2][6]);
			gotoxy(10,6); printf("|22 %c	|23 %c  |24 %c  |25 %c |26 %c |27 %c |28 %c |", papan.xy[3][0], papan.xy[3][1], papan.xy[3][2], papan.xy[3][3], papan.xy[3][4],papan.xy[3][5], papan.xy[3][6]);
			gotoxy(10,7); printf("|29 %c	|30 %c  |31 %c  |32 %c |33 %c |34 %c |35 %c |", papan.xy[4][0], papan.xy[4][1], papan.xy[4][2], papan.xy[4][3], papan.xy[4][4],papan.xy[4][5], papan.xy[4][6]);
			gotoxy(10,8); printf("|36 %c	|37 %c  |38 %c  |39 %c |40 %c |41 %c |42 %c |", papan.xy[5][0], papan.xy[5][1], papan.xy[5][2], papan.xy[5][3], papan.xy[5][4],papan.xy[5][5], papan.xy[5][6]);
			gotoxy(10,9); printf("|43 %c	|44 %c  |45 %c  |46 %c |47 %c |48 %c |49 %c |", papan.xy[6][0], papan.xy[6][1], papan.xy[6][2], papan.xy[6][3], papan.xy[6][4],papan.xy[6][5], papan.xy[6][6]);
			gotoxy(10,10); printf("---------------------------------------------");
			
			if(errorPilih==true){
				gotoxy(0,11); printf("Nomor tidak ada atau sudah diisi!\n");
			} 
			errorPilih = isiKotak(giliran,3,pilihan);
			
		}while(errorPilih == true);
		if(cekStatusKotak (3) == false)resetKotak(3); 
		if(gantiGiliran(giliran) == true) giliran++;
			else giliran--;
		if(cekGaris(giliran,3) == true)ronde++;
	}while(ronde < papan.ronde);
	showJuara();
}

void caraBermain(){
	system("CLS");
	printf("                Cara Bermain\n") ;
	printf("1. Setelah Player menentukan papan dan nama, selanjutnya pemain menentukan mode permainan.\n") ;
	printf("2. Saat game berlansung player memasukan nomor kotak yang ingin diisi dengan syarat kotak yang diisi belum diisi oleh lawan. Setiap giliran hanya bisa menginput satu simbol.\n") ;
	printf("3. Teruslah bergiliran mengisi simbol masing masing sampai salah satu pemain telah menggambar tiga atau lebih simbol yang sama secara berderet atau dinyatakan seri apabila tidak ada simbol yang berderet namun semua kotak sudah penuh.\n");
	
}

void skorTertinggi(){
	system("CLS");
	gotoxy(15,0); printf("Skor Tertinggi");
	if(User[0].skor > User[1].skor){		
		gotoxy(0,2); printf("%s\t	: %d", User[0].nama, User[0].skor);
		gotoxy(0,3); printf("%s\t	: %d", User[1].nama, User[1].skor);
	}else{
		gotoxy(0,2); printf("%s\t	: %d", User[1].nama, User[1].skor);
		gotoxy(0,3); printf("%s\t	: %d", User[0].nama, User[0].skor);
	}
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
            case 1 : game(); break;
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
