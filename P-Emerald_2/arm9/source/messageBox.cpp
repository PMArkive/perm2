/*
    Pok�mon Emerald 2 Version
    ------------------------------

    file        : messageBox.cpp
    author      : Philip Wellnitz (RedArceus)
    description : Functionality message boxes

    Copyright (C) 2012 - 2014
    Philip Wellnitz (RedArceus)

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any
    damages arising from the use of this software.

    Permission is granted to anyone to use this software for any
    purpose, including commercial applications, and to alter it and
    redistribute it freely, subject to the following restrictions:


    1.	The origin of this software must not be misrepresented; you
    must not claim that you wrote the original software. If you use
    this software in a product, an acknowledgment in the product
    is required.

    2.	Altered source versions must be plainly marked as such, and
    must not be misrepresented as being the original software.

    3.	This notice may not be removed or altered from any source
    distribution.
    */


#include "messageBox.h"
#include "sprite.h"
#include "screenLoader.h"
#include "item.h"
#include <cmath>
#include <vector>

#include "print.h"

extern void setMainSpriteVisibility( bool p_hidden );
extern backgroundSet BGs[ MAXBG ];
extern int BG_ind;
extern SpriteInfo spriteInfo[ SPRITE_COUNT ];
extern OAMTable *oam;
extern ConsoleFont cfont;
extern font::Font cust_font;
extern font::Font cust_font2;

bool back_, save_, main_;
SpriteEntry * back, *save;
int TEXTSPEED = 35;

void init( ) {
    for( int i = 0; i < 4; ++i )
        oam->oamBuffer[ 31 + 2 * i ].isHidden = true;
    for( int i = 9; i <= 12; ++i ) {
        oam->oamBuffer[ i ].isHidden = true;
        swiWaitForVBlank( );
    }

    updateOAMSub( oam );

    cust_font.setColor( 0, 0 );
    cust_font.setColor( 251, 1 );
    cust_font.setColor( 252, 2 );
    cust_font2.setColor( 0, 0 );
    cust_font2.setColor( 253, 1 );
    cust_font2.setColor( 254, 2 );

    BG_PALETTE_SUB[ 250 ] = RGB15( 31, 31, 31 );
    BG_PALETTE_SUB[ 251 ] = RGB15( 15, 15, 15 );
    BG_PALETTE_SUB[ 252 ] = RGB15( 3, 3, 3 );
    BG_PALETTE_SUB[ 253 ] = RGB15( 15, 15, 15 );
    BG_PALETTE_SUB[ 254 ] = RGB15( 31, 31, 31 );
    font::putrec( 0, 0, 256, 63, true, false, 250 );

    updateOAMSub( oam );
}
void dinit( ) {
    drawSub( );

    for( int i = 0; i < 4; ++i )
        oam->oamBuffer[ 31 + 2 * i ].isHidden = false;
}

void messageBox::clear( ) {
    font::putrec( 0, 0, 256, 63, true, false, 250 );
}
void messageBox::clearButName( ) {
    font::putrec( 72, 0, 256, 63, true, false, 250 );
}

void waitForTouchUp( bool p_uTime, bool p_tpar = false ) {
    while( 1 ) {
        swiWaitForVBlank( );
        scanKeys( );
        if( p_uTime )
            updateTime( p_tpar );
        auto touch = touchReadXY( );
        if( touch.px == 0 && touch.py == 0 )
            break;
    }
}

messageBox::messageBox( item p_item, const int p_count ) {
    m_isNamed = false;
    back = &oam->oamBuffer[ 0 ];
    save = &oam->oamBuffer[ 1 ];
    back_ = back->isHidden;
    save_ = save->isHidden;
    main_ = ( oam->oamBuffer[ BAG_ID ] ).isHidden;
    setSpriteVisibility( back, true );
    setSpriteVisibility( save, true );
    setMainSpriteVisibility( true );
    init( );
    int a = 0, b = 0, c = 0;
    drawItemIcon( oam, spriteInfo, p_item.m_itemName, 4, 4, a, b, c );
    updateOAMSub( oam );

    updateTime( );

    cust_font.setColor( 253, 3 );
    cust_font.setColor( 254, 4 );

    BG_PALETTE_SUB[ 253 ] = RGB15( 15, 15, 15 );
    BG_PALETTE_SUB[ 254 ] = RGB15( 0, 0, 15 );

    char buf[ 40 ];
    sprintf( buf, "%3d %s in der", p_count, p_item.getDisplayName( ).c_str( ) );
    cust_font.print_string_d( buf, 32, 8, true );
    cust_font.print_char( 489 - 21 + p_item.getItemType( ), 32, 24, true );
    sprintf( buf, "%s-Tasche verstaut.", bagnames[ p_item.m_itemType ].c_str( ) );
    cust_font.print_string_d( buf, 46, 24, true );

    oam->oamBuffer[ 8 ].isHidden = false;
    updateOAMSub( oam );
    touchPosition touch;
    while( 1 ) {
        swiWaitForVBlank( );
        updateTime( );
        scanKeys( );
        if( keysUp( ) & KEY_A )
            break;
        touchRead( &touch );

        if( touch.px > 224 && touch.py > 164 ) {
            waitForTouchUp( true );
            break;
        }
    }

    initMainSprites( oam, spriteInfo );
    //setMainSpriteVisibility(false);
    setSpriteVisibility( back, true );
    setSpriteVisibility( save, false );
    oam->oamBuffer[ 8 ].isHidden = true;
    dinit( );
    updateOAMSub( oam );
}

messageBox::messageBox( const char* p_text, bool p_time, bool p_remsprites ) {
    m_isNamed = false;
    back = &oam->oamBuffer[ 0 ];
    save = &oam->oamBuffer[ 1 ];
    back_ = back->isHidden;
    save_ = save->isHidden;
    main_ = ( oam->oamBuffer[ BAG_ID ] ).isHidden;
    setSpriteVisibility( back, true );
    setSpriteVisibility( save, true );
    setMainSpriteVisibility( true );

    init( );

    if( p_time ) updateTime( );

    cust_font.print_string_d( p_text, 8, 8, true );
    oam->oamBuffer[ 8 ].isHidden = false;
    updateOAMSub( oam );
    touchPosition touch;
    while( 1 ) {
        swiWaitForVBlank( );
        if( p_time )
            updateTime( );
        scanKeys( );
        if( keysUp( ) & KEY_A )
            break;
        touchRead( &touch );

        if( touch.px > 224 && touch.py > 164 ) {

            waitForTouchUp( p_time );
            break;
        }
    }

    setSpriteVisibility( back, back_ );
    setSpriteVisibility( save, save_ );
    setMainSpriteVisibility( main_ );
    oam->oamBuffer[ 8 ].isHidden = true;
    dinit( );
    updateOAMSub( oam );
    swiWaitForVBlank( );
}
messageBox::messageBox( const wchar_t* p_text, bool p_time, bool p_remsprites ) {
    m_isNamed = false;
    back = &oam->oamBuffer[ 0 ];
    save = &oam->oamBuffer[ 1 ];
    back_ = back->isHidden;
    save_ = save->isHidden;
    main_ = ( oam->oamBuffer[ BAG_ID ] ).isHidden;
    setSpriteVisibility( back, true );
    setSpriteVisibility( save, true );
    setMainSpriteVisibility( true );

    init( );

    if( p_time ) updateTime( );

    cust_font.print_string_d( p_text, 8, 8, true );
    oam->oamBuffer[ 8 ].isHidden = false;
    updateOAMSub( oam );
    touchPosition touch;
    while( 1 ) {
        swiWaitForVBlank( );
        if( p_time )
            updateTime( );
        scanKeys( );
        if( keysUp( ) & KEY_A )
            break;
        touchRead( &touch );

        if( touch.px > 224 && touch.py > 164 ) {

            waitForTouchUp( p_time );
            break;
        }
    }

    setSpriteVisibility( back, back_ );
    setSpriteVisibility( save, save_ );
    setMainSpriteVisibility( main_ );
    oam->oamBuffer[ 8 ].isHidden = true;
    for( int i = 9; i <= 12; ++i ) {
        oam->oamBuffer[ i ].isHidden = p_remsprites;
        swiWaitForVBlank( );
    }
    dinit( );
    updateOAMSub( oam );
    swiWaitForVBlank( );
}
messageBox::messageBox( const char* p_text, const char* p_name, bool p_time, bool p_a, bool p_remsprites, sprite_type p_sprt, int p_sprind ) {
    m_isNamed = p_name;
    back = &oam->oamBuffer[ 0 ];
    save = &oam->oamBuffer[ 1 ];
    back_ = back->isHidden;
    save_ = save->isHidden;
    main_ = ( oam->oamBuffer[ BAG_ID ] ).isHidden;
    setSpriteVisibility( back, true );
    setSpriteVisibility( save, true );
    setMainSpriteVisibility( true );
    if( p_sprt != no_sprite ) {
        int a = 0, b = 0, c = 0;
        if( p_sprt == sprite_pkmn ) {
            loadPKMNSpriteTop( oam, spriteInfo, "nitro:/PICS/SPRITES/pokemon/", p_sprind, (u16)-16, 0, a, b, c, true );
        }
        if( p_sprt == sprite_trainer ) {
            loadPKMNSpriteTop( oam, spriteInfo, "nitro:/PICS/SPRITES/TRAINER/", p_sprind, (u16)-16, 0, a, b, c, true );
        }
    }

    init( );

    if( p_time ) updateTime( );

    cust_font.print_string( p_name, 8, 8, true );
    cust_font.print_string_d( p_text, 72, 8, true );
    if( p_a )
        oam->oamBuffer[ 8 ].isHidden = false;
    updateOAMSub( oam );

    if( p_a ) {
        touchPosition touch;
        while( 1 ) {
            swiWaitForVBlank( );
            if( p_time )
                updateTime( );
            scanKeys( );
            if( keysUp( ) & KEY_A )
                break;
            touchRead( &touch );

            if( touch.px > 224 && touch.py > 164 ) {

                waitForTouchUp( p_time );
                break;
            }
        }
    }
    if( !p_remsprites )
        return;
    if( p_sprt != no_sprite )
        initMainSprites( oam, spriteInfo );
    setSpriteVisibility( back, back_ );
    setSpriteVisibility( save, save_ );
    setMainSpriteVisibility( main_ );
    oam->oamBuffer[ 8 ].isHidden = true;
    for( int i = 9; i <= 12; ++i ) {
        oam->oamBuffer[ i ].isHidden = p_remsprites;
        swiWaitForVBlank( );
    }
    dinit( );
    updateOAMSub( oam );
    swiWaitForVBlank( );
}
messageBox::messageBox( const wchar_t* p_text, const wchar_t* p_name, bool p_time, bool p_a, bool p_remsprites, sprite_type p_sprt, int p_sprind ) {
    m_isNamed = false;
    back = &oam->oamBuffer[ 0 ];
    save = &oam->oamBuffer[ 1 ];
    back_ = back->isHidden;
    save_ = save->isHidden;
    main_ = ( oam->oamBuffer[ BAG_ID ] ).isHidden;
    setSpriteVisibility( back, true );
    setSpriteVisibility( save, true );
    setMainSpriteVisibility( true );
    if( p_sprt != no_sprite ) {
        int a = 0, b = 0, c = 0;
        if( p_sprt == sprite_pkmn ) {
            loadPKMNSpriteTop( oam, spriteInfo, "nitro:/PICS/SPRITES/pokemon/", p_sprind, (u16)-16, 0, a, b, c, true );
        }
        if( p_sprt == sprite_trainer ) {
            loadPKMNSpriteTop( oam, spriteInfo, "nitro:/PICS/SPRITES/TRAINER/", p_sprind, (u16)-16, 0, a, b, c, true );
        }
    }
    updateOAMSub( oam );

    init( );

    if( p_name ) {
        cust_font.print_string( p_name, 8, 8, true );
        cust_font.print_string_d( p_text, 72, 8, true );
    } else {
        cust_font.print_string_d( p_text, 8, 8, true );
    }
    if( p_a )
        oam->oamBuffer[ 8 ].isHidden = false;
    updateOAMSub( oam );

    if( p_a ) {
        touchPosition touch;
        while( 1 ) {
            swiWaitForVBlank( );
            if( p_time )
                updateTime( );
            scanKeys( );
            if( keysUp( ) & KEY_A )
                break;
            touchRead( &touch );

            if( touch.px > 224 && touch.py > 164 ) {

                waitForTouchUp( p_time );
                break;
            }
        }
    }
    if( !p_remsprites )
        return;
    if( p_sprt != no_sprite )
        initMainSprites( oam, spriteInfo );
    setSpriteVisibility( back, back_ );
    setSpriteVisibility( save, save_ );
    setMainSpriteVisibility( main_ );
    oam->oamBuffer[ 8 ].isHidden = true;
    for( int i = 9; i <= 12; ++i ) {
        oam->oamBuffer[ i ].isHidden = p_remsprites;
        swiWaitForVBlank( );
    }
    dinit( );
    updateOAMSub( oam );
    swiWaitForVBlank( );
}

void messageBox::put( const char* p_text, bool p_a, bool p_time ) {
    init( );

    if( m_isNamed ) {
        cust_font.print_string( m_isNamed, 8, 8, true );
        cust_font.print_string_d( p_text, 72, 8, true );
    } else
        cust_font.print_string_d( p_text, 8, 8, true );

    if( p_a ) {
        touchPosition touch;
        while( 1 ) {
            swiWaitForVBlank( );
            if( p_time )
                updateTime( );
            scanKeys( );
            if( keysUp( ) & KEY_A )
                break;
            touchRead( &touch );

            if( touch.px > 224 && touch.py > 164 ) {

                waitForTouchUp( p_time );
                break;
            }
        }
    }
    swiWaitForVBlank( );
}

yesNoBox::yesNoBox( ) {
    back = &oam->oamBuffer[ 0 ];
    save = &oam->oamBuffer[ 1 ];
    back_ = back->isHidden;
    save_ = save->isHidden;
    main_ = ( oam->oamBuffer[ BAG_ID ] ).isHidden;
    setSpriteVisibility( back, true );
    setSpriteVisibility( save, true );
    setMainSpriteVisibility( true );
    oam->oamBuffer[ 8 ].isHidden = true;
    init( );
    updateOAMSub( oam );

    consoleSetWindow( &Bottom, 1, 1, 30, MAXLINES );
    consoleSelect( &Bottom );
    _isNamed = false;
}
yesNoBox::yesNoBox( const char* p_name ) {
    back = &oam->oamBuffer[ 0 ];
    save = &oam->oamBuffer[ 1 ];
    back_ = back->isHidden;
    save_ = save->isHidden;
    main_ = ( oam->oamBuffer[ BAG_ID ] ).isHidden;
    setSpriteVisibility( back, true );
    setSpriteVisibility( save, true );
    setMainSpriteVisibility( true );
    oam->oamBuffer[ 8 ].isHidden = true;

    init( );

    consoleSetWindow( &Bottom, 1, 1, 8, MAXLINES - 1 );
    consoleSelect( &Bottom );
    cust_font.print_string( p_name, 8, 8, true );
    consoleSetWindow( &Bottom, 9, 1, 22, MAXLINES );

    swiWaitForVBlank( );
    _isNamed = true;
}
yesNoBox::yesNoBox( messageBox p_box ) {
    back = &oam->oamBuffer[ 0 ];
    save = &oam->oamBuffer[ 1 ];
    back_ = back->isHidden;
    save_ = save->isHidden;
    main_ = ( oam->oamBuffer[ BAG_ID ] ).isHidden;
    setSpriteVisibility( back, true );
    setSpriteVisibility( save, true );
    setMainSpriteVisibility( true );
    oam->oamBuffer[ 8 ].isHidden = true;
    init( );
    updateOAMSub( oam );
    _isNamed = p_box.m_isNamed;
}

bool yesNoBox::getResult( const char* p_text = 0, bool p_time ) {

    updateOAMSub( oam );
    consoleSelect( &Bottom );
    if( p_text ) {
        if( _isNamed )
            cust_font.print_string_d( p_text, 72, 8, true );
        else
            cust_font.print_string_d( p_text, 8, 8, true );
    }
    for( int i = 19; i <= 22; ++i )
        oam->oamBuffer[ i ].isHidden = false;
    updateOAMSub( oam );
    consoleSetWindow( &Bottom, 5, 13, 10, 3 );
    printf( "\n    Ja" );
    consoleSetWindow( &Bottom, 17, 13, 10, 3 );
    printf( "\n   Nein" );

    while( 42 ) {
        swiWaitForVBlank( );
        updateOAMSub( oam );
        if( p_time )
            updateTime( );
        touchPosition t;
        touchRead( &t );
        if( t.px > 31 && t.py > 99 && t.px < 129 && t.py < 133 ) {
            oam->oamBuffer[ 21 ].isHidden = true;
            oam->oamBuffer[ 22 ].isHidden = true;
            updateOAMSub( oam );

            waitForTouchUp( p_time );
            oam->oamBuffer[ 19 ].isHidden = true;
            oam->oamBuffer[ 20 ].isHidden = true;
            setSpriteVisibility( back, back_ );
            setSpriteVisibility( save, save_ );
            oam->oamBuffer[ 8 ].isHidden = true;
            for( int i = 9; i <= 12; ++i ) {
                oam->oamBuffer[ i ].isHidden = true;
            }
            updateOAMSub( oam );
            consoleSetWindow( &Bottom, 1, 1, 30, 24 );
            consoleClear( );
            dinit( );
            return true;//YES
        } else if( t.px > 127 && t.py > 99 && t.px < 225 && t.py < 133 ) {
            oam->oamBuffer[ 19 ].isHidden = true;
            oam->oamBuffer[ 20 ].isHidden = true;
            updateOAMSub( oam );

            waitForTouchUp( p_time );
            oam->oamBuffer[ 21 ].isHidden = true;
            oam->oamBuffer[ 22 ].isHidden = true;
            setSpriteVisibility( back, back_ );
            setSpriteVisibility( save, save_ );
            oam->oamBuffer[ 8 ].isHidden = true;
            for( int i = 9; i <= 12; ++i ) {
                oam->oamBuffer[ i ].isHidden = true;
            }
            updateOAMSub( oam );
            consoleSetWindow( &Bottom, 1, 1, 30, 24 );
            consoleClear( );
            dinit( );
            return false;//No
        }
    }
    dinit( );
    return false;
}
bool yesNoBox::getResult( const wchar_t* p_text = 0, bool time ) {

    updateOAMSub( oam );
    consoleSelect( &Bottom );
    if( p_text ) {
        if( _isNamed )
            cust_font.print_string_d( p_text, 72, 8, true );
        else
            cust_font.print_string_d( p_text, 8, 8, true );
    }
    for( int i = 19; i <= 22; ++i )
        oam->oamBuffer[ i ].isHidden = false;
    updateOAMSub( oam );
    consoleSetWindow( &Bottom, 5, 13, 10, 3 );
    printf( "\n    Ja" );
    consoleSetWindow( &Bottom, 17, 13, 10, 3 );
    printf( "\n   Nein" );

    while( 42 ) {
        swiWaitForVBlank( );
        updateOAMSub( oam );
        if( time )
            updateTime( );
        touchPosition t;
        touchRead( &t );
        if( t.px > 31 && t.py > 99 && t.px < 129 && t.py < 133 ) {
            oam->oamBuffer[ 21 ].isHidden = true;
            oam->oamBuffer[ 22 ].isHidden = true;
            updateOAMSub( oam );

            waitForTouchUp( time );
            oam->oamBuffer[ 19 ].isHidden = true;
            oam->oamBuffer[ 20 ].isHidden = true;
            setSpriteVisibility( back, back_ );
            setSpriteVisibility( save, save_ );
            oam->oamBuffer[ 8 ].isHidden = true;
            for( int i = 9; i <= 12; ++i ) {
                oam->oamBuffer[ i ].isHidden = true;
            }
            updateOAMSub( oam );
            consoleSetWindow( &Bottom, 1, 1, 30, 24 );
            consoleClear( );
            dinit( );
            return true;//YES
        } else if( t.px > 127 && t.py > 99 && t.px < 225 && t.py < 133 ) {
            oam->oamBuffer[ 19 ].isHidden = true;
            oam->oamBuffer[ 20 ].isHidden = true;
            updateOAMSub( oam );


            waitForTouchUp( time );
            oam->oamBuffer[ 21 ].isHidden = true;
            oam->oamBuffer[ 22 ].isHidden = true;
            setSpriteVisibility( back, back_ );
            setSpriteVisibility( save, save_ );
            oam->oamBuffer[ 8 ].isHidden = true;
            for( int i = 9; i <= 12; ++i ) {
                oam->oamBuffer[ i ].isHidden = true;
            }
            updateOAMSub( oam );
            consoleSetWindow( &Bottom, 1, 1, 30, 24 );
            consoleClear( );
            dinit( );
            return false;//No
        }
    }
    dinit( );
    return false;
}

choiceBox::choiceBox( int p_num, const char** p_choices, const char* p_name = 0, bool p_big = false ) {
    _num = p_num;
    _choices = p_choices;
    _big = p_big || ( p_num <= 3 );

    back_ = oam->oamBuffer[ 0 ].isHidden;
    save_ = oam->oamBuffer[ 1 ].isHidden;
    main_ = ( oam->oamBuffer[ BAG_ID ] ).isHidden;
    setSpriteVisibility( &( oam->oamBuffer[ 0 ] ), true );
    setSpriteVisibility( &( oam->oamBuffer[ 1 ] ), true );
    setMainSpriteVisibility( true );
    oam->oamBuffer[ 8 ].isHidden = true;
    init( );

    for( int i = 13; i <= 29; ++i ) {
        oam->oamBuffer[ i ].isHidden = true;
    }
    updateOAMSub( oam );

    if( p_name ) {
        _name = true;
        cust_font.print_string( p_name, 8, 8, true );
    } else
        _name = false;

    swiWaitForVBlank( );
}

int fwdPos[ 2 ][ 2 ] = { { SCREEN_WIDTH - 12, SCREEN_HEIGHT - 12 }, { SCREEN_WIDTH - 11, SCREEN_HEIGHT - 31 } },
bwdPos[ 2 ][ 2 ] = { { SCREEN_WIDTH - 12, SCREEN_HEIGHT - 12 }, { SCREEN_WIDTH - 31, SCREEN_HEIGHT - 11 } };

choiceBox::~choiceBox( ) {
    dinit( );
    consoleSetWindow( &Bottom, 9, 1, 22, MAXLINES );
    consoleSelect( &Bottom );
    consoleClear( );
    consoleSetWindow( &Bottom, 1, 1, 8, MAXLINES - 1 );
    consoleClear( );
    consoleSetWindow( &Bottom, 1, 1, 30, 24 );
    consoleClear( );
    setMainSpriteVisibility( main_ );
    oam->oamBuffer[ 8 ].isHidden = true;
    for( int i = 9; i <= 29; ++i )
        oam->oamBuffer[ i ].isHidden = true;

    setSpriteVisibility( &( oam->oamBuffer[ 0 ] ), back_ );
    setSpriteVisibility( &( oam->oamBuffer[ 1 ] ), save_ );
    updateOAMSub( oam );
    swiWaitForVBlank( );
}

int choiceBox::getResult( const char* p_text = 0, bool p_time = true ) {
    int ret = 0;
    consoleSelect( &Bottom );
    if( p_text ) {
        if( _name )
            cust_font.print_string( p_text, 72, 8, true );
        else
            cust_font.print_string( p_text, 8, 8, true );
    }
    if( _num < 1 )
        return -1;
    else if( _num == 1 ) {
        ( oam->oamBuffer[ 20 ] ).isHidden = false;
        ( oam->oamBuffer[ 21 ] ).isHidden = false;
        ( oam->oamBuffer[ 28 ] ).isHidden = false;
        updateOAMSub( oam );

        consoleSetWindow( &Bottom, 5, 13, 22, 3 );
        printf( _choices[ 0 ] );

        while( 42 ) {
            swiWaitForVBlank( );
            updateOAMSub( oam );
            if( p_time )
                updateTime( true );
            touchPosition t;
            touchRead( &t );

            if( t.px > 31 && t.py > 99 && t.px < 225 && t.py < 133 ) {

                oam->oamBuffer[ 20 ].isHidden = true;
                oam->oamBuffer[ 21 ].isHidden = true;
                oam->oamBuffer[ 28 ].isHidden = true;
                updateOAMSub( oam );

                waitForTouchUp( p_time, true );
                consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                consoleClear( );

                return 0;
            }
        }
    } else if( _num == 2 ) {
        ( oam->oamBuffer[ 20 ] ).isHidden = false;
        ( oam->oamBuffer[ 21 ] ).isHidden = false;
        ( oam->oamBuffer[ 29 ] ).isHidden = false;
        ( oam->oamBuffer[ 24 ] ).isHidden = false;
        ( oam->oamBuffer[ 25 ] ).isHidden = false;
        ( oam->oamBuffer[ 28 ] ).isHidden = false;
        ( oam->oamBuffer[ 20 ] ).y -= 16;
        ( oam->oamBuffer[ 21 ] ).y -= 16;
        ( oam->oamBuffer[ 28 ] ).y -= 16;
        ( oam->oamBuffer[ 24 ] ).y -= 16;
        ( oam->oamBuffer[ 25 ] ).y -= 16;
        ( oam->oamBuffer[ 29 ] ).y -= 16;
        updateOAMSub( oam );

        consoleSetWindow( &Bottom, 5, 11, 22, 3 );
        printf( _choices[ 0 ] );
        consoleSetWindow( &Bottom, 5, 15, 22, 3 );
        printf( _choices[ 1 ] );

        while( 42 ) {
            swiWaitForVBlank( );
            updateOAMSub( oam );
            if( p_time )
                updateTime( true );
            touchPosition t;
            touchRead( &t );

            if( t.px > 31 && t.py > 83 && t.px < 225 && t.py < 117 ) {
                ( oam->oamBuffer[ 20 ] ).isHidden = true;
                ( oam->oamBuffer[ 21 ] ).isHidden = true;
                ( oam->oamBuffer[ 28 ] ).isHidden = true;
                updateOAMSub( oam );

                waitForTouchUp( p_time, true );
                ( oam->oamBuffer[ 24 ] ).isHidden = true;
                ( oam->oamBuffer[ 25 ] ).isHidden = true;
                ( oam->oamBuffer[ 29 ] ).isHidden = true;
                ( oam->oamBuffer[ 20 ] ).y += 16;
                ( oam->oamBuffer[ 21 ] ).y += 16;
                ( oam->oamBuffer[ 28 ] ).y += 16;
                ( oam->oamBuffer[ 24 ] ).y += 16;
                ( oam->oamBuffer[ 25 ] ).y += 16;
                ( oam->oamBuffer[ 29 ] ).y += 16;
                updateOAMSub( oam );
                consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                consoleClear( );

                return 0;
            } else if( t.px > 31 && t.py > 115 && t.px < 225 && t.py < 159 ) {
                ( oam->oamBuffer[ 24 ] ).isHidden = true;
                ( oam->oamBuffer[ 25 ] ).isHidden = true;
                ( oam->oamBuffer[ 29 ] ).isHidden = true;
                updateOAMSub( oam );

                waitForTouchUp( p_time, true );
                ( oam->oamBuffer[ 20 ] ).isHidden = true;
                ( oam->oamBuffer[ 21 ] ).isHidden = true;
                ( oam->oamBuffer[ 28 ] ).isHidden = true;
                ( oam->oamBuffer[ 20 ] ).y += 16;
                ( oam->oamBuffer[ 21 ] ).y += 16;
                ( oam->oamBuffer[ 28 ] ).y += 16;
                ( oam->oamBuffer[ 24 ] ).y += 16;
                ( oam->oamBuffer[ 25 ] ).y += 16;
                ( oam->oamBuffer[ 29 ] ).y += 16;
                updateOAMSub( oam );
                consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                consoleClear( );

                return 1;
            }
        }
    } else if( _num == 3 ) {
        for( int i = 0; i < 3; ++i ) {
            ( oam->oamBuffer[ 17 + 4 * i ] ).isHidden = false;
            ( oam->oamBuffer[ 16 + 4 * i ] ).isHidden = false;
            ( oam->oamBuffer[ 27 + i ] ).isHidden = false;
            updateOAMSub( oam );
            consoleSetWindow( &Bottom, 5, 9 + 4 * i, 22, 3 );
            printf( _choices[ i ] );
        }
        while( 42 ) {
            swiWaitForVBlank( );
            updateOAMSub( oam );
            if( p_time )
                updateTime( true );
            touchPosition t;
            touchRead( &t );

            if( t.px > 31 && t.py > 67 && t.px < 225 && t.py < 101 ) {
                oam->oamBuffer[ 17 ].isHidden = true;
                oam->oamBuffer[ 16 ].isHidden = true;
                oam->oamBuffer[ 27 ].isHidden = true;
                updateOAMSub( oam );

                waitForTouchUp( p_time, true );
                consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                consoleClear( );

                oam->oamBuffer[ 24 ].isHidden = true;
                oam->oamBuffer[ 25 ].isHidden = true;
                oam->oamBuffer[ 29 ].isHidden = true;
                oam->oamBuffer[ 21 ].isHidden = true;
                oam->oamBuffer[ 20 ].isHidden = true;
                oam->oamBuffer[ 28 ].isHidden = true;
                return 0;
            } else if( t.px > 31 && t.py > 99 && t.px < 225 && t.py < 133 ) {
                oam->oamBuffer[ 20 ].isHidden = true;
                oam->oamBuffer[ 21 ].isHidden = true;
                oam->oamBuffer[ 28 ].isHidden = true;
                updateOAMSub( oam );

                waitForTouchUp( p_time, true );
                consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                consoleClear( );

                oam->oamBuffer[ 24 ].isHidden = true;
                oam->oamBuffer[ 25 ].isHidden = true;
                oam->oamBuffer[ 29 ].isHidden = true;
                oam->oamBuffer[ 17 ].isHidden = true;
                oam->oamBuffer[ 16 ].isHidden = true;
                oam->oamBuffer[ 27 ].isHidden = true;
                return 1;
            } else if( t.px > 31 && t.py > 131 && t.px < 225 && t.py < 165 ) {
                oam->oamBuffer[ 24 ].isHidden = true;
                oam->oamBuffer[ 25 ].isHidden = true;
                oam->oamBuffer[ 29 ].isHidden = true;
                updateOAMSub( oam );

                waitForTouchUp( p_time, true );
                consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                consoleClear( );

                oam->oamBuffer[ 20 ].isHidden = true;
                oam->oamBuffer[ 21 ].isHidden = true;
                oam->oamBuffer[ 28 ].isHidden = true;
                oam->oamBuffer[ 17 ].isHidden = true;
                oam->oamBuffer[ 16 ].isHidden = true;
                oam->oamBuffer[ 27 ].isHidden = true;
                return 2;
            }
        }
    } else if( _num > 3 && _big ) {
        int page = 0;
        ( oam->oamBuffer[ 13 ] ).isHidden = false;
        ( oam->oamBuffer[ 13 ] ).x = fwdPos[ 0 ][ 0 ] - 16;
        ( oam->oamBuffer[ 13 ] ).y = fwdPos[ 0 ][ 1 ] - 16;
        for( int i = 0; i < 3; ++i ) {
            ( oam->oamBuffer[ 17 + 4 * i ] ).isHidden = false;
            ( oam->oamBuffer[ 16 + 4 * i ] ).isHidden = false;
            ( oam->oamBuffer[ 27 + i ] ).isHidden = false;
            updateOAMSub( oam );
            consoleSetWindow( &Bottom, 5, 9 + 4 * i, 22, 3 );
            printf( _choices[ i ] );
        }
        while( 42 ) {
            swiWaitForVBlank( );
            updateOAMSub( oam );
            if( p_time )
                updateTime( true );
            touchPosition t;
            touchRead( &t );

            if( t.px > 31 && t.py > 67 && t.px < 225 && t.py < 101 ) {
                oam->oamBuffer[ 17 ].isHidden = true;
                oam->oamBuffer[ 16 ].isHidden = true;
                oam->oamBuffer[ 27 ].isHidden = true;
                updateOAMSub( oam );

                waitForTouchUp( p_time, true );
                consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                consoleClear( );

                oam->oamBuffer[ 24 ].isHidden = true;
                oam->oamBuffer[ 25 ].isHidden = true;
                oam->oamBuffer[ 29 ].isHidden = true;
                oam->oamBuffer[ 21 ].isHidden = true;
                oam->oamBuffer[ 20 ].isHidden = true;
                oam->oamBuffer[ 28 ].isHidden = true;
                return 0 + 3 * page;
            } else if( _num >= 3 * page + 2 && t.px > 31 && t.py > 99 && t.px < 225 && t.py < 133 ) {
                oam->oamBuffer[ 20 ].isHidden = true;
                oam->oamBuffer[ 21 ].isHidden = true;
                oam->oamBuffer[ 28 ].isHidden = true;
                updateOAMSub( oam );

                waitForTouchUp( p_time, true );
                consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                consoleClear( );

                oam->oamBuffer[ 24 ].isHidden = true;
                oam->oamBuffer[ 25 ].isHidden = true;
                oam->oamBuffer[ 29 ].isHidden = true;
                oam->oamBuffer[ 17 ].isHidden = true;
                oam->oamBuffer[ 16 ].isHidden = true;
                oam->oamBuffer[ 27 ].isHidden = true;
                return 1 + 3 * page;
            } else if( _num >= 3 * page + 3 && t.px > 31 && t.py > 131 && t.px < 225 && t.py < 165 ) {
                oam->oamBuffer[ 24 ].isHidden = true;
                oam->oamBuffer[ 25 ].isHidden = true;
                oam->oamBuffer[ 29 ].isHidden = true;
                updateOAMSub( oam );

                waitForTouchUp( p_time, true );
                consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                consoleClear( );

                oam->oamBuffer[ 20 ].isHidden = true;
                oam->oamBuffer[ 21 ].isHidden = true;
                oam->oamBuffer[ 28 ].isHidden = true;
                oam->oamBuffer[ 17 ].isHidden = true;
                oam->oamBuffer[ 16 ].isHidden = true;
                oam->oamBuffer[ 27 ].isHidden = true;
                return 2 + 3 * page;
            } else if( ( page == 0 && sqrt( sq( t.px - fwdPos[ 0 ][ 0 ] ) + sq( t.py - fwdPos[ 0 ][ 1 ] ) ) < 17 ) || ( page && sqrt( sq( t.px - fwdPos[ 1 ][ 0 ] ) + sq( t.py - fwdPos[ 1 ][ 1 ] ) ) < 17 ) ) {

                waitForTouchUp( p_time, true );
                if( ( ++page ) >= ( ( _num - 1 ) / 3 ) ) {
                    ( oam->oamBuffer[ 13 ] ).isHidden = true;
                    ( oam->oamBuffer[ 14 ] ).isHidden = false;
                    ( oam->oamBuffer[ 14 ] ).x = bwdPos[ 0 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 14 ] ).y = bwdPos[ 0 ][ 1 ] - 16;
                    page = ( ( _num - 1 ) / 3 );
                } else {
                    ( oam->oamBuffer[ 14 ] ).isHidden = false;
                    ( oam->oamBuffer[ 13 ] ).isHidden = false;
                    ( oam->oamBuffer[ 14 ] ).x = bwdPos[ 1 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 14 ] ).y = bwdPos[ 1 ][ 1 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).x = fwdPos[ 1 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).y = fwdPos[ 1 ][ 1 ] - 16;
                }
                for( int i = 0; i < 3; ++i ) {
                    if( 3 * page + i >= _num ) {
                        ( oam->oamBuffer[ 17 + 4 * i ] ).isHidden = true;
                        ( oam->oamBuffer[ 16 + 4 * i ] ).isHidden = true;
                        ( oam->oamBuffer[ 27 + i ] ).isHidden = true;
                        updateOAMSub( oam );
                        consoleSetWindow( &Bottom, 5, 9 + 4 * i, 22, 3 );
                        consoleClear( );
                    } else {
                        consoleSetWindow( &Bottom, 5, 9 + 4 * i, 22, 3 );
                        consoleClear( );
                        printf( _choices[ 3 * page + i ] );
                    }
                }
                updateOAMSub( oam );
            } else if( ( page == ( _num - 1 ) / 3 && sqrt( sq( t.px - bwdPos[ 0 ][ 0 ] ) + sq( t.py - bwdPos[ 0 ][ 1 ] ) ) < 17 ) || ( page && sqrt( sq( t.px - bwdPos[ 1 ][ 0 ] ) + sq( t.py - bwdPos[ 1 ][ 1 ] ) ) < 17 ) ) {

                waitForTouchUp( p_time, true );
                if( ( --page ) <= 0 ) {
                    ( oam->oamBuffer[ 14 ] ).isHidden = true;
                    ( oam->oamBuffer[ 13 ] ).isHidden = false;
                    ( oam->oamBuffer[ 13 ] ).x = fwdPos[ 0 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).y = fwdPos[ 0 ][ 1 ] - 16;
                    page = 0;
                } else {
                    ( oam->oamBuffer[ 13 ] ).isHidden = false;
                    ( oam->oamBuffer[ 14 ] ).isHidden = false;
                    ( oam->oamBuffer[ 14 ] ).x = bwdPos[ 1 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 14 ] ).y = bwdPos[ 1 ][ 1 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).x = fwdPos[ 1 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).y = fwdPos[ 1 ][ 1 ] - 16;
                }
                for( int i = 0; i < 3; ++i ) {
                    ( oam->oamBuffer[ 17 + 4 * i ] ).isHidden = false;
                    ( oam->oamBuffer[ 16 + 4 * i ] ).isHidden = false;
                    ( oam->oamBuffer[ 27 + i ] ).isHidden = false;
                    updateOAMSub( oam );
                    consoleSetWindow( &Bottom, 5, 9 + 4 * i, 22, 3 );
                    consoleClear( );
                    printf( _choices[ 3 * page + i ] );
                }
                updateOAMSub( oam );
            }
        }
    } else {
        int page = 0,
            inds[ ] = { 17, 15, 21, 19, 25, 23 };
        for( int i = 0; i < std::min( 6, _num ); ++i ) {
            ( oam->oamBuffer[ inds[ i ] ] ).isHidden = false;
            ( oam->oamBuffer[ inds[ i ] + 1 ] ).isHidden = false;
            updateOAMSub( oam );
            consoleSetWindow( &Bottom, 5 + ( ( i % 2 ) * 12 ), 9 + 4 * ( i / 2 ), 10, 3 );
            printf( _choices[ i ] );
        }
        if( _num > 6 ) {
            ( oam->oamBuffer[ 13 ] ).isHidden = false;
            ( oam->oamBuffer[ 13 ] ).x = fwdPos[ 0 ][ 0 ] - 16;
            ( oam->oamBuffer[ 13 ] ).y = fwdPos[ 0 ][ 1 ] - 16;
        }
        updateOAMSub( oam );
        while( 42 ) {
            swiWaitForVBlank( );
            updateOAMSub( oam );
            if( p_time )
                updateTime( true );
            touchPosition t;
            touchRead( &t );

            for( int i = 0; i < std::min( 6, _num - 6 * page ); ++i ) {
                if( t.px > 31 + ( ( i % 2 ) * 96 ) && t.py > 71 + 32 * ( i / 2 ) && t.px < 225 - ( ( ( i + 1 ) % 2 ) * 96 ) && t.py < 105 + 32 * ( i / 2 ) ) {
                    ( oam->oamBuffer[ inds[ i ] ] ).isHidden = true;
                    ( oam->oamBuffer[ inds[ i ] + 1 ] ).isHidden = true;
                    updateOAMSub( oam );

                    waitForTouchUp( p_time, true );
                    consoleSetWindow( &Bottom, 1, 1, 30, 24 );
                    consoleClear( );
                    return i + 6 * page;
                }
            }

            if( ( page == 0 && sqrt( sq( t.px - fwdPos[ 0 ][ 0 ] ) + sq( t.py - fwdPos[ 0 ][ 1 ] ) ) < 17 ) || ( page && sqrt( sq( t.px - fwdPos[ 1 ][ 0 ] ) + sq( t.py - fwdPos[ 1 ][ 1 ] ) ) < 17 ) ) {

                waitForTouchUp( p_time, true );
                if( ( ++page ) >= ( _num / 6 ) ) {
                    ( oam->oamBuffer[ 13 ] ).isHidden = true;
                    ( oam->oamBuffer[ 14 ] ).isHidden = false;
                    ( oam->oamBuffer[ 14 ] ).x = bwdPos[ 0 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 14 ] ).y = bwdPos[ 0 ][ 1 ] - 16;
                    page = ( _num / 6 );
                } else {
                    ( oam->oamBuffer[ 14 ] ).isHidden = false;
                    ( oam->oamBuffer[ 13 ] ).isHidden = false;
                    ( oam->oamBuffer[ 14 ] ).x = bwdPos[ 1 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 14 ] ).y = bwdPos[ 1 ][ 1 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).x = fwdPos[ 1 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).y = fwdPos[ 1 ][ 1 ] - 16;
                }
                for( int i = 0; i < 6; ++i ) {
                    consoleSetWindow( &Bottom, 5 + ( ( i % 2 ) * 12 ), 9 + 4 * ( i / 2 ), 10, 3 );
                    consoleClear( );
                    if( i < _num - 6 * page ) {
                        ( oam->oamBuffer[ inds[ i ] ] ).isHidden = false;
                        ( oam->oamBuffer[ inds[ i ] + 1 ] ).isHidden = false;
                        printf( _choices[ i + 6 * page ] );
                    } else {
                        ( oam->oamBuffer[ inds[ i ] ] ).isHidden = true;
                        ( oam->oamBuffer[ inds[ i ] + 1 ] ).isHidden = true;
                    }
                    updateOAMSub( oam );
                }
            } else if( ( page == _num / 6 && sqrt( sq( t.px - bwdPos[ 0 ][ 0 ] ) + sq( t.py - bwdPos[ 0 ][ 1 ] ) ) < 17 ) || ( page && sqrt( sq( t.px - bwdPos[ 1 ][ 0 ] ) + sq( t.py - bwdPos[ 1 ][ 1 ] ) ) < 17 ) ) {

                waitForTouchUp( p_time, true );
                if( ( --page ) <= 0 ) {
                    ( oam->oamBuffer[ 14 ] ).isHidden = true;
                    ( oam->oamBuffer[ 13 ] ).isHidden = false;
                    ( oam->oamBuffer[ 13 ] ).x = fwdPos[ 0 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).y = fwdPos[ 0 ][ 1 ] - 16;
                    page = 0;
                } else {
                    ( oam->oamBuffer[ 13 ] ).isHidden = false;
                    ( oam->oamBuffer[ 14 ] ).isHidden = false;
                    ( oam->oamBuffer[ 14 ] ).x = bwdPos[ 1 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 14 ] ).y = bwdPos[ 1 ][ 1 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).x = fwdPos[ 1 ][ 0 ] - 16;
                    ( oam->oamBuffer[ 13 ] ).y = fwdPos[ 1 ][ 1 ] - 16;
                }
                for( int i = 0; i < 6; ++i ) {
                    consoleSetWindow( &Bottom, 5 + ( ( i % 2 ) * 12 ), 9 + 4 * ( i / 2 ), 10, 3 );
                    consoleClear( );
                    if( i < _num - 6 * page ) {
                        ( oam->oamBuffer[ inds[ i ] ] ).isHidden = false;
                        ( oam->oamBuffer[ inds[ i ] + 1 ] ).isHidden = false;
                        printf( _choices[ i + 6 * page ] );
                    } else {
                        ( oam->oamBuffer[ inds[ i ] ] ).isHidden = true;
                        ( oam->oamBuffer[ inds[ i ] + 1 ] ).isHidden = true;
                    }
                    updateOAMSub( oam );
                }
            }
        }
    }
    return -1;
}