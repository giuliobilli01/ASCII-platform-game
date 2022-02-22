#include "Shots.hpp"

/**
 * @brief Costruttore della classe Shots, setta a NULL i puntatori della lista
 * 
 */
Shots::Shots() {
    this->headShotList = NULL;
    this->currentShot = NULL;
}


/**
 * @brief inserisce in testa alla lista degli Shots un nuovo nodo Shot
 * 
 * @param x coordinata dello shot
 * @param y coordinata dello shot
 * @param direction direzione in cui deve muoversi lo shot
 * @param ch carattere dello shot
 */
void Shots::prependShot(int x, int y, Direction direction, char ch) {
    Shot* newShot = new Shot(x, y, direction, ch);
    newShot->nextShot = this->headShotList;
    this->headShotList = newShot;
    this->currentShot  = this->headShotList;
}


/**
 * @brief funzione che aggiorna la lista degli shot spostando avanti di uno gli shot 
 *        nella direzione in cui stanno andando e eliminando gli shot che non possono più andare avanti
 * 
 * @param level puntatore alla matrice del livello corrente
 */
void Shots::updateShots(Level* level) {
    if(this->headShotList != NULL) {

        while(this->currentShot != NULL) {
            this->currentShot->updateShotPosition(level);
            
            if(this->currentShot->shouldStop) {
                level->deleteElement(this->currentShot->getX(), this->currentShot->getY());
                this->deleteShot();
            }else{
                this->currentShot = this->currentShot->nextShot;
            }
        }
        
        //resetto il puntatore currentShot in testa
        this->currentShot = this->headShotList;
    }
}


/**
 * @brief cancella il nodo shot nel caso in cui debba fermarsi
 * 
 */
void Shots::deleteShot() {
    if(this->headShotList != NULL) {
        Shot* tmpShot = this->headShotList;
        Shot* prevShot = NULL;
        bool found = false;
        while(tmpShot != NULL && found == false) {
            if (tmpShot == this->currentShot) {
                if (tmpShot == this->headShotList) {
                    if(tmpShot->nextShot != NULL){
                    this->headShotList = tmpShot->nextShot;
                    delete tmpShot;
                    tmpShot = NULL;
                    this->currentShot = this->headShotList;
                    found = true;
                    }else {
                        this->headShotList = NULL;
                        delete tmpShot;
                        tmpShot = NULL;
                        this->currentShot = this->headShotList;
                        found = true;
                    }
                
                }
                else
                {
                    prevShot->nextShot = tmpShot->nextShot;
                    delete tmpShot;
                    tmpShot = NULL;
                    this->currentShot = prevShot;
                    found = true;
                }
            }
                if(!found) {
                prevShot = tmpShot;
                tmpShot = tmpShot->nextShot;
                }
        }
    }
}


/**
 * @brief cerca nella lista degli shot uno shot che abbia 
 *        le coordinate prese in input e restituisce un puntatore ad esso
 * 
 * @param x coordinata dello shot da trovare
 * @param y coordinata dello shot da trovare
 *
 * @return Shot* puntatore allo shot 
 */
Shot* Shots::foundShot(int x, int y) {
    if(this->headShotList != NULL) {
        Shot* tmpShot = this->headShotList;
        bool found = false;
        while(tmpShot != NULL && found == false) {
            if(tmpShot->getX() == x && tmpShot->getY() == y) {
                found = true;
                return tmpShot;
            }
            tmpShot = tmpShot->nextShot;
        }
    }
    return NULL;
}


/**
 * @brief cancella interamente la lista degli shot
 * 
 * @param level puntatore alla matrice del livello corrente
 */
void Shots::deleteList(Level* level) {
    if(this->headShotList != NULL) {
        Shot* tmpShot = this->headShotList;
        while(tmpShot != NULL) {
            if (tmpShot == this->headShotList) {
                    if(tmpShot->nextShot != NULL){
                        level->deleteElement(tmpShot->getX(), tmpShot->getY());
                        this->headShotList = tmpShot->nextShot;
                        delete tmpShot;
                        tmpShot = NULL;
                        tmpShot = this->headShotList;
                    }else {
                        level->deleteElement(tmpShot->getX(), tmpShot->getY());
                        this->headShotList = NULL;
                        delete tmpShot;
                        tmpShot = NULL;
                    }
            }

        }
    }
}