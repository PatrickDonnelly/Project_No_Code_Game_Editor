#include "TextureManager.h"

/// <summary>
/// Checks if a texture is loaded in memory and returns it
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
sf::Texture& TextureManager::getTexture(const std::string& filename) 
{
    auto it = m_textures.find(filename);
    if (it == m_textures.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            // handle error loading texture
        }
        it = m_textures.emplace(filename, std::move(texture)).first;
    }
    return it->second;
    
}

/// <summary>
/// Default constructor
/// </summary>
TextureManager::TextureManager()
{
}

/// <summary>
/// Default destructor
/// </summary>
TextureManager::~TextureManager()
{
}

/// <summary>
/// Returns the number of textures stored in memory
/// </summary>
void TextureManager::getNumberOfTextures()
{
    std::cout << "Total Textures : " << m_textures.size() << std::endl;
}
