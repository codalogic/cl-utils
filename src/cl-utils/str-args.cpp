//----------------------------------------------------------------------------
// Copyright (c) 2016, Codalogic Ltd (http://www.codalogic.com)
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

#include "cl-utils/str-args.h"

#include <cassert>

namespace clutils {

std::string * str_args::expand_append( std::string * p_out, const char * format ) const
{
    try
    {
        p_out->reserve( p_out->size() + strlen( format ) );
        for( size_t i=0; format[i] != '\0'; ++i )
        {
            if( format[i] != '%' )
                p_out->append( 1, format[i] );

            else
            {
                ++i;
                if( format[i] != '\0' )
                {
                    if( format[i] == '%' )  // %% -> %
                        p_out->append( 1, '%' );
                    else if( format[i] >= '0' && format[i] <= '9' )
                        p_out->append( args.at( format[i] - '0' ) );
                    else if( format[i] == '{' )
                    {
                        // Long form %{0:a description}
                        ++i;
                        if( format[i] != '\0' )
                        {
                            if( format[i] >= '0' && format[i] <= '9' )
                            {
                                size_t index = 0;
                                while( format[i] >= '0' && format[i] <= '9' )
                                    index = 10 * index + format[i++] - '0';
                                p_out->append( args.at( index ) );
                                for( ; format[i] != '\0' && format[i] != '}'; ++i )
                                {}  // Skip over rest of characters in format specifier
                            }
                            else
                            {
                                #ifndef TEST_ILL_FORMED_LONG_FORM_ARGS
                                    assert( 0 );    // Decided that ill-formed long form args (e.g. %{mumbo} should not be supported
                                #endif
                                p_out->append( "%{" );
                                p_out->append( 1, format[i] );
                            }
                        }
                    }
                    else
                    {
                        // % followed by non-digit allows for setting and using
                        // macro arguments, such as:
                        // l_output.generate( p_item, "^ with [arg => %0] ?The arg is ^%arg$$", 1 );
                        p_out->append( 1, '%' );
                        p_out->append( 1, format[i] );
                    }
                }
            }
        }

        return p_out;
    }

    catch( std::out_of_range & )
    {
        assert( 0 ); // We've done something like %1 in our args string when args[1] doesn't exist.  N.B. args are 0 based.

        throw str_argsOutOfRangeException( "str_args args[] index out of range" );
    }
}

}   // namespace clutils
