#pragma once
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "Enemy.h"
#include "AssetLoader.h"
#include "TextureManager.h"
#include "vector"

class AssetManager {
public:
    AssetManager();
    AssetManager(const AssetManager&) = delete;
    ~AssetManager();
    const std::vector<EnemyDef>& Getenemytempsref() const;
    const EnemyDef& Getenemytempref(uint16_t index) const;
private:
    TexManager texmanager;
    std::vector<EnemyDef> enemytemps;
};


#endif