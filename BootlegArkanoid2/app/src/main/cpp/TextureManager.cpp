#include "TextureManager.h"
#include <vector>

TextureManager::TextureManager(AAssetManager* assetManager)
        : m_assetManager(assetManager)
{}

TextureManager::~TextureManager(void)
{}

bool TextureManager::CreateTexture(const std::string path)
{
    if (path.empty())
    {
        return false;
    }

    auto textureIt = m_textures.find(path);
    if (textureIt != m_textures.end())
    {
        return false;
    }

    AAsset* textureFile = AAssetManager_open(m_assetManager, path.c_str(), AASSET_MODE_BUFFER);
    if (textureFile == nullptr)
    {
        return false;
    }

    AImageDecoder* decoder = nullptr;
    int32_t result = AImageDecoder_createFromAAsset(textureFile, &decoder);
    if (result != ANDROID_IMAGE_DECODER_SUCCESS)
    {
        return false;
    }

    AImageDecoder_setAndroidBitmapFormat(decoder, ANDROID_BITMAP_FORMAT_RGBA_8888);

    const AImageDecoderHeaderInfo* decoderHeader = nullptr;
    decoderHeader = AImageDecoder_getHeaderInfo(decoder);

    int32_t width = AImageDecoderHeaderInfo_getWidth(decoderHeader);
    int32_t height = AImageDecoderHeaderInfo_getHeight(decoderHeader);
    size_t stride = AImageDecoder_getMinimumStride(decoder);

    std::vector<uint8_t> textureBytes(height * stride);
    result = AImageDecoder_decodeImage(decoder, textureBytes.data(), stride, textureBytes.size());
    if (result != ANDROID_IMAGE_DECODER_SUCCESS)
    {
        return false;
    }

    GLuint ID = 0;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            textureBytes.data()
    );

    m_textures.insert({path, { width, height, static_cast<int32_t>(stride), ID } });

    AImageDecoder_delete(decoder);
    AAsset_close(textureFile);

    return true;
}

const Texture* TextureManager::GetTexture(const std::string path) const
{
    auto textureIt = m_textures.find(path);
    if (textureIt == m_textures.end())
    {
        return nullptr;
    }

    return &(textureIt->second);
}