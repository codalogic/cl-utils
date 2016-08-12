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

#include "cl-utils/str-convert.h"

#include <string>

#include "clunit.h"

using namespace clutils;

TFEATURE( "convert - Unchecked from_string()" )
{
    TTEST( from_string<int>( "123" ) == 123 );
    TTEST( from_string<int>( "   123" ) == 123 );

    TTEST( from_string<float>( "123.5" ) == 123.5 );

    TTEST( from_string<bool>( "false" ) == false );
    TTEST( from_string<bool>( "False" ) == false );
    TTEST( from_string<bool>( "FALSE" ) == false );
    TTEST( from_string<bool>( "true" ) == true );
    TTEST( from_string<bool>( "True" ) == true );
    TTEST( from_string<bool>( "TRUE" ) == true );
    TTEST( from_string<bool>( "0" ) == false );
    TTEST( from_string<bool>( "1" ) == true );

    TTEST( from_string<bool>( "   false" ) == false );
    TTEST( from_string<bool>( "   true" ) == true );
    TTEST( from_string<bool>( "   0" ) == false );
    TTEST( from_string<bool>( "   1" ) == true );

    // Error cases
    TTEST( from_string<int>( "foo" ) == 0 );
}

TFEATURE( "convert - Checked from_string()" )
{
    int iout;

    TTEST( from_string( iout, "123" ) == true );
    TTEST( iout == 123 );
    TTEST( from_string( iout, "   123" ) == true );
    TTEST( iout == 123 );

    float fout;

    TTEST( from_string( fout, "123.5" ) == true );
    TTEST( fout == 123.5 );

    bool bout;

    TTEST( from_string( bout, "false" ) == true );
    TTEST( bout == false );
    TTEST( from_string( bout, "False" ) == true );
    TTEST( bout == false );
    TTEST( from_string( bout, "FALSE" ) == true );
    TTEST( bout == false );
    TTEST( from_string( bout, "true" ) == true );
    TTEST( bout == true );
    TTEST( from_string( bout, "True" ) == true );
    TTEST( bout == true );
    TTEST( from_string( bout, "TRUE" ) == true );
    TTEST( bout == true );
    TTEST( from_string( bout, "0" ) == true );
    TTEST( bout == false );
    TTEST( from_string( bout, "1" ) == true );
    TTEST( bout == true );

    TTEST( from_string( bout, "   false" ) == true );
    TTEST( bout == false );
    TTEST( from_string( bout, "   true" ) == true );
    TTEST( bout == true );
    TTEST( from_string( bout, "   0" ) == true );
    TTEST( bout == false );
    TTEST( from_string( bout, "   1" ) == true );
    TTEST( bout == true );

    TTEST( from_string( iout, "foo" ) == false );
    TTEST( from_string( bout, "foo" ) == false );
}

TFEATURE( "convert - to_string()" )
{
    TTEST( to_string( "foo" ) == "foo" );
    TTEST( to_string( 123 ) == "123" );
    TTEST( to_string( 123.5 ) == "123.5" );

    TTEST( to_string( 0 ) == "0" );
    TTEST( to_string( 1 ) == "1" );

    TTEST( to_string( true ) == "true" );
    TTEST( to_string( false ) == "false" );
}
