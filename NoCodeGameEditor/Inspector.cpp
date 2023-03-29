#include "Inspector.h"

Inspector::Inspector(sf::Font & t_font)
{
}

Inspector::Inspector(std::string t_title)
{
}

Inspector::Inspector(ObjectPlacement* t_objects)
{
    m_objects = t_objects;
    m_fontManager = FontManager();
    m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
    initInspector();
    m_noOfOptions = 4;
    m_inspectorLabel = new Label(m_font);
    //             initInspectorOptions();

    //m_text.setString(t_title);
    initText();

    addDialogueTab();
}

bool Inspector::isNull()
{
    if (m_objects->getSelectedGridObject() == nullptr)
    {
        return true;
    }
    return false;
}

//Inspector::Inspector(std::string t_title, Attributes& t_object)
//{
//    m_objectData = t_object;
//    m_fontManager = FontManager();
//    m_font = m_fontManager.getFont("ASSETS\\FONTS\\Arial.ttf");
//    initInspector();
//    m_noOfOptions = 4;
//    m_inspectorLabel = new Label(m_font);
//    initInspectorOptions();
//    m_title = t_title;
//    //m_text.setString(t_title);
//    initText();
//
//    addDialogueTab();
//}

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
}

void Inspector::setInspectorSprite(sf::Sprite t_dialogueSprite)
{
}

void Inspector::render(sf::RenderWindow* t_window)
{
    // m_fontManager.getNumberOfFonts();

    t_window->draw(m_inspectorBGShape);
    for (int i = 0; i < m_noOfOptions; ++i)
    {
        m_inspectorOptions.at(0)->render(t_window);
    }
    m_inspectorLabel->render(t_window);
    t_window->draw(m_text);
    if (m_objects->getSelectedGridObject()->m_inpectorData.m_allowedDialogue)
    {
        m_addDialogueButton->render(t_window);
        m_addDialogueLabel->render(t_window);
    }
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

void Inspector::addDialogueTab()
{
    if (m_objects->getSelectedGridObject()->m_inpectorData.m_allowedDialogue)
    {
        m_addDialogueButton = new Button();
        m_addDialogueButton->setButtonPosition(sf::Vector2f(50, 50));
        m_addDialogueButton->resize(0.125f, 0.4f);
        m_addDialogueLabel = new Label();
        m_addDialogueLabel->setText("+");
        m_addDialogueLabel->setTextPosition(sf::Vector2f(m_addDialogueButton->getButtonPosition().x, m_addDialogueButton->getButtonPosition().y - 5));
    }
}

void Inspector::updateDialogueTab()
{
    if (m_objects->getSelectedGridObject()->m_inpectorData.m_allowedDialogue)
    {

    }
}

void Inspector::initText()
{
    setUpFontAndText();
    m_inspectorLabel->setText("Inspector - " + m_title);
    m_inspectorLabel->setTextPosition(sf::Vector2f(1522 + m_inspectorLabel->getText().getGlobalBounds().width / 2, (m_inspectorLabel->getText().getGlobalBounds().height / 2)));
}

