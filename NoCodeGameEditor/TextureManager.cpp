#include "TextureManager.h"

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

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::getNumberOfTextures()
{
    std::cout << "Total Textures : " << m_textures.size() << std::endl;
}
