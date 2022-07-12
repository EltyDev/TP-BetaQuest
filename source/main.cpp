/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date YYYY-MM-DD
 *
 * @copyright Copyright (c) YYYY
 *
 */
#include <display/console.h>     // Contains a very neat helper class to print to the console
#include <main.h>
#include <patch.h>     // Contains code for hooking into a function
#include <tp/f_ap_game.h>
#include <tp/m_do_controller_pad.h>
#include <tp/d_com_inf_game.h>
#include "tp/f_pc_node_req.h"
#include <tp/f_op_scene_req.h>
#include <cstring>
#include "tools.h"
#include "random/data.h"

namespace mod
{
    Mod* gMod = nullptr;

    void main()
    {
        Mod* mod = new Mod();
        mod->init();
    }

    void exit() {}

    Mod::Mod(): console( 0 ) { ticks = 0; }

    void Mod::init()
    {
        gMod = this;
        randomizer = new random::Randomizer();
        return_fapGm_Execute =
            libtp::patch::hookFunction( libtp::tp::f_ap_game::fapGm_Execute, []() { return gMod->procNewFrame(); } );
    }

    void Mod::procNewFrame()
    {
        using namespace libtp::tp::f_pc_node_req;
        using namespace libtp::tp::d_com_inf_game;
        using namespace libtp::tp::f_op_scene_req;
        using namespace libtp::tp::m_do_controller_pad;
        using namespace mod::random::data;

        ++ticks;
        if (l_fpcNdRq_Queue) {
            uint8_t prevState = gameState;
            uint8_t state = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>(l_fpcNdRq_Queue) + 0x59 );
            if ( prevState != GAME_ACTIVE && state == 11 ) {
                if (strcmp( "S_MV000", dComIfG_gameInfo.nextStageVars.nextStage) != 0)
                    gameState = GAME_ACTIVE;
            } else if (prevState != GAME_TITLE && ( state == 12 || state == 13 ))
                    gameState = GAME_TITLE;
            if  (gameState == GAME_ACTIVE && prevState == GAME_TITLE) {
                uint64_t temp_seed = ticks;
                libtp::tools::getRandom(&temp_seed, 0);
                randomizer->init(temp_seed);
            }
        }
        if (cpadInfo.buttonInput == 0x30 && lastButton != 0x30)
            setScreen(!consoleState);
        lastButton = cpadInfo.buttonInput;
        if (isLoading && !isRandomized && gameState == GAME_ACTIVE) {
            mod::random::Warp warp = mod::random::getWarp(randomizer->getWarps(), dComIfG_gameInfo.currentStage, actualRoom);
            strcpy(dComIfG_gameInfo.nextStageVars.nextStage, warp.stageTo);
            dComIfG_gameInfo.nextStageVars.nextRoom = warp.roomTo;
            dComIfG_gameInfo.nextStageVars.nextState = 0xFF;
            dComIfG_gameInfo.nextStageVars.nextSpawnPoint = 0x00;
            dComIfG_gameInfo.nextStageVars.isVoidorWarp = 0x00;
            isRandomized = true;
        } else if (!isLoading)
            isRandomized = false;
        console.setLine(6);
        console << "\r"
          << "Frames: " << ticks << "\n"
          << "Map: " << dComIfG_gameInfo.currentStage << "\n"
          << "Is Loading: " << isLoading << "\n"
          << "Room: " << dComIfG_gameInfo.nextStageVars.nextRoom << "\n"
          << "Seed: " << *randomizer->getSeed() << "\n"
          << "Game State: " << gameState << "\n"
          << "Warping Type: " << dComIfG_gameInfo.nextStageVars.isVoidorWarp << "\n"
          << "Trigger Load: " << dComIfG_gameInfo.nextStageVars.triggerLoad << "\n"
          << "Randomizer: " << "{ " << randomizer->getWarps()[0].stageFrom << " [" << randomizer->getWarps()[0].roomFrom << "]} -> " << randomizer->getWarps()[0].stageTo << " [" << randomizer->getWarps()[0].roomTo << "]}";
        actualRoom = dComIfG_gameInfo.nextStageVars.nextRoom;
        return return_fapGm_Execute();
    }

    void Mod::setScreen( bool state )
    {
        consoleState = state;
        libtp::display::setConsole( state, 0 );
    }
}     // namespace mod