#include <cstdlib>
#include <cstring>
#include <fstream>
#include <rapidxml_utils.hpp>
#include <texturemanager.hpp>
#include <error/snkexception.hpp>

namespace snk {

TextureManager::TextureManager(BasicShader& shader, const std::string& resDir)
: mShader(shader),
  mResDir(resDir + '/') {}


void TextureManager::loadTexture(const std::string& path) {

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

    attr = node->first_attribute("id");
    if (attr == nullptr) {
        
        throw SnakeException("Could not find id attribute when loading texture with: " + totalPath);

    }
    std::string identifier(attr->value());

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

    auto inserted = mTextures.insert(std::make_pair(identifier, std::move(newTexture))); 
    if (!inserted.second) {

        throw SnakeException("Atempting to load texture with already used ifentifier: " + identifier);

    }

}


Texture& TextureManager::getTexture(const std::string& identifier) {

    // throw exception on failure.
    auto it = mTextures.find(identifier);
    if (it == mTextures.end()) {

        throw SnakeException("Falied to find texture: " + identifier);

    }

    return *(it->second.get());

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
