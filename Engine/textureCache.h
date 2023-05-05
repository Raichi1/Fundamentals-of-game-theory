#pragma once
#include "GLTexture.h"
#include <map>
#include <string>
using namespace std;

class textureCache
{
private:
	map<string, GLTexture> textureMap;
public:
	textureCache();
	~textureCache();
	GLTexture getTexture(string texturePath);
};

