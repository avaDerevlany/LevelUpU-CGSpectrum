#pragma once
#include <vector>
#include <string>

class GameLevels
{
	static GameLevels* s_pInstance;

	std::vector<std::string> m_LevelNames;
	int numLevels = 3;

	int currentLevel = 0;

	GameLevels()
	{
		m_LevelNames.push_back("Level1.txt");
		m_LevelNames.push_back("Level4.txt");
		m_LevelNames.push_back("Level5.txt");
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
		//return m_LevelNames.size();
		return numLevels;
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
		if (currentLevel == numLevels) return true;
		return false;
	}
};