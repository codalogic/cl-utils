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

//----------------------------------------------------------------------------
// CircularBuffer implementes a circular buffer.  It is stack-like in
// behaviour in that you can `push` data onto the top of it, look at the `top`
// and `pop` stuff from the top.  However, once the buffer is full, when you
// push stuff onto the top of the stack, the item at the bottom of the stack
// is discarded.
//----------------------------------------------------------------------------

#ifndef CL_UTILS__CIRCULAR_BUFFER
#define CL_UTILS__CIRCULAR_BUFFER

#include <vector>
#include <cassert>

namespace clutils {

template< typename T >
class CircularBuffer
{
private:
    struct Members {
        std::vector< T > buffer;
        size_t top;     // top points to the next free location. i.e. one above the active top of the stack
        size_t bottom;
        Members() : top( 0 ), bottom( 0 ) {}
    } m;

public:
    CircularBuffer( size_t buffer_size )
    {
        m.buffer.reserve( buffer_size + 1 );    // We use an extra place, so when the buffer has buffer_size members we can tell if it's full or empty
    }
    bool empty() const { return m.top == m.bottom; }
    void push( const T & v )
    {
        if( m.buffer.size() < m.buffer.capacity() )
            m.buffer.push_back( v );
        else
            m.buffer[m.top] = v;
        m.top = (m.top + 1) % m.buffer.capacity();
        if( m.top == m.bottom )
            m.bottom = (m.bottom + 1) % m.buffer.capacity();
    }
    const T & top() const
    {
        assert( ! empty() );
        if( m.top == 0 )    // Can't use modulo arithmetic when doing unsigned subtraction
            return m.buffer[m.buffer.capacity() - 1];
        else
            return m.buffer[m.top - 1];
    }
    void pop()
    {
        assert( ! empty() );
        if( ! empty() )
        {
            if( m.top == 0 )    // Can't use modulo arithmetic when doing unsigned subtraction
                m.top = m.buffer.capacity() - 1;
            else
                --m.top;
        }
    }
};

} // namespace clutils

#endif // CL_UTILS__CIRCULAR_BUFFER
