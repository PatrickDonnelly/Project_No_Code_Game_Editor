#include "InspectorOptions.h"

/// <summary>
/// Default constructor for the inspector options class
/// </summary>
InspectorOptions::InspectorOptions()
{
}

/// <summary>
/// Overloaded constructor for the Inspector options class
/// </summary>
/// <param name="t_font"></param>
/// <param name="t_noOfOptions"></param>
/// <param name="t_tag"></param>
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

/// <summary>
/// initialise Options you can find in the inspector
/// </summary>
void InspectorOptions::initOptions()
{
    if (m_tag == "Behaviour")
    {
        for (int i = 0; i < m_noOfOptions; ++i)
        {
            if (i == 0)
                m_options.push_back(new CheckBox("Multi"));
            if (i == 1)
                m_options.push_back(new CheckBox("Patrol"));
            if (i == 2)
                m_options.push_back(new CheckBox("Wander"));
            if (i == 3)
                m_options.push_back(new CheckBox("Follow"));
            if (i == 4)
                m_options.push_back(new CheckBox("Static"));
            if (i == 5)
                m_options.push_back(new CheckBox("ConeVision"));
            if (i == 6)
                m_options.push_back(new CheckBox("RadialVision"));

            m_options.at(i)->setCheckBoxPosition(sf::Vector2f(
                (m_inspectorOptionsLabel->getText()->getPosition().x),
                (m_inspectorOptionsLabel->getText()->getPosition().y + 10 + (i * m_options.at(i)->getCheckBoxBounds().getGlobalBounds().height + 5))));
        }
    }
    else if (m_tag == "Stats")
    {
        for (int i = 0; i < m_noOfOptions; ++i)
        {
            if (i == 0)
                m_options.push_back(new CheckBox("Health"));
            if (i == 1)
                m_options.push_back(new CheckBox("Attack"));
            if (i == 2)
                m_options.push_back(new CheckBox("Speed"));

            m_options.at(i)->setCheckBoxPosition(sf::Vector2f(
                (m_inspectorOptionsLabel->getText()->getPosition().x),
                (m_inspectorOptionsLabel->getText()->getPosition().y + 10 + (i * m_options.at(i)->getCheckBoxBounds().getGlobalBounds().height + 5))));
        }
    }
    else if (m_tag == "Sound")
    {
        for (int i = 0; i < m_noOfOptions; ++i)
        {
            if (i == 0)
                m_options.push_back(new CheckBox("Add Sound"));
            if (i == 1)
                m_options.push_back(new CheckBox("Play When hit"));
            if (i == 2)
                m_options.push_back(new CheckBox("Play On Death"));
            if (i == 3)
                m_options.push_back(new CheckBox("Play On Interaction"));


            m_options.at(i)->setCheckBoxPosition(sf::Vector2f(
                (m_inspectorOptionsLabel->getText()->getPosition().x),
                (m_inspectorOptionsLabel->getText()->getPosition().y + 10 + (i * m_options.at(i)->getCheckBoxBounds().getGlobalBounds().height + 5))));
        }
    }
    else if (m_tag == "Dialogue")
    {
        for (int i = 0; i < m_noOfOptions; ++i)
        {

            m_options.push_back(new CheckBox("Add Dialogue"));


            m_options.at(i)->setCheckBoxPosition(sf::Vector2f(
                (m_inspectorOptionsLabel->getText()->getPosition().x),
                (m_inspectorOptionsLabel->getText()->getPosition().y + 10 + (i * m_options.at(i)->getCheckBoxBounds().getGlobalBounds().height + 5))));
        }
    }
}

/// <summary>
/// Deconstructor
/// </summary>
InspectorOptions::~InspectorOptions()
{
}

/// <summary>
/// returns the sprite of the inspector options
/// </summary>
/// <returns></returns>
sf::Sprite InspectorOptions::getInspectorOptionsSprite()
{
    return sf::Sprite();
}

/// <summary>
/// gets the position of the background
/// </summary>
/// <returns></returns>
sf::Vector2f InspectorOptions::getInspectorOptionsPosition()
{
    return m_inspectorOptionsBGShape.getPosition();
}

/// <summary>
/// initialises Inspector options Background
/// </summary>
void InspectorOptions::initInspectorOptions()
{
    m_inspectorOptionsBGShape.setSize(sf::Vector2f(400.0f, 200.0f));
    m_inspectorOptionsBGShape.setPosition(1520.0f, 40.0f);
    m_inspectorOptionsBGShape.setOutlineThickness(4.0f);
    m_inspectorOptionsBGShape.setOutlineColor(sf::Color::Black);
    m_inspectorOptionsBGShape.setFillColor(sf::Color(sf::Color(204, 204, 204)));
}

/// <summary>
/// Sets the position of the inspectors options background
/// </summary>
/// <param name="t_pos"></param>
void InspectorOptions::setInspectorOptionsPosition(sf::Vector2f t_pos)
{
    m_inspectorOptionsBGShape.setPosition(t_pos);
}


/// <summary>
/// Renders the inpector options class
/// </summary>
/// <param name="t_window"></param>
void InspectorOptions::render(sf::RenderWindow* t_window)
{
    t_window->draw(m_inspectorOptionsBGShape);
   // m_inspectorOptionsLabel->render(t_window);

    for (int i = 0; i < m_noOfOptions; ++i)
    {
        m_options.at(i)->render(t_window);
    }

    //t_window->draw(m_text);
}


/// <summary>
/// Init the label text
/// </summary>
void InspectorOptions::initText()
{

   // m_inspectorOptionsLabel->setText(m_tag);
   // m_inspectorOptionsLabel->setTextPosition(sf::Vector2f(m_inspectorOptionsBGShape.getPosition().x + m_inspectorOptionsLabel->getText()->getGlobalBounds().width /2 + 5, m_inspectorOptionsBGShape.getPosition().y +10));
}