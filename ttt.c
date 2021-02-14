#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

void gotoxy(int x, int y) {
    COORD coord;
     
    coord.X = x;
    coord.Y = y;
     
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//procedure
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

void pilihMode(){
	int pilihan;
	
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
		
		
		gotoxy(0,12);printf("> Masukan Pilihan (1-3) : ");
		scanf("%d", &pilihan);
	}while(pilihan > 3);
	
}
void bermain(){
	system("CLS");
	printf("INI BERMAIN\n");
	
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

//fungsi
int main(){
    int pilih;
    char ulangi;

	//repeat until
    do{
        menu();
        printf("Pilih Menu dari [1-5] : ");
        scanf("%d", &pilih);

        switch (pilih){
            case 1 : pilihMode(); break;
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
