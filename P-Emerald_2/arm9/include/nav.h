/*
Pok�mon Emerald 2 Version
------------------------------

file        : nav.h
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

#include <string>
#include <nds.h>
#include <nds/ndstypes.h>

namespace IO {
#define MAXBG 13
#define START_BG 0
    extern unsigned int   NAV_DATA[ 12288 ];
    extern unsigned short NAV_DATA_PAL[ 256 ];

    class nav {
      public:
        struct backgroundSet {
            std::string           m_name;
            const unsigned int *  m_mainMenu;
            const unsigned short *m_mainMenuPal;
            bool                  m_loadFromRom;
            bool                  m_allowsOverlay;
        };
        enum state { HOME, MAP, MAP_BIG, MAP_MUG };

      private:
        state _state;
        bool  _allowInit;
        u8    _curBank;
        u16   _curMap;

        void drawMapMug( );
        void drawBorder( );

      public:
        nav( );
        void draw( bool p_initMainSprites = false, u8 p_newIdx = (u8) 255 );
        void showNewMap( u8 p_bank );
        void updateMap( u16 p_map );
        void handleInput( touchPosition p_touch, const char *p_path );
        void home( ) {
            _state = HOME;
        }
    };
    extern nav::backgroundSet BGs[ MAXBG ];
    extern nav *              NAV;
}
