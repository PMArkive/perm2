/*
Pokémon neo
------------------------------

file        : mysteryGiftWifi.cpp
author      : Philip Wellnitz
description : Logic for receiving wifi gifts (ov 1)

Copyright (C) 2023 - 2026
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
#include <sys/select.h>

#include <nds.h>
#include <nds/system.h>

#include <dswifi9.h>
#include <netdb.h>
#include <netinet/in.h>
#include <overlay.h>
#include <sys/socket.h>

#include "defines.h"
#include "fs/data.h"
#include "io/message.h"
#include "io/strings.h"
#include "io/uio.h"
#include "ov.h"
#include "save/mysteryGift.h"

#ifdef __cplusplus
extern "C" {
#endif

bool setSocketTimeouts( int p_sock, u32 p_ms ) {
    struct timeval tv{ static_cast<time_t>( p_ms / 1000 ),
                       static_cast<suseconds_t>( ( p_ms % 1000 ) * 1000 ) };
    if( setsockopt( p_sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof( tv ) ) < 0 ) { return false; }
    if( setsockopt( p_sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof( tv ) ) < 0 ) { return false; }
    return true;
}

int selectRecv( int p_sock, char* p_buf, int p_len, u32 p_timeout_ms ) {
    fd_set rfds;
    FD_ZERO( &rfds );
    FD_SET( p_sock, &rfds );
    struct timeval tv{ static_cast<time_t>( p_timeout_ms / 1000 ),
                       static_cast<suseconds_t>( ( p_timeout_ms % 1000 ) * 1000 ) };
    int            sel = select( p_sock + 1, &rfds, nullptr, nullptr, &tv );
    if( sel < 0 ) { return -1; }
    if( sel == 0 ) { return 0; } // timeout
    return recv( p_sock, p_buf, p_len, 0 );
}

bool checkAndDownloadWCInternet( ) {
    // search for wc, download into TMP_WC
    SAVE::TMP_WC = SAVE::wonderCard{ };
    SAVE::message( GET_STRING( IO::STR_UI_SEARCHING_FOR_GIFT ) );

    // Note: This will only ever work for properly configured systems.
    if( !Wifi_InitDefault( WFC_CONNECT ) ) {
        SAVE::message( GET_STRING( IO::STR_UI_WFC_SETUP_FAILED ) );
        IO::waitForInteractS( );
        Wifi_DisableWifi( );
        return false;
    }

    const char*   url          = "neocard-serv.home.arpa";
    const char*   request_text = "GET / HTTP/1.1\r\n"
                                 "Host: localhost\r\n"
                                 "User-Agent: Nintendo DS\r\n"
                                 "Accept: */*\r\n"
                                 "Connection: close\r\n\r\n";
    constexpr u32 port         = 8000;

    // Create a TCP socket
    int my_socket = socket( AF_INET, SOCK_STREAM, 0 );
    if( my_socket < 0 ) {
#ifdef DESQUID
        SAVE::message( "(Socket creation failed.)" );
#else
        SAVE::message( GET_STRING( IO::STR_UI_WFC_SETUP_FAILED ) );
#endif
        IO::waitForInteractS( );
        Wifi_DisableWifi( );
        return false;
    }

    if( !setSocketTimeouts( my_socket, 5000 ) ) {
        closesocket( my_socket );
#ifdef DESQUID
        SAVE::message( "(Setting socket timeout failed.)" );
#else
        SAVE::message( GET_STRING( IO::STR_UI_WFC_SETUP_FAILED ) );
#endif
        IO::waitForInteractS( );
        Wifi_DisableWifi( );
        return false;
    }

    // Find the IP address of the server, with gethostbyname
    struct hostent* myhost = gethostbyname( url );
    if( !myhost || !myhost->h_addr_list[ 0 ] ) {
#ifdef DESQUID
        SAVE::message( "(DNS lookup failed.)" );
#else
        SAVE::message( GET_STRING( IO::STR_UI_WFC_SETUP_FAILED ) );
#endif
        IO::waitForInteractS( );
        Wifi_DisableWifi( );
        return false;
    }

    // Tell the socket to connect to the IP address we found
    struct sockaddr_in sain{ };
    sain.sin_family      = AF_INET;
    sain.sin_port        = htons( port );
    sain.sin_addr.s_addr = *( (u32*) ( myhost->h_addr_list[ 0 ] ) );
    if( connect( my_socket, (struct sockaddr*) &sain, sizeof( sain ) ) < 0 ) {
        closesocket( my_socket );

#ifdef DESQUID
        SAVE::message( "(Connection failed / timed out.)" );
#else
        SAVE::message( GET_STRING( IO::STR_UI_WFC_SETUP_FAILED ) );
#endif
        IO::waitForInteractS( );
        Wifi_DisableWifi( );
        return false;
    }

    // send our request
    if( send( my_socket, request_text, strlen( request_text ), 0 ) < 0 ) {
        closesocket( my_socket );

#ifdef DESQUID
        SAVE::message( "(Request failed.)" );
#else
        SAVE::message( GET_STRING( IO::STR_UI_WFC_SERVER_ERROR ) );
#endif
        IO::waitForInteractS( );
        Wifi_DisableWifi( );
        return false;
    }

    constexpr u32 BUF_SIZE = 512;
    char          incoming_buffer[ BUF_SIZE ];
    int           recvd_len  = 0;
    bool          got_header = false;
    bool          got_body   = false;
    const char    endm[ 5 ]  = "\r\n\r\n";

    while( recvd_len < (int) BUF_SIZE - 1 ) {
        int n
            = selectRecv( my_socket, incoming_buffer + recvd_len, BUF_SIZE - 1 - recvd_len, 5000 );
        if( n <= 0 ) { break; }
        recvd_len += n;

        if( !got_header ) {
            for( int i = 0; i + 3 < recvd_len; ++i ) {
                if( incoming_buffer[ i ] == endm[ 0 ] && incoming_buffer[ i + 1 ] == endm[ 1 ]
                    && incoming_buffer[ i + 2 ] == endm[ 2 ]
                    && incoming_buffer[ i + 3 ] == endm[ 3 ] ) {
                    // body starts at i+4
                    int bodyLen = recvd_len - ( i + 4 );
                    if( bodyLen >= (int) sizeof( SAVE::wonderCard ) ) {
                        memcpy( &SAVE::TMP_WC, incoming_buffer + i + 4,
                                sizeof( SAVE::wonderCard ) );
                        got_body = true;
                    }
                    got_header = true;
                    break;
                }
            }
            if( got_header ) { break; }
        }
    }

    shutdown( my_socket, SHUT_RDWR );
    closesocket( my_socket );
    for( u8 k = 0; k < 250; ++k ) { swiWaitForVBlank( ); }

    Wifi_DisableWifi( );
    return got_body && SAVE::TMP_WC.m_type != SAVE::WCTYPE_NONE;
}

#ifdef __cplusplus
}
#endif
