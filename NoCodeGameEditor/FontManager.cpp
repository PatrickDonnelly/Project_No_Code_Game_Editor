#include "FontManager.h"

std::unordered_map<std::string, sf::Font> FontManager::m_fonts;

sf::Font& FontManager::getFont(const std::string& filename)
{
    auto it = m_fonts.find(filename);
    if (it == m_fonts.end()) {
        sf::Font font;
        if (!font.loadFromFile(filename)) 
        {
            std::cout << "error loading font" << std::endl;
        }
        it = m_fonts.emplace(filename, std::move(font)).first;
    }
    else
    {
        //std::cout << "font already loaded" << std::endl;
    }
    return it->second;

}

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

void FontManager::getNumberOfFonts()
{
    std::cout << "Total Fonts : " << m_fonts.size() << std::endl;
}