#include "Levels.hpp"

/**
 * @brief Costruttore della classe Levels, setta i puntatori per la gestione dei puntatori
 * 			generando e stampando il livello 0.
 * 
 */
Levels::Levels()
{
	this->levelCounter = 0;
	this->headlevelList = new Level(this->levelCounter);
	this->currentLevel = this->headlevelList;
	this->lastLevel = this->headlevelList;
	this->currentLevel->printRoom();
}

/**
 * @brief funzione che sposta i vari puntatori per passare al 
 * 			livello successivo. Se il livello successivo non esiste ne viene 
 * 			creato un altro e il puntatore currentLevel viene spostato su questo livello.
 * 			
 */
void Levels::goToNextLevel()
{

	if (this->headlevelList != NULL && this->currentLevel != NULL)
	{
		if (this->currentLevel->nextLevel != NULL)
		{
			this->currentLevel->nextLevel->prevLevel = this->currentLevel;
			this->currentLevel = this->currentLevel->nextLevel;
		}
		else
		{
			this->currentLevel->nextLevel = new Level(this->levelCounter + 1);
			this->currentLevel->nextLevel->prevLevel = this->currentLevel;
			this->currentLevel = this->currentLevel->nextLevel;
			this->lastLevel = this->currentLevel;
			this->levelCounter++;
		}
	}
}

/**
 * @brief funzione che sposta i vari puntatori per passare al 
 * 			livello precedente. Nel caso in cui il currentLevel sia 
 * 			uguale al livello in testa non si ha la possibilità di andare
 * 			a un livello precedente
 * 
 */
void Levels::goToPrevLevel()
{

	if (!this->isFirstLevel())
	{
		this->currentLevel = this->currentLevel->prevLevel;
		//this->currentLevel->printRoom();
	}
}

/**
 * @brief funzione booleana che ritorna true se il 
 * 			currentLevel è uguale al livello 0 ovvero alla testa.
 * 
 * @return true se il currentLevel è uguale al livello 0 ovvero alla testa.
 * @return false
 */
bool Levels::isFirstLevel()
{
	if (this->currentLevel == this->headlevelList && this->currentLevel->prevLevel == NULL)
		return true;
	else
		return false;
}

/**
 * @brief funzione che permette di accedere al livello corrente
 * 			restituendo un puntatore ad esso
 * 
 * @return Level* puntatore al livello corrente
 */
Level *Levels::getLevel()
{
	return this->currentLevel;
}

/**
 * @brief ritorna true se il livello corrente è l'ultimo nella lista
 * 
 * @return true se il livello corrente è l'ultimo nella lista
 * @return false
 */
bool Levels::isLastLevel()
{
	if (this->currentLevel->nextLevel == NULL)
		return true;
	else
		return false;
}

/**
 * @brief ritorna true se il livello corrente è stato già visitato
 * 
 * @return true se il livello corrente è stato già visitato
 * @return false
 */
bool Levels::isExplorated()
{
	if (this->currentLevel->isExplorated)
		return true;
	else
		return false;
}

/**
 * @brief permette di settare a true il parametro isExplorated
 * 			che determina se un livello è già stato visitato
 * 
 */
void Levels::setExplorationTrue()
{
	this->currentLevel->isExplorated = true;
}