#include "HardEnemy.hpp"

/**
 * @brief costruttore della classe HardEnemy, estende il costruttore di Character da cui prende
 *          x, y, life e direction, poi prende il enemyLevelNumber, ovvero il numero del livello
 *          a cui è asseganto l'HardEnemy
 *      
 *
 * @param x coordinata x dell'HardEnemy
 * @param y coordinata y dell'HardEnemy
 * @param life vita dell'HardEnemy
 * @param direction direzione in cui deve sparare l'HardEnemy
 * @param enemyLevelNumber numero del livello a cui è assegnato l'HardEnemy
 */
HardEnemy::HardEnemy(int x, int y, int life, Direction direction, int enemyLevelNumber) : Character(x, y, life, direction)
{
    this->nextEnemy = NULL;
    this->isAlive = true;
    this->enemyLevelNumber = enemyLevelNumber;
}

/**
 * @brief funzione utilizzata per far sparare l'HardEnemy
 *          essa con una frequenza randomica genera uno sparo se il
 *          Player è nel campo visivo dell'HardEnemy
 * 
 * @param level puntatore al Level corrente
 * @param myshots puntatore alla lista di Shots degli HardEnemy
 * @param character puntatore a Character
 */
void HardEnemy::shotHardEnemy(Level *level, Shots *myShots, Character *character)
{

    if ((rand() % 15 + 1) == 5)
    {
        if ((character->getY() == this->getY()) &&
            (abs(character->getX() - this->getX()) < 20))
        {

            if (character->getX() < this->getX())
            {
                this->direction = LEFT;
                myShots->prependShot(this->x - 1, this->y, this->direction, '*');
            }
            else
            {
                this->direction = RIGHT;
                myShots->prependShot(this->x + 1, this->y, this->direction, '*');
            }
        }
    }
}

/**
 * @brief funzione che aggiorna lo stato dell'HardEnemy, se è ancora vivo viene ristampato e viene 
 *          chiamata la funzione per sparare
 * 
 * @param level puntatore al livello corrente
 * @param myShots puntatore alla lista degli Shots degli HardEnemy
 * @param character puntatore a Character
 */
void HardEnemy::updateHardEnemy(Level *level, Shots *myShots, Character *character)
{
    if (this->isDead())
    {
        this->isAlive = false;
    }
    else
    {
        level->addElement(this->x, this->y, 'H');
        this->shotHardEnemy(level, myShots, character);
    }
}

/**
 * @brief funzione che controlla a ogni iterazione del ciclo principale se l'HardEnemy sta per essere colpito da 
 *        uno Shot del Player
 * 
 * @param level puntatore al livello corrente
 * @param playerShots puntatore alla lista degli Shots del Player
 */
void HardEnemy::checkCollision(Level *level, Shots *playerShots)
{
    Shot *collisionShotRight = playerShots->foundShot(this->x + 1, this->y);
    Shot *collisionShotLeft = playerShots->foundShot(this->x - 1, this->y);
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
 * @brief controlla se l'HardEnemy ha vita = 0, nel caso restituisce true
 * 
 * @return true se l'HardEnemy è morto
 * @return false se l'HardEnemy è vivo
 */
bool HardEnemy::isDead()
{
    if (this->life <= 0)
        return true;
    else
        return false;
}

/**
 * @brief funzione che setta isAlive a false e life a 0, nel caso in cui il Player vada sopra l'HardEnemy 
 * 
 */
void HardEnemy::isKilledByPlayer()
{
    this->isAlive = false;
    this->life = 0;
}