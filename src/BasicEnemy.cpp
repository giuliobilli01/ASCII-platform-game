#include "BasicEnemy.hpp"

/**
 * @brief costruttore della classe BasicEnemy, estende il costruttore di Character da cui prende x, y, e life,
 *        e aggiunge il parametro enemyLevelNumber.
 *  
 * @param x coordinata x del BasicEnemy 
 * @param y coordinata y del BasicEnemy 
 * @param life vita del BasicEnemy
 * @param enemyLevelNumber numero del livello a cui appartiene il BasicEnemy
 */
BasicEnemy::BasicEnemy(int x, int y, int life, int enemyLevelNumber) : Character(x, y, life)
{
    this->nextEnemy = NULL;
    this->isAlive = true;
    this->enemyLevelNumber = enemyLevelNumber;
}

/**
 * @brief funzione per aggiornare il BasicEnemy, essa controlla ad ogni iterazione del ciclo principale 
 *        se il BasicEnemy è arrivato a life = 0, nel caso setta isAlive = false per comunicare alla gestione della
 *        lista che questo elemento va eliminato, se invece life != 0 allora ristampa il BasicEnemy
 *
 * @param level 
 */
void BasicEnemy::updateBasicEnemy(Level *level)
{
    if (this->isDead())
        this->isAlive = false;
    else
        level->addElement(this->x, this->y, 'K');
}

/**
 * @brief Funzione che controlla se il BasicEnemy sta per essere colpito da uno Shot
 *          controllando le due posizioni adiacenti a destra e a sinistra
 * 
 * @param level puntatore al livello corrente
 * @param shots puntatore alla lsita degli Shots
 */
void BasicEnemy::checkCollision(Level *level, Shots *shots)
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
        this->decreaseLife(10);
        if (this->isDead())
            this->isAlive = false;
    }
    if (!this->isAlive)
    {
        level->deleteElement(this->x, this->y);
    }
}

/**
 * @brief controlla se il BasicEnemy ha vita = 0, nel caso restituisce true
 * 
 * @return true se il BasicEnemy è morto
 * @return false se il BasicEnemy è vivo
 */
bool BasicEnemy::isDead()
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
void BasicEnemy::isKilledByPlayer()
{
    this->isAlive = false;
    this->life = 0;
}