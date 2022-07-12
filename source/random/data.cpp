/**	@file data.h
 *  @brief data file
 *
 *	@author Venodez
 *	@bug No known bugs.
 */

#include "random/data.h"
#include <cstring>

namespace mod::random::data
{
    struct Stage getStage(char stage[8]) {
        for (uint8_t i = 0; i < STAGE_NB; ++i) {
            if (!strcmp(stage, stages[i].name))
                return stages[i];
        }
        return {0};
    }

    uint8_t getRoomNb(struct Stage stage) {
        uint8_t len = 0;
        for (; len < MAX_ROOM_NUMBER && stage.rooms[len] != -1; ++len);
        return (len);
    }
}