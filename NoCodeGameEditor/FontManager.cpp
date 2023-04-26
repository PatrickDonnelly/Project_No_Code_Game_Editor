#include "FontManager.h"

std::unordered_map<std::string, sf::Font> FontManager::m_fonts; // stores fonts

/// <summary>
/// Checks if a font has already been loaded into memory.
/// If it has it returns a pointer to the font
/// If not it loads the font and reurns a pinter to it
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
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

/// <summary>
/// Constructor
/// </summary>
FontManager::FontManager()
{
}

/// <summary>
/// Deconstructor
/// </summary>
FontManager::~FontManager()
{
}

/// <summary>
/// Prints the number of fonts that have been loaded and stored in memory
/// </summary>
void FontManager::getNumberOfFonts()
{
    std::cout << "Total Fonts : " << m_fonts.size() << std::endl;
}