#include "ResourceManager.h"

textureCache ResourceManager::texturecache;

GLTexture ResourceManager::getTexture(string texturePath) {
	return texturecache.getTexture(texturePath);
}