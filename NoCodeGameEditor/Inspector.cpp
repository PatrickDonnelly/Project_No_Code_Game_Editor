#include "Inspector.h"

Inspector::Inspector(sf::Font & t_font)
{
}

Inspector::Inspector(std::string t_title)
{
}

//Inspector::Inspector(ObjectPlacement* t_objects)
//{
//    m_objects = t_objects;
//    m_fontManager = FontManager();
//    m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
//    initInspector();
//    m_noOfOptions = 4;
//    m_inspectorLabel = new Label(m_font);
//    //             initInspectorOptions();
//
//    //m_text.setString(t_title);
//    initText();
//
//    //addDialogueTab();
//}
//
//bool Inspector::isNull()
//{
//    if (m_objects->getSelectedGridObject() == nullptr)
//    {
//        return true;
//    }
//    return false;
//}

Inspector::Inspector(std::string t_title, Attributes& t_object)
{
    m_objectData = t_object;
    m_fontManager = FontManager();
    m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
    initInspector();
    m_noOfOptions = 4;
    m_inspectorLabel = new Label(m_font);
    initInspectorOptions();
    m_title = t_title;
    m_text.setString(t_title);
    initText();
    m_currentLabel = nullptr;
    addDialogueTab();
}

Inspector::Inspector()
{
    m_fontManager = FontManager();
    initInspector();
    m_noOfOptions = 4;
    m_inspectorLabel = new Label(m_font);
    initInspectorOptions();
    initText();
}

void Inspector::setUpFontAndText()
{
    m_text.setFont(m_font);
    m_text.setStyle(sf::Text::Italic | sf::Text::Bold);
    m_text.setCharacterSize(24U);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineThickness(2.0f);
    m_text.setPosition(sf::Vector2f((m_inspectorBGShape.getPosition().x + m_inspectorBGShape.getGlobalBounds().width / 2) - m_text.getGlobalBounds().width / 2, 5));
}

Inspector::~Inspector()
{
}

void Inspector::initInspectorOptions()
{
    for (int i = 0; i < m_noOfOptions; ++i)
    {
        /*        if (i == 0)
                    m_inspectorOptions.push_back(new InspectorOptions(m_font, 7, "Behaviour"));
                */if (i == 0)
                {
                    m_inspectorOptions.push_back(new InspectorOptions(m_font, 3, "Dialogue"));
                    m_inspectorOptions.at(i)->setInspectorOptionsPosition(sf::Vector2f(m_inspectorOptions.at(0)->getInspectorOptionsPosition().x,
                        m_inspectorOptions.at(0)->getInspectorOptionsPosition().y + m_inspectorOptions.at(0)->getInspectorOptionsSprite().getGlobalBounds().height));
                }
                //if (i == 2)
                //{
                //    m_inspectorOptions.push_back(new InspectorOptions(m_font, 3, "Stats"));
                //    m_inspectorOptions.at(i)->setInspectorOptionsPosition(sf::Vector2f(m_inspectorOptions.at(1)->getInspectorOptionsPosition().x,
                //        m_inspectorOptions.at(1)->getInspectorOptionsPosition().y + m_inspectorOptions.at(1)->getInspectorOptionsSprite().getGlobalBounds().height));
                //}
                //if (i == 3)
                //{
                //    m_inspectorOptions.push_back(new InspectorOptions(m_font, 4, "Sound"));
                //    m_inspectorOptions.at(i)->setInspectorOptionsPosition(sf::Vector2f(m_inspectorOptions.at(2)->getInspectorOptionsPosition().x,
                //        m_inspectorOptions.at(2)->getInspectorOptionsPosition().y + m_inspectorOptions.at(2)->getInspectorOptionsSprite().getGlobalBounds().height));
                //}


        /*        m_inspectorOptions.at(i).setCheckBoxPosition(sf::Vector2f(
                    (m_inspectorOptionsLabel->getText().getPosition().x),
                    (m_inspectorOptionsLabel->getText().getPosition().y + 10 + (i * m_options.at(i)->getCheckBoxBounds().getGlobalBounds().height + 5))));
           */
    }
}

sf::Sprite Inspector::getInspectorSprite()
{
    return sf::Sprite();
}

sf::Vector2f Inspector::getInspectorPosition()
{
    return sf::Vector2f();
}

void Inspector::initInspector()
{
    m_inspectorBGShape.setSize(sf::Vector2f(400.0f, 2160.0f));
    m_inspectorBGShape.setPosition(1520.0f, 0.0f);
    m_inspectorBGShape.setOutlineThickness(4.0f);
    m_inspectorBGShape.setOutlineColor(sf::Color(sf::Color(140, 140, 140)));
    m_inspectorBGShape.setFillColor(sf::Color(sf::Color(204, 204, 204)));

    m_applyButton = new Button();
    m_applyButton->resize(0.125f, 0.4f);
    m_applyButton->setButtonPosition(sf::Vector2f(1880.0f, 32.0f));
}

void Inspector::setInspectorSprite(sf::Sprite t_dialogueSprite)
{
}

void Inspector::render(sf::RenderWindow* t_window)
{
    // m_fontManager.getNumberOfFonts();
    //if (m_objects->getSelectedGridObject() != nullptr)
    //{
        t_window->draw(m_inspectorBGShape);
        /*for (int i = 0; i < m_noOfOptions; ++i)
        {
            m_inspectorOptions.at(0)->render(t_window);
        }*/
        m_inspectorLabel->render(t_window);
        t_window->draw(m_text);
        if (m_objectData.m_allowedDialogue)
        {
                m_addCategoryLabel->render(t_window);
                m_addDialogueButton->render(t_window);
                m_addDialogueLabel->render(t_window);
        }
        auto iter2 = m_dialogueButtons.begin();
        auto iter3 = m_dialogueLabels.begin();
        for (auto iter1 = m_deleteButtons.begin(); iter1 != m_deleteButtons.end();)
        {
            //m_dialogueButtons.at(i)->render(t_window);
            //m_dialogueLabels.at(i)->render(t_window);
            //m_deleteButtons.at(i)->render(t_window);
            (*iter1)->render(t_window);
            (*iter2)->render(t_window);
            (*iter3)->render(t_window);
            iter1++; iter2++; iter3++;
        }

        for (auto iter = m_dialogueDropDownMenu.begin(); iter != m_dialogueDropDownMenu.end(); iter++)
        {
            (*iter)->render(t_window);
        }

        m_applyButton->render(t_window);
   // }
}

bool Inspector::isEnabled()
{
    return false;
}

void Inspector::update(sf::Time deltaTime, sf::RenderWindow& window)
{

}

void Inspector::splitString(std::string t_dialogueText)
{
}

void Inspector::saveChanges(std::map<std::string, std::string>& t_dialoguePaths)
{
    for (int i = 0; i < m_dialogueDropDownMenu.size(); i++)
    {
        m_dialogueDropDownMenu.at(i)->checkEnabledOptions(t_dialoguePaths);
    }
}

void Inspector::processEvents(sf::Event t_event, sf::RenderWindow& t_window, GameState* t_gameState, std::string t_fileName, std::map<std::string, std::string>& t_dialoguePaths)
{
    m_gameState = t_gameState;
    sf::Event newEvent = t_event;

    if (m_applyButton->isButtonClicked(t_event, &t_window))
    {
        saveChanges(t_dialoguePaths);
    }

    if (m_addDialogueButton->isButtonClicked(t_event, &t_window))
    {
        std::cout << "Button Clicked";

        if (m_dialogueButtons.size() == 0)
        {
            m_dialogueButtons.push_back(new Button());
            m_dialogueButtons.at(m_dialogueButtons.size() - 1)->setButtonPosition(
                sf::Vector2f(
                    m_addCategoryLabel->getTextPosition().x + 100,
                    m_addCategoryLabel->getTextPosition().y + 32));
            m_dialogueButtons.at(m_dialogueButtons.size() - 1)->resize(1.0f, 0.4f);
        }
        else
        {
            m_dialogueButtons.push_back(new Button());
            m_dialogueButtons.at(m_dialogueButtons.size() - 1)->setButtonPosition(
                sf::Vector2f(m_dialogueButtons.at(m_dialogueButtons.size() - 2)->getButtonPosition().x,
                    m_dialogueButtons.at(m_dialogueButtons.size() - 2)->getButtonPosition().y + 32));
            m_dialogueButtons.at(m_dialogueButtons.size() - 2)->resize(1.0f, 0.4f);
        }
        m_dialogueLabels.push_back(new Label());
        m_dialogueLabels.at(m_dialogueLabels.size() - 1)->setText("Add Dialogue");
        m_dialogueLabels.at(m_dialogueLabels.size() - 1)->setTextPosition(sf::Vector2f(m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonPosition().x, m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonPosition().y));

        m_deleteButtons.push_back(new Button());
        m_deleteButtons.at(m_deleteButtons.size() - 1)->setButtonPosition(
            sf::Vector2f(
                m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonPosition().x + (m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonSprite().getGlobalBounds().width / 2) + 32,
                m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonPosition().y));
        m_dialogueButtons.at(m_dialogueButtons.size() - 1)->resize(1.0f, 0.4f);
        m_deleteButtons.at(m_deleteButtons.size() - 1)->resize(0.125f, 0.4f);

        m_dialogueDropDownMenu.push_back(new DropDownMenu("IsDialogue"));
        m_dialogueDropDownMenu.at(m_dialogueDropDownMenu.size() - 1)->setDropDownMenuPosition(m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonPosition(), m_dialogueButtons.at(m_dialogueButtons.size() - 1)->getButtonSprite().getGlobalBounds().width);
    }

    auto itera = m_dialogueButtons.begin();
    auto iterb = m_dialogueLabels.begin();
    auto iterc = m_deleteButtons.begin();

    for (auto iterd = m_dialogueDropDownMenu.begin(); iterd != m_dialogueDropDownMenu.end();)
    {
        (*iterd)->processEvents(t_event, t_window);
        if ((*iterd)->isEnabled() && !(*iterd)->isOpened())
        {
            (*iterd)->setOpened();
            itera++;
            iterb++;
            iterc++;
            iterd++;
            repositionDropDown(iterc, itera, iterb, iterd, +162);
            break;
        }
        else if (!(*iterd)->isEnabled() && (*iterd)->isOpened())
        {

            (*iterd)->setOpened();
            itera++;
            iterb++;
            iterc++;
            iterd++;
            repositionDropDown(iterc, itera, iterb, iterd, -162);
            break;

        }
        else
        {
            itera++;
            iterb++;
            iterc++;
            iterd++;
        }
    }

    //for (auto iter = m_dialogueDropDownMenu.begin(); iter != m_dialogueDropDownMenu.end();)
    //{
    //    if((*iter)->)
    //}
       

    auto iter2 = m_dialogueButtons.begin();
    auto iter3 = m_dialogueLabels.begin();
    auto iter4 = m_dialogueDropDownMenu.begin();


    for (auto iter1 = m_deleteButtons.begin(); iter1 != m_deleteButtons.end();)
    {
        if ((*iter1)->isButtonClicked(t_event, &t_window))
        {

            iter1 = m_deleteButtons.erase(iter1);
            iter2 = m_dialogueButtons.erase(iter2);
            iter3 = m_dialogueLabels.erase(iter3);
            iter4 = m_dialogueDropDownMenu.erase(iter4);
            repositionDialogueButtons();

            break;
        }
        else
        {
            iter1++;
            iter2++;
            iter3++;
            iter4++;
        }
    }
    auto iter1 = m_dialogueLabels.begin();
    for (auto iter = m_dialogueButtons.begin(); iter != m_dialogueButtons.end();)
    {
        if ((*iter)->isButtonClicked(t_event, &t_window))
        {
            std::cout << "Dialogue button Clicked" << std::endl;
            m_gameState->setState(State::CREATE_DIALOGUE);
            m_currentLabel = (*iter1);
            break;
        }
        else
        {
            iter++;
            iter1++;
        }
    }

    if (m_currentLabel != nullptr)
    {
        m_currentLabel->setText(t_fileName);
    }

}

void Inspector::repositionDialogueButtons()
{
    for (int i = 0; i < m_dialogueDropDownMenu.size(); i++)
    {
        if (m_dialogueDropDownMenu.at(i)->isOpened())
        {
            m_dialogueDropDownMenu.at(i)->setOpened();
        }
        if (m_dialogueDropDownMenu.at(i)->isEnabled())
        {
            m_dialogueDropDownMenu.at(i)->setEnabled();
        }
    }
    for (int i = 0; i < m_dialogueButtons.size(); i++)
    {
        if (i == 0)
        {

            m_dialogueButtons.at(i)->setButtonPosition(
                sf::Vector2f(
                    m_addCategoryLabel->getTextPosition().x + 100,
                    m_addCategoryLabel->getTextPosition().y + 32));

        }
        else
        {
            m_dialogueButtons.at(i)->setButtonPosition(
                sf::Vector2f(m_dialogueButtons.at(i-1)->getButtonPosition().x,
                    m_dialogueButtons.at(i-1)->getButtonPosition().y+32));

        }


        m_dialogueLabels.at(i)->setTextPosition(sf::Vector2f(m_dialogueButtons.at(i)->getButtonPosition().x, m_dialogueButtons.at(i)->getButtonPosition().y));


        m_deleteButtons.at(i)->setButtonPosition(
            sf::Vector2f(
                m_dialogueButtons.at(i)->getButtonPosition().x + (m_dialogueButtons.at(i)->getButtonSprite().getGlobalBounds().width / 2) + 32,
                m_dialogueButtons.at(i)->getButtonPosition().y));
 


        m_dialogueDropDownMenu.at(i)->setDropDownMenuPosition(m_dialogueButtons.at(i)->getButtonPosition(), m_dialogueButtons.at(i)->getButtonSprite().getGlobalBounds().width);
    }
}

void Inspector::repositionDropDown(std::vector<Button*>::iterator t_iter1, std::vector<Button*>::iterator t_iter2, std::vector<Label*>::iterator t_iter3, std::vector<DropDownMenu*>::iterator t_iter4, int t_offset)
{
    auto iterCopy2 = t_iter2;
    auto iterCopy3 = t_iter3;
    auto iterCopy4 = t_iter4;


    for (auto iterCopy1 = t_iter1; iterCopy1 != m_deleteButtons.end();)
    {
        (*iterCopy1)->setButtonPosition(sf::Vector2f((*iterCopy1)->getButtonPosition().x, (*iterCopy1)->getButtonPosition().y + t_offset));
        (*iterCopy2)->setButtonPosition(sf::Vector2f((*iterCopy2)->getButtonPosition().x, (*iterCopy2)->getButtonPosition().y + t_offset));
        (*iterCopy3)->setTextPosition(sf::Vector2f((*iterCopy3)->getTextPosition().x, (*iterCopy3)->getTextPosition().y + t_offset));
        (*iterCopy4)->setDropDownMenuPosition((*iterCopy2)->getButtonPosition(), (*iterCopy2)->getButtonSprite().getGlobalBounds().width);

        iterCopy1++;
        iterCopy2++;
        iterCopy3++;
        iterCopy4++;

    }
}

void Inspector::addDialogueTab()
{
    if (m_objectData.m_allowedDialogue)
    {
        m_addCategoryLabel = new Label();
        m_addCategoryLabel->setText("Dialogue : ");
        m_addCategoryLabel->setTextPosition(sf::Vector2f(m_inspectorLabel->getTextPosition().x - (m_addCategoryLabel->getText().getGlobalBounds().width /2) + 16, m_addCategoryLabel->getTextPosition().y + 64));

       // m_objects->getSelectedGridObject()->m_hasBeenSelected = true;
        m_addDialogueButton = new Button();
        m_addDialogueButton->setButtonPosition(sf::Vector2f(m_addCategoryLabel->getTextPosition().x + m_addCategoryLabel->getText().getGlobalBounds().width, m_addCategoryLabel->getTextPosition().y));
        m_addDialogueButton->resize(0.125f, 0.4f);
        m_addDialogueLabel = new Label();
        m_addDialogueLabel->setText("+");
        m_addDialogueLabel->setTextPosition(sf::Vector2f(m_addDialogueButton->getButtonPosition().x, m_addDialogueButton->getButtonPosition().y - 5));
    }
}

void Inspector::updateDialogueTab()
{
    //if (m_objects->getSelectedGridObject()->m_inpectorData.m_allowedDialogue)
    //{

    //}
}

void Inspector::initText()
{
    setUpFontAndText();
    m_inspectorLabel->setText("Inspector - " + m_title);
    m_inspectorLabel->setTextPosition(sf::Vector2f(1522 + m_inspectorLabel->getText().getGlobalBounds().width / 2, (m_inspectorLabel->getText().getGlobalBounds().height / 2)));
}

