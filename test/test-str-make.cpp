//----------------------------------------------------------------------------
// Copyright (c) 2018, Codalogic Ltd (http://www.codalogic.com)
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

#include "cl-utils/str-make.h"

#include "clunit.h"

using namespace clutils;

TFEATURE( "str-make" )
{
    {
    std::string my_string = str_make( "Test" ) << "Time" << 2 << 3.5 << true << false;
    TTEST( my_string == "TestTime23.5truefalse" );
    TTEST( std::string( str_make( "Test" ) << 3 << 4.5 << true << false ) == "Test34.5truefalse" );
    }
    {
    str_make sm1( "Test" ); sm1 << 3.5;
    str_make sm2( "Pass" ); sm2 << true;
    sm1 << sm2;
    TTEST( sm1.to_string() == "Test3.5Passtrue" );
    }
    {
    str_make sm1( "Test" ); sm1 << 3.5;
    str_make sm2( sm1 );
    TTEST( sm2.to_string() == "Test3.5" );
    }
    {
    str_make sm1( "Test" ); sm1 << 3.5;
    str_make sm2( "Pass" ); sm2 << true;
    sm2 = sm1;
    TTEST( sm2.to_string() == "Test3.5" );
    }
}
