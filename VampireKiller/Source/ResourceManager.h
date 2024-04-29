#pragma once
#include "raylib.h"
#include "Globals.h"
#include <unordered_map>
#include <string>

enum class ResourceImages {
    IMG_DEATH,
    IMG_WIN,
    IMG_DATA,
    IMG_MENU,
    IMG_PLAYER,
    IMG_ENEMY,
    IMG_TILES,
    IMG_ITEMS
};

enum class ResourceAudio {
    MUSIC_PROLOGUE,
    MUSIC_VAMPIREKILLER,
    MUSIC_STARKER,
    MUSIC_BOSS,
    MUSIC_ENDING,
    MUSIC_GAMEOVER,

    SOUND_ATTACK,
    SOUND_HEART,
    SOUND_ITEM

};

class ResourceManager {
public:
    //Singleton instance retrieval
    static ResourceManager& Instance()
    {
        static ResourceManager instance; //Guaranteed to be initialized only once
        return instance;
    }

    //Load and unload texture
    AppStatus LoadTexture(ResourceImages id, const std::string& file_path);
    void LoadMusic(ResourceAudio id, const std::string& file_path, bool loop);
    void LoadSound(ResourceAudio id, const std::string& file_path);
    void StartMusic(ResourceAudio id);
    void StartSound(ResourceAudio id);
    void ReleaseTexture(ResourceImages id);
    void ReleaseMusic(ResourceAudio id);
    void ReleaseSound(ResourceAudio id);

    //Get texture by key
    const Texture2D* GetTexture(ResourceImages id) const;
    const Music* GetMusic(ResourceAudio id) const;

    //Release resources
    void Release();

    //Ensure Singleton cannot be copied or assigned
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    //Private constructor to prevent instantiation
    ResourceManager();
    //Destructor
    ~ResourceManager();

    //Dictionary to store loaded textures
    std::unordered_map<ResourceImages, Texture2D> textures;
    std::unordered_map<ResourceAudio, Music> musics;
    std::unordered_map<ResourceAudio, Sound> sounds;
};