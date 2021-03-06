/*
Pok�mon Emerald 2 Version
------------------------------

file        : mapSprite.cpp
author      : Philip Wellnitz
description : Map Sprites.

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

#include "mapSprite.h"
#include "fs.h"
#include "sprite.h"
#include "uio.h"

#include "messageBox.h"

namespace MAP {
    const char* OW_PATH = "nitro:/PICS/SPRITES/OW/";

    mapSprite::mapSprite( u16 p_currX, u16 p_currY, u16 p_imageId, u8 p_startFrame, u8 p_oamIdx,
                          u8 p_palIdx, u16 p_tileIdx )
        : _oamIndex( p_oamIdx ), _palette( p_palIdx ), _tileIdx( p_tileIdx ), _picNum( p_imageId ),
          _curFrame( p_startFrame ) {
        if( !IO::loadOWSprite( OW_PATH, _picNum, p_currX, p_currY, _oamIndex, _palette,
                               _tileIdx ) ) {
            IO::messageBox m( "Sprite failed" );
            IO::NAV->draw( true );
        }
        IO::setOWSpriteFrame( _curFrame, _oamIndex, _tileIdx );
        IO::updateOAM( false );
    }

    ObjPriority mapSprite::getPriority( ) {
        return IO::OamTop->oamBuffer[ _oamIndex ].priority;
    }

    void mapSprite::setVisibility( bool p_value ) {
        IO::OamTop->oamBuffer[ _oamIndex ].isHidden = !p_value;
        IO::updateOAM( false );
    }
    void mapSprite::setPriority( ObjPriority p_value ) {
        IO::OamTop->oamBuffer[ _oamIndex ].priority = p_value;
        IO::updateOAM( false );
    }
    void mapSprite::drawFrame( u8 p_value ) {
        IO::setOWSpriteFrame( p_value, _oamIndex, _tileIdx );
        IO::updateOAM( false );
    }
    void mapSprite::drawFrame( u8 p_value, bool p_hFlip ) {
        IO::setOWSpriteFrame( p_value, p_hFlip, _oamIndex, _tileIdx );
        IO::updateOAM( false );
    }

    void mapSprite::setFrame( u8 p_value ) {
        _curFrame = p_value;
        drawFrame( _curFrame );
    }

    void mapSprite::currentFrame( ) {
        drawFrame( _curFrame );
    }
    void mapSprite::nextFrame( ) {
        _curFrame++;
        if( ( _curFrame % 20 ) % 3 == 0 ) _curFrame -= 2;
        drawFrame( _curFrame );
    }

    void mapSprite::move( direction p_direction, s16 p_amount ) {
        IO::OamTop->oamBuffer[ _oamIndex ].x += p_amount * dir[ p_direction ][ 0 ];
        IO::OamTop->oamBuffer[ _oamIndex ].y += p_amount * dir[ p_direction ][ 1 ];
        IO::updateOAM( false );
    }
} // namespace MAP
