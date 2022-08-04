#pragma once

class SceneInfo
{
public:
	enum class SceneName
	{
		None,
		MainMenu,
		Gameplay,
		Settings,
		HighScore,
		Lose,
		Win,
		LevelSelect,
	};

private:
	static SceneInfo* s_pInstance;

	SceneName m_currentScene;

	SceneInfo()
	{
		m_currentScene = SceneName::None;
	}

	~SceneInfo()
	{
		DestroyInstance();
	}

public:

	static SceneInfo* GetInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new SceneInfo();
		}
		return s_pInstance;
	}

	static void DestroyInstance()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	void SetCurrentScene(SceneName scene)
	{
		m_currentScene = scene;
	}

	SceneName GetSceneName()
	{
		return m_currentScene;
	}
};