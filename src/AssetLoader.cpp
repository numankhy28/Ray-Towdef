#include "AssetLoader.h"
#include "TextureManager.h"
#include "Variables/JSON_Keys.h"
#ifdef DEBUG 
#include "raylib.h"
#endif

#include <iostream>

constexpr uint8_t INVALID_VALUE = 255;

using  rapidjson::Document;

void parserfunc(Document& doc, std::ifstream& file);
float parsejsonfloat(const rapidjson::Value& val, const char* key, float defaultv = 0);
uint32_t parsejsonuint(const rapidjson::Value& val, const char* key, int defaultv = 20);
std::string parsejsonstring(const rapidjson::Value& val, const char* key);
bool parsejsonbool(const rapidjson::Value& val, const char* key);
uint8_t parsejsonbitmask(const rapidjson::Value& val, const char* key, uint8_t defaultv = 0x00);
AnimNames parsejsonanimename(const rapidjson::Value& val, const char* key);

Loader::Loader() {
    InitIndexJSON();
    //DEBUG COMM
    SetTraceLogLevel(LOG_DEBUG);
    TraceLog(LOG_DEBUG, "Loader Constructor works");
}

Loader::~Loader() {
    //DEBUG COMM
    SetTraceLogLevel(LOG_DEBUG);
    TraceLog(LOG_DEBUG, "Loader Deconstructor works");
}

void Loader::InitEnemyAssets(std::vector<EnemyDef>& enemy, TexManager& texm) {
    
    InitEnemyJSON(enemy, texm);
}

void Loader::InitEnemyJSON(std::vector<EnemyDef>& enemy, TexManager& texm) const {

    rapidjson::Document doc;
    for(auto ite = paths.begin() ; ite != paths.end() ; ++ite) {
        std::ifstream file(*ite);
        if(!file.is_open()) {
            SetTraceLogLevel(LOG_DEBUG);
            TraceLog(LOG_DEBUG, (*ite + " Cannot Opened").c_str());
            continue;
        }

        SetTraceLogLevel(LOG_DEBUG);
        TraceLog(LOG_DEBUG, (*ite + " Opened").c_str());
        parserfunc(doc, file);

        if(!doc.HasMember(JsonKeys::Unit) || !doc[JsonKeys::Unit].IsString() || !doc.HasMember(JsonKeys::Path) ||
        !doc[JsonKeys::Path].IsString() || !doc.HasMember(JsonKeys::Animations) || !doc[JsonKeys::Animations].IsArray()) {
            SetTraceLogLevel(LOG_DEBUG);
            TraceLog(LOG_DEBUG, "%s is corrupted",ite->c_str());
            return;
        }
            //DEBUG COMM
        SetTraceLogLevel(LOG_DEBUG);
        TraceLog(LOG_DEBUG, "%s is okey",ite->c_str());

        auto& ref = enemy.emplace_back();
        
        ref.damage            = parsejsonfloat(doc, JsonKeys::Damage);
        ref.maxhealth         = parsejsonfloat(doc, JsonKeys::MaxHealth);
        ref.attackspeed       = parsejsonfloat(doc, JsonKeys::AttackSpeed);
        ref.movespeed         = parsejsonfloat(doc, JsonKeys::MoveSpeed);  
        ref.unit              = parsejsonstring(doc, JsonKeys::Unit);
        ref.spawnweight       = parsejsonuint(doc, JsonKeys::Spawnweight);
        ref.tex_index         = texm.EnemyTexLoad(parsejsonstring(doc,JsonKeys::Path));
       
        //DEBUG COMM
        SetTraceLogLevel(LOG_DEBUG);
        TraceLog(LOG_DEBUG, "AS %f",ref.attackspeed);
        TraceLog(LOG_DEBUG, "DMG %f",ref.damage);
        TraceLog(LOG_DEBUG, "MH %f",ref.maxhealth);
        TraceLog(LOG_DEBUG, "SW %d",ref.spawnweight);
        TraceLog(LOG_DEBUG, "TI %d",ref.tex_index);
        TraceLog(LOG_DEBUG, ref.unit.c_str());

        ref.anims.reserve(doc[JsonKeys::Animations].Size());
        for(size_t i = 0; i < doc[JsonKeys::Animations].Size(); ++i) {
            ref.anims.emplace_back();
            ref.anims[i].framecount         = parsejsonuint(doc[JsonKeys::Animations][i], JsonKeys::Anim::FrameCount);
            ref.anims[i].framestarty        = parsejsonuint(doc[JsonKeys::Animations][i], JsonKeys::Anim::FrameStartY);
            ref.anims[i].frametime          = parsejsonuint(doc[JsonKeys::Animations][i], JsonKeys::Anim::FrameTime);
            ref.anims[i].frameheight        = parsejsonuint(doc[JsonKeys::Animations][i], JsonKeys::Anim::FrameHeight);
            ref.anims[i].framewidth         = parsejsonuint(doc[JsonKeys::Animations][i], JsonKeys::Anim::FrameWidth);
            ref.anims[i].isloop             = parsejsonbool(doc[JsonKeys::Animations][i], JsonKeys::Anim::IsLoop);
            ref.anims[i].hitframe_mask      = parsejsonbitmask(doc[JsonKeys::Animations][i], JsonKeys::Anim::HitFrames);
            ref.anims[i].animname           = parsejsonanimename(doc[JsonKeys::Animations][i], JsonKeys::Anim::AnimName);

            //DEBUG COMM
            SetTraceLogLevel(LOG_DEBUG);
            TraceLog(LOG_DEBUG, "A_FC %d",ref.anims[i].framecount);
            TraceLog(LOG_DEBUG, "A_FSY %d",ref.anims[i].framestarty );
            TraceLog(LOG_DEBUG, "A_FSH %d",ref.anims[i].frameheight);
            TraceLog(LOG_DEBUG, "A_FSW %d",ref.anims[i].framewidth );
            TraceLog(LOG_DEBUG, "A_BFM %d",ref.anims[i].hitframe_mask);
            TraceLog(LOG_DEBUG, "A_AN %d",ref.anims[i].animname);
            if(ref.anims[i].isloop) TraceLog(LOG_DEBUG, "LOOP: TRUE");
            else TraceLog(LOG_DEBUG, "LOOP: False");
        }

    }
}

void Loader::InitIndexJSON() {
   
    std::ifstream file(JsonKeys::IndexPath);
    if(!file.is_open()) return;
    parserfunc(docI, file);

    if(!docI.HasMember(JsonKeys::IndexElem)) return; // program çöker burada
    if(docI[JsonKeys::IndexElem].IsArray() && docI[JsonKeys::IndexElem].Size() > 0) {
        const auto& docref = docI[JsonKeys::IndexElem];
        paths.reserve(docref.Size());  
        for(size_t i = 0; i < docI[JsonKeys::IndexElem].Size(); i++){
            if(!docI[JsonKeys::IndexElem][i].IsString()) continue;
            paths.push_back(docI[JsonKeys::IndexElem][i].GetString());
            //DEBUG
            SetTraceLogLevel(LOG_DEBUG);
            TraceLog(LOG_DEBUG, paths.back().c_str());
        }
    }
}

uint16_t Loader::GetEnemyNum() {
    return docI[JsonKeys::IndexElem].Size();
}

void parserfunc(Document& doc, std::ifstream& file) {
    std::stringstream buffer;
    buffer << file.rdbuf(); 
    std::string json = buffer.str();
    doc.Parse(json.c_str());
    if(!doc.IsObject() || !doc.IsArray() && doc.HasParseError()) return;
}

float parsejsonfloat(const rapidjson::Value& val, const char* key, float defaultv) {
            TraceLogLevel(LOG_DEBUG);
        TraceLog(LOG_DEBUG,"parjsonfloat");
    
    if(!val.HasMember(key) || !val[key].IsNumber()) {
        return defaultv;
    }

    defaultv = val[key].GetFloat();
    return defaultv;
}

uint32_t parsejsonuint(const rapidjson::Value& val, const char* key, int defaultv) {
            TraceLogLevel(LOG_DEBUG);
        TraceLog(LOG_DEBUG,"parjsonfloat");

    if(!val.HasMember(key) || !val[key].IsNumber()) return defaultv;
    defaultv = val[key].GetUint();
    return defaultv;
}

std::string parsejsonstring(const rapidjson::Value& val, const char* key) {
            TraceLogLevel(LOG_DEBUG);
        TraceLog(LOG_DEBUG,"parjsonfloat");

    if(!val.HasMember(key) || !val[key].IsString() && key != JsonKeys::Path) 
        return "assets/spritesheets/error.png";
    if(!val.HasMember(key) || !val[key].IsString() && key != JsonKeys::Unit) 
        return "Unnamed";
    return val[key].GetString();
}

bool parsejsonbool(const rapidjson::Value& val, const char* key) {
        TraceLogLevel(LOG_DEBUG);
        TraceLog(LOG_DEBUG,"parjsonbool");

    if(!val.HasMember(key) ) return false;
    return val[key].GetBool();
}

uint8_t parsejsonbitmask(const rapidjson::Value& val, const char* key, uint8_t defaultv) {
    if(!val.HasMember(key)) return defaultv;
    if(val[key].IsArray()) {
        for(size_t i = 0; i < val[key].Size(); ++i) {
            defaultv |= (1 << val[key][i].GetInt() - 1);
        }
        return defaultv;
    } else {
       return (defaultv |= (1 << val[key].GetInt() - 1)); 
    }
}

AnimNames parsejsonanimename(const rapidjson::Value& val, const char* key) {
    if(!val.HasMember(key) || !val[key].IsString()) return AnimNames::Invalid;
    
    const char* str = val[key].GetString();

    if(strcmp(str, JsonKeys::Anim::A_Attack) == 0) return AnimNames::Attack;
    if(strcmp(str, JsonKeys::Anim::A_ChargeAttack) == 0) return AnimNames::ChargeAttack;
    if(strcmp(str, JsonKeys::Anim::A_Idle) == 0) return AnimNames::Idle;
    if(strcmp(str, JsonKeys::Anim::A_Run) == 0) return AnimNames::Run;

    return AnimNames::Invalid;
}