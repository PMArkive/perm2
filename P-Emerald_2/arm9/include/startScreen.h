/*
Pok�mon Emerald 2 Version
------------------------------

file        : startScreen.h
author      : Philip Wellnitz
description : Header file. Consult the corresponding source file for details.

Copyright (C) 2012 - 2018
Philip Wellnitz

This file is part of Pok�mon Emerald 2 Version.

Pok�mon Emerald 2 Version is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Pok�mon Emerald 2 Version is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Pok�mon Emerald 2 Version.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <vector>
#include "saveGame.h"

namespace SAVE {
    class startScreen {
      private:
        enum choiceType { CONTINUE, NEW_GAME, SPECIAL_EPISODE, TRANSFER_GAME, ABORT };

        void drawMainChoice( language p_lang, std::vector<u8> p_toDraw, s8 p_selected = -1,
                             s8 p_pressed = -1 );
        void drawSlotChoice( language p_current, s8 p_selected, s8 p_pressed = -1 );

        choiceType runMainChoice( language p_lang );
        s8         runSlotChoice( language p_lang, bool p_newGameMode = false );
        gameType   runEpisodeChoice( language p_current );

        language runLanguageChoice( language p_current );

        bool initNewGame( u8 p_file, gameType p_type, language p_lang );
        bool transferGame( u8 p_file );

      public:
        void run( );
    };
} // namespace SAVE
