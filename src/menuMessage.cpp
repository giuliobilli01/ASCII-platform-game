#include "menuMessage.h"

/**
 * @brief funzione chiamata all'inizio del main. Essa contiene il menu per a scelta multipla
 *      per accedere alle varie informazioni sul gioco
 *  
 */
void gameStart() {
    system("cls");
    char input;

    gotoxy(3, 2);
    cout << "WELCOME!";
    gotoxy(3, 4);
    cout << "Game instruction:";
    gotoxy(3, 5);
    cout << "Press '1' for instructions on player movement";
    gotoxy(3, 6);
    cout << "Press '2' for instructions on how to pass the levels";
    gotoxy(3, 7);
    cout << "Press '3' for instructions on the player's points and life";
    gotoxy(3, 8);
    cout << "Press '4' for instructions on the player's shooting skills";
    gotoxy(3, 9);
    cout << "Press '5' for instructions on the game's enemies";
    gotoxy(3, 10);
    cout << "Press '6' for instructions on ending the game";
    gotoxy(3, 12);
    cout << "Proceed with the in-depth information,";
    gotoxy(3, 13);
    cout << "otherwise press any other character to start the game" << endl << endl;
    gotoxy(3, 14);
    cout << "Choice: ";
    cin >> input;   
    
    if(input == '1') {
        instructionPlayerMovement();
        gameStart();
    }
    else if(input == '2') {
        instructionGameLevel();
        gameStart();
    }
    else if(input == '3') {
        instructionPlayerData();
        gameStart();
    }
    else if(input == '4') {
        instructionPlayerShooting();
        gameStart();
    }
    else if(input == '5') {
        instructionGameEnemies();
        gameStart();
    }
    else if(input == '6') {
        instructionEndGame();
        gameStart();
    }

}

/**
 * @brief funzione che stampa le istruzioni per muovere il Player
 *  
 */
void instructionPlayerMovement() {
    system("cls");

    gotoxy(3, 2);
    cout << "Player's movement instructions:";
    gotoxy(3, 4);
    cout << "1. The player is identified by the '@' character";
    gotoxy(3, 5);
    cout << "2. Press 'a' to move the player left";
    gotoxy(3, 6);
    cout << "3. Press 'd' to move the player right";
    gotoxy(3, 7);
    cout << "4. Press 's' to move the player down";
    gotoxy(3, 8);
    cout << "5. Press 'w' to move the player up" << endl << endl;

    system("pause");
}

/**
 * @brief funzione che stampa le informazioni su come sono organizzati i livelli e su come passarli 
 *  
 */
void instructionGameLevel() {
    system("cls");

    gotoxy(3, 2);
    cout << "Instructions for passing levels:";
    gotoxy(3, 4);
    cout << "1. Once the game has started, the player is placed in an empty initial room,";
    gotoxy(3, 5);
    cout << "   to give a taste of the dimensions of the game environment";
    gotoxy(3, 6);
    cout << "2. To go to the next level you need to go through a ')' door";
    gotoxy(3, 7);
    cout << "3. To go to the previous level you need to go through a '(' door";
    gotoxy(3, 8);
    cout << "4. The player can only move on '#' and '=' platforms";
    gotoxy(3, 9);
    cout << "5. The '|' walls block the passage to the player";
    gotoxy(3, 10);
    cout << "6. To move upwards you need to have a platform directly above which you can land on";
    gotoxy(3, 11);
    cout << "7. For downward movement there must be a platform directly below the current platform the player is on";
    gotoxy(3, 12);
    cout << "8. There are more ways to reach the next level";
    gotoxy(3, 13);
    cout << "9. The game is potentially infinite, there is no final level" << endl << endl;
    
    system("pause");
}

/**
 * @brief funzione che stampa le informazioni sui dati del Player che vengono
 *          che vengono stampati sulla parte destra della schermata
 *  
 */
void instructionPlayerData() {
    system("cls");

    gotoxy(3, 2);
    cout << "Player data instructions:";
    gotoxy(3, 4);
    cout << "1. The player has his own life and points";
    gotoxy(3, 5);
    cout << "2. At the start of the game the player has a life of 100 units";
    gotoxy(3, 6);
    cout << "   while it amounts to 0 units of points";
    gotoxy(3, 7);
    cout << "3. The player's points can only go up";
    gotoxy(3, 8);
    cout << "4. The player's life can both go up and down";
    gotoxy(3, 9);
    cout << "5. Obviously, the more life the player has, the more chance he has of continuing the game";
    gotoxy(3, 10);
    cout << "6. The player's points increase when the player reaches a position on the map where there is a '$' bonus";
    gotoxy(3, 11);
    cout << "7. The player's life increases when the player reaches a position on the map where there is a 'L' bonus";
    gotoxy(3, 12);
    cout << "8. For every 200 units of points obtained, the player's life increases by 50 units";
    gotoxy(3, 13);
    cout << "9. The player loses life when taking damage from enemies";
    gotoxy(3, 14);
    cout << "10. The damage obtained, which translates into subtracted life units, depends on the enemy encountered ";
    gotoxy(3, 15);
    cout << "11. The further you progress through the levels, the fewer bonuses there will be,";
    gotoxy(3, 16);
    cout << "   so the less chance of increasing the player's points and life" << endl << endl;

    system("pause");
}

/**
 * @brief funzione che stampa le informazioni su come funzionano gli spari del Player
 *  
 */
void instructionPlayerShooting() {
    system("cls");

    gotoxy(3, 2);
    cout << "Player's shooting ability instructions:";
    gotoxy(3, 4);
    cout << "1. Press 'p' to make the player shoot";
    gotoxy(3, 5);
    cout << "2. The shots have only a left and right direction, so you cannot shoot down or up";
    gotoxy(3, 6);
    cout << "3. Simultaneous shots can be made by repeatedly clicking the 'p' key";
    gotoxy(3, 7);
    cout << "4. The player's shot is in the '-' form";
    gotoxy(3, 8);
    cout << "5. The shots go through the empty space of the game map through the '$' bonuses";
    gotoxy(3, 9);
    cout << "6. The shots disappear when they meet a '|' wall or when they encounter an enemy";
    gotoxy(3, 10);
    cout << "7. Damage to enemies that are fired depends on the type of enemy encountered";
    gotoxy(3, 11);
    cout << "8. when the player is at a unitary distance from an enemy, he can make a shot";
    gotoxy(3, 12);
    cout << "   at all times, but this will not be displayed on the map";
    gotoxy(3, 13);
    cout << "9. The ammo for player shots is infinite" << endl << endl;

    system("pause");
}

/**
 * @brief funzione che stampa informazioni sui tipi di nemici e le loro caratteristiche
 *  
 */
void instructionGameEnemies() {
    system("cls");

    gotoxy(3, 2);
    cout << "Game enemy instructions:";
    gotoxy(3, 4);
    cout << "1. There are three types of enemies that differ in abilities and characteristics";
    gotoxy(3, 5);
    cout << "2. The base enemies 'K' are static enemies in the map and their purpose is";
    gotoxy(3, 6);
    cout << "   to block the paths useful to the player in the playing area";
    gotoxy(3, 7);
    cout << "3. If the player shoots the enemy 'K' he loses 10 units of life";
    gotoxy(3, 8);
    cout << "   and if the player crosses it 'K' dies and the player loses 50 life units";
    gotoxy(3, 9);
    cout << "4. Medium difficulty enemies 'M' are dynamic enemies in the map and their purpose is";
    gotoxy(3, 10);
    cout << "  to decrease the player's life by acting as 'kamikaze enemies'";
    gotoxy(3, 11);
    cout << "5. 'M' enemies move by covering the minimum distance that brings them closer to the player";
    gotoxy(3, 12);
    cout << "6. If the player shoots the enemy 'M' he loses 20 units of life";
    gotoxy(3, 13);
    cout << "   and if the player crosses it 'M' dies and the player loses 50 life units";
    gotoxy(3, 14);
    cout << "7. High difficulty 'H' enemies are static enemies in the map and their purpose is";
    gotoxy(3, 15);
    cout << "   to decrease the player's life by shooting them, when they are at a certain distance from them";
    gotoxy(3, 16);
    cout << "8. shots from enemy 'H' are in the form '*' and have left and right direction";
    gotoxy(3, 17);
    cout << "9. If the player shoots the enemy 'H' he loses 30 units of life";
    gotoxy(3, 18);
    cout << "   and if the player crosses it 'H' dies and the player loses 50 life units";
    gotoxy(3, 19);
    cout << "10. Enemies have respectively: 'K' 50, 'M' 40, 'H' 40 associated life units, which increase as you progress through the levels" << endl << endl;

    system("pause");
}

/**
 * @brief funzione che stampa le informazioni su come viene terminata la partita
 *  
 */
void instructionEndGame() {
    system("cls");

    gotoxy(3, 2);
    cout << "Instructions on terminating the game:";
    gotoxy(3, 4);
    cout << "1. The game can end in two ways";
    gotoxy(3, 5);
    cout << "2. The first way consists in having a player life equal to 0";
    gotoxy(3, 6);
    cout << "3. The second way is to click the 'e' button";
    gotoxy(3, 7);
    cout << "4. the last mode explained allows you to exit the game instantly,";
    gotoxy(3, 8);
    cout << "   without depending on the player's data";
    gotoxy(3, 9);
    cout << "5. In both cases, an end-of-game message will appear at the end of the game" << endl << endl;

    system("pause");
}

/**
 * @brief stampa il messaggio di GAME OVER
 *  
 */
void gameOver() {

    system("cls");

    gotoxy(0, 4);
    cout << "###############          ###########          #####            #####  ###############\n"
            "##                      ###        ###        ######          ######  ##############\n"
            "##                     ###          ###       ### ###        ### ###  ###\n"
            "##                    ###            ###      ###    ###  ###    ###  ########\n"
            "##         ####      ### ############ ###     ###      ####      ###  ########\n"
            "##           ##     ###                ###    ###                ###  ###\n"
            "###############    ###                  ###   ###                ###  ##############\n"
            "###############   ###                    ###  ###                ###  ###############\n";


    cout << "###############    ###                  ###   ###############    ###############\n"
            "##           ##     ###                ###    ##############     ###          ###\n"
            "##           ##      ###              ###     ###                ###          ###\n"
            "##           ##       ###            ###      ########           ###############\n"
            "##           ##        ###          ###       ########           ######\n"
            "##           ##         ###        ###        ###                ###  ###\n"
            "###############           ###    ###          ##############     ###      ###\n"
            "###############            ########           ###############    ###        ###\n"; 
  
    system("pause");
    system("cls");
    gotoxy(0, 5);
    cout << "Thanks for playing with us\n";

    system("pause");
}

/*
         
  */