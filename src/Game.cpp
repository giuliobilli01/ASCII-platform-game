#include "Game.hpp"

/**
 * @brief Costruttore della classe Game in cui vengono inizializzati a NULL i puntatori 
 * 		dei vari elementi del gioco 
 * 
 */
Game::Game()
{
	this->levelsList = NULL;
	this->basicEnemies = NULL;
	this->mediumEnemies = NULL;
	this->hardEnemies = NULL;
	this->generator = NULL;
	this->player = NULL;
	this->playerShots = NULL;
	this->hardEnemyShots = NULL;
}

/**
 * @brief Funzione principale in cui viene eseguito e gestito il gioco:
 * 		- inizializza la console e le sue dimensioni
 * 		- crea un nuovo oggetto per ogni puntatore di Game tramite initialize Game
 * 		- contiene il ciclo in cui viene eseguito il gioco
 * 			- il ciclo gestisce i vari input da tastiera e aggiorna gli elementi controllati dal computer
 * 
 */
void Game::play()
{
	init_console(W_CONSOLE, H_CONSOLE);
	system("cls");
	bool running = true;
	this->initializeGame();
	char input;
	char *inputP = &input;

	do
	{
		non_blocking_getch(inputP);
		if (input == 'e' || this->player->getLIfe() <= 0)
		{
			running = false;
			break;
		}
		else
		{
			this->checkInputs(input);
		}
		this->checkCollisions();
		this->update();

	} while (running);
}

/**
 * @brief Esegue l'aggiornamento di tutti gli elementi a schermo:
 * 			- chiama la funzione per aggiornare la lista dei BasicEnemy che se necessario vengono eliminati
 * 			- chiama la funzione per aggiornare la lista dei MediumEnemy che se necessario vengono eliminati 
 * 				oppure si spostano
 * 			- chiama la funzione per aggiornare la lista degli HardEnemy che se necessario vengono eliminati
 * 				oppure sparano
 * 			- chiama la funzione per aggiornare la lista degli Shot del Player e degli Enemy facendoli avanzare nel loro percorso 
 * 				oppure vengono eliminati se non possono proseguire
 */
void Game::update()
{
	this->basicEnemies->updateBasicEnemies(this->levelsList->getLevel(), this->playerShots);
	this->mediumEnemies->updateMediumEnemies(this->levelsList->getLevel(), this->playerShots, this->player);
	this->hardEnemies->updateHardEnemies(this->levelsList->getLevel(), this->playerShots, this->hardEnemyShots, this->player);
	this->playerShots->updateShots(this->levelsList->getLevel());
	this->hardEnemyShots->updateShots(this->levelsList->getLevel());
}

/**
 * @brief Manda al Player gli input da tastiera e chiama la funzione che controlla se bisogna cambiare livello
 *
 * @param input 
 */
void Game::checkInputs(char input)
{
	this->player->checkPlayerInput(input, this->levelsList, this->playerShots, this->basicEnemies, this->mediumEnemies, this->hardEnemies);
	this->changeLevel();
}

/**
 * @brief chiama la funzione del Player che controlla se sta per essere colpito da uno Shot nemico
 * 
 */
void Game::checkCollisions()
{
	this->player->checkCollisionWithShot(this->levelsList->getLevel(), this->hardEnemyShots);
}

/**
 * @brief Controlla se il Player deve cambiare livello:
 * 			- se il Player deve andare al livello precedente:
 * 				- vengono cancellate la lista degli shot del livello corrente  
 * 				- si passa al livello precedente spostandosi nella lista dei livelli
 * 				- viene spawnato il player nel nuovo livello
 * 				- viene stampata la mappa del nuovo livello
 * 				- viene resettato il parametro del Player che determina il cambio del livello
 * 				- vengono stampati i dati del Player
 * 			
 * 			- se il Player deve andare al livello successivo:
 * 				- vengono cancellate la lista degli shot del livello corrente
 * 				- si passa al livello successivo spostandosi nella lista dei livelli
 * 				- viene spawnato il player nel nuovo livello
 * 				- Se il livello era già stato esplorato viene stampato come era stato lasciato, se
 * 				 	invece è un livello nuovo vengono spawnati i nemici e i bonus
 * 				- viene resettato il parametro del Player che determina il cambio del livello
 * 				- vengono stampati i dati del Player
 */
void Game::changeLevel()
{
	if (this->player->getShouldChangeLevel() == PREV_LEVEL)
	{
		this->playerShots->deleteList(this->levelsList->getLevel());
		this->hardEnemyShots->deleteList(this->levelsList->getLevel());
		this->levelsList->goToPrevLevel();
		this->player->spawnPlayerInNewLevel(this->levelsList->getLevel(), '(');
		this->levelsList->getLevel()->printRoom();
		this->player->setShouldChangeLevel(CURRENT_LEVEL);
		this->player->printPlayerData(this->levelsList->getLevel());
	}
	else if (this->player->getShouldChangeLevel() == NEXT_LEVEL)
	{
		this->playerShots->deleteList(this->levelsList->getLevel());
		this->hardEnemyShots->deleteList(this->levelsList->getLevel());
		this->levelsList->goToNextLevel();
		this->player->spawnPlayerInNewLevel(this->levelsList->getLevel(), ')');
		if (!this->levelsList->isExplorated())
		{
			this->generator->generateBonusPoints(this->levelsList);
			this->generator->generateBonusLife(this->levelsList, this->player->getLIfe());
			this->generator->generateBasicEnemies(this->levelsList, this->basicEnemies);
			this->generator->generateMediumEnemies(this->levelsList, this->mediumEnemies);
			this->generator->generateHardEnemies(this->levelsList, this->hardEnemies);
			this->levelsList->setExplorationTrue();
		}
		this->levelsList->getLevel()->printRoom();
		this->player->setShouldChangeLevel(CURRENT_LEVEL);
		this->player->printPlayerData(this->levelsList->getLevel());
	}
}

/**
 * @brief Viene chiamata all'inizio della funzione play e 
 * 			chiama i costruttori di tutti gli elementi di gioco
 * 
 */
void Game::initializeGame()
{
	this->levelsList = new Levels();
	this->basicEnemies = new BasicEnemiesList();
	this->mediumEnemies = new MediumEnemiesList();
	this->hardEnemies = new HardEnemiesList();
	this->player = new Player(larghezza_max - 68, H_CONSOLE - 2, 100, RIGHT, 0);
	this->levelsList->getLevel()->addElement(this->player->getX(), this->player->getY(), '@');
	this->playerShots = new Shots();
	this->hardEnemyShots = new Shots();
	this->player->printPlayerData(this->levelsList->getLevel());
	this->generator = new Generator();
}