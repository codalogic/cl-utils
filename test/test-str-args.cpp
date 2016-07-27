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

#include <string>

#include "clunit.h"

using namespace clutils;

// OutputMumble to test the template expansion variants

class OutputMumble
{
public:
    std::ostream & output( std::ostream & os ) const
    {
        os << "Mumble";
        return os;
    }
};

std::ostream & operator << ( std::ostream & os, const OutputMumble & om )
{
    return om.output( os );
}

// Start of tests

TFEATURE( "str_args - String only" )
{
    TTEST( str_args().expand( "in" ) == "in" );
    TTEST( expand( "in", 18 ) == "in" );
}

TFEATURE( "str_args - %%" )
{
    TTEST( expand( "i%%n", 18 ) == "i%n" );
}

TFEATURE( "str_args - Positional indexing" )
{
    TTEST( expand( "i%0n", 18 ) == "i18n" );
    TTEST( expand( "i%{0}n", 18 ) == "i18n" );
    TTEST( expand( "i%{0:eighteen}n", 18 ) == "i18n" );

    TTEST( expand( "%0in", 18 ) == "18in" );
    TTEST( expand( "%{0}in", 18 ) == "18in" );
    TTEST( expand( "%{0:eighteen}in", 18 ) == "18in" );

    TTEST( expand( "in%0", 18 ) == "in18" );
    TTEST( expand( "in%{0}", 18 ) == "in18" );
    TTEST( expand( "in%{0:eighteen}", 18 ) == "in18" );

    TTEST( expand( "i%{0:eighteen}n%0out", 18 ) == "i18n18out" );

    TTEST( expand( "i%{0:eighteen}n%1out", 18, 19 ) == "i18n19out" );
    TTEST( expand( "i%{1:eighteen}n%0out", 18, 19 ) == "i19n18out" );
}

TFEATURE( "str_args - Big indexes" )
{
    TTEST( expand( "i%{18}n", str_args( 0 ) << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 <<
                                10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 ) == "i18n" );
    TTEST( expand( "i%{18:12}n", str_args( 0 ) << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 <<
                                10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 ) == "i18n" );
    TTEST( expand( "i%{18}%22n", str_args( 0 ) << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 <<
                                10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 ) == "i1822n" );
    TTEST( expand( "i%{18}%{12}n", str_args( 0 ) << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 <<
                                10 << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 ) == "i1812n" );
}

TFEATURE( "str_args - Bad index throws exception" )
{
    // Currently does an assert() if out of range

    //try
    //{
    //    TSETUP( expand( "i%9n", 18 ) ); // %9 is invalid index
    //    TTEST( false );
    //}
    //catch( str_argsOutOfRangeException & )
    //{
    //    TTEST( true );
    //}
}

TFEATURE( "str_args - Expand different types by construction" )
{
    TTEST( expand( "i%0n", 18 ) == "i18n" );
    TTEST( expand( "i%0n", str_args( 18 ) ) == "i18n" );
    TTEST( expand( "i%0n", std::string( "nternationalisatio" ) ) == "internationalisation" );
    TTEST( expand( "i%0n", (char)'c' ) == "icn" );
    TTEST( expand( "i%0n", "nternationalisatio" ) == "internationalisation" );
    TTEST( expand( "i%0n", true ) == "i1n" );
    TTEST( expand( "i%0n", OutputMumble() ) == "iMumblen" );
}

TFEATURE( "str_args - Expand different types by left-shift operator" )
{
    TTEST( expand( "i%0n", str_args() << 18 ) == "i18n" );
    TTEST( expand( "i%0n", str_args() << str_args( 18 ) ) == "i18n" );
    TTEST( expand( "i%0n", str_args() << std::string( "nternationalisatio" ) ) == "internationalisation" );
    TTEST( expand( "i%0n", str_args() << (char)'c' ) == "icn" );
    TTEST( expand( "i%0n", str_args() << "nternationalisatio" ) == "internationalisation" );
    TTEST( expand( "i%0n", str_args() << true ) == "i1n" );
    TTEST( expand( "i%0n", str_args() << OutputMumble() ) == "iMumblen" );

    TTEST( expand( "i%1n", str_args(1) << 18 ) == "i18n" );
    TTEST( expand( "i%1n", str_args(1) << str_args( 18 ) ) == "i18n" );
    TTEST( expand( "i%1n", str_args(1) << std::string( "nternationalisatio" ) ) == "internationalisation" );
    TTEST( expand( "i%1n", str_args(1) << (char)'c' ) == "icn" );
    TTEST( expand( "i%1n", str_args(1) << "nternationalisatio" ) == "internationalisation" );
    TTEST( expand( "i%1n", str_args(1) << true ) == "i1n" );
    TTEST( expand( "i%1n", str_args(1) << OutputMumble() ) == "iMumblen" );
}

TFEATURETODO( "Implement str_args_detail::process_named_long_form_parameter_decl()" )
