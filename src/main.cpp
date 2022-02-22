#include"Constant.h"
#include "Game.hpp"
#include "menuMessage.h"

/**
 * @brief funzione main del gioco, viene inizializzato un oggetto game e chiamato il metodo 
 * 		  in cui viene eseguito il gioco
 * 
 * @return int 
 */
int main()
{
	system("cls");
	gameStart();
	Game newGame = Game();
	newGame.play();
	gameOver();

	return 0;
}