#include "ResourceManager.h"
#include "PNG_Texture.h"

using namespace std;

map<string, Texture*> ResourceManager::textures;

void ResourceManager::LoadPNGTexture(std::string filename, std::string resource_name)
{
	
	if (textures.find(resource_name) == textures.end())
	{
		PNG_Texture* texture = new PNG_Texture();
		texture->Load(filename.c_str());
		textures[resource_name] = texture;
	}


}

Texture* ResourceManager::GetTexture(std::string resource_name)
{
	if (textures.find(resource_name) != textures.end())
	{
		return textures[resource_name];
	}
	else
	{
		return nullptr;
	}
}