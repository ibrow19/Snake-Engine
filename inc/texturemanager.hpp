#ifndef SNAKE_TEXTURE_MANAGER_HEADER
#define SNAKE_TEXTURE_MANAGER_HEADER

#include <map>
#include <memory>
#include <string>
#include <GL/gl.h>
#include <rapidxml.hpp>
#include "shader/basic.hpp"
#include "texture.hpp"

namespace snk {

class TextureManager {
public:

    TextureManager(BasicShader& shader);

    void loadTexture(const std::string& path);
    Texture& getTexture(const std::string& identifier);

private:

    bool parseClip(rapidxml::xml_node<>* node, Texture::clip& newClip);

private:

    BasicShader& mShader;
    std::map<std::string, std::unique_ptr<Texture>> mTextures;

};

} // namespace snk

#endif
