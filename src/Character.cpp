#include "Character.hpp"

Character::Character() {}

/**
 * @brief Variante del costruttore della classe Character 
 * 		  che prende le coordinate X e Y, la vita e la direzione 
 * 
 * @param x 
 * @param y 
 * @param life 
 * @param direction 
 */
Character::Character(int x, int y, int life, Direction direction)
{
	this->x = x;
	this->y = y;
	this->life = life;
	this->direction = RIGHT;
}

/**
 * @brief Variante del costruttore della classe Character 
 * 		  che prende le coordinate X e Y e la vita
 *
 * @param x
 * @param y
 * @param life
 */
Character::Character(int x, int y, int life)
{
	this->x = x;
	this->y = y;
	this->life = life;
}

/**
 * @brief funzione per restituire il parametro Life del Character
 * 
 * @return int 
 */
int Character::getLIfe() {
	return this->life;
}

/**
 * @brief funzione per restituire la coordinata X del Character
 * 
 * @return int 
 */
int Character::getX() {
	return this->x;
}

/**
 * @brief funzione per restituire la coordinata Y del Character
 * 
 * @return int 
 */
int Character::getY() {
	return this->y;
}

/**
 * @brief funzione per decrementare del parametro inserito la vita del Character
 * 
 * @param dec quantità da sottrarre alla vita
 */
void Character::decreaseLife(int dec) {
	this->life -= dec;
}

/**
 * @brief funzione per incrementare della quantità inserita la vita del Character
 * 
 * @param inc 
 */
void Character::increaseLife(int inc) {
	this->life += inc;
}

/**
 * @brief restituisce il parametro direction del Character
 *
 * @return Direction 
 */
Direction Character::getDirection() {
	return this->direction;
}

/**
 * @brief funzione utilizzata per stampare a schermo la vita del Character
 * 			essa converte il parametro life da Int a Char e lo inserisce nella matrice
 *
 * @param level 
 */
void Character::printLife(Level *level)
{
	int i = 0, j = 0;
	char value[40];

	for (i = 0; i < 40; i++)
		value[i] = '\0';
	_itoa(this->life, value, 10);
	for (i = larghezza_max + 9, j = 0; i <= W_CONSOLE - 2; i++, j++)
	{
		level->deleteElement(i, H_CONSOLE - 12);

		if (value[j] != '\0')
			level->addElement(i, H_CONSOLE - 12, value[j]);
	}
}