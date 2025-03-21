/*
Pok�mon Emerald 2 Version
------------------------------

file        : uio.h
author      : Philip Wellnitz
description : Consult corresponding source file.

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
#include <string>
#include <nds.h>

#include "font.h"
#include "nav.h"
#include "sprite.h"

namespace IO {

    const u8 SCREEN_TOP    = 1;
    const u8 SCREEN_BOTTOM = 0;
    const u8 FONT_WIDTH    = 16;
    const u8 FONT_HEIGHT   = 16;

    extern font*        regularFont;
    extern font*        boldFont;
    extern ConsoleFont* consoleFont;

    extern u8 ASpriteOamIndex;

    extern OAMTable*  Oam;
    extern SpriteInfo spriteInfo[ SPRITE_COUNT ];

    extern OAMTable*  OamTop;
    extern SpriteInfo spriteInfoTop[ SPRITE_COUNT ];

    extern u8 TEXTSPEED;

    extern int          bg2;
    extern int          bg3;
    extern int          bg2sub;
    extern int          bg3sub;
    extern PrintConsole Bottom;
    extern PrintConsole Top;

    void initVideo( );
    void initVideoSub( );
    void vramSetup( );

    void swapScreens( );

    void setDefaultConsoleTextColors( u16* p_palette, u8 p_start = 1 );

    struct inputTarget {
        enum inputType { BUTTON, TOUCH, TOUCH_CIRCLE };
        inputType   m_inputType;
        KEYPAD_BITS m_keys;
        u16         m_targetX1 = 0;
        u16         m_targetY1 = 0;
        u16         m_targetX2 = 300;
        u16         m_targetY2 = 300;
        u16         m_targetR  = 16;

        inputTarget( KEYPAD_BITS p_keys ) : m_inputType( BUTTON ), m_keys( p_keys ) {
        }
        inputTarget( u16 p_targetX1, u16 p_targetY1, u16 p_targetX2, u16 p_targetY2 )
            : m_inputType( TOUCH ), m_targetX1( p_targetX1 ), m_targetY1( p_targetY1 ),
              m_targetX2( p_targetX2 ), m_targetY2( p_targetY2 ) {
        }
        inputTarget( u16 p_targetX1, u16 p_targetY1, u16 p_targetR )
            : m_inputType( TOUCH_CIRCLE ), m_targetX1( p_targetX1 ), m_targetY1( p_targetY1 ),
              m_targetR( p_targetR ) {
        }
    };

    bool waitForTouchUp( u16 p_targetX1 = 0, u16 p_targetY1 = 0, u16 p_targetX2 = 300,
                         u16 p_targetY2 = 300 );
    bool waitForTouchUp( inputTarget p_inputTarget );

    bool waitForKeysUp( KEYPAD_BITS p_keys );
    bool waitForKeysUp( inputTarget p_inputTarget );

    bool waitForInput( inputTarget p_inputTarget );

    void initTextField( );

    void printRectangle( u8 p_x1, u8 p_y1, u8 p_x2, u8 p_y2, bool p_bottom = true,
                         bool p_striped = false, u8 p_color = 42 );

    void displayHP( u16 p_HPstart, u16 p_HP, u8 p_x, u8 p_y, u8 p_freecolor1, u8 p_freecolor2,
                    bool p_delay, bool p_big = false ); // HP in %
    void displayHP( u16 p_HPstart, u16 p_HP, u8 p_x, u8 p_y, u8 p_freecolor1, u8 p_freecolor2,
                    bool p_delay, u8 p_innerR, u8 p_outerR, bool p_sub = false ); // HP in %
    void displayEP( u16 p_EPstart, u16 p_EP, u8 p_x, u8 p_y, u8 p_freecolor1, u8 p_freecolor2,
                    bool p_delay, u8 p_innerR = 14, u8 p_outerR = 15, bool p_sub = false );

    void printChoiceBox( u8 p_x1, u8 p_y1, u8 p_x2, u8 p_y2, u8 p_borderWidth, u8 p_colorIdx,
                         bool p_pressed, bool p_bottom = true );
    void printChoiceBox( u8 p_x1, u8 p_y1, u8 p_x2, u8 p_y2, u8 p_borderWidth, u8 p_borderWidth2,
                         u8 p_colorIdx, bool p_pressed, bool p_bottom = true );

    void topScreenPlot( u8 p_x, u8 p_y, color p_color );
    void btmScreenPlot( u8 p_x, u8 p_y, color p_color );

    u16 getColor( type p_type );
} // namespace IO
