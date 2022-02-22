#include "Level.hpp"

/**
 * @brief Costruttore della classe Level, in base al numero del livello che prende in input
 *          viene deciso quale modello di stanza utilizzare in questo oggetto Level.
 * 
 * @param roomNumber numero del livello passato da Levels.
 */
Level::Level(int roomNumber)
{
    this->levelNumber = roomNumber;
    this->isExplorated = false;

    if (roomNumber == 0)
    {
        this->roomNumber = roomNumber;
        this->nextLevel = NULL;
        this->prevLevel = NULL;
        this->emptyRoom();
        this->generateFirstRoom();
    }
    else
    {
        this->roomNumber = roomNumber % 6;
        this->nextLevel = NULL;
        this->prevLevel = NULL;

        if (this->roomNumber == 0)
        {
            this->emptyRoom();
            this->generateMap6();
        }
        else if (this->roomNumber == 1)
        {
            this->emptyRoom();
            this->generateMap1();
        }
        else if (this->roomNumber == 2)
        {
            this->emptyRoom();
            this->generateMap2();
        }
        else if (this->roomNumber == 3)
        {
            this->emptyRoom();
            this->generateMap3();
        }
        else if (this->roomNumber == 4)
        {
            this->emptyRoom();
            this->generateMap4();
        }
        else if (this->roomNumber == 5)
        {
            this->emptyRoom();
            this->generateMap5();
        }
    }
}

/**
 * @brief genera i confini della stanza senza stamparli, le stanze hanno dimensione 20x70,
 *          l'intera schermata di gioco a dimensione 20x120
 *  
 */
void Level::generateBorders()
{
    int X = 0, Y = 0;

    for (Y = 0; Y <= H_CONSOLE - 1; Y++)
    { // genera la mappa mettrendo i contorni del livello
        for (X = 0; X <= W_CONSOLE - 1; X++)
        {
            if ((X == 0) || (Y == 0) || (X == larghezza_max - 1) || (X == W_CONSOLE - 1) || (Y == H_CONSOLE - 1))
                this->room[Y][X] = '#';
        }
    }

    this->setPlayerData();
}

/**
 * @brief Inserisce nella parte destra della matrice della schermata di gioco
 *          i campi dove verranno scritti i dati del giocatore
 * 
 */
void Level::setPlayerData()
{
    this->room[H_CONSOLE - 13][larghezza_max + 3] = 'P';
    this->room[H_CONSOLE - 13][larghezza_max + 4] = 'L';
    this->room[H_CONSOLE - 13][larghezza_max + 5] = 'A';
    this->room[H_CONSOLE - 13][larghezza_max + 6] = 'Y';
    this->room[H_CONSOLE - 13][larghezza_max + 7] = 'E';
    this->room[H_CONSOLE - 13][larghezza_max + 8] = 'R';
    this->room[H_CONSOLE - 13][larghezza_max + 9] = ' ';
    this->room[H_CONSOLE - 13][larghezza_max + 10] = 'D';
    this->room[H_CONSOLE - 13][larghezza_max + 11] = 'A';
    this->room[H_CONSOLE - 13][larghezza_max + 12] = 'T';
    this->room[H_CONSOLE - 13][larghezza_max + 13] = 'A';
    this->room[H_CONSOLE - 13][larghezza_max + 14] = ':';

    this->room[H_CONSOLE - 12][larghezza_max + 3] = 'L';
    this->room[H_CONSOLE - 12][larghezza_max + 4] = 'i';
    this->room[H_CONSOLE - 12][larghezza_max + 5] = 'f';
    this->room[H_CONSOLE - 12][larghezza_max + 6] = 'e';
    this->room[H_CONSOLE - 12][larghezza_max + 7] = ':';
    this->room[H_CONSOLE - 12][larghezza_max + 8] = ' ';

    this->room[H_CONSOLE - 11][larghezza_max + 3] = 'P';
    this->room[H_CONSOLE - 11][larghezza_max + 4] = 'o';
    this->room[H_CONSOLE - 11][larghezza_max + 5] = 'i';
    this->room[H_CONSOLE - 11][larghezza_max + 6] = 'n';
    this->room[H_CONSOLE - 11][larghezza_max + 7] = 't';
    this->room[H_CONSOLE - 11][larghezza_max + 8] = 's';
    this->room[H_CONSOLE - 11][larghezza_max + 9] = ':';
    this->room[H_CONSOLE - 11][larghezza_max + 10] = ' ';

    this->room[H_CONSOLE - 10][larghezza_max + 3] = 'L';
    this->room[H_CONSOLE - 10][larghezza_max + 4] = 'e';
    this->room[H_CONSOLE - 10][larghezza_max + 5] = 'v';
    this->room[H_CONSOLE - 10][larghezza_max + 6] = 'e';
    this->room[H_CONSOLE - 10][larghezza_max + 7] = 'l';
    this->room[H_CONSOLE - 10][larghezza_max + 8] = ':';
    this->room[H_CONSOLE - 10][larghezza_max + 9] = ' ';
}

/**
 * @brief inserisce il carattere in input nella cella senza stamparlo a schermo
 * 
 * @param x la coordinata x dell'elemento inserito 
 * @param y la coordinata y dell'elemento inserito 
 * @param ch il carattere da inserire 
 */
void Level::_add(int x, int y, char ch)
{
    this->room[y][x] = ch;
}

/**
 * @brief inserisce nella cella della matrice di coordinate inserite il carattere in input e lo stampa a schermo
 * 
 * @param x coordinata x della cella in cui inserire il carattere
 * @param y coordinata y della cella in cui inserire il carattere
 * @param ch carattere da inserire
 */
void Level::addElement(int x, int y, char ch)
{
    this->_add(x, y, ch);
    this->printElement(x, y);
}

/**
 * @brief cancella dalla matrice l'elemento presente nella cella 
 *      di coordinate inserite lo sostituisce con uno spazio vuoto e lo stampa a schermo
 * 
 * @param x coordinata x della cella da cancellare
 * @param y coordinata y della cella da cancellare
 */
void Level::deleteElement(int x, int y)
{
    this->_delete(x, y);
    this->printElement(x, y);
}

/**
 * @brief stampa l'intera matrice della schermata di gioco in cui sono presenti la stanza in ci muove il Player
 *          e la parte destra della scheramta dove vengono mostrati i dati del Player.
 *  
 */
void Level::printRoom()
{
    int X = 0, Y = 0;
    system("cls");

    for (Y = 0; Y <= H_CONSOLE - 1; Y++)
    {
        for (X = 0; X <= W_CONSOLE - 1; X++)
        {
            printElement(X, Y);
        }
    }
}

/**
 * @brief inserisce lo spazio nella cella corrispondente alle coordinate inserite
 * 
 * @param x coordinata x della cella da cancellare
 * @param y coordinata y della cella da cancellare
 */
void Level::_delete(int x, int y)
{
    this->room[y][x] = ' ';
}

/**
 * @brief pulisce la matrice della schermata di gioco inserendo '\0' in ogni casella,
 *      in modo da evitare la presenza di caratteri indesiderati presenti nell'area di memoria della matrice
 *  
 */
void Level::emptyRoom()
{
    int X = 0, Y = 0;

    for (Y = 0; Y <= H_CONSOLE - 1; Y++)
    { // inizializza la matrice vuota
        for (X = 0; X <= W_CONSOLE - 1; X++)
        {
            this->room[Y][X] = '\0';
        }
    }
}

/**
 * @brief stampa a schermo l'elemento della cella corrispondente alle coordinate inserite
 *
 * @param x coordinata x della cella 
 * @param y coordianta y della cella
 */
void Level::printElement(int x, int y)
{
    gotoxy(x, y);
    cout << this->room[y][x];
}

/**
 * @brief genera la prima stanza del gioco inserendo nella matrice i suoi elementi, costituita esclusivamente dai bordi della stanza,
 *  questa stanza è presente solo al livello 0
 *  
 */
void Level::generateFirstRoom()
{
    this->generateBorders();
    this->room[H_CONSOLE - 2][larghezza_max - 2] = ')';
}

/**
 * @brief genera il primo modello di stanza inserendo nella matrice i 
 *      suoi elementi, è costituita da piattaforme e ostacoli
 *  
 */
void Level::generateMap1()
{
    int X = 0, Y = 0;
    this->generateBorders();

    this->room[H_CONSOLE - 2][larghezza_max - 69] = '(';
    this->room[H_CONSOLE - 8][larghezza_max - 2] = ')';

    for (X = larghezza_max - 67; X <= larghezza_max - 61; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 50; X <= larghezza_max - 48; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 39; X <= larghezza_max - 32; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    this->room[H_CONSOLE - 3][larghezza_max - 16] = '=';

    for (X = larghezza_max - 68; X <= larghezza_max - 67; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 64; X <= larghezza_max - 61; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 40; X <= larghezza_max - 37; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    this->room[H_CONSOLE - 5][larghezza_max - 16] = '=';

    this->room[H_CONSOLE - 7][larghezza_max - 68] = '=';
    for (X = larghezza_max - 66; X <= larghezza_max - 63; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 38; X <= larghezza_max - 32; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 27; X <= larghezza_max - 22; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 19; X <= larghezza_max - 16; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 13; X <= larghezza_max - 10; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 5; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 7][X] = '=';

    this->room[H_CONSOLE - 9][larghezza_max - 68] = '=';
    for (X = larghezza_max - 65; X <= larghezza_max - 50; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 46; X <= larghezza_max - 44; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 41; X <= larghezza_max - 34; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 24; X <= larghezza_max - 18; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 10; X <= larghezza_max - 5; X++)
        this->room[H_CONSOLE - 9][X] = '=';

    this->room[H_CONSOLE - 11][larghezza_max - 68] = '=';
    for (X = larghezza_max - 58; X <= larghezza_max - 57; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 54; X <= larghezza_max - 50; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 46; X <= larghezza_max - 40; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 25; X <= larghezza_max - 24; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 19; X <= larghezza_max - 16; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 8; X <= larghezza_max - 7; X++)
        this->room[H_CONSOLE - 11][X] = '=';

    for (X = larghezza_max - 68; X <= larghezza_max - 65; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 63; X <= larghezza_max - 54; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 47; X <= larghezza_max - 46; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 43; X <= larghezza_max - 40; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 26; X <= larghezza_max - 24; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 17; X <= larghezza_max - 16; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 8; X <= larghezza_max - 7; X++)
        this->room[H_CONSOLE - 13][X] = '=';

    for (X = larghezza_max - 65; X <= larghezza_max - 61; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 55; X <= larghezza_max - 53; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 48; X <= larghezza_max - 47; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 40; X <= larghezza_max - 36; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 28; X <= larghezza_max - 26; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 16; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 15][X] = '=';

    for (X = larghezza_max - 62; X <= larghezza_max - 16; X++)
        this->room[H_CONSOLE - 17][X] = '=';

    for (X = larghezza_max - 13; X <= larghezza_max - 12; X++)
        this->room[H_CONSOLE - 18][X] = '=';
    for (X = larghezza_max - 3; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 18][X] = '=';

    for (Y = H_CONSOLE - 19; Y <= H_CONSOLE - 17; Y++)
        this->room[Y][larghezza_max - 64] = '|';
    for (Y = H_CONSOLE - 15; Y <= H_CONSOLE - 13; Y++)
        this->room[Y][larghezza_max - 64] = '|';
    for (Y = H_CONSOLE - 12; Y <= H_CONSOLE - 5; Y++)
        this->room[Y][larghezza_max - 49] = '|';
    this->room[H_CONSOLE - 2][larghezza_max - 49] = '|';
    for (Y = H_CONSOLE - 15; Y <= H_CONSOLE - 7; Y++)
        this->room[Y][larghezza_max - 31] = '|';
    for (Y = H_CONSOLE - 19; Y <= H_CONSOLE - 17; Y++)
        this->room[Y][larghezza_max - 14] = '|';
    for (Y = H_CONSOLE - 14; Y <= H_CONSOLE - 2; Y++)
        this->room[Y][larghezza_max - 14] = '|';
}

/**
 * @brief genera il secondo modello di stanza inserendo nella matrice i 
 *      suoi elementi, è costituita da piattaforme e ostacoli
 *  
 */
void Level::generateMap2()
{
    int X = 0, Y = 0;
    this->generateBorders();

    this->room[H_CONSOLE - 8][larghezza_max - 69] = '(';
    this->room[H_CONSOLE - 18][larghezza_max - 2] = ')';

    for (X = larghezza_max - 68; X <= larghezza_max - 65; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 61; X <= larghezza_max - 58; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 52; X <= larghezza_max - 48; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 37; X <= larghezza_max - 31; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 23; X <= larghezza_max - 22; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 10; X <= larghezza_max - 8; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    this->room[H_CONSOLE - 3][larghezza_max - 3] = '=';

    for (X = larghezza_max - 66; X <= larghezza_max - 59; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 50; X <= larghezza_max - 46; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    this->room[H_CONSOLE - 5][larghezza_max - 31] = '=';
    for (X = larghezza_max - 23; X <= larghezza_max - 20; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 18; X <= larghezza_max - 15; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 10; X <= larghezza_max - 9; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 3; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 5][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 63; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 59; X <= larghezza_max - 56; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 53; X <= larghezza_max - 50; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 46; X <= larghezza_max - 44; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 36; X <= larghezza_max - 31; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 25; X <= larghezza_max - 18; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 15; X <= larghezza_max - 9; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 4; X <= larghezza_max - 3; X++)
        this->room[H_CONSOLE - 7][X] = '=';

    for (X = larghezza_max - 63; X <= larghezza_max - 59; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 56; X <= larghezza_max - 55; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 53; X <= larghezza_max - 52; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 48; X <= larghezza_max - 35; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    this->room[H_CONSOLE - 9][larghezza_max - 25] = '=';
    this->room[H_CONSOLE - 9][larghezza_max - 15] = '=';
    for (X = larghezza_max - 9; X <= larghezza_max - 6; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 4; X <= larghezza_max - 3; X++)
        this->room[H_CONSOLE - 9][X] = '=';

    for (X = larghezza_max - 67; X <= larghezza_max - 62; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    this->room[H_CONSOLE - 11][larghezza_max - 55] = '=';
    this->room[H_CONSOLE - 11][larghezza_max - 53] = '=';
    for (X = larghezza_max - 47; X <= larghezza_max - 45; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 35; X <= larghezza_max - 25; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 19; X <= larghezza_max - 14; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 7; X <= larghezza_max - 6; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    this->room[H_CONSOLE - 11][larghezza_max - 4] = '=';

    this->room[H_CONSOLE - 13][larghezza_max - 66] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 63] = '=';
    for (X = larghezza_max - 55; X <= larghezza_max - 42; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 39] = '=';
    for (X = larghezza_max - 23; X <= larghezza_max - 19; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 14; X <= larghezza_max - 10; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 6] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 4] = '=';

    for (X = larghezza_max - 68; X <= larghezza_max - 66; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 63; X <= larghezza_max - 51; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 48; X <= larghezza_max - 45; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 43; X <= larghezza_max - 39; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 30; X <= larghezza_max - 23; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 10; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 15][X] = '=';

    for (X = larghezza_max - 66; X <= larghezza_max - 63; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 51; X <= larghezza_max - 48; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 45; X <= larghezza_max - 43; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 39; X <= larghezza_max - 30; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 4; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 17][X] = '=';

    for (Y = H_CONSOLE - 12; Y <= H_CONSOLE - 5; Y++)
        this->room[Y][larghezza_max - 54] = '|';
    for (Y = H_CONSOLE - 10; Y <= H_CONSOLE - 2; Y++)
        this->room[Y][larghezza_max - 28] = '|';
    for (Y = H_CONSOLE - 5; Y <= H_CONSOLE - 2; Y++)
        this->room[Y][larghezza_max - 13] = '|';
    for (Y = H_CONSOLE - 18; Y <= H_CONSOLE - 17; Y++)
        this->room[Y][larghezza_max - 5] = '|';
    for (Y = H_CONSOLE - 14; Y <= H_CONSOLE - 3; Y++)
        this->room[Y][larghezza_max - 5] = '|';
}

/**
 * @brief genera il terzo modello di stanza inserendo nella matrice i 
 *      suoi elementi, è costituita da piattaforme e ostacoli
 *
 */
void Level::generateMap3()
{
    int X = 0, Y = 0;
    this->generateBorders();

    this->room[H_CONSOLE - 18][larghezza_max - 69] = '(';
    this->room[H_CONSOLE - 2][larghezza_max - 2] = ')';

    this->room[H_CONSOLE - 3][larghezza_max - 63] = '=';
    this->room[H_CONSOLE - 3][larghezza_max - 60] = '=';
    for (X = larghezza_max - 54; X <= larghezza_max - 49; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 45; X <= larghezza_max - 43; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    this->room[H_CONSOLE - 3][larghezza_max - 37] = '=';
    for (X = larghezza_max - 32; X <= larghezza_max - 29; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 24; X <= larghezza_max - 22; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 19; X <= larghezza_max - 14; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    this->room[H_CONSOLE - 3][larghezza_max - 5] = '=';

    for (X = larghezza_max - 65; X <= larghezza_max - 63; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 60; X <= larghezza_max - 53; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 49; X <= larghezza_max - 45; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    this->room[H_CONSOLE - 5][larghezza_max - 37] = '=';
    for (X = larghezza_max - 31; X <= larghezza_max - 29; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 22; X <= larghezza_max - 18; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    this->room[H_CONSOLE - 5][larghezza_max - 5] = '=';

    for (X = larghezza_max - 67; X <= larghezza_max - 65; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    this->room[H_CONSOLE - 7][larghezza_max - 53] = '=';
    this->room[H_CONSOLE - 7][larghezza_max - 37] = '=';
    for (X = larghezza_max - 33; X <= larghezza_max - 31; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 19; X <= larghezza_max - 5; X++)
        this->room[H_CONSOLE - 7][X] = '=';

    for (X = larghezza_max - 65; X <= larghezza_max - 62; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    this->room[H_CONSOLE - 9][larghezza_max - 53] = '=';
    this->room[H_CONSOLE - 9][larghezza_max - 37] = '=';
    for (X = larghezza_max - 31; X <= larghezza_max - 28; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 20; X <= larghezza_max - 16; X++)
        this->room[H_CONSOLE - 9][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 63; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 57; X <= larghezza_max - 51; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 37; X <= larghezza_max - 30; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 17; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 11][X] = '=';

    for (X = larghezza_max - 68; X <= larghezza_max - 66; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 64] = '=';
    for (X = larghezza_max - 60; X <= larghezza_max - 56; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 51; X <= larghezza_max - 48; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 39; X <= larghezza_max - 36; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 30; X <= larghezza_max - 28; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 10; X <= larghezza_max - 6; X++)
        this->room[H_CONSOLE - 13][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 68; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 64; X <= larghezza_max - 59; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 48; X <= larghezza_max - 46; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 41; X <= larghezza_max - 38; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 28; X <= larghezza_max - 10; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 6; X <= larghezza_max - 4; X++)
        this->room[H_CONSOLE - 15][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 61; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 46; X <= larghezza_max - 41; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 38; X <= larghezza_max - 27; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 8; X <= larghezza_max - 3; X++)
        this->room[H_CONSOLE - 17][X] = '=';

    for (Y = H_CONSOLE - 9; Y <= H_CONSOLE - 3; Y++)
        this->room[Y][larghezza_max - 61] = '|';
    for (Y = H_CONSOLE - 16; Y <= H_CONSOLE - 7; Y++)
        this->room[Y][larghezza_max - 43] = '|';
    for (Y = H_CONSOLE - 12; Y <= H_CONSOLE - 5; Y++)
        this->room[Y][larghezza_max - 23] = '|';
    this->room[H_CONSOLE - 2][larghezza_max - 23] = '|';
    for (Y = H_CONSOLE - 6; Y <= H_CONSOLE - 2; Y++)
        this->room[Y][larghezza_max - 7] = '|';
}

/**
 * @brief genera il quarto modello di stanza inserendo nella matrice i 
 *      suoi elementi, è costituita da piattaforme e ostacoli
 *
 */
void Level::generateMap4()
{
    int X = 0, Y = 0;
    this->generateBorders();

    this->room[H_CONSOLE - 2][larghezza_max - 69] = '(';
    this->room[H_CONSOLE - 18][larghezza_max - 2] = ')';

    for (X = larghezza_max - 66; X <= larghezza_max - 65; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 62; X <= larghezza_max - 60; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 40; X <= larghezza_max - 38; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 33; X <= larghezza_max - 29; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 10; X <= larghezza_max - 6; X++)
        this->room[H_CONSOLE - 3][X] = '=';

    for (X = larghezza_max - 68; X <= larghezza_max - 65; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 61; X <= larghezza_max - 58; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 50; X <= larghezza_max - 8; X++)
        this->room[H_CONSOLE - 5][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 66; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 63; X <= larghezza_max - 61; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 58; X <= larghezza_max - 55; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 49; X <= larghezza_max - 46; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 24; X <= larghezza_max - 21; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 13; X <= larghezza_max - 12; X++)
        this->room[H_CONSOLE - 7][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 68; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 61; X <= larghezza_max - 60; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 51; X <= larghezza_max - 6; X++)
        this->room[H_CONSOLE - 9][X] = '=';

    this->room[H_CONSOLE - 11][larghezza_max - 69] = '=';
    this->room[H_CONSOLE - 11][larghezza_max - 65] = '=';
    for (X = larghezza_max - 62; X <= larghezza_max - 61; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 33; X <= larghezza_max - 30; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 8; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 11][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 67; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 61; X <= larghezza_max - 60; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 57; X <= larghezza_max - 5; X++)
        this->room[H_CONSOLE - 13][X] = '=';

    for (X = larghezza_max - 67; X <= larghezza_max - 66; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 62; X <= larghezza_max - 61; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 55; X <= larghezza_max - 53; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 39; X <= larghezza_max - 36; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 22; X <= larghezza_max - 17; X++)
        this->room[H_CONSOLE - 15][X] = '=';

    for (X = larghezza_max - 66; X <= larghezza_max - 62; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 56; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 17][X] = '=';

    for (Y = H_CONSOLE - 16; Y <= H_CONSOLE - 2; Y++)
        this->room[Y][larghezza_max - 64] = '|';
    this->room[H_CONSOLE - 2][larghezza_max - 31] = '|';
    this->room[H_CONSOLE - 2][larghezza_max - 8] = '|';
}

/**
 * @brief genera il quinto modello di stanza inserendo nella matrice i 
 *      suoi elementi, è costituita da piattaforme e ostacoli
 *
 */
void Level::generateMap5()
{
    int X = 0, Y = 0;
    this->generateBorders();

    this->room[H_CONSOLE - 18][larghezza_max - 69] = '(';
    this->room[H_CONSOLE - 12][larghezza_max - 2] = ')';

    for (X = larghezza_max - 66; X <= larghezza_max - 63; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 53; X <= larghezza_max - 51; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 43; X <= larghezza_max - 39; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    this->room[H_CONSOLE - 3][larghezza_max - 34] = '=';
    for (X = larghezza_max - 27; X <= larghezza_max - 25; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 10; X <= larghezza_max - 6; X++)
        this->room[H_CONSOLE - 3][X] = '=';

    for (X = larghezza_max - 67; X <= larghezza_max - 64; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 54; X <= larghezza_max - 50; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 35; X <= larghezza_max - 33; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 25; X <= larghezza_max - 22; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 7; X <= larghezza_max - 4; X++)
        this->room[H_CONSOLE - 5][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 7][X] = '=';

    for (X = larghezza_max - 68; X <= larghezza_max - 66; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 61; X <= larghezza_max - 59; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    this->room[H_CONSOLE - 9][larghezza_max - 52] = '=';
    for (X = larghezza_max - 47; X <= larghezza_max - 45; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 37; X <= larghezza_max - 29; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 16; X <= larghezza_max - 15; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 8; X <= larghezza_max - 4; X++)
        this->room[H_CONSOLE - 9][X] = '=';

    for (X = larghezza_max - 68; X <= larghezza_max - 67; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    this->room[H_CONSOLE - 11][larghezza_max - 60] = '=';
    for (X = larghezza_max - 53; X <= larghezza_max - 51; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 45; X <= larghezza_max - 43; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 31; X <= larghezza_max - 16; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 5; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 11][X] = '=';

    this->room[H_CONSOLE - 13][larghezza_max - 68] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 60] = '=';
    for (X = larghezza_max - 56; X <= larghezza_max - 50; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 45] = '=';
    for (X = larghezza_max - 37; X <= larghezza_max - 29; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 3] = '=';

    for (X = larghezza_max - 68; X <= larghezza_max - 65; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 61; X <= larghezza_max - 55; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 51; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 15][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 59; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 35; X <= larghezza_max - 31; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 20; X <= larghezza_max - 18; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 6; X <= larghezza_max - 5; X++)
        this->room[H_CONSOLE - 17][X] = '=';

    this->room[H_CONSOLE - 8][larghezza_max - 60] = '|';
    for (Y = H_CONSOLE - 19; Y <= H_CONSOLE - 17; Y++)
        this->room[Y][larghezza_max - 44] = '|';
    for (Y = H_CONSOLE - 14; Y <= H_CONSOLE - 12; Y++)
        this->room[Y][larghezza_max - 44] = '|';
    this->room[H_CONSOLE - 2][larghezza_max - 41] = '|';
    this->room[H_CONSOLE - 8][larghezza_max - 36] = '|';
    for (Y = H_CONSOLE - 10; Y <= H_CONSOLE - 8; Y++)
        this->room[Y][larghezza_max - 18] = '|';
    this->room[H_CONSOLE - 2][larghezza_max - 8] = '|';
}

/**
 * @brief genera il sesto modello di stanza inserendo nella matrice i 
 *      suoi elementi, è costituita da piattaforme e ostacoli
 *
 */
void Level::generateMap6()
{

    int X = 0, Y = 0;
    this->generateBorders();

    this->room[H_CONSOLE - 12][larghezza_max - 69] = '(';
    this->room[H_CONSOLE - 2][larghezza_max - 2] = ')';

    for (X = larghezza_max - 68; X <= larghezza_max - 62; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 54; X <= larghezza_max - 53; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    this->room[H_CONSOLE - 3][larghezza_max - 45] = '=';
    for (X = larghezza_max - 40; X <= larghezza_max - 37; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 28; X <= larghezza_max - 27; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 24; X <= larghezza_max - 21; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    for (X = larghezza_max - 12; X <= larghezza_max - 7; X++)
        this->room[H_CONSOLE - 3][X] = '=';
    this->room[H_CONSOLE - 3][larghezza_max - 4] = '=';

    for (X = larghezza_max - 62; X <= larghezza_max - 60; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 55; X <= larghezza_max - 53; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 46; X <= larghezza_max - 44; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 38; X <= larghezza_max - 21; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 11; X <= larghezza_max - 8; X++)
        this->room[H_CONSOLE - 5][X] = '=';
    for (X = larghezza_max - 5; X <= larghezza_max - 2; X++)
        this->room[H_CONSOLE - 5][X] = '=';

    for (X = larghezza_max - 65; X <= larghezza_max - 58; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 56; X <= larghezza_max - 53; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 48; X <= larghezza_max - 38; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 29; X <= larghezza_max - 25; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    for (X = larghezza_max - 22; X <= larghezza_max - 18; X++)
        this->room[H_CONSOLE - 7][X] = '=';
    this->room[H_CONSOLE - 7][larghezza_max - 10] = '=';
    this->room[H_CONSOLE - 7][larghezza_max - 8] = '=';
    for (X = larghezza_max - 6; X <= larghezza_max - 5; X++)
        this->room[H_CONSOLE - 7][X] = '=';

    for (X = larghezza_max - 66; X <= larghezza_max - 64; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 53; X <= larghezza_max - 47; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    this->room[H_CONSOLE - 9][larghezza_max - 43] = '=';
    for (X = larghezza_max - 27; X <= larghezza_max - 24; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 18; X <= larghezza_max - 17; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    for (X = larghezza_max - 15; X <= larghezza_max - 10; X++)
        this->room[H_CONSOLE - 9][X] = '=';
    this->room[H_CONSOLE - 9][larghezza_max - 8] = '=';
    for (X = larghezza_max - 5; X <= larghezza_max - 3; X++)
        this->room[H_CONSOLE - 9][X] = '=';

    for (X = larghezza_max - 69; X <= larghezza_max - 61; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 56; X <= larghezza_max - 53; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 44; X <= larghezza_max - 43; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 31; X <= larghezza_max - 26; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 24; X <= larghezza_max - 22; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 19; X <= larghezza_max - 15; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 11; X <= larghezza_max - 8; X++)
        this->room[H_CONSOLE - 11][X] = '=';
    for (X = larghezza_max - 6; X <= larghezza_max - 3; X++)
        this->room[H_CONSOLE - 11][X] = '=';

    for (X = larghezza_max - 61; X <= larghezza_max - 60; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 54; X <= larghezza_max - 53; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    for (X = larghezza_max - 45; X <= larghezza_max - 41; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 29] = '=';
    for (X = larghezza_max - 23; X <= larghezza_max - 20; X++)
        this->room[H_CONSOLE - 13][X] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 11] = '=';
    this->room[H_CONSOLE - 13][larghezza_max - 3] = '=';

    for (X = larghezza_max - 60; X <= larghezza_max - 58; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 55; X <= larghezza_max - 50; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 47; X <= larghezza_max - 44; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 41; X <= larghezza_max - 36; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    for (X = larghezza_max - 30; X <= larghezza_max - 28; X++)
        this->room[H_CONSOLE - 15][X] = '=';
    this->room[H_CONSOLE - 15][larghezza_max - 21] = '=';
    this->room[H_CONSOLE - 15][larghezza_max - 11] = '=';
    for (X = larghezza_max - 5; X <= larghezza_max - 3; X++)
        this->room[H_CONSOLE - 15][X] = '=';

    for (X = larghezza_max - 58; X <= larghezza_max - 54; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 50; X <= larghezza_max - 47; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    for (X = larghezza_max - 36; X <= larghezza_max - 5; X++)
        this->room[H_CONSOLE - 17][X] = '=';
    this->room[H_CONSOLE - 17][larghezza_max - 2] = '=';

    for (Y = H_CONSOLE - 16; Y <= H_CONSOLE - 3; Y++)
        this->room[Y][larghezza_max - 57] = '|';
    for (Y = H_CONSOLE - 16; Y <= H_CONSOLE - 7; Y++)
        this->room[Y][larghezza_max - 33] = '|';
    for (Y = H_CONSOLE - 4; Y <= H_CONSOLE - 2; Y++)
        this->room[Y][larghezza_max - 33] = '|';
    for (Y = H_CONSOLE - 16; Y <= H_CONSOLE - 11; Y++)
        this->room[Y][larghezza_max - 13] = '|';
    for (Y = H_CONSOLE - 8; Y <= H_CONSOLE - 2; Y++)
        this->room[Y][larghezza_max - 13] = '|';
    for (Y = H_CONSOLE - 16; Y <= H_CONSOLE - 5; Y++)
        this->room[Y][larghezza_max - 7] = '|';
    this->room[H_CONSOLE - 2][larghezza_max - 7] = '|';
    for (Y = H_CONSOLE - 14; Y <= H_CONSOLE - 12; Y++)
        this->room[Y][larghezza_max - 4] = '|';
}

/**
 * @brief funzione che ritorna il carattere presente nella cella della matrice
 *          con le coordinate in input
 * 
 * @param y coordianta y della cella
 * @param x coordianta x della cella
 *
 * @return char carattere nella cella [y][x]
 */
char Level::getChar(int y, int x)
{
    return this->room[y][x];
}