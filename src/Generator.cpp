#include "Generator.hpp"

/**
 * @brief costruttore della classe Generator
 *  
 */
Generator::Generator() {}

/**
 * @brief funzione che inserisce in modo casuale all'interno del 
 *      livello corrente i BonusPoint. La quantità è influenzata da
 *      parametri che variano a seconda del numero del livello
 *      
 * @param levels puntatore alla lista dei livelli
 */
void Generator::generateBonusPoints(Levels *levels)
{
    srand(time(NULL));
    int X = 0, Y = 0;
    int maxNumber = 0;
    int numBonus = 6 - levels->getLevel()->levelNumber;
    if (numBonus <= 0)
        numBonus = ((rand()% 25) + 1);

    //controllo tutte posizioni dispari
    for (Y = H_CONSOLE - 18; Y <= H_CONSOLE - 2; Y = Y + 2)
    {
        if (numBonus <= 0)
            break;
        maxNumber = 0;

        for (X = larghezza_max - 68; X <= larghezza_max - 2; X++)
        {
            if (numBonus <= 0)
                break;

            if (((rand() % 80 + 1) <= 5) &&
                (levels->getLevel()->getChar(Y, X) == '\0') &&
                (levels->getLevel()->getChar(Y, X + 1) == '\0') &&
                (levels->getLevel()->getChar(Y, X - 1) == '\0') &&
                ((levels->getLevel()->getChar(Y + 1, X) == '=' ||
                  (levels->getLevel()->getChar(Y + 1, X) == '#'))))
            {
                levels->getLevel()->_add(X, Y, '$');

                numBonus--;
                maxNumber++;
            }

            if (maxNumber > 2)
                break;
        }
    }
}

/**
 * @brief funzione che inserisce in modo casuale all'interno del 
 *      livello corrente i BonusLife. La quantità è influenzata da
 *      parametri che variano a seconda del numero del livello
 *      
 * @param levels puntatore alla lista dei livelli
 */
void Generator::generateBonusLife(Levels *levels, int life)
{
    srand(time(NULL));
    int X = 0, Y = 0;
    int maxNumber = 0;

    int numBonus = (100 - life) / 20;
    if(levels->getLevel()->levelNumber > 5) {
        numBonus = (100 - life) / 40;
    }
    else if(levels->getLevel()->levelNumber > 10) {
        numBonus = 1;
    }

    for (Y = H_CONSOLE - 18; Y <= H_CONSOLE - 2; Y = Y + 4)
    {
        if (numBonus <= 0)
            break;
        maxNumber = 0;

        for (X = larghezza_max - 68; X <= larghezza_max - 2; X++)
        {
            if (numBonus <= 0)
                break;

            if (((rand() % 60 + 1) <= 5) &&
                (levels->getLevel()->getChar(Y, X) == '\0') &&
                (levels->getLevel()->getChar(Y, X + 1) == '\0') &&
                (levels->getLevel()->getChar(Y, X - 1) == '\0') &&
                ((levels->getLevel()->getChar(Y + 1, X) == '=' ||
                  (levels->getLevel()->getChar(Y + 1, X) == '#'))))
            {
                levels->getLevel()->_add(X, Y, 'L');

                numBonus--;
                maxNumber++;
            }

            if (maxNumber > 1)
                break;
        }
    }
}

/**
 * @brief funzione che inserisce in modo casuale all'interno del 
 *      livello corrente i BasicEnemis. Il numero del livello in cui vengono inseriti 
 *      influisce sulla quantità di vita dei nemici e sulla loro quantità
 * 
 * @param levels puntatore alla lista dei livelli
 * @param basicEnemies puntatore alla lista dei BasicEnemy
 */
void Generator::generateBasicEnemies(Levels *levels, BasicEnemiesList *basicEnemies)
{
    srand(time(NULL));
    int X = 0, Y = 0;
    int maxNumber = 0;
    int lifeIncreaser = 10;

    lifeIncreaser = lifeIncreaser * levels->getLevel()->levelNumber;
    int numBasicEnemies = 6 + levels->getLevel()->levelNumber;
    if (levels->getLevel()->levelNumber > 6)
        numBasicEnemies = 3;

    //controllo tutte posizioni dispari
    for (Y = H_CONSOLE - 18; Y <= H_CONSOLE - 2; Y = Y + 2)
    {
        if (numBasicEnemies <= 0)
            break;
        maxNumber = 0;

        for (X = larghezza_max - 65; X <= larghezza_max - 2; X = X + 2)
        {
            if (numBasicEnemies <= 0)
                break;

            if (((rand() % 120 + 1) <= 5) &&
                (levels->getLevel()->getChar(Y, X) == '\0') &&
                (levels->getLevel()->getChar(Y, X + 1) == '\0') &&
                (levels->getLevel()->getChar(Y, X - 1) == '\0') &&
                ((levels->getLevel()->getChar(Y + 1, X) == '=' ||
                  (levels->getLevel()->getChar(Y + 1, X) == '#'))))
            {
                levels->getLevel()->_add(X, Y, 'K');
                basicEnemies->prependBasicEnemy(X, Y, levels->getLevel()->levelNumber, 50 + lifeIncreaser);

                numBasicEnemies--;
                maxNumber++;
            }

            if (maxNumber > 2)
                break;
        }
    }
}

/**
 * @brief funzione che inserisce in modo casuale all'interno del 
 *      livello corrente i MediumEnemis. Il numero del livello in cui vengono inseriti 
 *      influisce sulla quantità di vita dei nemici e sulla loro quantità
 * 
 * @param levels puntatore alla lista dei livelli
 * @param basicEnemies puntatore alla lista dei MediumEnemy
 */
void Generator::generateMediumEnemies(Levels *levels, MediumEnemiesList *mediumEnemies)
{
    srand(time(NULL));
    int X = 0, Y = 0;
    int maxNumber = 0;
    int lifeIncreaser = 10;

    lifeIncreaser = lifeIncreaser * (levels->getLevel()->levelNumber * 0.5);
    int numMediumEnemies = levels->getLevel()->levelNumber + (rand() % 3);
    if(levels->getLevel()->levelNumber < 3) {
        numMediumEnemies = 0;
    }
    else if(levels->getLevel()->levelNumber > 6) {
        numMediumEnemies = 6 + (rand() % 3);
    }

    //controllo tutte posizioni dispari
    for (Y = H_CONSOLE - 18; Y <= H_CONSOLE - 2; Y = Y + 2)
    {
        if (numMediumEnemies <= 0)
            break;
        maxNumber = 0;

        for (X = larghezza_max - 40; X <= larghezza_max - 2; X ++)
        {
            if (numMediumEnemies <= 0)
                break;

            if (((rand() % 80 + 1) <= 5) &&
                (levels->getLevel()->getChar(Y, X) == '\0') &&
                (levels->getLevel()->getChar(Y, X + 1) == '\0') &&
                (levels->getLevel()->getChar(Y, X - 1) == '\0') &&
                ((levels->getLevel()->getChar(Y + 1, X) == '=' ||
                  (levels->getLevel()->getChar(Y + 1, X) == '#'))))
            {
                levels->getLevel()->_add(X, Y, 'M');
                mediumEnemies->prependMediumEnemy(X, Y, levels->getLevel()->levelNumber, 40 + lifeIncreaser);

                numMediumEnemies--;
                maxNumber++;
            }

            if (maxNumber > 2)
                break;
        }
    }
}

/**
 * @brief funzione che inserisce in modo casuale all'interno del 
 *      livello corrente gli HardEnemis. Il numero del livello in cui vengono inseriti 
 *      influisce sulla quantità di vita dei nemici e sulla loro quantità
 * 
 * @param levels puntatore alla lista dei livelli
 * @param basicEnemies puntatore alla lista degli HardEnemy
 */
void Generator::generateHardEnemies(Levels *levels, HardEnemiesList *hardEnemies)
{
    srand(time(NULL));
    int X = 0, Y = 0;
    int maxNumber = 0;
    int lifeIncreaser = 10;
    
    lifeIncreaser = lifeIncreaser * (levels->getLevel()->levelNumber * 0.25);
    int numHardEnemies = levels->getLevel()->levelNumber;
    if(levels->getLevel()->levelNumber > 8)
        numHardEnemies = 7 + (rand() % 3);

    //controllo tutte posizioni dispari
    for (Y = H_CONSOLE - 18; Y <= H_CONSOLE - 2; Y = Y + 2)
    {
        if (numHardEnemies <= 0)
            break;
        maxNumber = 0;

        for (X = larghezza_max - 60; X <= larghezza_max - 2; X = X + 2)
        {
            if (numHardEnemies <= 0)
                break;

            if (((rand() % 100 + 1) <= 5) &&
                (levels->getLevel()->getChar(Y, X) == '\0') &&
                (levels->getLevel()->getChar(Y, X + 1) == '\0') &&
                (levels->getLevel()->getChar(Y, X - 1) == '\0') &&
                ((levels->getLevel()->getChar(Y + 1, X) == '=' ||
                  (levels->getLevel()->getChar(Y + 1, X) == '#'))))
            {
                levels->getLevel()->_add(X, Y, 'H');
                hardEnemies->prependHardEnemy(X, Y, levels->getLevel()->levelNumber, 50 + lifeIncreaser);

                numHardEnemies--;
                maxNumber++;
            }

            if (maxNumber > 2)
                break;
        }
    }
}