#pragma Once

#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <cstdint>
#include <string>

struct Texture;
typedef struct Texture Texture2D;

enum class AnimNames : uint8_t{
    Idle = 0,
    Run,
    Attack,
    ChargeAttack,
    Count,
    Invalid = Count
};


struct AnimationsClip{
    AnimNames                   animname;
    uint16_t                    framestarty;
    uint16_t                    frameheight;
    uint16_t                    framewidth;
    uint8_t                     framecount;
    uint8_t                     frametime;
    uint8_t                     hitframe_mask = 0x00;
    //biti 1 olan kareler vuruş kareleri
    //json = tile-based kodda -1 uygulanmalı. json: 5 = 4.index
    bool                        isloop;
};

struct EnemyDef{
    std::string                 unit;
    uint8_t                    tex_index;
    float                       maxhealth;
    float                       attackspeed;
    float                       movespeed;
    float                       damage;
    uint8_t                     spawnweight;
    std::vector<AnimationsClip> anims;

    const AnimationsClip* getAnimation(AnimNames anim) const;
};



#endif