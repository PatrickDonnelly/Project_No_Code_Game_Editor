#pragma once
#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    sf::Texture& getTexture(const std::string& filename);
    void getNumberOfTextures();
private:
    std::unordered_map<std::string, sf::Texture> m_textures;

};
#endif //!TEXTUREMANAGER_HPP
