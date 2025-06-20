#include "menu.h"
#include "spesifikasi.h"
#include "morse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_screen() { 
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause(const char* message) { 
    printf("\n%s", message);
    printf("Tekan Enter untuk melanjutkan..."); 
    while (getchar() != '\n'); 
    getchar();
}

void print_welcome() {
    clear_screen();
    printf("===============================================\n");
    printf("      PROGRAM KONVERSI SANDI MORSE     \n");
    printf("===============================================\n");
}

void print_goodbye() {
    clear_screen();
    printf("===============================================\n");
    printf("      TERIMA KASIH TELAH MENGGUNAKAN PROGRAM    \n");
    printf("===============================================\n");
}

void print_morse_table() {
    printf("\n╔════════════════════════════════════════════╗");
    printf("\n║               TABEL SANDI MORSE            ║");
    printf("\n╠══════════╦══════════╦══════════╦═══════════╣");
    printf("\n║ Karakter ║   Kode   ║ Karakter ║   Kode    ║");
    printf("\n╠══════════╬══════════╬══════════╬═══════════╣");
    printf("\n║    A     ║    !     ║    S     ║   ?!!     ║");
    printf("\n║    B     ║    ?     ║    O     ║   ?!?     ║");
    printf("\n║    K     ║   !!     ║    P     ║   ??""!   ║");
    printf("\n║    Z     ║   !?     ║    Q     ║   ???     ║");
    printf("\n║    M     ║   ?!     ║    I     ║  !!!!     ║");
    printf("\n║    N     ║   ??     ║    V     ║  !!!?     ║");
    printf("\n║    G     ║  !!!     ║    F     ║  !!""?!   ║"); 
    printf("\n║    H     ║  !!?     ║    L     ║  !!""??   ║"); 
    printf("\n║    T     ║  !?!     ║    W     ║  !?""!!   ║"); 
    printf("\n║    R     ║  !??     ║    5     ║  !?""!?   ║"); 
    printf("\n║  SPASI   ║ !?""!??  ║    2     ║  ?""!!!!  ║"); 
    printf("\n║    E     ║  ?""!!!  ║    7     ║  ??""!!!  ║"); 
    printf("\n║    D     ║  ?""!!?  ║    6     ║  ?""?""?""!!║"); 
    printf("\n╚══════════╩══════════╩══════════╩═══════════╝");
    printf("\n\nCatatan: ! = titik (dot), ? = strip (dash)\n");
}

void show_menu() {
    MorseTree morseTree;
    buildMorseTree(&morseTree);
    
    int choice;
    do {
        print_welcome();
        printf("MENU UTAMA:\n");
        printf("1. Tampilkan Hasil Transversal Inorder\n");
        printf("2. Konversi Teks ke Morse\n");
        printf("3. Konversi Morse ke Teks\n");
        printf("4. Konversi File (input.txt -> out.txt)\n");
        printf("5. Tampilkan Tabel Sandi Morse\n");
        printf("6. Keluar\n");
        printf("\nPilihan Anda: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = 0;
        }
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                clear_screen();
                printf("DAFTAR KARAKTER YANG DIDUKUNG:\n");
                InOrder(&morseTree, 1);
                pause("");
                break;
                
            case 2: {
                clear_screen();
                char text[256], morse[1024];
                printf("KONVERSI TEKS KE SANDI MORSE\n");
                printf("Masukkan teks (maks 255 karakter):\n> ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';
                
                encodeToMorse(text, morse, &morseTree);
                printf("\nHasil Konversi:\n");
                printf("Teks  : %s\n", text);
                printf("Morse : %s\n", morse);
                pause("\nKonversi selesai!\n");
                break;
            }
                
            case 3: {
                clear_screen();
                char morse[1024], text[256];
                printf("KONVERSI SANDI MORSE KE TEKS\n");
                printf("Masukkan kode morse (pisahkan dengan spasi):\n> ");
                fgets(morse, sizeof(morse), stdin);
                morse[strcspn(morse, "\n")] = '\0';
                
                decodeFromMorse(morse, text, &morseTree);
                printf("\nHasil Konversi:\n");
                printf("Morse : %s\n", morse);
                printf("Teks  : %s\n", text);
                pause("\nKonversi selesai!\n");
                break;
            }
                
            case 4: {
                clear_screen();
                printf("KONVERSI FILE TEKS KE MORSE\n");
                printf("Pastikan file 'input.txt' ada di direktori ini\n");
                
                FILE *input = fopen("input.txt", "r");
                if (!input) {
                    printf("\nERROR: File input.txt tidak ditemukan!\n");
                    printf("Silakan buat file teks bernama 'input.txt'\n");
                    pause("");
                    break;
                }
                
                FILE *out = fopen("out.txt", "w");
                if (!out) {
                    printf("\nERROR: Gagal membuat output.txt!\n");
                    fclose(input);
                    pause("");
                    break;
                }
                
                char line[256];
                int line_count = 0;
                while (fgets(line, sizeof(line), input)) {
                    line[strcspn(line, "\n")] = '\0';
                    char morse[1024] = {0}; 
                    encodeToMorse(line, morse, &morseTree);
                    fprintf(out, "%s\n", morse); 
                    line_count++;
                }
                
                fclose(input);
                fclose(out);
                
                printf("\nSUKSES: Konversi file berhasil!\n");
                printf(" - %d baris diproses\n", line_count);
                printf(" - Hasil disimpan di 'output.txt'\n");
                pause("");
                break;
            }
                
            case 5:
                clear_screen();
                print_morse_table();
                pause("");
                break;
                
            case 6:
                Clear_tree(&morseTree);
                print_goodbye();
                return;
                
            default:
                printf("\nPilihan tidak valid! Silakan pilih 1-6.\n");
                pause("");
        }
    } while (1);
}