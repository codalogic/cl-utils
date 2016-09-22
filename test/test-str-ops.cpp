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

#include "cl-utils/str-ops.h"

#include <string>

#include "clunit.h"

using namespace clutils;

TFEATURE( "[lr]?trim - copy" )
{
    TTEST( ltrim( "" ) == "" );
    TTEST( ltrim( "  " ) == "" );
    TTEST( ltrim( "  x" ) == "x" );
    TTEST( ltrim( "\r\n \t\v\fxy" ) == "xy" );
    TTEST( ltrim( "  x  " ) == "x  " );
    TTEST( ltrim( "abx", "ab" ) == "x" );

    TTEST( rtrim( "" ) == "" );
    TTEST( rtrim( "  " ) == "" );
    TTEST( rtrim( "x  " ) == "x" );
    TTEST( rtrim( "xy\r\n \t\v\f" ) == "xy" );
    TTEST( rtrim( "  x  " ) == "  x" );
    TTEST( rtrim( "xab", "ab" ) == "x" );

    TTEST( trim( "" ) == "" );
    TTEST( trim( "  " ) == "" );
    TTEST( trim( "x  " ) == "x" );
    TTEST( trim( "\r\n \t\v\fxy\r\n \t\v\f" ) == "xy" );
    TTEST( trim( "  x  " ) == "x" );
    TTEST( trim( "abxab", "ab" ) == "x" );
}

void test_in_place_ltrim( const char * in, const char * out )
{
    std::string s( in );
    TTEST( ltrim( &s ) == out );
    TTEST( s == out );
}

void test_in_place_rtrim( const char * in, const char * out )
{
    std::string s( in );
    TTEST( rtrim( &s ) == out );
    TTEST( s == out );
}

void test_in_place_trim( const char * in, const char * out )
{
    std::string s( in );
    TTEST( trim( &s ) == out );
    TTEST( s == out );
}

TFEATURE( "[lr]?trim - in-place" )
{
    TCALL( test_in_place_ltrim( "", "" ) );
    TCALL( test_in_place_ltrim( "  ", "" ) );
    TCALL( test_in_place_ltrim( "  x", "x" ) );
    TCALL( test_in_place_ltrim( "\r\n \t\v\fxy", "xy" ) );
    TCALL( test_in_place_ltrim( "  x  ", "x  " ) );

    TCALL( test_in_place_rtrim( "", "" ) );
    TCALL( test_in_place_rtrim( "  ", "" ) );
    TCALL( test_in_place_rtrim( "x  ", "x" ) );
    TCALL( test_in_place_rtrim( "xy\r\n \t\v\f", "xy" ) );
    TCALL( test_in_place_rtrim( "  x  ", "  x" ) );

    TCALL( test_in_place_trim( "", "" ) );
    TCALL( test_in_place_trim( "  ", "" ) );
    TCALL( test_in_place_trim( "x  ", "x" ) );
    TCALL( test_in_place_trim( "\r\n \t\v\fxy\r\n \t\v\f", "xy" ) );
    TCALL( test_in_place_trim( "  x  ", "x" ) );
}
