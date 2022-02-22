#include "BasicEnemiesList.hpp"

/**
 * @brief costruttore della classe BasicEnemiesList, esso inizializza i puntatori per gestire la lista dei
 *      BasicEnemies a NULL
 * 
 */
BasicEnemiesList::BasicEnemiesList()
{
    this->headBasicEnemiesList = NULL;
    this->currentBasicEnemy = NULL;
}

/**
 * @brief Funzione per l'inserimento in testa alla lista di un nuovo nodo BasicEnemy 
 *
 * @param x coordianta x del nuovo nodo BasicEnemy
 * @param y coordinata y del nuvoo nodo BasicEnemy
 * @param levelNumber numero del livello a cui appartiene il nuovo nodo BasicEnemy
 * @param enemyLife vita del nuvo nodo BasicEnemy
 */
void BasicEnemiesList::prependBasicEnemy(int x, int y, int levelNumber, int enemyLife)
{
    BasicEnemy *newEnemy = new BasicEnemy(x, y, enemyLife, levelNumber);
    newEnemy->nextEnemy = this->headBasicEnemiesList;
    this->headBasicEnemiesList = newEnemy;
    this->currentBasicEnemy = this->headBasicEnemiesList;
}

/**
 * @brief funzione per cancellare un elemento della lista: 
 *      la lista viene scansionata in updateBaicEnemies e la funzione viene chiamata se
 *      il nodo corrente va eliminato
 * 
 */
void BasicEnemiesList::deleteBasicEnemy()
{
    if (this->headBasicEnemiesList != NULL)
    {
        BasicEnemy *tmpEnemy = this->headBasicEnemiesList;
        BasicEnemy *prevEnemy = NULL;
        bool found = false;
        while (tmpEnemy != NULL && found == false)
        {
            if (tmpEnemy == this->currentBasicEnemy)
            {
                if (tmpEnemy == this->headBasicEnemiesList)
                {
                    if (tmpEnemy->nextEnemy != NULL)
                    {
                        this->headBasicEnemiesList = tmpEnemy->nextEnemy;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentBasicEnemy = this->headBasicEnemiesList;
                        found = true;
                    }
                    else
                    {
                        this->headBasicEnemiesList = NULL;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentBasicEnemy = this->headBasicEnemiesList;
                        found = true;
                    }
                }
                else
                {
                    prevEnemy->nextEnemy = tmpEnemy->nextEnemy;
                    delete tmpEnemy;
                    tmpEnemy = NULL;
                    this->currentBasicEnemy = prevEnemy;
                    found = true;
                }
            }
            if (!found)
            {
                prevEnemy = tmpEnemy;
                tmpEnemy = tmpEnemy->nextEnemy;
            }
        }
    }
}

/**
 * @brief funzione che scorre tutta la lista dei nemici e aggiorna ogni nodo che appartiene al livello corrente.
 *      Per ogni nodo aggiorna il suo stato e controlla se sta per essere colpito da uno Shot, nel caso il nodo 
 *      debba essere eliminato(vita a 0) viene chiamata deleteBasicEnemy.
 *          
 *
 * @param level puntatore al livello corrente
 * @param shots puntatore a una lista degli Shots
 */
void BasicEnemiesList::updateBasicEnemies(Level *level, Shots *shots)
{
    if (this->headBasicEnemiesList != NULL)
    {
        bool listFinished = false;
        while (this->currentBasicEnemy != NULL)
        {

            if (level->levelNumber == this->currentBasicEnemy->enemyLevelNumber)
            {
                if (!this->currentBasicEnemy->isDead())
                {
                    this->currentBasicEnemy->updateBasicEnemy(level);
                    this->currentBasicEnemy->checkCollision(level, shots);
                }
                else if (this->currentBasicEnemy->isDead())
                {
                    level->deleteElement(this->currentBasicEnemy->getX(), this->currentBasicEnemy->getY());
                    this->deleteBasicEnemy();
                    if (this->currentBasicEnemy == NULL)
                        listFinished = true;
                }
            }

            if (!listFinished)
                this->currentBasicEnemy = this->currentBasicEnemy->nextEnemy;
        }

        this->currentBasicEnemy = this->headBasicEnemiesList;
    }
}

/**
 * @brief funzione che permette di controllare la lista per cercare un nemico date le coordinate
 *
 * @param x coordinata x del nemico da trovare
 * @param y coordinata y del nemico da trovare
 * 
 * @return BasicEnemy* puntatore al nemico trovato, NULL se l'elemento non c'è
 */
BasicEnemy *BasicEnemiesList::foundBasicEnemy(int x, int y)
{
    if (this->headBasicEnemiesList != NULL)
    {
        BasicEnemy *tmpEnemy = this->headBasicEnemiesList;
        bool found = false;
        while (tmpEnemy != NULL && found == false)
        {
            if (tmpEnemy->getX() == x && tmpEnemy->getY() == y)
            {
                found = true;
                return tmpEnemy;
            }
            tmpEnemy = tmpEnemy->nextEnemy;
        }
    }
    return NULL;
}

/**
 * @brief Variante della funzione deleteBasicEnemy che cancella un nodo in base alle coordinate inserite.
 *          La funzione viene usata in altre classi per cancellare un nemico in base alle coordinate
 *          
 *
 * @param level Puntatore al livello corrente
 * @param x coordinata x del BasicEnemy da eliminare
 * @param y coordinata y del BasicEnemy da eliminare
 * 
 */
void BasicEnemiesList::deleteBasicEnemyWithXY(Level *level, int x, int y)
{
    if (this->headBasicEnemiesList != NULL)
    {
        BasicEnemy *tmpEnemy = this->headBasicEnemiesList;
        BasicEnemy *prevEnemy = NULL;
        bool found = false;
        while (tmpEnemy != NULL && found == false)
        {
            if (tmpEnemy->getX() == x && tmpEnemy->getY() == y)
            {
                level->deleteElement(tmpEnemy->getX(), tmpEnemy->getY());
                if (tmpEnemy == this->headBasicEnemiesList)
                {
                    if (tmpEnemy->nextEnemy != NULL)
                    {
                        this->headBasicEnemiesList = tmpEnemy->nextEnemy;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentBasicEnemy = this->headBasicEnemiesList;
                        found = true;
                    }
                    else
                    {
                        this->headBasicEnemiesList = NULL;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentBasicEnemy = this->headBasicEnemiesList;
                        found = true;
                    }
                }
                else
                {
                    prevEnemy->nextEnemy = tmpEnemy->nextEnemy;
                    delete tmpEnemy;
                    tmpEnemy = NULL;
                    this->currentBasicEnemy = prevEnemy;
                    found = true;
                }
            }
            if (!found)
            {
                prevEnemy = tmpEnemy;
                tmpEnemy = tmpEnemy->nextEnemy;
            }
        }
    }
}