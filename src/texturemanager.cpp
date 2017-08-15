#include <cstdlib>
#include <cstring>
#include <fstream>
#include <rapidxml_utils.hpp>
#include <texturemanager.hpp>
#include <error/snkexception.hpp>

namespace snk {

TextureManager::TextureManager(unsigned int textureCount, 
                               const std::string& defaultPath)
: mShader(nullptr),
  mDefaultPath(defaultPath + '/'),
  mTextureData(textureCount) {}


void TextureManager::setShader(BasicShader& shader) {

    mShader = &shader;

}


void TextureManager::setDefaultPath(const std::string& texturePath) {

    mDefaultPath = texturePath + '/';

}


void TextureManager::registerTexture(TextureId textureId, const std::string& path) {

    if (textureId >= mTextureData.size()) {

        throw SnakeException("Attempting to assign texture Id which is greater than maximum texture Id");

    }

    if (mTextureData[textureId].init) {

        throw SnakeException("Attempting to assign already assigned texture Id");

    }

    if (path.empty()) {

        throw SnakeException("Attempting to assign empty path for texture");

    }

    mTextureData[textureId].init = true;
    mTextureData[textureId].path = path;

}


Texture& TextureManager::getTexture(TextureId textureId) {

    if (textureId >= mTextureData.size()) {

        throw SnakeException("Attempting to get texture Id which is greater than maximum texture Id");

    }
    TextureData& data = mTextureData[textureId];
    if (data.init != true) {

        throw SnakeException("Attempting to get texture Id which has uninitialied entry in manager");

    }

    try {

        return mTextures.dereference(mTextureData[textureId].handle);

    } catch (SnakeException& e) {

        loadTexture(textureId);
        return mTextures.dereference(mTextureData[textureId].handle);
        
    }

}


void TextureManager::loadTexture(TextureId textureId) { 

    assert(mShader != nullptr);

    std::string totalPath = mDefaultPath + mTextureData[textureId].path;
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

    TextureHandle newHandle;
    Texture& newTexture = mTextures.create(newHandle);
    mTextureData[textureId].handle = newHandle;
    newTexture.init(*mShader, mDefaultPath + attr->value());

    bool valid = true;
    Texture::clip newClip = {0.f, 0.f, 0.f, 0.f};
    for (node = node->first_node();
         valid && (node != nullptr);
         node = node->next_sibling()) {

        valid = parseClip(node, newClip);
        if (valid) {

            newTexture.addClip(newClip);

        }

    }
    if (!valid) {

        throw SnakeException("Invalid clip node found when loading texture with: " + totalPath);

    }

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
