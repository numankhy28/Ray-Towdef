#include "TextureManager.h"

TexManager::TexManager() {
    enemytexs.reserve(8);
}

TexManager::TexManager(uint8_t size) {
    enemytexs.reserve(size);
}

TexManager::~TexManager() {
    for(const Texture2D& tex : enemytexs) {
        UnloadTexture(tex);
    }
    enemytexs.clear();
}

uint8_t TexManager::EnemyTexLoad(std::string str) {

    enemytexs.push_back(LoadTexture(str.c_str()));
    return uint8_t(enemytexs.size() - 1);
};
