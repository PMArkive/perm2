/*
Pokémon neo
------------------------------

file        : ov.h
author      : Philip Wellnitz
description : Overlay table and wrapper definitions.

Copyright (C) 2026
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
#include <overlay.h>

constexpr u32 OV_MG_ALBUM = 0; // slot 0
constexpr u32 OV_MG_WIFI  = 1; // slot 0

/*
TODO: to be added later
constexpr u32 OV_MG              = 0;  // slot 0/1/2/3

constexpr u32 OV_MG_ALBUM = 1; // slot 0
constexpr u32 OV_MG_WIFI  = 2; // slot 0
constexpr u32 OV_MG_LOCAL        = 3; // slot 4/5/6/7
constexpr u32 OV_MG_RECEIVE_ANIM = 4; // slot 4/5

constexpr u32 OV_BT            = 5;  // slot 0/1/2/3
constexpr u32 OV_BX            = 6;  // slot 0/1/2/3
constexpr u32 OV_ID            = 7; // slot 0/1/2/3
constexpr u32 OV_SETTINGS      = 8; // slot 0/1/2/3
constexpr u32 OV_SPX_BLENDER   = 9; // slot 0/1/2/3
constexpr u32 OV_SPX_GAMESTART = 10; // slot 0/1/2/3
constexpr u32 OV_SPX_EVOLUTION = 11; // slot 0/1/2/3
constexpr u32 OV_SPX_POKESEL   = 12; // slot 0/1/2/3
constexpr u32 OV_SPX_TRADE     = 13; // slot 0/1/2/3

constexpr u32 OV_STS             = 14; // slot 4/5/6/7
constexpr u32 OV_BAG             = 15; // slot 4/5/6/7
constexpr u32 OV_DEX             = 16; // slot 4/5/6/7
*/

namespace OV {
    constexpr u32 OV_MAX = 2;

    struct ovGuard {
        u32  m_id;
        bool m_loaded;

        explicit ovGuard( u32 p_id ) : m_id{ p_id }, m_loaded{ false } {
        }

        ~ovGuard( ) {
            if( m_loaded ) { ovUnload( m_id ); }
        }

        inline int load( ) {
            if( m_loaded ) { return 0; }
            int res  = ovLoad( m_id );
            m_loaded = ( ovLoad( m_id ) == 0 );
            return res;
        }

        inline void unload( ) {
            if( m_loaded ) { ovUnload( m_id ); }
            m_loaded = false;
        }

        ovGuard( const ovGuard& )            = delete;
        ovGuard& operator=( const ovGuard& ) = delete;
    };

    void overlayInit( );
} // namespace OV
