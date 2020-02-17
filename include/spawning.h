#pragma once

#include <stdint.h>
#include "libtp_c/include/tp.h"
#include <string.h>

struct ActorMemory {
    uint32_t params;
    Vec3 coord;
    uint16_t rotation[2];
    uint16_t flag;
    uint16_t enemyId;
    uint8_t flags[9];
    uint8_t room_id;
    uint8_t padding[2];
};

struct ActorTemplate {
    uint8_t name[8];
    uint32_t params;
    Vec3 coord;
    uint16_t rotation[2];
    uint16_t flag;
    uint16_t enemyId;
};

struct ActorInfo {
    char name[8];
    uint16_t param;
    uint8_t param1;
    uint8_t param2;
};

#define fopAcM_CreateAppend_addr 0x80019AA8
#define dStage_ActorCreate_addr 0x80024EFC

typedef ActorMemory *(*fopAcM_CreateAppend_t)(void);
typedef void (*dStage_ActorCreate_t)(ActorTemplate &, ActorMemory &);

#define fopAcM_CreateAppend ((fopAcM_CreateAppend_t)fopAcM_CreateAppend_addr)
#define dStage_ActorCreate ((dStage_ActorCreate_t)dStage_ActorCreate_addr)

void createActor(const char *name, Vec3 &coord, uint16_t rotation) {
    ActorTemplate actTemp;
    actTemp.coord.x = coord.x;
    actTemp.coord.y = coord.y;
    actTemp.coord.z = coord.z;
    actTemp.params = 0;
    actTemp.flag = 0;
    actTemp.enemyId = -1;
    actTemp.rotation[0] = 0;
    actTemp.rotation[1] = rotation;
    strcpy((char *)(actTemp.name), name);

    ActorMemory *mem = fopAcM_CreateAppend();
    mem->params = actTemp.params;
    mem->coord.x = actTemp.coord.x;
    mem->coord.y = actTemp.coord.y;
    mem->coord.z = actTemp.coord.z;
    mem->rotation[0] = actTemp.rotation[0];
    mem->rotation[1] = actTemp.rotation[1];
    mem->flag = actTemp.flag;
    mem->enemyId = actTemp.enemyId;
    mem->room_id = tp_gameInfo.last_room_id;

    dStage_ActorCreate(actTemp, *mem);
}

void spawn(const char *name) {
    auto link = TP::get_link_debug();
    if (link) {
        createActor(name, link->position, link->facing);
    }
}