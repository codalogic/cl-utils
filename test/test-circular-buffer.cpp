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

#include "cl-utils/circular-buffer.h"

#include "clunit.h"

using namespace clutils;

TFEATURE( "CircularBuffer" )
{
    {
    // Ensure copy construct and assignment
    CircularBuffer<char> cb( 4 );
    CircularBuffer<char> cb_copy( cb );
    CircularBuffer<char> cb_eq( 4 );
    cb_eq = cb;
    }
    {
    TSETUP( CircularBuffer<char> cb( 4 ) );
    TTEST( cb.empty() );
    TSETUP( cb.push( 'a' ) );
    TTEST( cb.empty() == false );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'a' );
    TTEST( cb.top() == 'a' );
    TSETUP( cb.pop() );
    TTEST( cb.empty() );
    }
    {
    TSETUP( CircularBuffer<char> cb( 4 ) );
    TTEST( cb.empty() );
    TSETUP( cb.push( 'a' ) );
    TSETUP( cb.push( 'b' ) );
    TTEST( cb.empty() == false );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'b' );
    TTEST( cb.top() == 'b' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'a' );
    TTEST( cb.top() == 'a' );
    TSETUP( cb.pop() );
    TTEST( cb.empty() );
    }
    {
    TSETUP( CircularBuffer<char> cb( 4 ) );
    TSETUP( cb.push( 'a' ) );
    TSETUP( cb.push( 'b' ) );
    TSETUP( cb.push( 'c' ) );
    TSETUP( cb.push( 'd' ) );
    TTEST( cb.empty() == false );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'd' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'c' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'b' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'a' );
    TSETUP( cb.pop() );
    TTEST( cb.empty() );
    }
    {
    TSETUP( CircularBuffer<char> cb( 4 ) );
    TSETUP( cb.push( 'a' ) );
    TSETUP( cb.push( 'b' ) );
    TSETUP( cb.push( 'c' ) );
    TSETUP( cb.push( 'd' ) );
    TSETUP( cb.push( 'e' ) );
    TSETUP( cb.push( 'f' ) );
    TTEST( cb.empty() == false );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'f' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'e' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'd' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'c' );
    TSETUP( cb.pop() );
    TTEST( cb.empty() );
    }
    {
    TSETUP( CircularBuffer<char> cb( 4 ) );
    TSETUP( cb.push( 'a' ) );
    TSETUP( cb.push( 'b' ) );
    TSETUP( cb.push( 'c' ) );
    TSETUP( cb.push( 'd' ) );
    TSETUP( cb.push( 'e' ) );
    TSETUP( cb.push( 'f' ) );
    TTEST( cb.empty() == false );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'f' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'e' );
    TSETUP( cb.pop() );
    TSETUP( cb.push( 'g' ) );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'g' );
    TSETUP( cb.pop() );
    TSETUP( cb.push( 'h' ) );
    TSETUP( cb.push( 'i' ) );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'i' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'h' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'd' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'c' );
    TSETUP( cb.pop() );
    TTEST( cb.empty() );
    }
    {
    TSETUP( CircularBuffer<char> cb( 4 ) );
    for( size_t i=0; i<20; ++i )
        cb.push( 'A' + i );
    TSETUP( cb.push( 'a' ) );
    TSETUP( cb.push( 'b' ) );
    TSETUP( cb.push( 'c' ) );
    TSETUP( cb.push( 'd' ) );
    TSETUP( cb.push( 'e' ) );
    TSETUP( cb.push( 'f' ) );
    TTEST( cb.empty() == false );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'f' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'e' );
    TSETUP( cb.pop() );
    TSETUP( cb.push( 'g' ) );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'g' );
    TSETUP( cb.pop() );
    TSETUP( cb.push( 'h' ) );
    TSETUP( cb.push( 'i' ) );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'i' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'h' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'd' );
    TSETUP( cb.pop() );
    TCRITICALTEST( ! cb.empty() );
    TTEST( cb.top() == 'c' );
    TSETUP( cb.pop() );
    TTEST( cb.empty() );
    }
}
