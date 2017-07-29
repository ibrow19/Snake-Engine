#include <cstdlib>
#include <cstring>
#include <fstream>
#include <rapidxml_utils.hpp>
#include <texturemanager.hpp>
#include <error/snkexception.hpp>

namespace snk {

TextureManager::TextureManager(unsigned int textureCount,
                               BasicShader& shader, 
                               const std::string& resDir)
: mShader(shader),
  mResDir(resDir + '/'),
  mTextures(textureCount) {
      
    if (textureCount == 0) {

        throw SnakeException("Texture manager must be able to hold at least one texture");

    }

}


void TextureManager::registerTexture(Id textureId, const std::string& path) {

    if (textureId >= mTextures.size()) {

        throw SnakeException("Attempting to assign texture Id which is greater than maximum texture Id");

    }

    if (mTextures[textureId].init) {

        throw SnakeException("Attempting to assign already assigned texture Id");

    }

    if (path.empty()) {

        throw SnakeException("Attempting to assign empty path for texture");

    }

    mTextures[textureId].init = true;
    mTextures[textureId].path = path;

}


Texture& TextureManager::getTexture(Id textureId) {

    if (textureId >= mTextures.size()) {

        throw SnakeException("Attempting to get texture Id which is greater than maximum texture Id");

    }
    Texture* texture = mTextures[textureId].texture.get();
    if (texture == nullptr) {

        loadTexture(textureId);
        texture = mTextures[textureId].texture.get();

    }
    return *texture;

}


void TextureManager::loadTexture(Id textureId) {

    std::string& path = mTextures[textureId].path;
    if (path.empty()) {

        throw SnakeException("Attempting to load texture with Id which has not been initialised");

    }

    std::string totalPath = mResDir + path;
    rapidxml::file<> xmlFile(totalPath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* node = doc.first_node("texture");

    if (node == nullptr) {

        throw SnakeException("Could not find texture node when loading texture with: " + totalPath);

    }

    rapidxml::xml_attribute<>* attr =  node->first_attribute("path");
    if (attr == nullptr) {
        
        throw SnakeException("Could not find path attribute when loading texture with: " + totalPath);

    }
    std::unique_ptr<Texture> newTexture(new Texture(mShader, mResDir + attr->value()));

    bool valid = true;
    Texture::clip newClip = {0.f, 0.f, 0.f, 0.f};
    for (node = node->first_node();
         valid && (node != nullptr);
         node = node->next_sibling()) {

        valid = parseClip(node, newClip);
        if (valid) {

            newTexture->addClip(newClip);

        }

    }
    if (!valid) {

        throw SnakeException("Invalid clip node found when loading texture with: " + totalPath);

    }

    mTextures[textureId].texture = std::move(newTexture);

}


bool TextureManager::parseClip(rapidxml::xml_node<>* node, Texture::clip& newClip) {

    if (node == nullptr || std::strcmp(node->name(),"clip") != 0) {

        return false;

    }
        
    rapidxml::xml_attribute<>* left = node->first_attribute("left");
    rapidxml::xml_attribute<>* top = node->first_attribute("top");
    rapidxml::xml_attribute<>* width = node->first_attribute("width");
    rapidxml::xml_attribute<>* height = node->first_attribute("height");

    if (left == nullptr ||
        top == nullptr ||
        width == nullptr ||
        height == nullptr) {

        return false;

    }

    // TODO: could do more validation here.
    newClip.left = std::strtof(left->value(), nullptr);
    newClip.top = std::strtof(top->value(), nullptr);
    newClip.width = std::strtof(width->value(), nullptr);
    newClip.height = std::strtof(height->value(), nullptr);
        
    return true; 

}

} // namespace snk
