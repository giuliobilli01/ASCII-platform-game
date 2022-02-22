#include "Player.hpp"

/**
 * @brief Costruttore della classe Player, esso estende il costruttore di Character da cui prende i parametri
 * 		x, y, life, direction e prende anche i punti, che all'inizio sono a 0.
 * 
 * @param x coordinata x del Player
 * @param y coordinata y del Player
 * @param life vita iniziale del Player
 * @param direction direzione iniziale del Player(inizialmente viene settata a destra)
 * @param points punti iniziali del Player
 */
Player::Player(int x, int y, int  life, Direction direction, int points):Character(x, y, life, direction) {
	this->points = points;
	this->shouldChangeLevel = CURRENT_LEVEL;
	
}


/**
 * @brief Funzione che aggiorna la posizione del Player dopo i controlli avvenuti in movePlayer.
 * 		La funzione inserisce il carattere @ ,che indica il Player, nella cella corrispondente alla nuova posizione
 * 		poi stampa la cella. 
 * 
 * @param input carattere che identifica la direzione in cui deve spostarsi il Player
 * @param level puntatore al livello corrente
 */
void Player::updatePlayerPosition(char input, Level* level) {
	
	if (input == 'w') {
		level->deleteElement(this->x, this->y);
		this->y = this->y - 2;
		level->addElement(this->x, this->y, '@');
	}
	if (input == 'a') {
		level->deleteElement(this->x, this->y);
		this->x--;
		level->addElement(this->x, this->y, '@');
	}
	if (input == 's') {
		level->deleteElement(this->x, this->y);
		this->y = this->y + 2;
		level->addElement(this->x, this->y, '@');
	}
	if (input == 'd') {
		level->deleteElement(this->x, this->y);
		this->x++;
		level->addElement(this->x, this->y, '@');
	}
}


/**
 * @brief funzione che permette il movimento del Player nelle 4 direzioni tramite i comandi "W" "A" "S" "D".
 * 			Per ogni direzione viene controllato il contenuto della cella in cui bisogna spostarsi per 
 * 			capire se il movimento è possibile oppure no. In alcuni casi il contenuto della cella può 
 * 			generare un cambiamento dei parametri del Player come la vita se va su un nemico,
 * 			oppure il cambio del livello se va su una porta. Ogni cambiamento provoca 
 * 			la stampa  dei dati aggiornati del Player.
 * 
 * @param input carattere in input da tastiera
 * @param levels lista dei livelli 
 * @param basicEnemies lista dei basicEnemies per controllare eventuali collisioni o generare variazioni della vita
 * @param mediumEnemies lista dei mediumEnemies per controllare eventuali collisioni o generare variazioni della vita
 * @param hardEnemies lista degli hardEnemies per controllare eventuali collisioni o generare variazioni della vita
 */
void Player::movePlayer(char input, Levels* levels, BasicEnemiesList* basicEnemies, MediumEnemiesList* mediumEnemies, HardEnemiesList* hardEnemies) {
	if (input == 'w') {
		if ((levels->getLevel()->getChar(this->y - 1, this->x) == '=') &&
			(levels->getLevel()->getChar(this->y - 2, this->x) != '#') &&
			(levels->getLevel()->getChar(this->y - 2, this->x) != '|')) {
			
			if (levels->getLevel()->getChar(this->y - 2, this->x) == '(') {
				levels->getLevel()->deleteElement(this->x, this->y);
				this->setShouldChangeLevel(PREV_LEVEL);

			} else if (levels->getLevel()->getChar(this->y - 2, this->x) == ')') {
				levels->getLevel()->deleteElement(this->x, this->y);
				this->setShouldChangeLevel(NEXT_LEVEL);

			} else if(levels->getLevel()->getChar(this->y - 2, this->x) == '*') {
				this->decreaseLife(10);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printLife(levels->getLevel());

			} else if(levels->getLevel()->getChar(this->y - 2, this->x) == '$') {
				this->increasePoints(20);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printPlayerPoints(levels->getLevel());
				this->checkPoints(levels->getLevel());

			} else if(levels->getLevel()->getChar(this->y - 2, this->x) == 'L') {
				this->increaseLife(20);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printLife(levels->getLevel());
			
			} else if(levels->getLevel()->getChar(this->y - 2, this->x) == 'K') {
				if(basicEnemies->foundBasicEnemy(this->x, this->y - 2) != NULL) {
					basicEnemies->foundBasicEnemy(this->x, this->y - 2)->isKilledByPlayer();
					basicEnemies->deleteBasicEnemyWithXY(levels->getLevel(), this->x, this->y - 2);
				}
				this->decreaseLife(30);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());

			} else if(levels->getLevel()->getChar(this->y - 2, this->x) == 'M') {
				if(mediumEnemies->foundMediumEnemy(this->x, this->y - 2) != NULL)
					mediumEnemies->foundMediumEnemy(this->x, this->y - 2)->isKilledByPlayer();
				this->decreaseLife(20);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());

			} else if(levels->getLevel()->getChar(this->y - 2, this->x) == 'H') {
				if(hardEnemies->foundHardEnemy(this->x, this->y - 2) != NULL) {
					hardEnemies->foundHardEnemy(this->x, this->y - 2)->isKilledByPlayer();
					hardEnemies->deleteHardEnemyWithXY(levels->getLevel(), this->x, this->y - 2);
				}
				this->decreaseLife(50);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());
			
			} else {
				this->updatePlayerPosition(input, levels->getLevel());
			}
		}
	}
	if (input == 'a') {
		if ((levels->getLevel()->getChar(this->y, this->x - 1) != '#') &&
			(levels->getLevel()->getChar(this->y, this->x - 1) != '|') &&
			(levels->getLevel()->getChar(this->y + 1, this->x - 1) != '\0')) {
					
			if (levels->getLevel()->getChar(this->y, this->x - 1) == '(') {
				levels->getLevel()->deleteElement(this->x, this->y);
				
				this->setShouldChangeLevel(PREV_LEVEL);
				this->direction = LEFT;

			} else if (levels->getLevel()->getChar(this->y, this->x - 1) == ')') {
				levels->getLevel()->deleteElement(this->x, this->y);
				
				this->setShouldChangeLevel(NEXT_LEVEL);
				this->direction = LEFT;
				
			} else if(levels->getLevel()->getChar(this->y, this->x - 1) == '*') {
				this->decreaseLife(10);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printLife(levels->getLevel());

			} else if(levels->getLevel()->getChar(this->y, this->x - 1) == '$') {
				this->increasePoints(20);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printPlayerPoints(levels->getLevel());
				this->checkPoints(levels->getLevel());

			} else if(levels->getLevel()->getChar(this->y, this->x - 1) == 'L') {
				this->increaseLife(20);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printLife(levels->getLevel());
		
			} else if(levels->getLevel()->getChar(this->y, this->x - 1) == 'K') {
				if(basicEnemies->foundBasicEnemy(this->x - 1, this->y) != NULL) {
					basicEnemies->foundBasicEnemy(this->x - 1, this->y)->isKilledByPlayer();
					basicEnemies->deleteBasicEnemyWithXY(levels->getLevel(), this->x - 1, this->y);
				}
				this->decreaseLife(30);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());

			} else if(levels->getLevel()->getChar(this->y, this->x - 1) == 'M') {
				if(mediumEnemies->foundMediumEnemy(this->x - 1, this->y) != NULL)
					mediumEnemies->foundMediumEnemy(this->x - 1, this->y)->isKilledByPlayer();
				this->decreaseLife(20);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());
			
			} else if(levels->getLevel()->getChar(this->y, this->x - 1) == 'H') {
				if(hardEnemies->foundHardEnemy(this->x - 1, this->y) != NULL) {
					hardEnemies->foundHardEnemy(this->x - 1, this->y)->isKilledByPlayer();
					hardEnemies->deleteHardEnemyWithXY(levels->getLevel(), this->x - 1, this->y);
				}
				this->decreaseLife(50);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());
					
			} else {
				this->updatePlayerPosition(input, levels->getLevel());
				this->direction = LEFT;
			}
		} 
	}
	if (input == 's') {
		if ((levels->getLevel()->getChar(this->y + 2, this->x) != '#') &&
			(levels->getLevel()->getChar(this->y + 2, this->x) != '|') &&
			(levels->getLevel()->getChar(this->y + 3, this->x) != '\0') &&
			(this->y != H_CONSOLE - 2)) {
			
			if (levels->getLevel()->getChar(this->y + 2, this->x) == '(') {
				levels->getLevel()->deleteElement(this->x, this->y);
				this->setShouldChangeLevel(PREV_LEVEL);
				
			} else if (levels->getLevel()->getChar(this->y + 2, this->x) == ')') {
				levels->getLevel()->deleteElement(this->x, this->y);
				this->setShouldChangeLevel(NEXT_LEVEL);
				
			} else if(levels->getLevel()->getChar(this->y + 2, this->x) == '*') {
				this->decreaseLife(10);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printLife(levels->getLevel());
			
			} else if(levels->getLevel()->getChar(this->y + 2, this->x) == '$') {
				this->increasePoints(20);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printPlayerPoints(levels->getLevel());
				this->checkPoints(levels->getLevel());
			
			} else if(levels->getLevel()->getChar(this->y + 2, this->x) == 'L') {
				this->increaseLife(20);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printLife(levels->getLevel());
				
			} else if(levels->getLevel()->getChar(this->y + 2, this->x) == 'K') {
				if(basicEnemies->foundBasicEnemy(this->x, this->y + 2) != NULL) {
					basicEnemies->foundBasicEnemy(this->x, this->y + 2)->isKilledByPlayer();
					basicEnemies->deleteBasicEnemyWithXY(levels->getLevel(), this->x, this->y + 2);
				}
				this->decreaseLife(30);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());
			
			} else if(levels->getLevel()->getChar(this->y + 2, this->x) == 'M') {
				if(mediumEnemies->foundMediumEnemy(this->x, this->y + 2) != NULL)
					mediumEnemies->foundMediumEnemy(this->x, this->y + 2)->isKilledByPlayer();
				this->decreaseLife(20);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());
			
			} else if(levels->getLevel()->getChar(this->y + 2, this->x) == 'H') {
				if(hardEnemies->foundHardEnemy(this->x, this->y + 2) != NULL) {
					hardEnemies->foundHardEnemy(this->x, this->y + 2)->isKilledByPlayer();
					hardEnemies->deleteHardEnemyWithXY(levels->getLevel(), this->x, this->y + 2);
				}
				this->decreaseLife(50);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());
			
			} else {
				this->updatePlayerPosition(input, levels->getLevel());
			}
		}
	}
	if (input == 'd') {
		if((levels->getLevel()->getChar(this->y, this->x + 1) != '#') &&
		   (levels->getLevel()->getChar(this->y, this->x + 1) != '|') &&
		   (levels->getLevel()->getChar(this->y + 1, this->x + 1) != '\0')) { 
		
			if (levels->getLevel()->getChar(this->y, this->x + 1) == '(') {
				levels->getLevel()->deleteElement(this->x, this->y);
				this->setShouldChangeLevel(PREV_LEVEL);
				this->direction = RIGHT;
				
			} else if (levels->getLevel()->getChar(this->y, this->x + 1) == ')') {
				levels->getLevel()->deleteElement(this->x, this->y);
				this->setShouldChangeLevel(NEXT_LEVEL);
				this->direction = RIGHT;
				
			} else if(levels->getLevel()->getChar(this->y, this->x + 1) == '*') {
				this->decreaseLife(10);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printLife(levels->getLevel());
		
			} else if(levels->getLevel()->getChar(this->y, this->x + 1) == '$') {
				this->increasePoints(20);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printPlayerPoints(levels->getLevel());
				this->checkPoints(levels->getLevel());
		
			} else if(levels->getLevel()->getChar(this->y, this->x + 1) == 'L') {
				this->increaseLife(20);
				this->updatePlayerPosition(input, levels->getLevel());
				this->printLife(levels->getLevel());
		
			} else if(levels->getLevel()->getChar(this->y, this->x + 1) == 'K') {
				if(basicEnemies->foundBasicEnemy(this->x + 1, this->y) != NULL) {
					basicEnemies->foundBasicEnemy(this->x + 1, this->y)->isKilledByPlayer();
					basicEnemies->deleteBasicEnemyWithXY(levels->getLevel(),this->x + 1, this->y);
				}
				this->decreaseLife(30);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());
			
			} else if(levels->getLevel()->getChar(this->y, this->x + 1) == 'M') {
				if(mediumEnemies->foundMediumEnemy(this->x + 1, this->y) != NULL)
					mediumEnemies->foundMediumEnemy(this->x + 1, this->y)->isKilledByPlayer();
				this->decreaseLife(20);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());
			
			} else if(levels->getLevel()->getChar(this->y, this->x + 1) == 'H') {
				if(hardEnemies->foundHardEnemy(this->x + 1, this->y) != NULL) {
					hardEnemies->foundHardEnemy(this->x + 1, this->y)->isKilledByPlayer();
					hardEnemies->deleteHardEnemyWithXY(levels->getLevel(), this->x + 1, this->y);
				}
				this->decreaseLife(50);
				this->printLife(levels->getLevel());
				this->updatePlayerPosition(input, levels->getLevel());
			
			} else {
				this->setShouldChangeLevel(CURRENT_LEVEL);
				this->updatePlayerPosition(input, levels->getLevel());
				this->direction = RIGHT;
			}
		}
	}
}


/**
 * @brief restituisce i punti del Player
 * 
 * @return int 
 */
int Player::getPoints() {
	return this->points;
}


/**
 * @brief Questa funzione smista gli input ricevuti da tastiera nel ciclo principale di Play:
 * 			- Input uguale a "p":
 * 				- viene controllata il parametro direction del Player 
 * 					e viene aggiunto uno shot alla lista degli shots con quella direzione nel caso in cui possa sparare
 * 			- Input diverso da "p":
 * 				- l'input viene mandato alla funzione per il movimento del Player
 * 
 * @param input il carattere premuto da tastiera
 * @param levels la lista dei livelli
 * @param shots la lista degli spari
 * @param basicEnemies la lista dei basicEnemies
 * @param mediumEnemies la lista dei mediumEnemies
 * @param hardEnemies la lista degli hardEnemies
 */
void Player::checkPlayerInput(char input, Levels* levels, Shots* shots, BasicEnemiesList* basicEnemies, MediumEnemiesList* mediumEnemies, HardEnemiesList* hardEnemies) {
	if(input == 'p'){
		if(this->direction == RIGHT) {
			if(this->canShotRight(levels->getLevel())){ 
				shots->prependShot(this->x + 1, this->y, this->direction, '-');
			} else if(levels->getLevel()->getChar(this->y, this->x + 1) == 'K') {
				if(basicEnemies->foundBasicEnemy(this->x + 1, this->y) != NULL)
					basicEnemies->foundBasicEnemy(this->x + 1, this->y)->decreaseLife(10);

			} else if(levels->getLevel()->getChar(this->y, this->x + 1) == 'M') {
				if(mediumEnemies->foundMediumEnemy(this->x + 1, this->y) != NULL)
					mediumEnemies->foundMediumEnemy(this->x + 1, this->y)->decreaseLife(20);
		
			} else if(levels->getLevel()->getChar(this->y, this->x + 1) == 'H') {
				if(hardEnemies->foundHardEnemy(this->x + 1, this->y) != NULL)
					hardEnemies->foundHardEnemy(this->x + 1, this->y)->decreaseLife(30);
			}
		}
		if(this->direction == LEFT) {
			if(this->canShotLeft(levels->getLevel())){
				shots->prependShot(this->x - 1, this->y, this->direction, '-');
			} else if(levels->getLevel()->getChar(this->y, this->x - 1) == 'K') {
				if(basicEnemies->foundBasicEnemy(this->x - 1, this->y) != NULL)
					basicEnemies->foundBasicEnemy(this->x - 1, this->y)->decreaseLife(10);
				
			} else if(levels->getLevel()->getChar(this->y, this->x - 1) == 'M') {
				if(mediumEnemies->foundMediumEnemy(this->x - 1, this->y) != NULL)
					mediumEnemies->foundMediumEnemy(this->x - 1, this->y)->decreaseLife(20);
			
			} else if(levels->getLevel()->getChar(this->y, this->x - 1) == 'H') {
				if(hardEnemies->foundHardEnemy(this->x - 1, this->y) != NULL)
					hardEnemies->foundHardEnemy(this->x - 1, this->y)->decreaseLife(30);
			}
		}
			
	} else {
		this->movePlayer(input, levels, basicEnemies, mediumEnemies, hardEnemies);
	}
}


/**
 * @brief funzione per incrementare i punti del Player della quantità presa in input
 * 
 * @param inc quantità da sommare ai punti attuali del Player
 */
void Player::increasePoints(int inc) {
	this->points += inc;
}


/**
 * @brief controlla costantemente se il player viene colpito da uno shot, viene chiamata nel ciclo principale
 * 		 del gioco all'interno della funzione play in modo da controllare a ogni iterazione se il Player 
 * 		 sta per essere colpito da uno sparo
 * 
 * @param level puntatore al livello corrente
 * @param shots puntatore alla lista degli Shots nemici
 */
void Player::checkCollisionWithShot(Level* level, Shots* shots) {
	Shot* collisionShotRight = shots->foundShot(this->x + 1, this->y);
	Shot* collisionShotLeft = shots->foundShot(this->x - 1, this->y);
	if((collisionShotRight != NULL && collisionShotRight->ownerCharacter != '-') || (collisionShotLeft != NULL && collisionShotLeft->ownerCharacter != '-')) {
		this->decreaseLife(10);
		this->printLife(level);
	}
}


/**
 * @brief funzione utilizzata per stampare a schermo i punti del Player,
 * 			essa converte il parametro Points da Int a Char e lo inserisce nella matrice
 * 
 * @param level puntatore al livello corrente
 */
void Player::printPlayerPoints(Level* level) {
	int i = 0, j = 0;
	char value[40];

	for (i = 0; i < 40; i ++)
		value[i] = '\0';
	_itoa (this->points, value, 10);
	for (i = larghezza_max + 11, j = 0; i <= W_CONSOLE -2; i ++, j ++) {
		level->deleteElement(i, H_CONSOLE - 11);
		
		if (value[j] != '\0')		
			level->addElement(i, H_CONSOLE - 11, value[j]);
	}
}


/**
 * @brief funzione utilizzata per stampare a schermo il numero del livello in cui è il Player,
 * 			essa converte il parametro levelNumber del livello corrente da Int a Char e lo inserisce nella matrice
 * 
 * @param level puntatore al livello corrente
 */
void Player::printPlayerLevel(Level* level) {
	int i = 0, j = 0;
	char value[40];

	for (i = 0; i < 40; i ++)
		value[i] = '\0';
	_itoa (level->levelNumber, value, 10);
	for (i = larghezza_max + 10, j = 0; i <= W_CONSOLE -2; i ++, j ++) {
		level->deleteElement(i, H_CONSOLE - 10);
		
		if (value[j] != '\0')		
			level->addElement(i, H_CONSOLE - 10, value[j]);
	}
}


/**
 * @brief Stampa a schermo tutti i dati (LevelNumber, Life, Points)
 * 			convertendoli da int a char e inserendoli nella matrice
 * 
 * @param level puntatore al livello corrente
 */
void Player::printPlayerData(Level* level) {
	this->printPlayerLevel(level);
	this->printLife(level);
	this->printPlayerPoints(level);
}


/**
 * @brief Controlla il punteggio del Player per vedere se sono abbastanza per
 * 			ottenere un incremento della vita (+ 20)
 * 
 * @param level puntatore al livello corrente
 */
void Player:: checkPoints(Level* level) {
	if(this->points % 200 == 0) {
		this->life += 50;
		this->printLife(level);
	}
}


/**
 * @brief permette di settare il parametro del Player shouldChangeLevel 
 * 			che viene utilizzato in Game per capire se bisogna cambiare livello
 * 
 * @param condition la condizione da asseganre al parametro del Player
 */
void Player::setShouldChangeLevel(changeLevelConditions condition) {
	this->shouldChangeLevel = condition;
}


/**
 * @brief ritorna il parametro shouldChangeLevel del Player
 * 
 * @return changeLevelConditions 
 */
changeLevelConditions Player::getShouldChangeLevel() {
	return this->shouldChangeLevel;
}


/**
 * @brief Inserisce il carattere del Player in prossimità della porta della stanza
 * 		 del livello corrente. Questa funzione viene chiamata ogni volta che bisogna cambiare il livello
 * 		 per spawnare il Player nel nuovo livello 
 * 			
 * 
 * @param level puntatore al livello corrente
 * @param doorType parametro char che identifica il tipo di porta, è utilizzato per capire in quale modello
 * 					di stanza è entrato il Player
 */
void Player::spawnPlayerInNewLevel(Level* level, char doorType) {
	if(doorType == '(') {
		if(level->roomNumber % 6 == 0) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 2;
			this->x = larghezza_max - 4;
			level->addElement(this->x, this->y, '@');	
	
		} else if(level->roomNumber % 6 == 1) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 8;
			this->x = larghezza_max - 4;
			level->addElement(this->x, this->y, '@');
	
		} else if(level->roomNumber % 6 == 2) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 18;
			this->x = larghezza_max - 4;
			level->addElement(this->x, this->y, '@');

		} else if(level->roomNumber % 6 == 3) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 2;
			this->x = larghezza_max - 4;
			level->addElement(this->x, this->y, '@');

		} else if(level->roomNumber % 6 == 4) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 18;
			this->x = larghezza_max - 4;
			level->addElement(this->x, this->y, '@');
	
		} else if(level->roomNumber % 6 == 5) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 12;
			this->x = larghezza_max - 4;
			level->addElement(this->x, this->y, '@');
		}
	
	} else if(doorType == ')') {
		if(level->roomNumber % 6 == 0) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 12;
			this->x = larghezza_max - 67;
			level->addElement(this->x, this->y, '@');

		} else if(level->roomNumber % 6 == 1) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 2;
			this->x = larghezza_max - 67;
			level->addElement(this->x, this->y, '@');
		
		} else if(level->roomNumber % 6 == 2) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 8;
			this->x = larghezza_max - 67;
			level->addElement(this->x, this->y, '@');
		
		} else if(level->roomNumber % 6 == 3) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 18;
			this->x = larghezza_max - 67;
			level->addElement(this->x, this->y, '@');
		
		} else if(level->roomNumber % 6 == 4) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 2;
			this->x = larghezza_max - 67; 
			level->addElement(this->x, this->y, '@');
		
		} else if(level->roomNumber % 6 == 5) {
			level->deleteElement(this->x, this->y);
			this->y = H_CONSOLE - 18;
			this->x = larghezza_max - 67;
			level->addElement(this->x, this->y, '@');
		}
	}
}


/**
 * @brief funzione booleana che controlla se il Player può sparare alla sua sinistra,
 * 			per farlo si controlla se nella prima cella alla sua sinistra è presente un elemento 
 * 			che può essere colpito 
 * 
 * @param level puntatore al livello corrente
 * @return true se può sparare a sinsitra
 * @return false se non può sparare a sinistra
 */
bool Player::canShotLeft(Level* level) {
	if((level->getChar(this->y, this->x - 1) != '#') &&
	   (level->getChar(this->y, this->x - 1) != '|') &&
       (level->getChar(this->y, this->x - 1) != '(') &&
       (level->getChar(this->y, this->x - 1) != ')') &&
       (level->getChar(this->y, this->x - 1) != '$') &&
	   (level->getChar(this->y, this->x - 1) != 'L') &&
       (level->getChar(this->y, this->x - 1) != '*') &&
       (level->getChar(this->y, this->x - 1) != 'K') &&
       (level->getChar(this->y, this->x - 1) != 'M') &&
	   (level->getChar(this->y, this->x - 1) != 'H')) 
		return true;
	else
		return false;
}


/**
 * @brief funzione booleana che controlla se il Player può sparare alla sua destra,
 * 			per farlo si controlla se nella prima cella alla sua destra è presente un elemento 
 * 			che può essere colpito 
 * 
 * @param level puntatore alla matrice del livello corrente per permettere il controllo 
 * 				degli elementi presenti nella stanza
 * @return true se può sparare a destra
 * @return false se non può sparare a destra
 */
bool Player::canShotRight(Level* level) {
	if((level->getChar(this->y, this->x + 1) != '#') &&
	   (level->getChar(this->y, this->x + 1) != '|') &&
       (level->getChar(this->y, this->x + 1) != '(') &&
       (level->getChar(this->y, this->x + 1) != ')') &&
       (level->getChar(this->y, this->x + 1) != '$') &&
	   (level->getChar(this->y, this->x + 1) != 'L') &&
       (level->getChar(this->y, this->x + 1) != '*') &&
       (level->getChar(this->y, this->x + 1) != 'K') &&
       (level->getChar(this->y, this->x + 1) != 'M') &&
	   (level->getChar(this->y, this->x + 1) != 'H'))
		return true;
	else
		return false;
}