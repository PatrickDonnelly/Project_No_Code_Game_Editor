#pragma once
#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>


class FontManager
{
public:
    FontManager();
    ~FontManager();

    sf::Font& getFont(const std::string& filename);
    void getNumberOfFonts();
private:
    static std::unordered_map<std::string, sf::Font> m_fonts;

};



#endif //!FONTMANAGER_HPP

