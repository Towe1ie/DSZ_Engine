#pragma once

#include <map>
#include <string>
#include "Texture.h"
#include "PNG_Texture.h"

class ResourceManager
{
private:
	static std::map<std::string, Texture*> textures;

public:
	static void LoadPNGTexture(std::string filename, std::string resource_name);
	static Texture* GetTexture(std::string resource_name);
};