/*
Pok�mon Emerald 2 Version
------------------------------

file        : screenFade.cpp
author      : Philip Wellnitz
description :

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

#include <nds/arm9/background.h>
#include <nds/arm9/sprite.h>
#include <nds/bios.h>

#include "defines.h"
#include "fs.h"
#include "screenFade.h"
#include "uio.h"

namespace IO {
    void fadeScreen( fadeType p_type ) {
        switch( p_type ) {
        case IO::UNFADE: {
            u16 val = 0x1F;
            for( s8 i = 4; i >= 0; --i ) {
                for( u8 j = 0; j < 5; ++j ) swiWaitForVBlank( );
                val &= ~( 1 << u8( i ) );
                REG_BLDY = val;
            }
            swiWaitForVBlank( );
            break;
        }
        case IO::UNFADE_FAST: {
            u16 val = 0x1F;
            for( s8 i = 3; i >= 0; i -= 2 ) {
                swiWaitForVBlank( );
                val &= ~( 3 << u8( i ) );
                REG_BLDY = val;
            }
            swiWaitForVBlank( );
            break;
        }
        case IO::CLEAR_DARK_FAST:
            REG_BLDCNT = BLEND_FADE_BLACK | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3
                         | BLEND_SRC_SPRITE;
            REG_BLDY = 1;
            for( u8 i = 1; i < 5; i += 2 ) {
                swiWaitForVBlank( );
                REG_BLDY |= ( 3 << i );
            }
            swiWaitForVBlank( );
            break;
        case IO::CLEAR_DARK:
        case IO::CAVE_ENTRY:
            REG_BLDCNT = BLEND_FADE_BLACK | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3
                         | BLEND_SRC_SPRITE;
            REG_BLDY = 1;
            for( u8 i = 1; i < 5; ++i ) {
                for( u8 j = 0; j < 4; ++j ) swiWaitForVBlank( );
                REG_BLDY |= ( 1 << i );
            }
            swiWaitForVBlank( );
            if( p_type == CLEAR_DARK ) break;
            break;
        case IO::CLEAR_WHITE_FAST:
            REG_BLDCNT = BLEND_FADE_WHITE | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3
                         | BLEND_SRC_SPRITE;
            REG_BLDY = 1;
            for( u8 i = 1; i < 5; i += 2 ) {
                for( u8 j = 0; j < 4; ++j ) swiWaitForVBlank( );
                REG_BLDY |= ( 3 << i );
            }
            swiWaitForVBlank( );
            break;
        case IO::CLEAR_WHITE:
        case IO::CAVE_EXIT:
            REG_BLDCNT = BLEND_FADE_WHITE | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3
                         | BLEND_SRC_SPRITE;
            REG_BLDY = 1;
            for( u8 i = 1; i < 5; ++i ) {
                for( u8 j = 0; j < 4; ++j ) swiWaitForVBlank( );
                REG_BLDY |= ( 1 << i );
            }
            swiWaitForVBlank( );
            if( p_type == CLEAR_WHITE ) break;
            break;
        case IO::BATTLE:
        case IO::BATTLE_STRONG_OPPONENT:
            REG_BLDCNT = BLEND_FADE_BLACK | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3;
            for( u8 j = 0; j < p_type - IO::BATTLE + 1; ++j ) {
                u16 val = 0x1F;
                for( s8 i = 4; i >= 0; --i ) {
                    for( u8 k = 0; k < 2 + j; ++k ) swiWaitForVBlank( );
                    val &= ~( 1 << u8( i ) );
                    REG_BLDY = val;
                }
                for( u8 i = 1; i < 3; ++i ) swiWaitForVBlank( );
                REG_BLDY = 1;
                for( u8 i = 1; i < 5; ++i ) {
                    for( u8 k = 0; k < 2 + j; ++k ) swiWaitForVBlank( );
                    REG_BLDY |= ( 1 << i );
                }
                for( u8 i = 1; i < 3; ++i ) swiWaitForVBlank( );
            }
            REG_BLDCNT = BLEND_FADE_BLACK | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3
                         | BLEND_SRC_SPRITE;
            for( u8 i = 1; i < 5; ++i ) {
                for( u8 j = 0; j < 4; ++j ) swiWaitForVBlank( );
                REG_BLDY |= ( 1 << i );
            }
            swiWaitForVBlank( );
            break;
        default:
            break;
        }
    }

    void clearScreen( bool p_bottom, bool p_both, bool p_dark ) {
        const char* file = p_dark ? "ClearD" : "Clear";
        if( p_both || p_bottom ) {
            FS::readPictureData( bgGetGfxPtr( bg3sub ), "nitro:/PICS/", file, 512, 49152, true );
            FS::readPictureData( bgGetGfxPtr( bg2sub ), "nitro:/PICS/", file, 512, 49152, true );
        }
        if( p_both || !p_bottom ) {
            FS::readPictureData( bgGetGfxPtr( bg3 ), "nitro:/PICS/", file );
            FS::readPictureData( bgGetGfxPtr( bg2 ), "nitro:/PICS/", file );
        }
        regularFont->setColor( RGB( 0, 31, 31 ), 0 );
    }
    void clearScreenConsole( bool p_bottom, bool p_both ) {
        if( p_both || !p_bottom ) {
            consoleSelect( &Top );
            consoleSetWindow( &Top, 0, 0, 32, 24 );
            consoleClear( );
        }
        if( p_both || p_bottom ) {
            consoleSelect( &Bottom );
            consoleSetWindow( &Bottom, 0, 0, 32, 24 );
            consoleClear( );
        }
    }
} // namespace IO
