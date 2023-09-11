#ifndef BOOTLEG_ARKANOID_2_TEXTUREMANAGER_H
#define BOOTLEG_ARKANOID_2_TEXTUREMANAGER_H

#include <map>
#include <string>
#include <android/asset_manager.h>
#include <android/imagedecoder.h>
#include "Texture.h"

class TextureManager
{
public:
    explicit TextureManager(AAssetManager* assetManager);
    ~TextureManager(void);

    bool CreateTexture(const std::string path);

    const Texture* GetTexture(const std::string path) const;

private:
    AAssetManager* m_assetManager;
    std::map<std::string, Texture> m_textures;
};

#endif //BOOTLEG_ARKANOID_2_TEXTUREMANAGER_H
