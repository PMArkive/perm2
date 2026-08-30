/*
Pokémon neo
------------------------------

file        : mysteryGiftAlbum.cpp
author      : Philip Wellnitz
description : WC Album (overlay 0)

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
#include <nds.h>
#include <nds/system.h>

#include "defines.h"
#include "fs/data.h"
#include "fs/fs.h"
#include "io/choiceBox.h"
#include "io/message.h"
#include "io/screenFade.h"
#include "io/uio.h"
#include "ov.h"
#include "save/mysteryGift.h"

#ifdef __cplusplus
extern "C" {
#endif

void displayWonderCard( u8 p_cardIdx, bool p_reverse ) {
    bgSetScale( IO::bg3, 1 << 7, 1 << 7 );
    bgSetScroll( IO::bg3, 0, 0 );
    bgUpdate( );
    FS::readPictureData( bgGetGfxPtr( IO::bg3 ), "nitro:/PICS/", "wcbg", 0, 256 * 256 / 2, false );
    if( p_reverse ) {
        FS::readPictureData( bgGetGfxPtr( IO::bg2 ), "nitro:/PICS/", "wc2", 200, 3, 256 * 192,
                             false );
    } else {
        FS::readPictureData( bgGetGfxPtr( IO::bg2 ), "nitro:/PICS/", "wc1", 200, 3, 256 * 192,
                             false );
    }

    BG_PALETTE[ 1 ]     = 0xfbba;
    BG_PALETTE[ 2 ]     = 0xf775;
    BG_PALETTE_SUB[ 1 ] = 0xfbba;
    BG_PALETTE_SUB[ 2 ] = 0xf775;

    SAVE::initTopSprites( false );

    const auto& wc = SAVE::CURRENT_FILE->m_storedWonderCards[ p_cardIdx ];

    BG_PALETTE[ IO::BLACK_IDX ] = IO::BLACK2;
    BG_PALETTE[ IO::GRAY_IDX ]  = IO::STEEL_COLOR;
    IO::regularFont->setColor( IO::BLACK_IDX, 1 );
    IO::regularFont->setColor( IO::GRAY_IDX, 2 );

    for( u8 i = 0; i < 3; ++i ) {
        IO::OamTop->oamBuffer[ SAVE::SPR_CARD_ICON_OAM + i ].isHidden = true;
    }
    if( !p_reverse ) {
        IO::regularFont->printStringC( GET_STRING( IO::STR_UI_WONDERCARD ), 16, 28, false );
        if( SAVE::CURRENT_FILE->collectedWC( wc.m_id ) ) {
            IO::regularFont->printStringC( GET_STRING( IO::STR_UI_THANK_YOU_FOR_PLAYING ), 16, 85,
                                           false );
        } else {
            IO::regularFont->printStringC( GET_STRING( IO::STR_UI_PLEASE_COLLECT_GIFT ), 16, 85,
                                           false );
        }
        IO::regularFont->printStringC(
            IO::formatDate( SAVE::date{ wc.m_year, wc.m_month, wc.m_day } ).c_str( ), 144, 150,
            false );

#ifdef DESQUID
        IO::regularFont->printStringC( std::to_string( wc.m_id ).c_str( ), 16, 149, false );
#endif

        IO::regularFont->setColor( IO::WHITE_IDX, 1 );
        IO::regularFont->setColor( IO::GRAY_IDX, 2 );
        IO::regularFont->printStringC( wc.m_title, 16, 62, false );
        IO::regularFont->printStringC( GET_STRING( IO::STR_UI_DATE_RECEIVED ), 48, 149, false );

        IO::regularFont->setColor( IO::BLACK_IDX, 1 );
        IO::regularFont->setColor( IO::GRAY_IDX, 2 );

        // depending on wc type, load icon
        switch( wc.m_type ) {
        case SAVE::WCTYPE_ITEM: {
            u8  idx   = 0;
            u16 tccnt = 0;
            for( u8 i = 0; i < 3; ++i ) {
                if( !wc.m_data.m_item.m_itemId[ 2 - i ] ) { continue; }
                tccnt = IO::loadItemIcon(
                    wc.m_data.m_item.m_itemId[ 2 - i ], 256 - 24 * ( idx + 1 ) - 20, 18,
                    SAVE::SPR_CARD_ICON_OAM + idx, SAVE::SPR_CARD_ICON_PAL + idx, tccnt, false );
                ++idx;
            }
            IO::updateOAM( false );
            break;
        }
        case SAVE::WCTYPE_PKMN: {
            if( wc.m_data.m_pkmn.m_isEgg ) {
                IO::loadEggIcon( 256 - 32 - 24 - 14, 14, SAVE::SPR_CARD_ICON_OAM,
                                 SAVE::SPR_CARD_ICON_PAL, 0, false,
                                 wc.m_data.m_pkmn.m_species == PKMN_MANAPHY );
            } else {
                auto sInfo = pkmnSpriteInfo{ wc.m_data.m_pkmn.m_species,
                                             wc.m_data.m_pkmn.m_forme,
                                             wc.m_data.m_pkmn.m_female,
                                             wc.m_data.m_pkmn.m_shiny == 2,
                                             false,
                                             DEFAULT_SPRITE_PID };
                IO::loadPKMNIcon( sInfo, 256 - 32 - 24 - 14, 14, SAVE::SPR_CARD_ICON_OAM,
                                  SAVE::SPR_CARD_ICON_PAL, 0, false );
            }
            IO::updateOAM( false );
            break;
        }
        default: break;
        }
    } else {
        IO::updateOAM( false );

        IO::regularFont->setColor( IO::BLACK_IDX, 1 );
        IO::regularFont->setColor( IO::GRAY_IDX, 2 );
        IO::regularFont->printStringC(
            GET_WC_STRING( SAVE::CURRENT_FILE->collectedWC( wc.m_id ) + 2 * wc.m_descriptionId ),
            16, 36, false );
    }
}

int ov_0_main( ) {
    u8   currentCard = 0;
    bool reverse     = false;

    loop( ) {
        // TODO: "Details" (flips card)
        // "Delete card" (deletes card)
        // "Share with a friend"
        // "Back"
        // "left" / "right"
        // TODO: allow redistributing the card to a friend (new option to be
        // implemented); friend downloads via "receive from friend" method

        IO::choiceBox    cb = IO::choiceBox( IO::choiceBox::MODE_UP_DOWN );
        std::vector<u16> wcopts;
        auto             res = cb.getResult(
            [ & ]( u8 p_slot ) {
                currentCard = p_slot;
                auto& wc    = SAVE::CURRENT_FILE->m_storedWonderCards[ currentCard ];

                dmaFillWords( 0, bgGetGfxPtr( IO::bg2sub ), COMPLETE_SCREEN );
                wcopts.clear( );
                wcopts.push_back( IO::STR_UI_WC_FLIP );
                if( SAVE::CURRENT_FILE->collectedWC( wc.m_id ) ) {
                    wcopts.push_back( IO::STR_UI_WC_TOSS );
                }
                wcopts.push_back( IO::STR_UI_CANCEL );

                IO::regularFont->setColor( IO::WHITE_IDX, 1 );
                IO::regularFont->setColor( IO::GRAY_IDX, 2 );
                auto rs = SAVE::drawChoice(
                    0, wcopts, false, currentCard > 0,
                    currentCard + 1 < SAVE::MAX_STORED_WC
                        && SAVE::SAV.getActiveFile( ).m_storedWonderCards[ currentCard + 1 ].m_type
                               != SAVE::WCTYPE_NONE );
                displayWonderCard( currentCard, reverse );
                return rs;
            },
            [ & ]( u8 p_choice ) { SAVE::selectMainChoice( p_choice ); }, 0,
            [ & ]( ) {
                // ++frame;
                // IO::animateBG( frame, IO::bg3 );
                // IO::animateBG( frame, IO::bg3sub );
                // bgUpdate( );
            },
            currentCard );

        if( res == wcopts.size( ) - 1 || res == IO::choiceBox::BACK_CHOICE ) {
            SAVE::clearText( );
            SAVE::hideSpritesSub( );
            return 0;
        } else if( res == 0 ) {
            reverse = !reverse;
        } else if( res == 1 && res == wcopts.size( ) - 2 ) {
            for( u8 i = currentCard; i + 1 < SAVE::MAX_STORED_WC; ++i ) {
                memcpy( &SAVE::CURRENT_FILE->m_storedWonderCards[ i ],
                        &SAVE::CURRENT_FILE->m_storedWonderCards[ i + 1 ],
                        sizeof( SAVE::wonderCard ) );
            }
            memset( &SAVE::CURRENT_FILE->m_storedWonderCards[ SAVE::MAX_STORED_WC - 1 ], 0,
                    sizeof( SAVE::wonderCard ) );

            if( SAVE::CURRENT_FILE->m_storedWonderCards[ 0 ].m_type == SAVE::WCTYPE_NONE ) {
                SAVE::clearText( );
                SAVE::hideSpritesSub( );
                return 0;
            }
        }
    }
    return 0;
}

#ifdef __cplusplus
}
#endif
