#include "Enemy.h"


 const AnimationsClip* EnemyDef::getAnimation(AnimNames anim) const {
    for(size_t i = 0; i < this->anims.size(); ++i) {
        if(anim == this->anims[i].animname) return &this->anims[i];
    }
    return nullptr;
}

//inline getters