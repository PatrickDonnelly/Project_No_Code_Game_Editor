#include "InspectorOptions.h"


InspectorOptions::InspectorOptions()
{
}

InspectorOptions::InspectorOptions(sf::Font& t_font, int t_noOfOptions, std::string t_tag)
{
    m_tag = t_tag;
    m_font = t_font;
    m_noOfOptions = t_noOfOptions;
    initInspectorOptions();
    m_inspectorOptionsLabel = new Label(m_font);
    initText();
    initOptions();
}

void InspectorOptions::initOptions()
{
    if (m_tag == "Behaviour")
    {
        for (int i = 0; i < m_noOfOptions; ++i)
        {
            if (i == 0)
                m_options.push_back(new CheckBox(m_font, "Multi"));
            if (i == 1)
                m_options.push_back(new CheckBox(m_font, "Patrol"));
            if (i == 2)
                m_options.push_back(new CheckBox(m_font, "Wander"));
            if (i == 3)
                m_options.push_back(new CheckBox(m_font, "Follow"));
            if (i == 4)
                m_options.push_back(new CheckBox(m_font, "Static"));
            if (i == 5)
                m_options.push_back(new CheckBox(m_font, "ConeVision"));
            if (i == 6)
                m_options.push_back(new CheckBox(m_font, "RadialVision"));

            m_options.at(i)->setCheckBoxPosition(sf::Vector2f(
                (m_inspectorOptionsLabel->getText().getPosition().x),
                (m_inspectorOptionsLabel->getText().getPosition().y + 10 + (i * m_options.at(i)->getCheckBoxBounds().getGlobalBounds().height + 5))));
        }
    }
    else if (m_tag == "Stats")
    {
        for (int i = 0; i < m_noOfOptions; ++i)
        {
            if (i == 0)
                m_options.push_back(new CheckBox(m_font, "Health"));
            if (i == 1)
                m_options.push_back(new CheckBox(m_font, "Attack"));
            if (i == 2)
                m_options.push_back(new CheckBox(m_font, "Speed"));

            m_options.at(i)->setCheckBoxPosition(sf::Vector2f(
                (m_inspectorOptionsLabel->getText().getPosition().x),
                (m_inspectorOptionsLabel->getText().getPosition().y + 10 + (i * m_options.at(i)->getCheckBoxBounds().getGlobalBounds().height + 5))));
        }
    }
    else if (m_tag == "Sound")
    {
        for (int i = 0; i < m_noOfOptions; ++i)
        {
            if (i == 0)
                m_options.push_back(new CheckBox(m_font, "Add Sound"));
            if (i == 1)
                m_options.push_back(new CheckBox(m_font, "Play When hit"));
            if (i == 2)
                m_options.push_back(new CheckBox(m_font, "Play On Death"));
            if (i == 3)
                m_options.push_back(new CheckBox(m_font, "Play On Interaction"));


            m_options.at(i)->setCheckBoxPosition(sf::Vector2f(
                (m_inspectorOptionsLabel->getText().getPosition().x),
                (m_inspectorOptionsLabel->getText().getPosition().y + 10 + (i * m_options.at(i)->getCheckBoxBounds().getGlobalBounds().height + 5))));
        }
    }
    else if (m_tag == "Dialogue")
    {
        for (int i = 0; i < m_noOfOptions; ++i)
        {

            m_options.push_back(new CheckBox(m_font, "Add Dialogue"));


            m_options.at(i)->setCheckBoxPosition(sf::Vector2f(
                (m_inspectorOptionsLabel->getText().getPosition().x),
                (m_inspectorOptionsLabel->getText().getPosition().y + 10 + (i * m_options.at(i)->getCheckBoxBounds().getGlobalBounds().height + 5))));
        }
    }
}

InspectorOptions::~InspectorOptions()
{
}

sf::Sprite InspectorOptions::getInspectorOptionsSprite()
{
    return sf::Sprite();
}

sf::Vector2f InspectorOptions::getInspectorOptionsPosition()
{
    return m_inspectorOptionsBGShape.getPosition();
}

void InspectorOptions::initInspectorOptions()
{
    m_inspectorOptionsBGShape.setSize(sf::Vector2f(400.0f, 200.0f));
    m_inspectorOptionsBGShape.setPosition(1520.0f, 40.0f);
    m_inspectorOptionsBGShape.setOutlineThickness(4.0f);
    m_inspectorOptionsBGShape.setOutlineColor(sf::Color::Black);
    m_inspectorOptionsBGShape.setFillColor(sf::Color(sf::Color(204, 204, 204)));
}

void InspectorOptions::setInspectorOptionsPosition(sf::Vector2f t_pos)
{
    m_inspectorOptionsBGShape.setPosition(t_pos);
}



void InspectorOptions::render(sf::RenderWindow* t_window)
{
    t_window->draw(m_inspectorOptionsBGShape);
    m_inspectorOptionsLabel->render(t_window);

    for (int i = 0; i < m_noOfOptions; ++i)
    {
        m_options.at(i)->render(t_window);
    }

    //t_window->draw(m_text);
}

bool InspectorOptions::isEnabled()
{
    return false;
}

void InspectorOptions::splitString(std::string t_dialogueText)
{
}

void InspectorOptions::initText()
{
    //m_text.setFont(m_font);
    //m_text.setCharacterSize(20.0f);
    //m_text.setFillColor(sf::Color::Blue);
    //m_text.setOutlineColor(sf::Color::Red);
    //m_text.setOutlineThickness(2.0f);
    //m_text.setPosition(10.0f, 10.0f);
    m_inspectorOptionsLabel->setText(m_tag);
    m_inspectorOptionsLabel->setTextPosition(sf::Vector2f(m_inspectorOptionsBGShape.getPosition().x + m_inspectorOptionsLabel->getText().getGlobalBounds().width /2 + 5, m_inspectorOptionsBGShape.getPosition().y +10));
}