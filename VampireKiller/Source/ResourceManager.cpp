#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
    Release();
}

//Load a texture from a file and associate it with the key id
AppStatus ResourceManager::LoadTexture(ResourceImages id, const std::string& file_path)
{
    //Load the texture
    Texture2D texture = ::LoadTexture(file_path.c_str());
    if (texture.id == 0)
    {
        //Error loading texture
        LOG("Failed to load texture ", file_path);
        return AppStatus::ERROR;
    }

    //Insert the loaded texture into the map with the specified key
    textures[id] = texture;
    return AppStatus::OK;
}

void ResourceManager::LoadMusic(ResourceAudio id, const std::string& file_path, bool loop)
{
    Music music = ::LoadMusicStream(file_path.c_str());
    musics[id] = music;
    music.looping = loop;
    PlayMusicStream(musics[id]);
    
}

void ResourceManager::LoadSound(ResourceAudio id, const std::string& file_path)
{
    Sound sound = ::LoadSound(file_path.c_str());
    sounds[id] = sound;
    PlaySound(sounds[id]);
}

//Release the texture associated with the key id
void ResourceManager::ReleaseTexture(ResourceImages id)
{
    //Find the texture associated with the key
    auto it = textures.find(id);

    //If found, unload the texture and remove it from the map
    if (it != textures.end())
    {
        UnloadTexture(it->second);
        textures.erase(it);
    }
}

void ResourceManager::ReleaseMusic(ResourceAudio id)
{
    //Find the texture associated with the key
    auto it = musics.find(id);

    //If found, unload the texture and remove it from the map
    if (it != musics.end())
    {
        UnloadMusicStream(it->second);
        musics.erase(it);
    }
}

void ResourceManager::ReleaseSound(ResourceAudio id)
{
    //Find the texture associated with the key
    auto it = sounds.find(id);

    //If found, unload the texture and remove it from the map
    if (it != sounds.end())
    {
        UnloadSound(it->second);
        sounds.erase(it);
    }
}

void ResourceManager::StartMusic(ResourceAudio id)
{
    UpdateMusicStream(musics[id]);
}
void ResourceManager::StartSound(ResourceAudio id)
{
    
}

//Get a texture by key
const Texture2D* ResourceManager::GetTexture(ResourceImages id) const
{
    //Find the texture associated with the key and return it
    auto it = textures.find(id);
    if (it != textures.end())   return &(it->second);

    //Return nullptr if key is not found
    return nullptr;
}

const Music* ResourceManager::GetMusic(ResourceAudio id) const
{
    //Find the texture associated with the key and return it
    auto it = musics.find(id);
    if (it != musics.end())   return &(it->second);

    //Return nullptr if key is not found
    return nullptr;
}

void ResourceManager::Release()
{
    for (auto& pair : textures)
    {
        UnloadTexture(pair.second);
    }
    textures.clear();
}
