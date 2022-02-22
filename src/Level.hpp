#pragma once
#include"WindowsFunction.h"
//#include "BasicEnemiesList.hpp"
#include <time.h>

class Level {
	 
	public:
		char room[H_CONSOLE][W_CONSOLE];
		int levelNumber;
		int roomNumber;
		bool isExplorated;
		Level* nextLevel;
		Level* prevLevel;


		Level(int roomNumber);

		void emptyRoom();

		void generateBorders();

		void generateFirstRoom();

		void generateMap1();

		void generateMap2();

		void generateMap3();

		void generateMap4();

		void generateMap5();

		void generateMap6();

		void _add(int x, int y, char ch);

		void _delete(int x, int y);

		void addElement(int x, int y, char ch);

		void deleteElement(int x, int y);

		char getChar(int y, int x);

		void printElement(int x, int y);

		void printRoom();

		void setPlayerData();
};
