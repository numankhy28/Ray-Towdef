#include "AssetManager.h"

AssetManager::AssetManager() {

    
       { Loader load;

        enemytemps.reserve(load.GetEnemyNum());

        SetTraceLogLevel(LOG_DEBUG);
        TraceLog(LOG_DEBUG, "%d", enemytemps.capacity());

        load.InitEnemyAssets(enemytemps, texmanager);}

}

AssetManager::~AssetManager() {
    enemytemps.clear();
}

const std::vector<EnemyDef>& AssetManager::Getenemytempsref() const {
    return enemytemps;
}

const EnemyDef& AssetManager::Getenemytempref(uint16_t index) const {
    return enemytemps[index];
}