#include "DropDownMenu.h"

DropDownMenu::DropDownMenu()
{
}

DropDownMenu::DropDownMenu(std::string t_type)
{
	m_type = t_type;
	setUpDropDownMenu();
}

DropDownMenu::~DropDownMenu()
{
}

void DropDownMenu::setUpDropDownMenu()
{
	if (m_type == "IsDialogue")
	{
		m_dropDownMenuButton = new Button();
		m_dropDownMenuButton->setButtonPosition(sf::Vector2f(25, 25));
		m_dropDownMenuButton->resize(0.125f, 0.4f);
		for (int i = 0; i < 4; i++)
		{
			if(i==0)
				m_dropDownMenuOptions.push_back(CheckBox("Interacted"));
			if (i == 1)
				m_dropDownMenuOptions.push_back(CheckBox("Damaged"));
			if (i == 2)
				m_dropDownMenuOptions.push_back(CheckBox("Defeated"));
			if (i == 3)
				m_dropDownMenuOptions.push_back(CheckBox("InRange"));
			//if (i == 4)
			//	m_dropDownMenuOptions.push_back(CheckBox("Interacted"));
			m_dropDownMenuOptions.at(i).setCheckBoxPosition(sf::Vector2f(25, i * 64));
			m_dropDownMenuOptions.at(i).setEnabled(false);
		}
	}
}

void DropDownMenu::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{

    sf::Event newEvent = t_event;
    //if (m_objects->getSelectedGridObject() != nullptr)
    //{
    //    addDialogueTab();
    //}

	if (m_dropDownMenuButton->isButtonClicked(t_event, &t_window))
	{
		std::cout << m_enabled << std::endl;

		setEnabled();
		std::cout << m_enabled << std::endl;
	}
	if (m_enabled == true)
	{
		for (int i =0; i < m_dropDownMenuOptions.size(); i++)
		{
			m_dropDownMenuOptions.at(i).isCheckBoxClicked(t_event, &t_window);
		}
	}

}

void DropDownMenu::render(sf::RenderWindow* t_window)
{
	if (m_type == "IsDialogue")
	{
		m_dropDownMenuButton->render(t_window);
		if (m_enabled)
		{
			for (int i = 0; i < m_dropDownMenuOptions.size(); i++)
			{
				m_dropDownMenuOptions.at(i).render(t_window);
			}
		}
	}
}

void DropDownMenu::setDropDownMenuPosition(sf::Vector2f t_position, float t_width)
{
	m_dropDownMenuButton->setButtonPosition(sf::Vector2f(t_position.x - (t_width/2) -32, t_position.y));
	for (int i = 0; i < m_dropDownMenuOptions.size(); i++)
	{
		m_dropDownMenuOptions.at(i).setCheckBoxPosition(sf::Vector2f(m_dropDownMenuButton->getButtonPosition().x,
		m_dropDownMenuButton->getButtonPosition().y +(32*(i +1))));
	}
	//m_deleteButtons.at(m_deleteButtons.size() - 1)->setButtonPosition(
	//	sf::Vector2f(
	//		m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonPosition().x + (m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonSprite().getGlobalBounds().width / 2) + 32,
	//		m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonPosition().y));




}
