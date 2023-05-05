#pragma once
#include "GLTexture.h"
#include "textureCache.h"

class ResourceManager
{
private:
	static textureCache texturecache;
public:
	static GLTexture getTexture(string texturePath);
};

