#pragma once
#include"Level.hpp"

class Levels {

	protected:
		Level* headlevelList;
		Level* lastLevel;
		Level* currentLevel;
		int levelCounter;
	
	public:

		Levels();

		void goToNextLevel();

		bool isFirstLevel();

		bool isLastLevel();

		void goToPrevLevel();

		bool isExplorated();

		void setExplorationTrue();

		Level* getLevel();

};