#pragma once

#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include "vector"
#include "string"
#include "enemy.h"
#include "rapidjson/document.h"
#include <fstream>
#include <sstream>

class TexManager;

class Loader{
public:
    Loader();
    Loader(const Loader&) = delete;
    ~Loader();
    void InitEnemyAssets(std::vector<EnemyDef>& enemy, TexManager& texm);
    uint16_t GetEnemyNum();
private:
    void InitEnemyJSON(std::vector<EnemyDef>& enemy, TexManager& texm) const;
    void InitIndexJSON();
    std::vector<std::string> paths;
    rapidjson::Document docI;
};

#endif