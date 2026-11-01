#pragma once

#ifndef JSON_KEYS_H
#define JSON_KEYS_H

namespace JsonKeys {

    inline constexpr const char* IndexPath   = "assets/index.json";
    inline constexpr const char* IndexElem   = "enemypaths";

    inline constexpr const char* Unit        = "unit";
    inline constexpr const char* MoveSpeed   = "movespeed";
    inline constexpr const char* AttackSpeed = "attackspeed";
    inline constexpr const char* MaxHealth   = "maxhealth";
    inline constexpr const char* Damage      = "damage";
    inline constexpr const char* Path        = "path";
    inline constexpr const char* Animations  = "animations";
    inline constexpr const char* Spawnweight = "spawnweight";

    namespace Anim {
        inline constexpr const char* AnimName    = "animname";
        inline constexpr const char* FrameCount  = "framecount";
        inline constexpr const char* FrameTime   = "frametime";
        inline constexpr const char* IsLoop      = "isloop";
        inline constexpr const char* FrameStartY = "framestarty";
        inline constexpr const char* FrameWidth  = "framewidth";
        inline constexpr const char* FrameHeight = "frameheight";
        inline constexpr const char* HitFrames   = "hitframes";

        inline constexpr const char* A_Idle         = "Idle";
        inline constexpr const char* A_Run          = "Run";
        inline constexpr const char* A_ChargeAttack = "ChargeAttack";
        inline constexpr const char* A_Attack       = "Attack";
    }
    
}

#endif