#pragma once
#include <vector>
#include <string>

/*
	Originally the file names/ level names were part of the GameState class.
	However, I wanted to be able to edit the game level file names easily and so I made them their
	own easy class to find. I also wanted to be able to access the level names outside of the game
	actually running (for a level selection menu).
	Lastly, the GameState itself only ever accessed the current level and number of levels. It 
	did not need to know about all possible levels, so I extracted them out to their own class.
*/

class GameLevels
{
private:
	static GameLevels* s_pInstance;

	std::vector<std::string> m_LevelNames;
	//int numLevels = 3;

	int currentLevel = 0;

	GameLevels()
	{
		m_LevelNames.push_back("Level1.txt");
		m_LevelNames.push_back("Level4.txt");
		m_LevelNames.push_back("Level5.txt");
	}

	~GameLevels()
	{
		DestroyInstance();
	}

public:
	static GameLevels* GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new GameLevels();
		}
		return s_pInstance;
	}

	static void DestroyInstance()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	std::string GetLevelName(int index)
	{
		return m_LevelNames.at(index);
	}

	std::string GetCurrentLevelName()
	{
		return m_LevelNames.at(currentLevel);
	}

	int GetNumberOfLevels()
	{
		return m_LevelNames.size();
		//return numLevels;
	}

	void SetCurrentLevel(int index)
	{
		currentLevel = index;
	}

	void IncreaseCurrentLevel()
	{
		++currentLevel;
	}

	int GetCurrentLevel()
	{
		return currentLevel;
	}

	bool CheckReachedMaxLevel()
	{
		//if (currentLevel == m_LevelNames.size()) return true;
		if (currentLevel == m_LevelNames.size()) return true;
		return false;
	}
};