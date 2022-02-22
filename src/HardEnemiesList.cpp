#include "HardEnemiesList.hpp"

/**
 * @brief costruttore della classe HardEnemiesList, setta a NULL i puntatori per la
 *         gestione della lista
 * 
 */
HardEnemiesList::HardEnemiesList()
{
    this->headHardEnemiesList = NULL;
    this->currentHardEnemy = NULL;
}

/**
 * @brief Funzione per l'inserimento in testa alla lista di un nuovo nodo HardEnemy 
 *
 * @param x coordianta x del nuovo nodo HardEnemy
 * @param y coordinata y del nuvoo nodo HardEnemy
 * @param levelNumber numero del livello a cui appartiene il nuovo nodo HardEnemy
 * @param enemyLife vita del nuvo nodo HardEnemy
 */
void HardEnemiesList::prependHardEnemy(int x, int y, int levelNumber, int enemyLife)
{
    HardEnemy *newEnemy = new HardEnemy(x, y, 70, RIGHT, levelNumber);
    newEnemy->nextEnemy = this->headHardEnemiesList;
    this->headHardEnemiesList = newEnemy;
    this->currentHardEnemy = this->headHardEnemiesList;
}

/**
 * @brief funzione per cancellare un elemento della lista: 
 *      la lista viene scansionata in updateBaicEnemies e la funzione viene chiamata se
 *      il nodo corrente va eliminato
 */
void HardEnemiesList::deleteHardEnemy()
{
    if (this->headHardEnemiesList != NULL)
    {
        HardEnemy *tmpEnemy = this->headHardEnemiesList;
        HardEnemy *prevEnemy = NULL;
        bool found = false;
        while (tmpEnemy != NULL && found == false)
        {
            if (tmpEnemy == this->currentHardEnemy)
            {
                if (tmpEnemy == this->headHardEnemiesList)
                {
                    if (tmpEnemy->nextEnemy != NULL)
                    {
                        this->headHardEnemiesList = tmpEnemy->nextEnemy;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentHardEnemy = this->headHardEnemiesList;
                        found = true;
                    }
                    else
                    {
                        this->headHardEnemiesList = NULL;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentHardEnemy = this->headHardEnemiesList;
                        found = true;
                    }
                }
                else
                {
                    prevEnemy->nextEnemy = tmpEnemy->nextEnemy;
                    delete tmpEnemy;
                    tmpEnemy = NULL;
                    this->currentHardEnemy = prevEnemy;
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
 *      debba essere eliminato(vita a 0) viene chiamata deleteHardEnemy.
 *          
 *
 * @param level puntatore al livello corrente
 * @param shots puntatore a una lista degli Shots
 */
void HardEnemiesList::updateHardEnemies(Level *level, Shots *playerShots, Shots *myShots, Character *character)
{
    if (this->headHardEnemiesList != NULL)
    {
        bool listFinished = false;
        while (this->currentHardEnemy != NULL)
        {

            if (level->levelNumber == this->currentHardEnemy->enemyLevelNumber)
            {
                if (!this->currentHardEnemy->isDead())
                {
                    this->currentHardEnemy->updateHardEnemy(level, myShots, character);
                    this->currentHardEnemy->checkCollision(level, playerShots);
                }
                else if (this->currentHardEnemy->isDead())
                {
                    level->deleteElement(this->currentHardEnemy->getX(), this->currentHardEnemy->getY());
                    this->deleteHardEnemy();
                    if (this->currentHardEnemy == NULL)
                        listFinished = true;
                }
            }

            if (!listFinished)
                this->currentHardEnemy = this->currentHardEnemy->nextEnemy;
        }

        this->currentHardEnemy = this->headHardEnemiesList;
    }
}

/**
 * @brief funzione che permette di controllare la lista per cercare un nemico date le coordinate
 *
 * @param x coordinata x del nemico da trovare
 * @param y coordinata y del nemico da trovare
 * 
 * @return HardEnemy* puntatore al nemico trovato, NULL se l'elemento non c'è
 */
HardEnemy *HardEnemiesList::foundHardEnemy(int x, int y)
{
    if (this->headHardEnemiesList != NULL)
    {
        HardEnemy *tmpEnemy = this->headHardEnemiesList;
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
 * @param x coordinata x dell'HardEnemy da eliminare
 * @param y coordinata y dell'HardEnemy da eliminare
 * 
 */
void HardEnemiesList::deleteHardEnemyWithXY(Level *level, int x, int y)
{
    if (this->headHardEnemiesList != NULL)
    {
        HardEnemy *tmpEnemy = this->headHardEnemiesList;
        HardEnemy *prevEnemy = NULL;
        bool found = false;
        while (tmpEnemy != NULL && found == false)
        {
            if (tmpEnemy->getX() == x && tmpEnemy->getY() == y)
            {
                level->deleteElement(tmpEnemy->getX(), tmpEnemy->getY());
                if (tmpEnemy == this->headHardEnemiesList)
                {
                    if (tmpEnemy->nextEnemy != NULL)
                    {
                        this->headHardEnemiesList = tmpEnemy->nextEnemy;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentHardEnemy = this->headHardEnemiesList;
                        found = true;
                    }
                    else
                    {
                        this->headHardEnemiesList = NULL;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentHardEnemy = this->headHardEnemiesList;
                        found = true;
                    }
                }
                else
                {
                    prevEnemy->nextEnemy = tmpEnemy->nextEnemy;
                    delete tmpEnemy;
                    tmpEnemy = NULL;
                    this->currentHardEnemy = prevEnemy;
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