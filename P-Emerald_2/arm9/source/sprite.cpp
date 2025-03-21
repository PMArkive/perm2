/*
Pok�mon Emerald 2 Version
------------------------------

file        : sprite.cpp
author      : Philip Wellnitz
description : Some sprite code.

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

#include <algorithm>
#include <cstdio>
#include <initializer_list>

#include "fs.h"
#include "move.h"
#include "ribbon.h"
#include "sprite.h"
#include "uio.h"

#include "Egg.h"

#include "NoItem.h"
#include "damage_0.h"
#include "damage_1.h"
#include "damage_2.h"

#include "plat0a.h"
#include "plat0b.h"
#include "plat10a.h"
#include "plat10b.h"
#include "plat11a.h"
#include "plat11b.h"
#include "plat1a.h"
#include "plat1b.h"
#include "plat2a.h"
#include "plat2b.h"
#include "plat3a.h"
#include "plat3b.h"
#include "plat4a.h"
#include "plat4b.h"
#include "plat5a.h"
#include "plat5b.h"
#include "plat6a.h"
#include "plat6b.h"
#include "plat7a.h"
#include "plat7b.h"
#include "plat8a.h"
#include "plat8b.h"
#include "plat9a.h"
#include "plat9b.h"

#include "messageBox.h"
unsigned int   TEMP[ 12288 ]   = {0};
unsigned short TEMP_PAL[ 256 ] = {0};

namespace IO {
    const unsigned int* TypeTiles[ 19 ]
        = {NormalTiles, KampfTiles, FlugTiles,  GiftTiles,   BodenTiles, GestTiles, KaeferTiles,
           GeistTiles,  StahlTiles, UnbekTiles, WasserTiles, FeuerTiles, PflTiles,  ElekTiles,
           PsychoTiles, EisTiles,   DraTiles,   UnlTiles,    FeeTiles};
    const unsigned short* TypePals[ 19 ]
        = {NormalPal, KampfPal, FlugPal,  GiftPal,   BodenPal, GestPal, KaeferPal,
           GeistPal,  StahlPal, UnbekPal, WasserPal, FeuerPal, PflPal,  ElekPal,
           PsychoPal, EisPal,   DraPal,   UnlPal,    FeePal};
    const unsigned int* RibbonTiles[ MAX_RIBBONS ]
        = {r0Tiles,  r1Tiles,  r2Tiles,  r3Tiles,  r4Tiles,  r5Tiles,  r6Tiles,  r7Tiles,
           r8Tiles,  r9Tiles,  r10Tiles, r11Tiles, r12Tiles, r13Tiles, r14Tiles, r15Tiles,

           r16Tiles, r17Tiles, r18Tiles, r19Tiles, r20Tiles, r21Tiles, r22Tiles, r23Tiles,
           r24Tiles, r25Tiles, r26Tiles, r27Tiles, r28Tiles, r29Tiles, r30Tiles, r31Tiles,

           r32Tiles, r33Tiles, r34Tiles, r35Tiles, r36Tiles, r37Tiles, r38Tiles, r39Tiles,
           r40Tiles, r41Tiles, r42Tiles, r43Tiles, r44Tiles, r45Tiles, r46Tiles, r47Tiles,

           r48Tiles, r49Tiles, r50Tiles, r51Tiles, r52Tiles, r53Tiles, r54Tiles, r55Tiles,
           r56Tiles, r57Tiles, r58Tiles, r59Tiles, r60Tiles, r61Tiles, r62Tiles, r63Tiles,

           r64Tiles, r65Tiles, r66Tiles, r67Tiles, r68Tiles, r69Tiles, r70Tiles, r71Tiles,
           r72Tiles, r73Tiles, r74Tiles, r75Tiles, r76Tiles, r77Tiles, r78Tiles, r79Tiles,

           r80Tiles, r81Tiles, r82Tiles, r83Tiles, r84Tiles, r85Tiles};
    const unsigned short* RibbonPals[ MAX_RIBBONS ]
        = {r0Pal,  r1Pal,  r2Pal,  r3Pal,  r4Pal,  r5Pal,  r6Pal,  r7Pal,
           r8Pal,  r9Pal,  r10Pal, r11Pal, r12Pal, r13Pal, r14Pal, r15Pal,

           r16Pal, r17Pal, r18Pal, r19Pal, r20Pal, r21Pal, r22Pal, r23Pal,
           r24Pal, r25Pal, r26Pal, r27Pal, r28Pal, r29Pal, r30Pal, r31Pal,

           r32Pal, r33Pal, r34Pal, r35Pal, r36Pal, r37Pal, r38Pal, r39Pal,
           r40Pal, r41Pal, r42Pal, r43Pal, r44Pal, r45Pal, r46Pal, r47Pal,

           r48Pal, r49Pal, r50Pal, r51Pal, r52Pal, r53Pal, r54Pal, r55Pal,
           r56Pal, r57Pal, r58Pal, r59Pal, r60Pal, r61Pal, r62Pal, r63Pal,

           r64Pal, r65Pal, r66Pal, r67Pal, r68Pal, r69Pal, r70Pal, r71Pal,
           r72Pal, r73Pal, r74Pal, r75Pal, r76Pal, r77Pal, r78Pal, r79Pal,

           r80Pal, r81Pal, r82Pal, r83Pal, r84Pal, r85Pal};
    const unsigned int* PlatformTiles[ 2 * MAX_PLATFORMS ]
        = {plat0aTiles, plat0bTiles, plat1aTiles,  plat1bTiles,  plat2aTiles,  plat2bTiles,
           plat3aTiles, plat3bTiles, plat4aTiles,  plat4bTiles,  plat5aTiles,  plat5bTiles,
           plat6aTiles, plat6bTiles, plat7aTiles,  plat7bTiles,  plat8aTiles,  plat8bTiles,
           plat9aTiles, plat9bTiles, plat10aTiles, plat10bTiles, plat11aTiles, plat11bTiles};
    const unsigned short* PlatformPals[ MAX_PLATFORMS ]
        = {plat0aPal, plat1aPal, plat2aPal, plat3aPal, plat4aPal,  plat5aPal,
           plat6aPal, plat7aPal, plat8aPal, plat9aPal, plat10aPal, plat11aPal};

    const unsigned int*   HitTypeTiles[ 3 ] = {damage_0Tiles, damage_1Tiles, damage_2Tiles};
    const unsigned short* HitTypePals[ 3 ]  = {damage_0Pal, damage_1Pal, damage_2Pal};

    const u8  SPRITE_DMA_CHANNEL      = 2;
    const u16 BYTES_PER_16_COLOR_TILE = 32;
    const u16 COLORS_PER_PALETTE      = 16;
    const u16 BOUNDARY_VALUE          = 32;
    const u16 OFFSET_MULTIPLIER       = ( BOUNDARY_VALUE / sizeof( SPRITE_GFX[ 0 ] ) );
    const u16 OFFSET_MULTIPLIER_SUB   = ( BOUNDARY_VALUE / sizeof( SPRITE_GFX_SUB[ 0 ] ) );

    void updateOAM( bool p_bottom ) {
        OAMTable* oam = ( p_bottom ? Oam : OamTop );
        DC_FlushAll( );
        if( p_bottom ) {
            dmaCopyHalfWords( SPRITE_DMA_CHANNEL, oam->oamBuffer, OAM_SUB,
                              SPRITE_COUNT * sizeof( SpriteEntry ) );
        } else {
            dmaCopyHalfWords( SPRITE_DMA_CHANNEL, oam->oamBuffer, OAM,
                              SPRITE_COUNT * sizeof( SpriteEntry ) );
        }
    }
    void initOAMTable( bool p_bottom ) {
        OAMTable* oam = ( p_bottom ? Oam : OamTop );
        /*
         * For all 128 sprites on the DS, disable and clear any attributes they
         * might have. This prevents any garbage from being displayed and gives
         * us a clean slate to work with.
         */
        for( int i = 0; i < SPRITE_COUNT; i++ ) {
            oam->oamBuffer[ i ].attribute[ 0 ] = ATTR0_DISABLED;
            oam->oamBuffer[ i ].attribute[ 1 ] = 0;
            oam->oamBuffer[ i ].attribute[ 2 ] = 0;
            oam->oamBuffer[ i ].isHidden       = true;
        }
        for( int i = 0; i < MATRIX_COUNT; i++ ) {
            /* If you look carefully, you'll see this is that affine trasformation
             * matrix again. We initialize it to the identity matrix, as we did
             * with backgrounds
             */
            oam->matrixBuffer[ i ].hdx = 1 << 8;
            oam->matrixBuffer[ i ].hdy = 0;
            oam->matrixBuffer[ i ].vdx = 0;
            oam->matrixBuffer[ i ].vdy = 1 << 8;
        }

        if( p_bottom )
            memset( SPRITE_GFX_SUB, 0, 1024 );
        else
            memset( SPRITE_GFX, 0, 1024 );
        updateOAM( p_bottom );
    }
    void rotateSprite( SpriteRotation* p_spriteRotation, int p_angle ) {
        s16 s = sinLerp( p_angle ) >> 4;
        s16 c = cosLerp( p_angle ) >> 4;

        p_spriteRotation->hdx = c;
        p_spriteRotation->hdy = s;
        p_spriteRotation->vdx = -s;
        p_spriteRotation->vdy = c;
    }
    void setSpriteVisibility( SpriteEntry* p_spriteEntry, bool p_hidden, bool p_affine,
                              bool p_doubleBound ) {
        if( p_hidden ) {
            /*
             * Make the sprite invisible.
             *
             * An affine sprite cannot be hidden. We have to turn it into a
             * non-affine sprite before we can hide it. To hide any sprite, we must
             * set bit 8 and clear bit 9. For non-affine sprites, this is a bit
             * redundant, but it is faster than a branch to just set it regardless
             * of whether or not it is already set.
             */
            p_spriteEntry->isRotateScale = false; // Bit 9 off
            p_spriteEntry->isHidden      = true;  // Bit 8 on
        } else {
            /* Make the sprite visible.*/
            if( p_affine ) {
                /* Again, keep in mind that affine sprites cannot be hidden, so
                 * enabling affine is enough to show the sprite again. We also need
                 * to allow the user to get the double bound flag in the sprite
                 * attribute. If we did not, then our sprite hiding function would
                 * not be able to properly hide and restore double bound sprites.
                 * We enable bit 9 here because we want an affine sprite.
                 */
                p_spriteEntry->isRotateScale = true;

                /* The double bound flag only acts as the double bound flag when
                 * the sprite is an affine sprite. At all other times, it acts as
                 * the sprite invisibility flag. We only enable bit 8 here if we want
                 * a double bound sprite. */
                p_spriteEntry->isSizeDouble = p_doubleBound;
            } else {
                /* Bit 9 (the affine flag) will already be off here, so we don't
                 * need to clear it. However, bit 8 (the sprite invisibility flag)
                 * will need to be cleared. */
                p_spriteEntry->isHidden = false;
            }
        }
    }
    inline void setSpritePosition( SpriteEntry* p_spriteEntry, u16 p_x, u16 p_y ) {
        p_spriteEntry->x = p_x;
        p_spriteEntry->y = p_y;
    }
    inline void setSpritePriority( SpriteEntry* p_spriteEntry, ObjPriority p_priority ) {
        p_spriteEntry->priority = p_priority;
    }

    void copySpritePal( const unsigned short* p_spritePal, const u8 p_palIdx, bool p_bottom ) {
        copySpritePal( p_spritePal, p_palIdx, 32, p_bottom );
    }
    void copySpritePal( const unsigned short* p_spritePal, const u8 p_palIdx, const u16 p_palLen,
                        bool p_bottom ) {
        if( !p_bottom && p_spritePal )
            dmaCopyHalfWords( SPRITE_DMA_CHANNEL, p_spritePal,
                              &SPRITE_PALETTE[ p_palIdx * COLORS_PER_PALETTE ], p_palLen );
        else if( p_spritePal )
            dmaCopyHalfWords( SPRITE_DMA_CHANNEL, p_spritePal,
                              &SPRITE_PALETTE_SUB[ p_palIdx * COLORS_PER_PALETTE ], p_palLen );
    }
    void copySpriteData( const unsigned int* p_spriteData, const u16 p_tileIdx,
                         const u32 p_spriteDataLen, bool p_bottom ) {
        if( !p_bottom && p_spriteData )
            dmaCopyHalfWords( SPRITE_DMA_CHANNEL, p_spriteData,
                              &SPRITE_GFX[ (u32) p_tileIdx * OFFSET_MULTIPLIER ], p_spriteDataLen );
        else if( p_spriteData )
            dmaCopyHalfWords( SPRITE_DMA_CHANNEL, p_spriteData,
                              &SPRITE_GFX_SUB[ (u32) p_tileIdx * OFFSET_MULTIPLIER_SUB ],
                              p_spriteDataLen );
    }

    u16 loadSprite( const u8 p_oamIdx, const u8 p_palIdx, const u16 p_tileIdx, const u16 p_posX,
                    const u16 p_posY, const u8 p_width, const u8 p_height,
                    const unsigned short* p_spritePal, const unsigned int* p_spriteData,
                    const u32 p_spriteDataLen, bool p_flipX, bool p_flipY, bool p_hidden,
                    ObjPriority p_priority, bool p_bottom ) {
        IO::SpriteInfo* sInfo = ( p_bottom ? spriteInfo : spriteInfoTop ) + p_oamIdx;
        OAMTable*       oam   = ( p_bottom ? Oam : OamTop );

        SpriteEntry* spriteEntry = &oam->oamBuffer[ p_oamIdx ];

        sInfo->m_oamId  = p_oamIdx;
        sInfo->m_width  = p_width;
        sInfo->m_height = p_height;
        sInfo->m_angle  = 0;
        sInfo->m_entry  = spriteEntry;

        spriteEntry->palette  = p_palIdx;
        spriteEntry->gfxIndex = p_tileIdx;
        spriteEntry->x        = p_posX;
        spriteEntry->y        = p_posY;
        spriteEntry->vFlip    = p_flipX;
        spriteEntry->hFlip    = p_flipY;
        spriteEntry->isHidden = p_hidden;
        spriteEntry->priority = p_priority;

        spriteEntry->isRotateScale = false;
        spriteEntry->isMosaic      = false;
        spriteEntry->blendMode     = OBJMODE_NORMAL;
        spriteEntry->colorMode     = OBJCOLOR_16;

        spriteEntry->shape = ( ( p_width == p_height )
                                   ? OBJSHAPE_SQUARE
                                   : ( ( p_width > p_height ) ? OBJSHAPE_WIDE : OBJSHAPE_TALL ) );

        u8 maxSize = std::max( p_width, p_height );
        spriteEntry->size
            = ( ( maxSize == 64 )
                    ? OBJSIZE_64
                    : ( ( maxSize == 32 ) ? OBJSIZE_32
                                          : ( ( maxSize == 16 ) ? OBJSIZE_16 : OBJSIZE_8 ) ) );

        copySpriteData( p_spriteData, p_tileIdx, p_spriteDataLen, p_bottom );
        copySpritePal( p_spritePal, p_palIdx, p_bottom );
        return p_tileIdx + ( p_spriteDataLen / BYTES_PER_16_COLOR_TILE );
    }

    u16 loadSprite( const u8 p_oamIdx, const u8 p_palIdx, const u8 p_palpos, const u16 p_tileIdx,
                    const u16 p_posX, const u16 p_posY, const u8 p_width, const u8 p_height,
                    const unsigned short* p_spritePal, const unsigned int* p_spriteData,
                    const u32 p_spriteDataLen, bool p_flipX, bool p_flipY, bool p_hidden,
                    ObjPriority p_priority, bool p_bottom ) {
        IO::SpriteInfo* sInfo = ( p_bottom ? spriteInfo : spriteInfoTop ) + p_oamIdx;
        OAMTable*       oam   = ( p_bottom ? Oam : OamTop );

        SpriteEntry* spriteEntry = &oam->oamBuffer[ p_oamIdx ];

        sInfo->m_oamId  = p_oamIdx;
        sInfo->m_width  = p_width;
        sInfo->m_height = p_height;
        sInfo->m_angle  = 0;
        sInfo->m_entry  = spriteEntry;

        spriteEntry->palette  = p_palIdx;
        spriteEntry->gfxIndex = p_tileIdx;
        spriteEntry->x        = p_posX;
        spriteEntry->y        = p_posY;
        spriteEntry->vFlip    = p_flipX;
        spriteEntry->hFlip    = p_flipY;
        spriteEntry->isHidden = p_hidden;
        spriteEntry->priority = p_priority;

        spriteEntry->isRotateScale = false;
        spriteEntry->isMosaic      = false;
        spriteEntry->blendMode     = OBJMODE_NORMAL;
        spriteEntry->colorMode     = OBJCOLOR_256;

        spriteEntry->shape = ( ( p_width == p_height )
                                   ? OBJSHAPE_SQUARE
                                   : ( ( p_width > p_height ) ? OBJSHAPE_WIDE : OBJSHAPE_TALL ) );

        u8 maxSize = std::max( p_width, p_height );
        spriteEntry->size
            = ( ( maxSize == 64 )
                    ? OBJSIZE_64
                    : ( ( maxSize == 32 ) ? OBJSIZE_32
                                          : ( ( maxSize == 16 ) ? OBJSIZE_16 : OBJSIZE_8 ) ) );

        // Attention! The following code is not meant to be read.

        const u8* nspD = reinterpret_cast<const u8*>( p_spriteData );

        if( !p_bottom ) {
            vramSetBankF( VRAM_F_LCD );
            if( p_spritePal )
                for( u8 i = 0; i < 16; ++i )
                    VRAM_F_EXT_SPR_PALETTE[ p_palIdx ][ 16 * p_palpos + i ] = p_spritePal[ i ];
            vramSetBankF( VRAM_F_SPRITE_EXT_PALETTE );
            if( p_spriteData )
                for( u32 i = 0; i < p_spriteDataLen; ++i ) {
                    u8 ac                                                 = nspD[ i ];
                    SPRITE_GFX[ (u32) p_tileIdx * OFFSET_MULTIPLIER + i ] = 0;
                    if( ac >> 4 )
                        SPRITE_GFX[ (u32) p_tileIdx * OFFSET_MULTIPLIER + i ]
                            |= ( 16 * p_palpos + ( ac >> 4 ) ) << 8;
                    if( ac % ( 1 << 4 ) )
                        SPRITE_GFX[ (u32) p_tileIdx * OFFSET_MULTIPLIER + i ]
                            |= ( 16 * p_palpos + ( ac % ( 1 << 4 ) ) );
                }
        } else {
            vramSetBankI( VRAM_I_LCD );
            if( p_spritePal )
                for( u8 i = 0; i < 16; ++i )
                    VRAM_I_EXT_SPR_PALETTE[ p_palIdx ][ 16 * p_palpos + i ] = p_spritePal[ i ];
            vramSetBankI( VRAM_I_SUB_SPRITE_EXT_PALETTE );

            if( p_spriteData )
                for( u32 i = 0; i < p_spriteDataLen; ++i ) {
                    u8 ac                                                     = nspD[ i ];
                    SPRITE_GFX_SUB[ (u32) p_tileIdx * OFFSET_MULTIPLIER + i ] = 0;
                    if( ac >> 4 )
                        SPRITE_GFX_SUB[ (u32) p_tileIdx * OFFSET_MULTIPLIER + i ]
                            |= ( 16 * p_palpos + ( ac >> 4 ) ) << 8;
                    if( ac % ( 1 << 4 ) )
                        SPRITE_GFX_SUB[ (u32) p_tileIdx * OFFSET_MULTIPLIER + i ]
                            |= ( 16 * p_palpos + ( ac % ( 1 << 4 ) ) );
                }
        }

        return p_tileIdx + 2 * ( p_spriteDataLen / BYTES_PER_16_COLOR_TILE );
    }

    u16 loadPKMNSprite( const char* p_path, const u16 p_pkmnId, const s16 p_posX, const s16 p_posY,
                        u8 p_oamIndex, u8 p_palCnt, u16 p_tileCnt, bool p_bottom, bool p_shiny,
                        bool p_female, bool p_flipx, bool p_topOnly, u8 p_forme ) {
        char* buffer = new char[ 100 ];
        if( !p_forme ) {
            if( !p_female )
                snprintf( buffer, 99, "%d/%d", p_pkmnId, p_pkmnId );
            else
                snprintf( buffer, 99, "%d/%df", p_pkmnId, p_pkmnId );
        } else {
            if( !p_female )
                snprintf( buffer, 99, "%d/%d-%hhu", p_pkmnId, p_pkmnId, p_forme );
            else
                snprintf( buffer, 99, "%d/%d-%hhuf", p_pkmnId, p_pkmnId, p_forme );
        }

        memset( TEMP_PAL, 0, sizeof( TEMP_PAL ) );
        memset( TEMP, 0, sizeof( TEMP ) );

        if( !FS::readData<unsigned short, unsigned int>( p_path, buffer, 16, TEMP_PAL, 96 * 96 / 8,
                                                         TEMP ) ) {
            delete[] buffer;
            return false;
        }

        if( p_shiny ) {
            if( !p_forme ) {
                if( !p_female )
                    snprintf( buffer, 99, "%d/%ds", p_pkmnId, p_pkmnId );
                else
                    snprintf( buffer, 99, "%d/%dsf", p_pkmnId, p_pkmnId );
            } else {
                if( !p_female )
                    snprintf( buffer, 99, "%d/%d-%hhus", p_pkmnId, p_pkmnId, p_forme );
                else
                    snprintf( buffer, 99, "%d/%d-%hhusf", p_pkmnId, p_pkmnId, p_forme );
            }
            FS::readData<unsigned short, unsigned int>( p_path, buffer, 16, TEMP_PAL, 96 * 96 / 8,
                                                        TEMP );
        }

        loadSprite( p_oamIndex++, p_palCnt, p_tileCnt, p_flipx ? 32 + p_posX : p_posX, p_posY, 64,
                    64, TEMP_PAL, TEMP, 96 * 96 / 2, false, p_flipx, false, OBJPRIORITY_1,
                    p_bottom );
        loadSprite( p_oamIndex++, p_palCnt, p_tileCnt + 64, p_flipx ? p_posX : 64 + p_posX, p_posY,
                    32, 64, 0, 0, 0, false, p_flipx, false, OBJPRIORITY_1, p_bottom );
        if( !p_topOnly ) {
            loadSprite( p_oamIndex++, p_palCnt, p_tileCnt + 96, p_flipx ? 32 + p_posX : p_posX,
                        p_posY + 64, 64, 32, 0, 0, 0, false, p_flipx, false, OBJPRIORITY_1,
                        p_bottom );
            loadSprite( p_oamIndex, p_palCnt, p_tileCnt + 128, p_flipx ? p_posX : 64 + p_posX,
                        p_posY + 64, 32, 32, 0, 0, 0, false, p_flipx, false, OBJPRIORITY_1,
                        p_bottom );
        }
        updateOAM( p_bottom );
        delete[] buffer;
        return p_tileCnt + 144;
    }
    u16 loadEggSprite( const u16 p_posX, const u16 p_posY, u8 p_oamIndex, u8 p_palCnt,
                       u16 p_tileCnt, bool p_bottom ) {
        return loadSprite( p_oamIndex, p_palCnt, p_tileCnt, p_posX, p_posY, 64, 64, EggPal,
                           EggTiles, EggTilesLen, false, false, false, OBJPRIORITY_1, p_bottom );
    }

    u16 loadTrainerSprite( const char* p_path, const char* p_name, const s16 p_posX,
                           const s16 p_posY, u8 p_oamIndex, u8 p_palCnt, u16 p_tileCnt,
                           bool p_bottom, bool p_flipx, bool p_topOnly ) {
        char* buffer = new char[ 100 ];
        snprintf( buffer, 99, "Sprite_%s", p_name );

        memset( TEMP_PAL, 0, sizeof( TEMP_PAL ) );
        memset( TEMP, 0, sizeof( TEMP ) );

        if( !FS::readData<unsigned short, unsigned int>( p_path, buffer, 16, TEMP_PAL, 96 * 96 / 8,
                                                         TEMP ) ) {
            delete[] buffer;
            return false;
        }

        loadSprite( p_oamIndex++, p_palCnt, p_tileCnt, p_flipx ? 32 + p_posX : p_posX, p_posY, 64,
                    64, TEMP_PAL, TEMP, 96 * 96 / 2, false, p_flipx, false, OBJPRIORITY_0,
                    p_bottom );
        loadSprite( p_oamIndex++, p_palCnt, p_tileCnt + 64, p_flipx ? p_posX : 64 + p_posX, p_posY,
                    32, 64, 0, 0, 0, false, p_flipx, false, OBJPRIORITY_0, p_bottom );
        if( !p_topOnly ) {
            loadSprite( p_oamIndex++, p_palCnt, p_tileCnt + 96, p_flipx ? 32 + p_posX : p_posX,
                        p_posY + 64, 64, 32, 0, 0, 0, false, p_flipx, false, OBJPRIORITY_0,
                        p_bottom );
            loadSprite( p_oamIndex++, p_palCnt, p_tileCnt + 128, p_flipx ? p_posX : 64 + p_posX,
                        p_posY + 64, 32, 32, 0, 0, 0, false, p_flipx, false, OBJPRIORITY_0,
                        p_bottom );
        }
        updateOAM( p_bottom );
        delete[] buffer;
        return p_tileCnt + 144;
    }

    u16 loadOWSprite( const char* p_path, const u16 p_picnum, const s16 p_posX, const s16 p_posY,
                      u8 p_oamIndex, u8 p_palCnt, u16 p_tileCnt ) {

        FILE* f = FS::open( p_path, p_picnum, ".rsd" );
        FS::read( f, TEMP_PAL, sizeof( unsigned short ), 16 );
        u8 frameCount, width, height;
        FS::read( f, &frameCount, sizeof( u8 ), 1 );
        FS::read( f, &width, sizeof( u8 ), 1 );
        FS::read( f, &height, sizeof( u8 ), 1 );
        FS::read( f, TEMP, sizeof( unsigned int ), width * height * frameCount / 8 );
        FS::close( f );

        return loadSprite( p_oamIndex, p_palCnt, p_tileCnt, p_posX, p_posY, width, height, TEMP_PAL,
                           TEMP, width * height * frameCount / 2, false, false, false,
                           OBJPRIORITY_2, false );
    }
    void setOWSpriteFrame( u8 p_frame, u8 p_oamIndex, u16 p_tileCnt ) {
        u8 frame = p_frame;
        if( frame % 20 >= 9 ) frame -= 3;
        if( p_frame % 20 == 15 ) frame--;
        u8 memPos = frame / 20 * 9 + frame % 20;

        setOWSpriteFrame( memPos,
                          ( frame != p_frame ) && ( p_frame % 20 < 12 || p_frame % 20 == 15 ),
                          p_oamIndex, p_tileCnt );
    }
    void setOWSpriteFrame( u8 p_memPos, bool p_hFlip, u8 p_oamIndex, u16 p_tileCnt ) {
        u8 width  = spriteInfoTop[ p_oamIndex ].m_width,
           height = spriteInfoTop[ p_oamIndex ].m_height;

        OamTop->oamBuffer[ p_oamIndex ].hFlip    = p_hFlip;
        OamTop->oamBuffer[ p_oamIndex ].gfxIndex = p_tileCnt + p_memPos * width * height / 64;
    }

    u16 loadIcon( const char* p_path, const char* p_name, const s16 p_posX, const s16 p_posY,
                  u8 p_oamIndex, u8 p_palCnt, u16 p_tileCnt, bool p_bottom ) {
        if( FS::readData( p_path, p_name, (unsigned int) 128, TEMP, (unsigned short) 16,
                          TEMP_PAL ) ) {
            return loadSprite( p_oamIndex, p_palCnt, p_tileCnt, p_posX, p_posY, 32, 32, TEMP_PAL,
                               TEMP, 512, false, false, false,
                               p_bottom ? OBJPRIORITY_1 : OBJPRIORITY_0, p_bottom );
        } else {
            return loadSprite( p_oamIndex, p_palCnt, p_tileCnt, p_posX, p_posY, 32, 32, NoItemPal,
                               NoItemTiles, NoItemTilesLen, false, false, false,
                               p_bottom ? OBJPRIORITY_1 : OBJPRIORITY_0, p_bottom );
        }
    }
    u16 loadIcon( const char* p_path, const char* p_name, const s16 p_posX, const s16 p_posY,
                  u8 p_oamIndex, u8 p_palCnt, u8 p_palpos, u16 p_tileCnt, bool p_bottom ) {
        if( FS::readData( p_path, p_name, (unsigned int) 128, TEMP, (unsigned short) 16,
                          TEMP_PAL ) ) {
            return loadSprite( p_oamIndex, p_palCnt, p_palpos, p_tileCnt, p_posX, p_posY, 32, 32,
                               TEMP_PAL, TEMP, 512, false, false, false,
                               p_bottom ? OBJPRIORITY_1 : OBJPRIORITY_0, p_bottom );
        } else {
            return loadSprite( p_oamIndex, p_palCnt, p_palpos, p_tileCnt, p_posX, p_posY, 32, 32,
                               NoItemPal, NoItemTiles, NoItemTilesLen, false, false, false,
                               p_bottom ? OBJPRIORITY_1 : OBJPRIORITY_0, p_bottom );
        }
    }

    u16 loadPKMNIcon( const u16 p_pkmnId, const u16 p_posX, const u16 p_posY, u8 p_oamIndex,
                      u8 p_palCnt, u16 p_tileCnt, bool p_bottom, u8 p_forme ) {
        char* buffer = new char[ 100 ];
        if( !p_forme )
            snprintf( buffer, 99, "%hu/Icon_%hu", p_pkmnId, p_pkmnId );
        else
            snprintf( buffer, 99, "%hu/Icon_%hu-%hhu", p_pkmnId, p_pkmnId, p_forme );
        auto res = loadIcon( "nitro:/PICS/SPRITES/PKMN/", buffer, p_posX, p_posY, p_oamIndex,
                             p_palCnt, p_tileCnt, p_bottom );
        delete[] buffer;
        return res;
    }

    u16 loadPKMNIcon( const u16 p_pkmnId, const u16 p_posX, const u16 p_posY, u8 p_oamIndex,
                      u8 p_palCnt, u8 p_palpos, u16 p_tileCnt, bool p_bottom, u8 p_forme ) {
        char* buffer = new char[ 100 ];
        if( !p_forme )
            snprintf( buffer, 99, "%hu/Icon_%hu", p_pkmnId, p_pkmnId );
        else
            snprintf( buffer, 99, "%hu/Icon_%hu-%hhu", p_pkmnId, p_pkmnId, p_forme );
        auto res = loadIcon( "nitro:/PICS/SPRITES/PKMN/", buffer, p_posX, p_posY, p_oamIndex,
                             p_palCnt, p_palpos, p_tileCnt, p_bottom );
        delete[] buffer;
        return res;
    }

    u16 loadEggIcon( const u16 p_posX, const u16 p_posY, u8 p_oamIndex, u8 p_palCnt, u16 p_tileCnt,
                     bool p_bottom ) {
        return loadIcon( "nitro:/PICS/SPRITES/PKMN/0/", "Icon_0-1", p_posX, p_posY, p_oamIndex,
                         p_palCnt, p_tileCnt, p_bottom );
    }
    u16 loadEggIcon( const u16 p_posX, const u16 p_posY, u8 p_oamIndex, u8 p_palCnt, u8 p_palpos,
                     u16 p_tileCnt, bool p_bottom ) {
        return loadIcon( "nitro:/PICS/SPRITES/PKMN/0/", "Icon_0-1", p_posX, p_posY, p_oamIndex,
                         p_palCnt, p_palpos, p_tileCnt, p_bottom );
    }

    u16 loadItemIcon( const std::string& p_itemName, const u16 p_posX, const u16 p_posY,
                      u8 p_oamIndex, u8 p_palCnt, u16 p_tileCnt, bool p_bottom ) {
        return loadIcon( "nitro:/PICS/SPRITES/ITEMS/", p_itemName.c_str( ), p_posX, p_posY,
                         p_oamIndex, p_palCnt, p_tileCnt, p_bottom );
    }

    u16 loadTMIcon( type p_type, bool p_hm, const u16 p_posX, const u16 p_posY, u8 p_oamIndex,
                    u8 p_palCnt, u16 p_tileCnt, bool p_bottom ) {
        std::string itemname
            = ( p_hm ? "VM" : "TM" )
              + ( std::vector<std::string>{"Normal", "Kampf", "Flug", "Gift", "Boden", "Gestein",
                                           "Pflanze", "Geist", "Stahl", "Unbekannt", "Wasser",
                                           "Feuer", "Pflanze", "Elektro", "Psycho", "Eis", "Drache",
                                           "Unlicht", "Fee"}[ p_type ] );

        return loadItemIcon( itemname, p_posX, p_posY, p_oamIndex, p_palCnt, p_tileCnt, p_bottom );
    }

    u16 loadTypeIcon( type p_type, const u16 p_posX, const u16 p_posY, u8 p_oamIndex, u8 p_palCnt,
                      u16 p_tileCnt, bool p_bottom ) {
        return loadSprite( p_oamIndex, p_palCnt, p_tileCnt, p_posX, p_posY, 32, 16,
                           TypePals[ p_type ], TypeTiles[ p_type ], 256, false, false, false,
                           OBJPRIORITY_0, p_bottom );
    }

    u16 loadRibbonIcon( u8 p_ribbonIdx, const u16 p_posX, const u16 p_posY, u8 p_oamIndex,
                        u8 p_palCnt, u16 p_tileCnt, bool p_bottom ) {
        if( !RibbonPals[ p_ribbonIdx ] || !RibbonTiles[ p_ribbonIdx ] ) return 0;
        return loadSprite( p_oamIndex, p_palCnt, p_tileCnt, p_posX, p_posY, 32, 32,
                           RibbonPals[ p_ribbonIdx ], RibbonTiles[ p_ribbonIdx ], 512, false, false,
                           false, OBJPRIORITY_0, p_bottom );
    }

    u16 loadDamageCategoryIcon( move::moveHitTypes p_type, const u16 p_posX, const u16 p_posY,
                                u8 p_oamIndex, u8 p_palCnt, u16 p_tileCnt, bool p_bottom ) {
        return loadSprite( p_oamIndex, p_palCnt, p_tileCnt, p_posX, p_posY, 32, 16,
                           HitTypePals[ p_type ], HitTypeTiles[ p_type ], 256, false, false, false,
                           OBJPRIORITY_0, p_bottom );
    }

} // namespace IO
