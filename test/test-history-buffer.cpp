//----------------------------------------------------------------------------
// Copyright (c) 2017, Codalogic Ltd (http://www.codalogic.com)
// All rights reserved.
//
// The license for this file is based on the BSD-3-Clause license
// (http://www.opensource.org/licenses/BSD-3-Clause).
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// - Neither the name Codalogic Ltd nor the names of its contributors may be
//   used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------------------

#include "cl-utils/history-buffer.h"

#include "clunit.h"

using namespace clutils;

TFEATURE( "HistoryBuffer" )
{
    {
    // Ensure copy construct and assignment
    HistoryBuffer<char> hb( 4 );
    HistoryBuffer<char> hb_copy( hb );
    HistoryBuffer<char> hb_eq( 4 );
    hb_eq = hb;
    }
    {
    TSETUP( HistoryBuffer<char> hb( 4 ) );
    TTEST( ! hb.has_back() );
    TSETUP( hb.push( 'a' ) );
    TTEST( hb.has_back() == false );
    TCRITICALTEST( ! hb.has_back() );
    TTEST( hb.get() == 'a' );
    TTEST( hb.get() == 'a' );
    TTEST( ! hb.has_back() );
    }
    {
    TSETUP( HistoryBuffer<char> hb( 4 ) );
    TTEST( ! hb.has_back() );
    TSETUP( hb.push( 'a' ) );
    TSETUP( hb.push( 'b' ) );
    TTEST( hb.has_back() == true );
    TTEST( hb.get() == 'b' );
    TTEST( hb.get() == 'b' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'a' );
    TTEST( hb.get() == 'a' );
    TTEST( ! hb.has_back() );
    }
    {
    TSETUP( HistoryBuffer<char> hb( 4 ) );
    TTEST( ! hb.has_back() );
    TSETUP( hb.push( 'a' ) );
    TSETUP( hb.push( 'b' ) );
    TTEST( hb.has_back() == true );
    TTEST( hb.get() == 'b' );
    TTEST( hb.get() == 'b' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'a' );
    TTEST( hb.get() == 'a' );
    TTEST( ! hb.has_back() );
    TTEST( hb.has_frwd() == true );
    TSETUP( hb.go_frwd() );
    TTEST( hb.get() == 'b' );
    TTEST( hb.has_frwd() == false );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'a' );
    TTEST( ! hb.has_back() );
    }
    {
    TSETUP( HistoryBuffer<char> hb( 4 ) );
    TTEST( ! hb.has_back() );
    TSETUP( hb.push( 'a' ) );
    TSETUP( hb.push( 'b' ) );
    TTEST( hb.has_back() == true );
    TTEST( hb.get() == 'b' );
    TTEST( hb.get() == 'b' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'a' );
    TTEST( hb.get() == 'a' );
    TTEST( ! hb.has_back() );
    TTEST( hb.has_frwd() == true );
    TSETUP( hb.push( 'c' ) );
    TTEST( hb.has_frwd() == false );
    TTEST( hb.get() == 'c' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'a' );
    TTEST( ! hb.has_back() );
    }
    {
    TSETUP( HistoryBuffer<char> hb( 4 ) );
    TSETUP( hb.push( 'a' ) );
    TSETUP( hb.push( 'b' ) );
    TSETUP( hb.push( 'c' ) );
    TSETUP( hb.push( 'd' ) );
    TTEST( hb.has_back() == true );
    TCRITICALTEST( hb.has_back() );
    TTEST( hb.get() == 'd' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'c' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'b' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'a' );
    TTEST( ! hb.has_back() );
    }
    {
    TSETUP( HistoryBuffer<char> hb( 4 ) );
    TSETUP( hb.push( 'a' ) );
    TSETUP( hb.push( 'b' ) );
    TSETUP( hb.push( 'c' ) );
    TSETUP( hb.push( 'd' ) );
    TSETUP( hb.push( 'e' ) );
    TSETUP( hb.push( 'f' ) );
    TTEST( hb.has_back() == true );
    TCRITICALTEST( hb.has_back() );
    TTEST( hb.get() == 'f' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'e' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'd' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'c' );
    TTEST( ! hb.has_back() );
    }
    {
    TSETUP( HistoryBuffer<char> hb( 4 ) );
    TSETUP( hb.push( 'a' ) );
    TSETUP( hb.push( 'b' ) );
    TSETUP( hb.push( 'c' ) );
    TSETUP( hb.push( 'd' ) );
    TSETUP( hb.push( 'e' ) );
    TSETUP( hb.push( 'f' ) );
    TTEST( hb.has_back() == true );
    TCRITICALTEST( hb.has_back() );
    TTEST( hb.get() == 'f' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'e' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TSETUP( hb.push( 'g' ) );
    TTEST( hb.get() == 'g' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TSETUP( hb.push( 'h' ) );
    TSETUP( hb.push( 'i' ) );
    TTEST( hb.get() == 'i' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'h' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'd' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'c' );
    TTEST( ! hb.has_back() );
    }
    {
    TSETUP( HistoryBuffer<char> hb( 4 ) );
    for( size_t i=0; i<20; ++i )
        hb.push( 'A' + i );
    TSETUP( hb.push( 'a' ) );
    TSETUP( hb.push( 'b' ) );
    TSETUP( hb.push( 'c' ) );
    TSETUP( hb.push( 'd' ) );
    TSETUP( hb.push( 'e' ) );
    TSETUP( hb.push( 'f' ) );
    TTEST( hb.has_back() == true );
    TCRITICALTEST( hb.has_back() );
    TTEST( hb.get() == 'f' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'e' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TSETUP( hb.push( 'g' ) );
    TTEST( hb.get() == 'g' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TSETUP( hb.push( 'h' ) );
    TSETUP( hb.push( 'i' ) );
    TTEST( hb.get() == 'i' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'h' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'd' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'c' );
    TTEST( ! hb.has_back() );
    }
    {
    TSETUP( HistoryBuffer<char> hb( 4 ) );
    for( size_t i=0; i<20; ++i )
        hb.push( 'A' + i );
    TTEST( hb.has_back() );
    TSETUP( hb.push( 'a' ) );
    TSETUP( hb.push( 'b' ) );
    TSETUP( hb.push( 'c' ) );
    TSETUP( hb.push( 'd' ) );
    TTEST( hb.has_back() == true );
    TTEST( hb.get() == 'd' );
    TTEST( hb.get() == 'd' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'c' );
    TTEST( hb.get() == 'c' );
    TTEST( hb.has_back() == true );
    TTEST( hb.has_frwd() == true );
    TSETUP( hb.push( 'e' ) );
    TTEST( hb.has_frwd() == false );
    TTEST( hb.get() == 'e' );
    TSETUP( hb.push( 'f' ) );
    TTEST( hb.has_frwd() == false );
    TTEST( hb.get() == 'f' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'e' );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'c' );
    TCRITICALTEST( hb.has_back() );
    TSETUP( hb.go_back() );
    TTEST( hb.get() == 'b' );
    TTEST( ! hb.has_back() );
    }
}
