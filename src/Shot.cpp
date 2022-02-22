#include "Shot.hpp"

/**
 * @brief costruttore della classe Shot
 * 
 * @param x coordinata x dello shot
 * @param y coordinata y dello shot
 * @param direction direzione in cui è stato sparato lo shot 
 * @param ownerCharacter carattere che contraddistingue chi ha sparato
 */
Shot::Shot(int x, int y, Direction direction, char ownerCharacter) {
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->nextShot = NULL;
    this->shouldStop = false;
    this->ownerCharacter = ownerCharacter;
}


/**
 * @brief funzione che aggiorna la posizione dello Shot, controllando se la posizione 
 *          in cui deve andare è libera
 * 
 * @param level puntatore al livello corrente
 */
void Shot::updateShotPosition(Level* level) {

    if(this->direction == RIGHT){
    
        if(this->CanIRight(level) == 1) {
            level->deleteElement(this->x, this->y);
            this->x++;
            level->addElement(this->x, this->y, this->ownerCharacter);   
        }
        else if(this->CanIRight(level) == 2) {
            level->deleteElement(this->x, this->y);
            this->x = this->x + 2;
        }
        else {
            level->deleteElement(this->x, this->y);
            this->shouldStop = true;
        }
    }
    else if(this->direction == LEFT) {

        if(this->CanILeft(level) == 1) {
            level->deleteElement(this->x, this->y);
            this->x--;
            level->addElement(this->x, this->y, this->ownerCharacter);
        }
        else if(this->CanILeft(level) == 2) {
            level->deleteElement(this->x, this->y);
            this->x = this->x - 2;
        }
        else {
            level->deleteElement(this->x, this->y);
            this->shouldStop = true;
        }
    }
}

/**
 * @brief funzione che controlla se lo Shot può spostarsi nella cella 
 *        alla sua destra, controllando il suo contenuto 
 *         
 * @param level puntatore al livello corrente
 *
 * @return int intero che identifica il movimento da fare: 
 *          1 --> si sposta nella cella accanto
 *          2 --> si sposta di due celle se deve scavalcare qualcosa
 *          3 --> si ferma
 */
int Shot::CanIRight(Level* level){
    if ((level->getChar(this->y, this->x + 1) != '#') &&
		(level->getChar(this->y, this->x + 1) != '|') &&
        (level->getChar(this->y, this->x + 1) != '(') &&
        (level->getChar(this->y, this->x + 1) != ')') &&
        (level->getChar(this->y, this->x + 1) != '$') &&
        (level->getChar(this->y, this->x + 1) != 'L') &&
        (level->getChar(this->y, this->x + 1) != '-') &&
        (level->getChar(this->y, this->x + 1) != 'K') &&
        (level->getChar(this->y, this->x + 1) != 'M') &&
        (level->getChar(this->y, this->x + 1) != 'H') &&
        (level->getChar(this->y, this->x + 1) != '@')){
        return 1;
    }
    else if(((level->getChar(this->y, this->x + 1) == '$') ||
            (level->getChar(this->y, this->x + 1) == 'L')) &&
            (level->getChar(this->y, this->x + 2) != '#') &&
            (level->getChar(this->y, this->x + 2) != '|') &&
            (level->getChar(this->y, this->x + 2) != '(') &&
            (level->getChar(this->y, this->x + 2) != ')') ){   
        return 2;
    }
    else if(((level->getChar(this->y, this->x + 1) == '$') ||
            (level->getChar(this->y, this->x + 1) == 'L') ||
            (level->getChar(this->y, this->x + 1) == 'M')) &&
            ((level->getChar(this->y, this->x + 2) == '#') ||
            (level->getChar(this->y, this->x + 2) == '|') ||
            (level->getChar(this->y, this->x + 2) == '(') ||
            (level->getChar(this->y, this->x + 2) == ')')) ){
        return 3;
    }
    else if((level->getChar(this->y, this->x + 1) == '-') || 
            (level->getChar(this->y, this->x + 2) == '-') ){
        return 3;
    }
    else if((level->getChar(this->y, this->x + 1) == '@') &&
            (level->getChar(this->y, this->x + 1) == 'K') &&
            (level->getChar(this->y, this->x + 1) == 'M') &&
            (level->getChar(this->y, this->x + 1) == 'H')) {
        return 3;
    }
    else {
        return 3;
    }    
}

/**
 * @brief funzione che controlla se lo Shot può spostarsi nella cella 
 *        alla sua sinistra, controllando il suo contenuto 
 *         
 * @param level puntatore al livello corrente
 *
 * @return int intero che identifica il movimento da fare: 
 *          1 --> si sposta nella cella accanto
 *          2 --> si sposta di due celle se deve scavalcare qualcosa
 *          3 --> si ferma
 */
int Shot::CanILeft(Level* level) {
    if ((level->getChar(this->y, this->x - 1) != '#') &&
		(level->getChar(this->y, this->x - 1) != '|') &&
        (level->getChar(this->y, this->x - 1) != '(') &&
        (level->getChar(this->y, this->x - 1) != ')') &&
        (level->getChar(this->y, this->x - 1) != '$') &&
        (level->getChar(this->y, this->x - 1) != 'L') &&
        (level->getChar(this->y, this->x - 1) != '-') &&
        (level->getChar(this->y, this->x - 1) != 'K') &&
        (level->getChar(this->y, this->x - 1) != 'M') &&
        (level->getChar(this->y, this->x - 1) != 'H') &&
        (level->getChar(this->y, this->x - 1) != '@')){
        return 1;
    }
    else if(((level->getChar(this->y, this->x - 1) == '$') ||
            (level->getChar(this->y, this->x - 1) == 'L')) &&
            (level->getChar(this->y, this->x - 2) != '#') &&
            (level->getChar(this->y, this->x - 2) != '|') &&
            (level->getChar(this->y, this->x - 2) != '(') &&
            (level->getChar(this->y, this->x - 2) != ')')){
        return 2;
    }
    else if(((level->getChar(this->y, this->x - 1) == '$') ||
            (level->getChar(this->y, this->x - 1) == 'L') ||
            (level->getChar(this->y, this->x - 1) == 'M')) &&
            ((level->getChar(this->y, this->x - 2) == '#') ||
            (level->getChar(this->y, this->x - 2) == '|') ||
            (level->getChar(this->y, this->x - 2) == '(') ||
            (level->getChar(this->y, this->x - 2) == ')'))){
        return 3;
    }
    else if((level->getChar(this->y, this->x - 1) == '-') || 
            (level->getChar(this->y, this->x - 2) == '-')){
        return 3;
    }
    else if((level->getChar(this->y, this->x - 1) == '@') &&
            (level->getChar(this->y, this->x - 1) == 'K') &&
            (level->getChar(this->y, this->x - 1) == 'M') &&
            (level->getChar(this->y, this->x - 1) == 'H')) {
        return 3;
    }
    else {
        return 3;
    }
}


/**
 * @brief resistuisce la coordinata x del proiettile
 * 
 * @return int 
 */
int Shot::getX(){
    return this->x;
}


/**
 * @brief resistuisce la coordinata y del proiettile
 * 
 * @return int 
 */
int Shot::getY(){
    return this->y;
}