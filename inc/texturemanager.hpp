#ifndef SNAKE_TEXTURE_MANAGER_HEADER
#define SNAKE_TEXTURE_MANAGER_HEADER

#include <vector>
#include <memory>
#include <string>
#include <GL/gl.h>
#include <rapidxml.hpp>
#include <shader/basic.hpp>
#include <texture.hpp>
#include <identifiers.hpp>
#include <resourcemanager.hpp>

namespace snk {

class TextureManager {
public:

    TextureManager(unsigned int textureCount);

    void setShader(BasicShader& shader);
    void setDefaultPath(const std::string& texturePath);

    /// Register a texture with specified Id and path.
    void registerTexture(TextureId textureId, const std::string& path);

    /// Gets specified texture. If texture is not currently loaded, 
    /// then it must be loaded from file first.
    Texture& getTexture(TextureId textureId);

private:

    struct TextureTag {};
    typedef Handle<TextureTag> TextureHandle;

private:

    struct TextureData {

        // init represents whether this entry has been initialised or not.
        bool init = false;
        std::string path;
        TextureHandle handle;

    };

private:

    void loadTexture(TextureId textureId);
    bool parseClip(rapidxml::xml_node<>* node, Texture::clip& newClip);

private:

    BasicShader* mShader;
    std::string mDefaultPath;
    std::vector<TextureData> mTextureData;

    ResourceManager<Texture, TextureTag> mTextures;

};

} // namespace snk

#endif
