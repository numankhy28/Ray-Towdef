#pragma once

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "raylib.h"
#include "cstdint"
#include "vector"
#include "string"

class TexManager{
public:
    TexManager();
    TexManager(uint8_t size);
    TexManager(const TexManager&) = delete;
    ~TexManager();
    uint8_t EnemyTexLoad(std::string str);
private:
    std::vector<Texture2D> enemytexs;
};


#endif