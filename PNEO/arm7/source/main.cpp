/*
Pokémon neo
------------------------------

file        : main.cpp
author      : Philip Wellnitz (modifications)
description :

Copyright (C) 2012 - 2026
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

/*---------------------------------------------------------------------------------

default ARM7 core

Copyright (C) 2005 - 2010
Michael Noland (joat)
Jason Rogers (dovoto)
Dave Murphy (WinterMute)

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1.	The origin of this software must not be misrepresented; you
must not claim that you wrote the original software. If you use
this software in a product, an acknowledgment in the product
documentation would be appreciated but is not required.

2.	Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3.	This notice may not be removed or altered from any source
distribution.

---------------------------------------------------------------------------------*/
#include <dswifi7.h>
#include <nds.h>
#ifndef NO_SOUND
#include "sound/sseq.h"
#endif

#define FADE_SPEED          9
#define FADE_TICK_INTERVAL  2
#define WIFI_POLL_INTERVAL  1
#define INPUT_POLL_INTERVAL 1

static volatile bool EXIT_FLAG   = false;
static volatile bool WIFI_DIRTY  = false;
static volatile bool INPUT_DIRTY = false;
static volatile u32  VBLANK_CNT  = 0;

void VblankHandler( ) {
    // below sadly doesn't work with current libnds version (gives linker error / -latomic
    // not available)
    // __atomic_fetch_add( &VBLANK_CNT, 1, __ATOMIC_RELAXED );
    __atomic_store_n( &VBLANK_CNT, __atomic_load_n( &VBLANK_CNT, __ATOMIC_RELAXED ) + 1,
                      __ATOMIC_RELAXED );
    __atomic_store_n( &WIFI_DIRTY, true, __ATOMIC_RELEASE );
}

void VcountHandler( ) {
    __atomic_store_n( &INPUT_DIRTY, true, __ATOMIC_RELEASE );
}

void powerButtonCB( ) {
    __atomic_store_n( &EXIT_FLAG, true, __ATOMIC_RELEASE );
}

void soundInit( ) {
    powerOn( POWER_SOUND );
    REG_SOUNDCNT = SOUND_ENABLE;
    writePowerManagement( PM_CONTROL_REG, ( readPowerManagement( PM_CONTROL_REG ) & ~PM_SOUND_MUTE )
                                              | PM_SOUND_AMP );
    REG_MASTER_VOLUME = 127;
}

#ifndef NO_SOUND
static void processFade( ) {
    u32 status = __atomic_load_n( &SOUND::SSEQ::XA_SEQ_STATUS, __ATOMIC_ACQUIRE );

    if( status == SOUND::SSEQ::STATUS_FADE_OUT ) {
        u32 vol = __atomic_load_n( &SOUND::SSEQ::XA_ADSR_MASTER_VOLUME, __ATOMIC_ACQUIRE );
        if( !vol ) { return; }
        u32 next = ( vol <= FADE_SPEED ) ? 0 : ( vol - FADE_SPEED );
        __atomic_store_n( &SOUND::SSEQ::XA_ADSR_MASTER_VOLUME, next, __ATOMIC_RELEASE );
        if( !next ) { SOUND::SSEQ::stopSequence( ); }
    } else if( status == SOUND::SSEQ::STATUS_FADE_IN ) {
        u32 vol    = __atomic_load_n( &SOUND::SSEQ::XA_ADSR_MASTER_VOLUME, __ATOMIC_ACQUIRE );
        u32 target = __atomic_load_n( &SOUND::SSEQ::XA_ADSR_FADE_TARGET_VOLUME, __ATOMIC_ACQUIRE );
        if( vol >= target ) { return; }
        u32 next = ( vol + FADE_SPEED >= target ) ? target : ( vol + FADE_SPEED );
        __atomic_store_n( &SOUND::SSEQ::XA_ADSR_MASTER_VOLUME, next, __ATOMIC_RELEASE );
        if( next == target ) { SOUND::SSEQ::setSequenceStatus( SOUND::SSEQ::STATUS_PLAYING ); }
    }
}
#endif

int main( ) {
    readUserSettings( );
    ledBlink( 0 );

    irqInit( );
    initClockIRQ( );
    fifoInit( );
    touchInit( );

#ifndef NO_SOUND
    soundInit( );
    SOUND::SSEQ::installSoundSys( );
#endif

    SetYtrigger( 80 );

    installWifiFIFO( );
    installSoundFIFO( );

    installSystemFIFO( );

    irqSet( IRQ_VCOUNT, VcountHandler );
    irqSet( IRQ_VBLANK, VblankHandler );

    irqEnable( IRQ_VBLANK | IRQ_VCOUNT | IRQ_NETWORK );

    setPowerButtonCB( powerButtonCB );

    while( !__atomic_load_n( &EXIT_FLAG, __ATOMIC_ACQUIRE ) ) {
        if( 0 == ( REG_KEYINPUT & ( KEY_SELECT | KEY_START | KEY_L | KEY_R ) ) ) {
            __atomic_store_n( &EXIT_FLAG, true, __ATOMIC_RELEASE );
            break;
        }

        swiWaitForVBlank( );

        // WIFI_DIRTY / INPUT_DIRTY are set-to-true-only by IRQ handlers.
        // A read-then-clear is safe on single-core ARM7: the worst case
        // is one redundant update call, never a missed one.
        if( WIFI_DIRTY ) {
            WIFI_DIRTY = false;
            Wifi_Update( );
        }
        if( INPUT_DIRTY ) {
            INPUT_DIRTY = false;
            inputGetAndSend( );
        }

#ifndef NO_SOUND
        if( ( __atomic_load_n( &VBLANK_CNT, __ATOMIC_RELAXED ) % FADE_TICK_INTERVAL ) == 0 ) {
            processFade( );
        }
#endif
    }
    return 0;
}
