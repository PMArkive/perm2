/*
    Pokémon neo
    ------------------------------

    file        : sound.h
    author      : Philip Wellnitz
    description : Header file. Consult the corresponding source file (item.cpp) for details.

    Copyright (C) 2012 - 2022
    Philip Wellnitz

    This file is part of Pokémon neo.

    Pokémon neo is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pokémon neo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Pokémon neo.  If not, see <http://www.gnu.org/licenses/>.
    */

#pragma once

#include <nds/ndstypes.h>
#include "locationNames.h"
#include "mapDefines.h"
#include "pokemonNames.h"
#include "soundbank.h"
#include "trainerClassNames.h"

#define SFX_BATTLE_ABILITY       0
#define SFX_BATTLE_BALLDROP      1
#define SFX_BATTLE_BALLSHAKE     2
#define SFX_BATTLE_DAMAGE_NORMAL 3
#define SFX_BATTLE_DAMAGE_SUPER  4
#define SFX_BATTLE_DAMAGE_WEAK   5
#define SFX_BATTLE_DECREASE      6
#define SFX_BATTLE_ESCAPE        7
#define SFX_BATTLE_EXPFULL       8
#define SFX_BATTLE_FAINT         9
#define SFX_BATTLE_INCREASE      10
#define SFX_BATTLE_JUMPTOBALL    11
#define SFX_BATTLE_RECALL        12
#define SFX_BATTLE_THROW         13
#define SFX_BIKE                 14
#define SFX_BUMP                 15
#define SFX_CANCEL               16
#define SFX_CAVE_WARP            17
#define SFX_CHOOSE               18
#define SFX_ENTER_DOOR           19
#define SFX_EXMARK               20
#define SFX_JUMP                 21
#define SFX_MENU                 22
#define SFX_NAV                  23
#define SFX_OBTAIN_EGG           24
#define SFX_OBTAIN_ITEM          25
#define SFX_OBTAIN_KEY_ITEM      26
#define SFX_PC_CLOSE             27
#define SFX_PC_OPEN              28
#define SFX_SAVE                 29
#define SFX_SELECT               30
#define SFX_SHINY                31
#define SFX_USE_ITEM             32
#define SFX_WARP                 33
#define SFX_TELEPORT_DOWN        34
#define SFX_TELEPORT_UP          35
#define SFX_SLIDING_DOOR         36
#define SFX_HM_CUT               37
#define SFX_HM_FLY               38
#define SFX_HM_ROCKSMASH         39
#define SFX_HM_STRENGTH          40
#define SFX_OBTAIN_TM            41
#define SFX_BUY_SUCCESSFUL       42
#define SFX_CAPTURE_SUCCESSFUL   43

void initSound( );

namespace SOUND {
    constexpr u16 JBOX_DISABLED = u16( -1 );

    extern bool BGMforced;
    extern u16  currentBGM;

    /*
     * @brief: Initializes sound effects for battles.
     */
    void initBattleSound( );

    /*
     * @brief: Unloads battle SFX and loads general sfx.
     */
    void deinitBattleSound( );

    void playBGM( u16 p_id, bool p_force = false );
    void playBGMOneshot( u16 p_id );
    void playSoundEffect( u16 p_id );

    void playCry( u16 p_pokemonId, u8 p_formeId = 0, bool p_female = false );

    void setVolume( u16 p_newValue );
    void dimVolume( );
    void restoreVolume( );

    u16           BGMforWeather( MAP::mapWeather p_weather );
    u16           BGMforMoveMode( MAP::moveMode p_moveMode );
    constexpr u16 BGMforTrainerEncounter( u16 p_trainerClassId ) {
        switch( p_trainerClassId ) {
        case TC_POKEMON_TRAINER: return MOD_ENCOUNTER_BRENDAN;
        case TC__POKEMON_TRAINER: return MOD_ENCOUNTER_MAY;
        case TC_AQUA_ADMIN:
        case TC_AQUA_LEADER:
        case TC_TEAM_AQUA:
        case TC_MAGMA_ADMIN:
        case TC_MAGMA_LEADER:
        case TC_TEAM_MAGMA: return MOD_ENCOUNTER_TEAM_AM;
        case TC_TWINS:
        case TC_SCHOOLBOY:
        case TC_SCHOOLGIRL:
        case TC_SCHOOLKID: return MOD_ENCOUNTER_TWINS;
        case TC_TUBER:
        case TC__TUBER:
        case TC_PRESCHOOLER:
        case TC__PRESCHOOLER:
        case TC_FAIRY_TALE_GIRL: return MOD_ENCOUNTER_TUBER;
        case TC_YOUNGSTER:
        case TC_CAMPER:
        case TC_PICNICKER:
        case TC_LASS:
        case TC_SIS_BRO:
        case TC_BUG_CATCHER:
        case TC_YOUNG_COUPLE: return MOD_ENCOUNTER_YOUNGSTER;
        case TC_HIKER:
        case TC_RUIN_MANIAC:
        case TC_TOURIST:
        case TC__TOURIST:
        case TC_BACKPACKER:
        case TC_WORKER: return MOD_ENCOUNTER_HIKER;
        case TC_DELINQUENT:
        case TC_GUITARIST:
        case TC_PUNK_COUPLE:
        case TC_PUNK_GIRL:
        case TC_PUNK_GUY: return MOD_ENCOUNTER_ELECTRIC;
        case TC_SAILOR:
        case TC_RANGERS:
        case TC_MONSIEUR:
        case TC_MADAME:
        case TC_GENTLEMAN:
        case TC_EXPERT:
        case TC__EXPERT:
        case TC_FISHERMAN:
        case TC_BUG_MANIAC:
        case TC_COLLECTOR: return MOD_ENCOUNTER_SAILOR;
        default: return MOD_ENCOUNTER_YOUNGSTER;
        }
    }
    constexpr u16 BGMforTrainerBattle( u16 p_trainerClassId ) {
        switch( p_trainerClassId ) {
        case TC_POKEMON_TRAINER:
        case TC__POKEMON_TRAINER: return MOD_BATTLE_MAY_BRENDAN;
        case TC_LEADER:
        case TC__LEADER:
        case TC_LEADERS: return MOD_BATTLE_GYM_LEADER;
        case TC_MAGMA_LEADER:
        case TC_AQUA_LEADER:
            // return MOD_BATTLE_TEAM_AM_LEADER;
        case TC_AQUA_ADMIN:
        case TC_TEAM_AQUA:
        case TC_MAGMA_ADMIN:
        case TC_TEAM_MAGMA: return MOD_BATTLE_TEAM_AM;
        default: return MOD_BATTLE_TRAINER;
        }
    }
    constexpr u16 BGMforTrainerWin( u16 p_trainerClassId ) {
        switch( p_trainerClassId ) {
        case TC_LEADER:
        case TC__LEADER:
        case TC_LEADERS: return MOD_VICTORY_GYM_LEADER;
        case TC_MAGMA_LEADER:
        case TC_AQUA_LEADER:
        case TC_AQUA_ADMIN:
        case TC_TEAM_AQUA:
        case TC_MAGMA_ADMIN:
        case TC_TEAM_MAGMA: return MOD_VICTORY_TEAM_AM_GRUNT;
        default: return MOD_VICTORY_TRAINER;
        }
    }
    constexpr u16 BGMforWildBattle( u16 p_pokemonId ) {
        switch( p_pokemonId ) {
        case PKMN_RAIKOU:
        case PKMN_SUICUNE:
        case PKMN_ENTEI: return MOD_BATTLE_RAIKOU_ENTEI_SUICUNE;
        case PKMN_REGIROCK:
        case PKMN_REGICE:
        case PKMN_REGISTEEL:
        case PKMN_REGIGIGAS:
        case PKMN_REGIELEKI:
        case PKMN_REGIDRAGO: return MOD_BATTLE_REGI;
        case PKMN_GROUDON:
        case PKMN_KYOGRE:
        case PKMN_RAYQUAZA: return MOD_BATTLE_RAYQUAZA;
        default:
            if( p_pokemonId > PKMN_DEOXYS && p_pokemonId <= PKMN_ARCEUS ) {
                return MOD_BATTLE_EX01;
            }
            return MOD_BATTLE_WILD;
        }
    }

    void setJBoxBGM( u16 p_id );
    u16  getJBoxBGM( );

    /*
     * @brief: Starts/Stops the special poketore music
     */
    void setTracerStatus( bool p_active, bool p_silent = false );

    void onWeatherChange( MAP::mapWeather p_newWeather );
    void onLocationChange( u16 p_newLocatonId );
    void onMovementTypeChange( MAP::moveMode p_newMoveMode );
    void restartBGM( );
    void stopBGM( );
} // namespace SOUND
