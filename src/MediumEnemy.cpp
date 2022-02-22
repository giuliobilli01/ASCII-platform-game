#include "MediumEnemy.hpp"

/**
 * @brief costruttore della classe MediumEnemy che estende il costruttore di Character da cui prende 
 *        x ,y, e Life e poi prende il numero del livello a cui è assegnato il nemico
 * 
 * @param x coordinata x del MediumEnemy
 * @param y coordinata x del MediumEnemy
 * @param life vita del MediumEnemy
 * @param enemyLevelNumber numero del livello a cui è assegnato il MediumEnemy
 */
MediumEnemy::MediumEnemy(int x, int y, int life, int enemyLevelNumber) : Character(x, y, life)
{
    this->nextEnemy = NULL;
    this->isAlive = true;
    this->enemyLevelNumber = enemyLevelNumber;
}

/**
 * @brief funzione che permette di muovere il MediumEnemy nella stanza in cui si trova. 
 *        A ogni iterazione del ciclo principale la funzione controlla qual è la direzione migliore per 
 *        per avvicinarsi al Player e se può spostarsi in quella direzione si muove altrimenti controlla 
 *        le altre direzioni in ordine decrescente di convenienza per avvicinarsi al Player. 
 * 
 * @param level puntatore al livello corrente
 * @param shots puntatore alla lista di Shots
 * @param character puntatore al Character a cui avvicinarsi, in questo caso il Player
 */
void MediumEnemy::moveMediumEnemy(Level *level, Shots *shots, Character *character)
{

    if ((rand() % 15 + 1) == 5)
    {
        float dist[4];
        dist[0] = sqrt(pow((this->x + 1) - character->getX(), 2) + pow(this->y - character->getY(), 2)); //movimento destra
        dist[1] = sqrt(pow((this->x - 1) - character->getX(), 2) + pow(this->y - character->getY(), 2)); //movimento sinistra
        dist[2] = sqrt(pow(this->x - character->getX(), 2) + pow((this->y - 1) - character->getY(), 2)); //movimento alto
        dist[3] = sqrt(pow(this->x - character->getX(), 2) + pow((this->y + 1) - character->getY(), 2)); //movimento basso

        int min[4];
        min[0] = 0;
        min[1] = 1;
        min[2] = 2;
        min[3] = 3;

        int i, j, tmp;
        for (i = 0; i < 4; i++)
        {
            for (j = i + 1; j < 4; j++)
            {
                if (dist[min[i]] > dist[min[j]])
                {
                    tmp = min[i];
                    min[i] = min[j];
                    min[j] = tmp;
                }
            }
        }

        i = 0;
        bool esc = false;
        while (i < 4 && !esc)
        {
            if (min[i] == 0)
            {
                if (this->canGoRigth(level, shots, character) != 0)
                {
                    this->positionEnemy(level, 'd', shots, character);
                    esc = true;
                }
            }
            else if (min[i] == 1)
            {
                if (this->canGoLeft(level, shots, character) != 0)
                {
                    this->positionEnemy(level, 'a', shots, character);
                    esc = true;
                }
            }
            else if (min[i] == 2)
            {
                if (this->canGoUp(level, shots, character))
                {
                    this->positionEnemy(level, 'w', shots, character);
                    esc = true;
                }
            }
            else if (min[i] == 3)
            {
                if (this->canGoDown(level, shots, character))
                {
                    this->positionEnemy(level, 's', shots, character);
                    esc = true;
                }
            }

            i++;
        }
    }
}

/**
 * @brief Funzione che controlla se il MediumEnemy può spostarsi nella cella alla sua destra, controllando
 *          il contenuto della cella. A seconda del contenuto della cella vengono aggiornate le coordinate
 *          del MediumEnemy, oppure aggiornata la sua vita o il suo stato.
 * 
 * @param level puntatore al livello corrente
 * @param shots puntatore alla lista degli Shots
 * @param character puntatore al character
 *
 * @return int intero che identifica il movimento da fare
 */
int MediumEnemy::canGoRigth(Level *level, Shots *shots, Character *character)
{

    if ((level->getChar(this->y + 1, this->x + 1) == '=') ||
        (level->getChar(this->y + 1, this->x + 1) == '#'))
    {

        if ((level->getChar(this->y, this->x + 1) == '\0') ||
            (level->getChar(this->y, this->x + 1) == ' ') ||
            (level->getChar(this->y, this->x + 1) == '-') ||
            (level->getChar(this->y, this->x + 1) == '@'))
        {

            if (level->getChar(this->y, this->x + 1) == '@')
            {
                character->decreaseLife(20);
                character->printLife(level);
                this->life = 0;
                if (this->isDead())
                    this->isAlive = false;
            }
            if (level->getChar(this->y, this->x + 1) == '-')
            {
                this->decreaseLife(20);
                if (this->isDead())
                    this->isAlive = false;
            }

            return 1;
        }
        else if (((level->getChar(this->y, this->x + 1) == 'K') ||
                  (level->getChar(this->y, this->x + 1) == 'H') ||
                  (level->getChar(this->y, this->x + 1) == '$') ||
                  (level->getChar(this->y, this->x + 1) == 'L')) &&
                 ((level->getChar(this->y, this->x + 2) == ' ') ||
                  (level->getChar(this->y, this->x + 2) == '\0')) &&
                 ((level->getChar(this->y + 1, this->x + 2) == '=') ||
                  (level->getChar(this->y + 1, this->x + 2) == '#')))
        {
            return 2;
        }
    }

    return 0;
}

/**
 * @brief Funzione che controlla se il MediumEnemy può spostarsi nella cella alla sua sinistra, controllando
 *          il contenuto della cella. A seconda del contenuto della cella vengono aggiornate le coordinate
 *          del MediumEnemy, oppure aggiornata la sua vita o il suo stato.
 * 
 * @param level puntatore al livello corrente
 * @param shots puntatore alla lista degli Shots
 * @param character puntatore al character
 *
 * @return int intero che identifica il movimento da fare
 */
int MediumEnemy::canGoLeft(Level *level, Shots *shots, Character *character)
{

    if ((level->getChar(this->y + 1, this->x - 1) == '=') ||
        (level->getChar(this->y + 1, this->x - 1) == '#'))
    {

        if ((level->getChar(this->y, this->x - 1) == '\0') ||
            (level->getChar(this->y, this->x - 1) == ' ') ||
            (level->getChar(this->y, this->x - 1) == '-') ||
            (level->getChar(this->y, this->x - 1) == '@'))
        {

            if (level->getChar(this->y, this->x - 1) == '@')
            {
                character->decreaseLife(20);
                character->printLife(level);
                this->life = 0;
                if (this->isDead())
                    this->isAlive = false;
            }
            if (level->getChar(this->y, this->x - 1) == '-')
            {
                this->decreaseLife(20);
                if (this->isDead())
                    this->isAlive = false;
            }

            return 1;
        }
        else if (((level->getChar(this->y, this->x - 1) == 'K') ||
                  (level->getChar(this->y, this->x - 1) == 'H') ||
                  (level->getChar(this->y, this->x - 1) == '$') ||
                  (level->getChar(this->y, this->x - 1) == 'L')) &&
                  ((level->getChar(this->y, this->x - 2) == ' ') ||
                 (level->getChar(this->y, this->x - 2) == '\0')) &&
                 ((level->getChar(this->y + 1, this->x - 2) == '=') ||
                  (level->getChar(this->y + 1, this->x - 1) == '#')))
        {
            return 2;
        }
    }

    return 0;
}

/**
 * @brief Funzione che controlla se il MediumEnemy può spostarsi nella piattaforma sopra di lui, controllando
 *          se esiste e se è vota. A seconda delle condizioni della piattaforma vengono aggiornate le coordinate
 *          del MediumEnemy, oppure aggiornata la sua vita o il suo stato.
 * 
 * @param level puntatore al livello corrente
 * @param shots puntatore alla lista degli Shots
 * @param character puntatore al character
 *
 * @return int intero che identifica il movimento da fare
 */
bool MediumEnemy::canGoUp(Level *level, Shots *shots, Character *character)
{

    if ((level->getChar(this->y - 1, this->x) == '=') &&
        ((level->getChar(this->y - 2, this->x) == '\0') ||
         (level->getChar(this->y - 2, this->x) == ' ') ||
         (level->getChar(this->y - 2, this->x) == '-') ||
         (level->getChar(this->y - 2, this->x) == '@')))
    {

        if (level->getChar(this->y - 2, this->x) == '@')
        {
            character->decreaseLife(20);
            character->printLife(level);
            this->life = 0;
            if (this->isDead())
                this->isAlive = false;
        }
        if (level->getChar(this->y - 2, this->x) == '-')
        {
            this->decreaseLife(20);
            if (this->isDead())
                this->isAlive = false;
        }

        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Funzione che controlla se il MediumEnemy può spostarsi nella piattaforma sotto di lui, controllando
 *          se esiste e se è vuota. A seconda delle condizioni della piattaforma vengono aggiornate le coordinate
 *          del MediumEnemy, oppure aggiornata la sua vita o il suo stato.
 * 
 * @param level puntatore al livello corrente
 * @param shots puntatore alla lista degli Shots
 * @param character puntatore al character
 *
 * @return int intero che identifica il movimento da fare
 */
bool MediumEnemy::canGoDown(Level *level, Shots *shots, Character *character)
{

    if ((level->getChar(this->y + 1, this->x) == '=') &&
        ((level->getChar(this->y + 3, this->x) == '=') ||
         (level->getChar(this->y + 3, this->x) == '#')) &&
        ((level->getChar(this->y + 2, this->x) == '\0') ||
         (level->getChar(this->y + 2, this->x) == ' ') ||
         (level->getChar(this->y + 2, this->x) == '-') ||
         (level->getChar(this->y + 2, this->x) == '@')))
    {

        if (level->getChar(this->y + 2, this->x) == '@')
        {
            character->decreaseLife(20);
            character->printLife(level);
            this->life = 0;
            if (this->isDead())
                this->isAlive = false;
        }
        if (level->getChar(this->y + 2, this->x) == '-')
        {
            this->decreaseLife(20);
            if (this->isDead())
                this->isAlive = false;
        }

        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief funzione che aggiorna le coordinate del MediumEnemy se può spostarsi nella direzione 
 *        più conveniente in cui può andare
 * 
 * @param level puntatore al livello corrente
 * @param direction carattere che identifica la direzione in cui si muove il MediumEnemy
 * @param shots puntatore alla lista degli Shots
 * @param character puntatore al Character
 */
void MediumEnemy::positionEnemy(Level *level, char direction, Shots *shots, Character *character)
{
    if (direction == 'd' && !this->isDead())
    {
        if (this->canGoRigth(level, shots, character) == 1)
        {
            level->deleteElement(this->x, this->y);
            this->x = this->x + 1;
            level->addElement(this->x, this->y, 'M');
        }
        else
        {
            level->deleteElement(this->x, this->y);
            this->x = this->x + 2;
            level->addElement(this->x, this->y, 'M');
        }
    }
    else if (direction == 'a' && !this->isDead())
    {
        if (this->canGoLeft(level, shots, character) == 1)
        {
            level->deleteElement(this->x, this->y);
            this->x = this->x - 1;
            level->addElement(this->x, this->y, 'M');
        }
        else
        {
            level->deleteElement(this->x, this->y);
            this->x = this->x - 2;
            level->addElement(this->x, this->y, 'M');
        }
    }
    else if (direction == 'w' && !this->isDead())
    {
        level->deleteElement(this->x, this->y);
        this->y = this->y - 2;
        level->addElement(this->x, this->y, 'M');
    }
    else if (direction == 's' && !this->isDead())
    {
        level->deleteElement(this->x, this->y);
        this->y = this->y + 2;
        level->addElement(this->x, this->y, 'M');
    }
}

/**
 * @brief funzione che controlla a ogni iterazione del ciclo principale del gioco se il MediumEnemy sta per 
 *        essere colpito da uno Shot del Player
 * 
 * @param level puntatore al livello corrente
 * @param shots puntatore agli Shots del Player
 */
void MediumEnemy::checkCollision(Level *level, Shots *shots)
{
    Shot *collisionShotRight = shots->foundShot(this->x + 1, this->y);
    Shot *collisionShotLeft = shots->foundShot(this->x - 1, this->y);
    if (collisionShotRight != NULL || collisionShotLeft != NULL)
    {
        if (collisionShotRight != NULL)
        {
            collisionShotRight->shouldStop = true;
        }
        else if (collisionShotLeft != NULL)
        {
            collisionShotLeft->shouldStop = true;
        }
        this->decreaseLife(20);
        if (this->isDead())
            this->isAlive = false;
    }
    if (!this->isAlive)
    {
        level->deleteElement(this->x, this->y);
    }
}

/**
 * @brief funzione che restituisce true se il MediumEnemy ha vita <= 0
 * 
 * @return true se il MediumEnemy è morto
 * @return false
 */
bool MediumEnemy::isDead()
{
    if (this->life <= 0)
        return true;
    else
        return false;
}

/**
 * @brief funzione che setta isAlive a false e life a 0, nel caso in cui il Player vada sopra il BasicEnemy
 * 
 */
void MediumEnemy::isKilledByPlayer() {
    this->isAlive = false;
    this->life = 0;
}