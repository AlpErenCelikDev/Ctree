#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>

// Ses kütüphanesini otomatik baðlamak için (Visual Studio vb. için)
#pragma comment(lib, "winmm.lib")

// RENK VE ÝMLEÇ KONTROL ÞÝFRELERÝ (ANSI)
#define RESET       "\033[0m"
#define GREEN       "\033[1;32m"
#define RED         "\033[1;31m"
#define YELLOW      "\033[1;33m"
#define CYAN        "\033[1;36m"
#define MAGENTA     "\033[1;35m"
#define BROWN       "\033[0;33m"
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

// FONKSÝYON PROTOTÝPLERÝ
void tree();
void clean();
void bekle(int milisaniye);

int main(void) {
    srand(time(NULL));
    
    // 1. Konsol ekranýndaki eski yazýlarý temizle ve imleci gizle
    system("cls");
    printf(HIDE_CURSOR);
    
    // 2. Ayný klasördeki "muzik.wav" dosyasýný arka planda döngüye sokarak çal
    PlaySound(TEXT("muzik.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    
    // 3. Animasyon Döngüsü
    while(1) {
        tree();         // Aðacý Çiz
        bekle(300);     // 300ms Bekle (Iþýk çakma hýzý)
        clean();        // Titremeyi önleyerek imleci baþa al
        
        // Eðer klavyeden herhangi bir tuþa basýlýrsa döngüyü bitir
        if (_kbhit()) {
            break;
        }
    }
    
    // 4. Çýkýþ Ýþlemleri
    PlaySound(NULL, 0, 0); // Müziði durdur
    printf(SHOW_CURSOR);   // Ýmleci tekrar görünür yap
    system("cls");         // Ekraný temizleyerek kapat
    
    return 0;
}

void tree() {
    // Tepe Yýldýzý
    for(int k = 15; k > 0; k--) printf(" ");
    printf(YELLOW "*\033[K\n" RESET);

    // Aðaç Yapraklarý ve Iþýklar
    for (int i = 0; i < 15; i++) {
        for(int k = 15 - i; k > 0; k--) {
            printf(" ");
        }
        
        for (int j = 1; j <= (2*i + 1); j++) {
            int luck = rand() % 15;
            
            if (luck == 0) {
                printf(RED "*" RESET);
            }
            else if (luck == 1) {
                printf(YELLOW "*" RESET);
            }
            else if (luck == 2) {
                printf(CYAN "*" RESET);
            }
            else if (luck == 3) {
                printf(MAGENTA "*" RESET);
            }
            else {
                printf(GREEN "^" RESET);
            }
        }
        // Satýr Silgisi: Alt satýra geçerken saðda kalan çöp karakterleri siler
        printf("\033[K\n");
    }
    
    // Aðaç Gövdesi
    for(int j = 0; j < 4; j++) {
        for (int i = 0; i < 13; i++) {
            printf(" ");
        }
        printf(BROWN "=====" RESET "\033[K\n");
    }
    
    // Aðacýn altýnda kalan alaný süpür
    printf("\033[J");
}

void clean() {
    // Ýmleci en sol üst köþeye ýþýnlar (Titreþimi sýfýrlar)
    printf("\033[H");
}

void bekle(int milisaniye) {
    if (milisaniye <= 0) return;
    Sleep(milisaniye); // Windows kütüphanesini kullandýðýmýz için doðrudan Sleep
}
