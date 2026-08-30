/*
Pokémon neo
------------------------------

file        : mysteryGift.h
author      : Philip Wellnitz
description : Header file. Consult the corresponding source file for details.

Copyright (C) 2023 - 2023
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

#include "save/startScreen.h"
#include "save/wonderCard.h"

namespace SAVE {

#define SPR_SMALL_CHOICE_OAM_SUB       0
#define SPR_LARGE_CHOICE_OAM_SUB       1
#define SPR_ARROW_LEFT_OAM_SUB         5
#define SPR_ARROW_RIGHT_OAM_SUB        6
#define SPR_PAGE_LEFT_OAM_SUB          7
#define SPR_PAGE_RIGHT_OAM_SUB         8
#define SPR_CHOICE_OAM_SUB( p_choice ) ( 30 + 10 * ( p_choice ) )
#define SPR_PKMN_OAM_SUB               120

    constexpr u8 SPR_MBOX_PAL_TOP        = 3;
    constexpr u8 SPR_MBOX_OAM_START_TOP  = 8;
    constexpr u8 SPR_MBOX_PAL_TOP2       = 4;
    constexpr u8 SPR_MBOX_OAM_START_TOP2 = 30;
    constexpr u8 SPR_MBOX_OAM_LENGTH     = 13;
    constexpr u8 SPR_CARD_ICON_OAM       = 0;
    constexpr u8 SPR_CARD_ICON_PAL       = 0;

#define SPR_BOX_PAL_SUB      0
#define SPR_SELECTED_PAL_SUB 1
#define SPR_ARROW_X_PAL_SUB  2
#define SPR_PKMN_PAL_SUB     15

    extern wonderCard TMP_WC;

    void clearText( );
    void message( const char* p_message, bool p_init = true );
    void hideSpritesSub( );
    void initTopSprites( bool );
    void initBottomSprites( );

    void selectMainChoice( u8 p_selection );

    std::vector<std::pair<IO::inputTarget, startScreen::choice>>
    drawChoice( u16 p_message, const std::vector<u16>& p_choices, bool p_init = true,
                bool p_left = false, bool p_right = false );

    void runMysteryGift( );
} // namespace SAVE

#ifdef __cplusplus
extern "C" {
#endif

// OV0
extern int ov_0_main( void );

// stored in ov0
extern void displayWonderCard( u8 p_cardIdx, bool p_reverse = false );

// stored in ov1
extern bool checkAndDownloadWCInternet( );

#ifdef __cplusplus
}
#endif
