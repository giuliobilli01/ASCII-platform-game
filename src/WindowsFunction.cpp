#include"WindowsFunction.h"

HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

/**
 * @brief imposta i parametri del cursore della console in modo da non essere visibile
 *
 */
void setcursor() {
   HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = false;
    lpCursor.dwSize = 1;
    SetConsoleCursorInfo(console, &lpCursor);
}

/**
 * @brief permette di spostare il cursore nelle coordinate inserite, 
 *        si ricorda che le coordinate dello schermo hanno lo (0,0) in alto a sinistra ,andando in giù aumenta la y
 *        e andando a destra aumenta la x 
 *
 * @param x
 * @param y
 */
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
        coord); // setta la nuova posizione del cursore
}

/**
 * @brief setta le dimensioni della console in cui viene visualizzato il gioco
 *
 * @param W_console
 * @param H_console
 */
void set_console_size(int W_console, int H_console) {
    COORD dim;
    dim.X = W_console;
    dim.Y = H_console;
    SMALL_RECT rect = { 0, 0, (SHORT)W_console, (SHORT)H_console };

    SetConsoleScreenBufferSize(h_console, dim);
    SetConsoleWindowInfo(h_console, TRUE, &rect);
}

/**
 * @brief chiama le funzioni necessarie all'inizializzazione della schermata di gioco:
 *          - set_console_size ridimensiona la console con le dimensioni inserite
 *          - setcursor imposta i parametri del cursore
 * @param W_console
 * @param H_console
 */
void init_console(int W_console, int H_console) {
    system("cls");
    set_console_size(W_console, H_console);
    setcursor();
}

/**
 * @brief una versione del getch che non ferma l'esecuzione mentre aspetta un input
 * 
 * @param input 
 */
void non_blocking_getch(char *input) {
    if(kbhit()){
        *input = getch();
    }
    else{
        for(int i=0;i<20000000;i++) {
        }
        *input = '1';
    }
}