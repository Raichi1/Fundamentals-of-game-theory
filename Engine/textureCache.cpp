#include "textureCache.h"
#include "ImageLoader.h"

textureCache::textureCache()
{
}

textureCache::~textureCache()
{
}

GLTexture textureCache::getTexture(string texturePath)
{
    auto mit = textureMap.find(texturePath);
    if (mit == textureMap.end()) {
        GLTexture texture = ImageLoader::loadPNG(texturePath);
        textureMap[texturePath] = texture;
        return texture;
    }
    return mit->second;
}
