/**	@file randomizer.h
 *  @brief Randomizer main class
 *
 *	@author Venodez
 *	@bug No known bugs.
 */

#pragma once
#include <cinttypes>
#include "random/data.h"

namespace mod::random
{

    struct Warp
    {
        char stageFrom[8];
        uint8_t roomFrom;
        char stageTo[8];
        uint8_t roomTo;
    } __attribute__( ( __packed__ ) );

    class Randomizer {
        public:
            Randomizer();
            ~Randomizer();
            inline uint64_t *getSeed() { return &seed;}
            inline Warp *getWarps() { return warps; }
            void init(uint64_t seed);
        private:
            uint64_t seed = 0;
            struct Warp warps[STAGE_NB] = {{0}};
            
    };

    Warp getWarp(Warp warps[STAGE_NB], char stage[8], uint8_t room);
    bool roomIsAlreadyUsed(Warp warps[STAGE_NB], const char *stage, uint8_t room);
}