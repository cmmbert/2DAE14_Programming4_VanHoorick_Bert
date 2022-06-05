#pragma once
#include <BaseComponent.h>
#include <vector>

#include "ModeButton.h"
#include "ServiceLocator.h"

class SelectModeComp final :
    public dae::BaseComponent
{
	size_t m_NrOfOptions{ 0 };
	size_t m_SelectedOption{};
	std::vector<ModeButton*> m_ModeButtons;
public:
	explicit SelectModeComp(dae::GameObject* gameObject, std::vector<ModeButton*> modeButtons)
		: BaseComponent(gameObject), m_ModeButtons(modeButtons)
	{
		m_NrOfOptions = m_ModeButtons.size();
		m_SelectedOption = m_NrOfOptions - 1;
		IncrementSelection(1);
	}
	void IncrementSelection(int direction)
	{
		m_SelectedOption += direction;
		m_SelectedOption %= m_NrOfOptions;
		for (size_t i = 0; i < m_NrOfOptions; ++i)
		{
			m_ModeButtons[i]->SetActive(i == m_SelectedOption);
		}
	}
	void SelectCurrentMode()
	{
		m_ModeButtons[m_SelectedOption]->SetMode();
		dae::SceneManager::GetInstance().SetActiveScene("Menu", false);
		LevelGen::ReadLevelFromFile("BurgerTime/level2.json", dae::SceneManager::GetInstance().GetScene("Level1"));
		ServiceLocator::GetAudioService()->PlaySound(2, 0.5f);
		dae::SceneManager::GetInstance().SetActiveScene("Level1");
	}
};

