#include "framework/AssetManager.h"

namespace ly
{
    unique<AssetManager> AssetManager::assetManager{nullptr};

    AssetManager::AssetManager()
        : mRootDirectory()
    {

    }

    AssetManager &AssetManager::Get()
    {
        if(!assetManager)
        {
            assetManager = unique<AssetManager>{new AssetManager};
        }

        return *assetManager;
    }

    shared<sf::Texture> AssetManager::LoadTexture(const std::string &path)
    {
        return LoadAsset(path, mLoadedTextureMap);
    }

    shared<sf::Font> AssetManager::LoadFont(const std::string &path)
    {
        return LoadAsset(path, mLoadedFontMap);
    }

    void AssetManager::CleanCycle()
    {
        CleanUniqueRef(mLoadedTextureMap);
        CleanUniqueRef(mLoadedFontMap);
    }

    void AssetManager::SetAssetRootDirectory(const std::string &directory)
    {
        mRootDirectory = directory;
    }
}
