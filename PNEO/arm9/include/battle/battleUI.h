/*
Pokémon neo
------------------------------

file        : battleUI.h
author      : Philip Wellnitz
description : Consult corresponding source file.

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

#include <functional>
#include <string>
#include <vector>

#include "battle/battleDefines.h"
#include "io/uio.h"
#include "io/yesNoBox.h"
#include "save/saveGame.h"

namespace BATTLE {
    class battleUI {
        u8             _platform;
        u8             _platform2;
        u8             _background;
        battleMode     _mode;
        bool           _isWildBattle;
        battleTrainer* _battleTrainer = nullptr;

        u8 _currentLogLine = 0;

        u8 _curHP[ 2 ][ 2 ] = { { 0 } };

        weather _currentWeather;
        terrain _currentTerrain;

        void initTop( );
        void initSub( );

        /*
         * @brief: Updates the HP bar for the given pkmn to the specified value.
         * @param p_init: Initialize the hp bar first.
         */
        void updateHPbar( bool p_opponent, u8 p_pos, u8 p_newValue, bool p_init = false );

        /*
         * @brief: Loads a pkmn sprite for the given pkmn at the specified position.
         */
        void loadPkmnSprite( bool p_opponent, u8 p_pos, pokemon* p_pokemon );

        /*
         * @brief: Animates the given ball type opening
         */
        void animateBallRelease( bool p_opponent, u8 p_slot, u8 p_ballId ) const;

        /*
         * @brief: Animates the given ball being thrown at the opponents pkmn in the given
         * slot.
         */
        void animateBallThrow( u8 p_slot, u8 p_ballId ) const;

        /*
         * @brief: Plays the shiny animation for the given pkmn.
         */
        void animateShiny( bool p_opponent, u8 p_slot, u8 p_shinyType = 0 ) const;

        /*
         * @brief: Plays the boosts animation for the given stat change.
         */
        void animateStatChange( bool p_opponent, u8 p_slot, bool p_down ) const;

        /*
         * @brief: Redraws the battle bg picture.
         */
        void redrawBattleBG( );

      public:
        battleUI( ) {
        }

        battleUI( u8 p_platform, u8 p_platform2, u8 p_background, battleMode p_mode,
                  bool p_isWildBattle )
            : _platform( p_platform ), _platform2( p_platform2 ), _background( p_background ),
              _mode( p_mode ), _isWildBattle( p_isWildBattle ) {
        }

        /*
         * @brief: Initializes the battleUI. Destroys anything that was previously on the
         * screen.
         */
        void init( weather p_initialWeather, terrain p_initialTerrain );

        void deinit( );

        /*
         * @brief: Returns a string correctly describing the given pkmn.
         */
        std::string getPkmnName( pokemon* p_pokemon, bool p_opponent,
                                 bool p_sentenceStart = true ) const;

        /*
         * @brief: Plays an animation that the pkmn at the specified slot obtains
         * the specified status condition.
         */
        void animateGetVolatileStatusCondition( pokemon* p_pokemon, bool p_opponent, u8 p_slot,
                                                volatileStatus p_status );

        /*
         * @brief: Plays an animation that the pkmn at the specified slot currently has
         * the specified status condition.
         */
        void animateVolatileStatusCondition( pokemon* p_pokemon, bool p_opponent, u8 p_slot,
                                             volatileStatus p_status );

        /*
         * @brief: Plays an animation that the pkmn at the specified slot obtains
         * the specified status condition.
         */
        void animateStatusCondition( pokemon* p_pokemon, bool p_opponent, u8 p_slot, u8 p_status );

        /*
         * @brief: Plays an animation that the pkmn at the specified slot obtains
         * the specified status condition.
         */
        void animateGetStatusCondition( pokemon* p_pokemon, bool p_opponent, u8 p_slot,
                                        u8 p_status );

        /*
         * @brief: Runs the animation when the given move is prepared and prints
         * corresponding log commands.
         */
        void prepareMove( pokemon* p_pokemon, bool p_opponent, u8 p_slot, battleMove p_move );

        /*
         * @brief: Initializes and shows the log screen.
         */
        void resetLog( );

        /*
         * @brief: prints the given message to the battle log.
         */
        void log( std::string p_message );

        /*
         * @brief: Logs the boosts the given pkmn obtains.
         */
        void logBoosts( pokemon* p_pokemon, bool p_opponent, u8 p_slot, boosts p_intended,
                        boosts p_actual );

        /*
         * @brief: Logs that the given pkmn's item is effective.
         */
        void logItem( pokemon* p_pokemon, bool p_opponent );

        /*
         * @brief: Logs that the given pkmn's ability is effective.
         */
        void logAbility( pokemon* p_pokemon, bool p_opponent );

        /*
         * @brief: Prints that the given pkmn's forewarn ability has identified the
         * specified move.
         */
        void logForewarn( pokemon* p_pokemon, bool p_opponent, u16 p_move );

        /*
         * @brief: Prints that the given pkmn's anticipation ability has identified
         * something.
         */
        void logAnticipation( pokemon* p_pokemon, bool p_opponent );

        /*
         * @brief: Prints that the given pkmn's frisk ability has identified the
         * specified items.
         */
        void logFrisk( pokemon* p_pokemon, bool p_opponent, std::vector<u16> p_itms );

        /*
         * @brief: Animates that the specified pkmn was hit by an attack with the
         * specified effectiveness.
         */
        void animateHitPkmn( bool p_opponent, u8 p_pos, u8 p_effectiveness );

        /*
         * @brief: Update the stats of the pkmn at the given position.
         */
        void updatePkmnStats( bool p_opponent, u8 p_pos, pokemon* p_pokemon, bool p_redraw = true );

        /*
         * @brief: Hides the specified pokemon's stats.
         */
        void hidePkmnStats( bool p_opponent, u8 p_pos );

        /*
         * @brief: Hides the specified pokemon.
         */
        void hidePkmn( bool p_opponent, u8 p_pos );

        /*
         * @brief: Shows the specified pokemon.
         */
        void showPkmn( bool p_opponent, u8 p_pos );

        /*
         * @brief: Updates the pkmn at the specified position (e.g. after a form change)
         */
        void updatePkmn( bool p_opponent, u8 p_pos, pokemon* p_pokemon );

        /*
         * @brief: faints the specified pokemon.
         */
        void faintPkmn( bool p_opponent, u8 p_pos, pokemon* p_pokemon );

        /*
         * @brief: Recalls the given pkmn.
         * @param p_forced: True if the recall was forced by the trainer
         */
        void recallPkmn( bool p_opponent, u8 p_pos, pokemon* p_pokemon, bool p_forced = false );

        /*
         * @brief: Sends out the given pkmn at the specified position.
         */
        void sendOutPkmn( bool p_opponent, u8 p_pos, pokemon* p_pokemon );

        /*
         * @brief: shows the wild pkmn appear
         */
        void startWildBattle( pokemon* p_pokemon );

        /*
         * @brief: plays the intro for the given trainer
         */
        void startTrainerBattle( battleTrainer* p_trainer );

        /*
         * @brief: Shows the move selection for the given pkmn ("attack", "item", "pkmn",
         * "run", etc)
         */
        std::vector<std::pair<IO::inputTarget, u8>>
        showMoveSelection( pokemon* p_pokemon, u8 p_slot, u8 p_highlightedButton = -1 );

        /*
         * @brief: Shows the attack selection for the given pkmn.
         */
        std::vector<std::pair<IO::inputTarget, u8>>
        showAttackSelection( boxPokemon* p_pokemon, bool p_canUseMove[ 4 ],
                             bool p_showMegaEvolution, u8 p_highlightedButton = -1,
                             bool p_megaButtonActive = false );
        inline std::vector<std::pair<IO::inputTarget, u8>>
        showAttackSelection( pokemon* p_pokemon, bool p_canUseMove[ 4 ], bool p_showMegaEvolution,
                             u8 p_highlightedButton = -1, bool p_megaButtonActive = false ) {
            return showAttackSelection( &p_pokemon->m_boxdata, p_canUseMove, p_showMegaEvolution,
                                        p_highlightedButton, p_megaButtonActive );
        }

        /*
         * @brief: Shows the target selection for the specified choices.
         */
        std::vector<std::pair<IO::inputTarget, u8>>
        showTargetSelection( u8 p_choices, bool p_hasChoices,
                             std::function<pokemon*( bool, u8 )> p_getPkmn,
                             u8                                  p_highlightedButton = -1 );

        /*
         * @brief: Animates an attempt at capturing the wild pkmn with the given ball and
         * the specified amount of ticks.
         */
        void animateCapturePkmn( u16 p_pokeball, u8 p_ticks );

        /*
         * @brief: Displays the pkmn capture screen.
         */
        void handleCapture( pokemon* p_pokemon );

        /*
         * @brief: Displays the trainer's win/loos message after the battle.
         */
        void handleBattleEnd( bool p_playerWon );

        /*
         * @brief: Shows choice boxes for a yesNoBox.
         */
        std::vector<std::pair<IO::inputTarget, IO::yesNoBox::selection>>
        printYNMessage( u8 p_selection );

        /*
         * @brief: Shows the specified pkmn centered on the top screen, destroys
         * any sprites that were previously on the top screen.
         */
        void showTopMessagePkmn( pokemon* p_pokemon );

        /*
         * @brief: Prints a message to a mbox on the top screen. To be used only when no
         * battlers are on the screen.
         */
        void printTopMessage( const char* p_message, bool p_init );

        /*
         * @brief: Hides the mbox on the top screen.
         */
        void hideTopMessage( );

        /*
         * @brief: Sets the current weather to the specified weather.
         */
        void setNewWeather( weather p_newWeather );

        /*
         * @brief: Continues the current weather (e.g. between turns)
         */
        void continueWeather( );

        /*
         * @brief: adds the specified pseudo weather to the current pseudo weather.
         */
        void addPseudoWeather( u8 p_newPseudoWeatherIdx );

        /*
         * @brief: Removes the specified pseudo weather.
         */
        void removePseudoWeather( u8 p_pseudoWeatherIdx );

        /*
         * @brief: Sets the current terrain to the specified value.
         */
        void setNewTerrain( terrain p_newTerrain );
    };
} // namespace BATTLE
