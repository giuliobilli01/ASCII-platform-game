#include "MediumEnemiesList.hpp"

/**
 * @brief costruttore della classe MediumEnemiesList, inizializza i puntatori per gestire la lista
 *      a NULL 
 *  
 */
MediumEnemiesList::MediumEnemiesList()
{
    this->headMediumEnemiesList = NULL;
    this->currentMediumEnemy = NULL;
}

/**
 * @brief inserisce in testa alla lista dei MediumEnemy un nuovo nodo MediumEnemy
 * 
 * @param x coordinata x del MediumEnemy
 * @param y coordinata y del MediumEnemy
 * @param levelNumber numero del livello a cui appartiene il MediumEnemy
 */
void MediumEnemiesList::prependMediumEnemy(int x, int y, int levelNumber, int enemyLife)
{
    MediumEnemy *newEnemy = new MediumEnemy(x, y, enemyLife, levelNumber);
    newEnemy->nextEnemy = this->headMediumEnemiesList;
    this->headMediumEnemiesList = newEnemy;
    this->currentMediumEnemy = this->headMediumEnemiesList;
}

/**
 * @brief aggiorna ogni nodo della lista, richiamando la funzione di movimento di ogni MediumEnemy e controllando
 *          se si verificano collisioni. Nel caso in cui un MediumEnemy ha vita zero viene chiamata la funzione per
 *          eliminare il nodo
 * 
 * @param level puntatore al livello corrente
 * @param shots puntatore alla lista degli shots
 * @param character puntatore Character 
 */
void MediumEnemiesList::updateMediumEnemies(Level *level, Shots *shots, Character *character)
{
    if (this->headMediumEnemiesList != NULL)
    {
        bool listFinished = false;
        while (this->currentMediumEnemy != NULL)
        {

            if (level->levelNumber == this->currentMediumEnemy->enemyLevelNumber)
            {
                if (!this->currentMediumEnemy->isDead())
                {
                    this->currentMediumEnemy->moveMediumEnemy(level, shots, character);
                    this->currentMediumEnemy->checkCollision(level, shots);
                }
                else if (!this->currentMediumEnemy->isAlive)
                {
                    this->deleteMediumEnemy();
                    if (this->currentMediumEnemy == NULL)
                        listFinished = true;
                }
            }

            if (!listFinished)
                this->currentMediumEnemy = this->currentMediumEnemy->nextEnemy;
        }

        this->currentMediumEnemy = this->headMediumEnemiesList;
    }
}

/**
 * @brief funzione per cancellare un elemento della lista: 
 *      la lista viene scansionata in updateMediumEnemies e la funzione viene chiamata se
 *      il nodo corrente va eliminato
 *  
 */
void MediumEnemiesList::deleteMediumEnemy()
{
    if (this->headMediumEnemiesList != NULL)
    {
        MediumEnemy *tmpEnemy = this->headMediumEnemiesList;
        MediumEnemy *prevEnemy = NULL;
        bool found = false;
        while (tmpEnemy != NULL && found == false)
        {
            if (tmpEnemy == this->currentMediumEnemy)
            {
                if (tmpEnemy == this->headMediumEnemiesList)
                {
                    if (tmpEnemy->nextEnemy != NULL)
                    {
                        this->headMediumEnemiesList = tmpEnemy->nextEnemy;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentMediumEnemy = this->headMediumEnemiesList;
                        found = true;
                    }
                    else
                    {
                        this->headMediumEnemiesList = NULL;
                        delete tmpEnemy;
                        tmpEnemy = NULL;
                        this->currentMediumEnemy = this->headMediumEnemiesList;
                        found = true;
                    }
                }
                else
                {
                    prevEnemy->nextEnemy = tmpEnemy->nextEnemy;
                    delete tmpEnemy;
                    tmpEnemy = NULL;
                    this->currentMediumEnemy = prevEnemy;
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
 * @brief funzione che permette di controllare la lista per cercare un nemico date le coordinate
 *
 * @param x coordinata x del nemico da trovare
 * @param y coordinata y del nemico da trovare
 * 
 * @return MediumEnemy* puntatore al nemico trovato, NULL se l'elemento non c'è
 */
MediumEnemy* MediumEnemiesList::foundMediumEnemy(int x, int y)
{
    if (this->headMediumEnemiesList != NULL)
    {
        MediumEnemy *tmpEnemy = this->headMediumEnemiesList;
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