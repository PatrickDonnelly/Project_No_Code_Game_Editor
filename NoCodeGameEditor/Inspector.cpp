#include "Inspector.h"

Inspector::Inspector(sf::Font& t_font)
{
}

Inspector::Inspector()
{
    initInspector();
    m_noOfOptions = 4;
    m_inspectorLabel = new Label(m_font);
    initInspectorOptions();
    initText();
}

void Inspector::setUpFontAndText()
{
    if (!m_font.loadFromFile("ASSETS\\FONTS\\Arial.ttf"))
    {
        std::cout << "problem loading arial black font" << std::endl;
    }
    m_text.setFont(m_font);
    m_text.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
    m_text.setPosition(400.0f, 400.0f);
    m_text.setCharacterSize(16U);
    m_text.setOutlineColor(sf::Color::White);
    m_text.setFillColor(sf::Color::Black);
    m_text.setOutlineThickness(1.0f);
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
            m_inspectorOptions.push_back(new InspectorOptions(m_font, 1, "Dialogue"));
      /*      m_inspectorOptions.at(i)->setInspectorOptionsPosition(sf::Vector2f(m_inspectorOptions.at(0)->getInspectorOptionsPosition().x, 
                m_inspectorOptions.at(0)->getInspectorOptionsPosition().y + m_inspectorOptions.at(0)->getInspectorOptionsSprite().getGlobalBounds().height));
       */ }
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
   */ }
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
    t_window->draw(m_inspectorBGShape);
    m_inspectorLabel->render(t_window);
    t_window->draw(m_text);
    for (int i = 0; i < m_noOfOptions; ++i)
    {
        m_inspectorOptions.at(0)->render(t_window);
    }
}

bool Inspector::isEnabled()
{
    return false;
}

void Inspector::splitString(std::string t_dialogueText)
{
}

void Inspector::initText()
{
    setUpFontAndText();
    m_text.setFont(m_font);
    m_text.setCharacterSize(20.0f);
    m_text.setFillColor(sf::Color::Blue);
    m_text.setOutlineColor(sf::Color::Red);
    m_text.setOutlineThickness(2.0f);
    m_text.setPosition(10.0f, 10.0f);
    m_inspectorLabel->setText("Inspector");
    m_inspectorLabel->setTextPosition(sf::Vector2f(m_inspectorBGShape.getPosition().x + m_inspectorBGShape.getGlobalBounds().width /2, 10));
}
