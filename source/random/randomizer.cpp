/**	@file randomizer.cpp
 *  @brief Randomizer main class
 *
 *	@author Venodez
 *	@bug No known bugs.
 */

#include "random/randomizer.h"

#include <cstring>

#include "tools.h"
#include <gc_wii/card.h>
#include "random/data.h"

namespace mod::random
{

    using namespace mod::random::data;

    Randomizer::Randomizer() {}

    void Randomizer::init(uint64_t seed)
    {
        this->seed = seed;
        int index = 0;
        for (int i = 0; i < STAGE_NB; ++i) {
            for (int j = 0; j < MAX_ROOM_NUMBER && stages[i].rooms[j] != -1; ++j) {
                if (!roomIsAlreadyUsed(warps, stages[i].name, stages[i].rooms[j]))
                    continue;
                strcpy(warps[index].stageFrom, stages[i].name);
                warps[index].roomFrom = stages[i].rooms[j];
                uint32_t k = libtp::tools::getRandom(&seed, STAGE_NB);
                uint32_t l = libtp::tools::getRandom(&seed, getRoomNb(stages[k]));
                while (roomIsAlreadyUsed(warps, stages[k].name, stages[k].rooms[l])) {
                    k = libtp::tools::getRandom(&seed, STAGE_NB);
                    l = libtp::tools::getRandom(&seed, getRoomNb(stages[k]));
                }
                strcpy(warps[index].stageTo, stages[k].name);
                warps[index].roomTo = stages[k].rooms[l];
                ++index;
                strcpy(warps[index].stageFrom, stages[k].name);
                warps[index].roomFrom = stages[k].rooms[l];
                strcpy(warps[index].stageTo, stages[i].name);
                warps[index].roomTo = stages[i].rooms[j];
                ++index;
            }
        }
    }

    bool roomIsAlreadyUsed(Warp warps[STAGE_NB], const char *stage, uint8_t room)
    {
        for (int i = 0; i < STAGE_NB; ++i) {
            if (!strcmp(warps[i].stageFrom, stage) && warps[i].roomFrom == room) 
                return true;
        }
        return false;
    }

    Warp getWarp(Warp warps[STAGE_NB], char stage[8], uint8_t room)
    {
        for (int i = 0; i < STAGE_NB; ++i) {
            if (!strcmp(warps[i].stageFrom, stage) && warps[i].roomFrom == room) 
                return warps[i];
        }
        return {0};
    }
}