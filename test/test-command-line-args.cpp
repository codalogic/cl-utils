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

#include "cl-utils/command-line-args.h"

#include "clunit.h"

using namespace clutils;

#define N( av ) (sizeof( av ) / sizeof( av[0] ))
#define SIZED_ARGV( x ) N( x ), x

bool is_fake_help_run = false;
void fake_help()
{
    is_fake_help_run = true;
}

char * argv_none[] = {    // `char * []` is the type passed into main(), so test this compiles OK
    const_cast<char *>("Prog name - unused")
    };

const char * argv_help[] = {
    "Prog name - unused",
    "-?"
    };

const char * argv_file_names[] = {
    "Prog name - unused",
    "my-file.txt",
    "my-other-file.txt"
    };

const char * argv_flag_and_single_file_name[] = {
    "Prog name - unused",
    "-o",
    "my-file.txt"
    };

const char * argv_flag_and_file_names[] = {
    "Prog name - unused",
    "-o",
    "my-file.txt",
    "my-other-file.txt"
    };

const char * argv_long_flag_and_file_names[] = {
    "Prog name - unused",
    "-output",
    "my-file.txt",
    "my-other-file.txt"
    };

const char * argv_double_dash_flag_and_file_names[] = {
    "Prog name - unused",
    "--output",
    "my-file.txt",
    "my-other-file.txt"
    };


TFEATURE( "CommandLineArgs" )
{
    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_none ) ) );
    TTEST( cla == false );
    TTEST( cla.empty() );
    }

    {
    TSETUP( is_fake_help_run = false );
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_none ), fake_help ) );
    TTEST( is_fake_help_run == true );
    TTEST( cla.empty() );
    }

    // Test resilience to calling next() too many times
    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_none ) ) );
    TTEST( cla.empty() );
    TSETUP( cla.next() );
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_help ) ) );
    TTEST( cla == true );
    TTEST( ! cla.empty() );
    TTEST( cla.is_flag() );
    TTEST( cla.is_flag( "?" ) );
    TTEST( cla.is_flag( "h", "?" ) );
    TTEST( cla.is_flag( "?", "h" ) );
    TTEST( cla.flag_marker() == std::string( "-" ) );
    TTEST( cla.flag_name() == std::string( "?" ) );
    TTEST( cla.flag() == "-?" );
    TTEST( cla.is_flag( "other" ) == false );
    TSETUP( cla.next() );
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_file_names ) ) );
    TTEST( cla == true );
    TTEST( ! cla.empty() );
    TTEST( cla.is_flag() == false );
    TTEST( cla.current() == std::string( "my-file.txt" ) );
    TTEST( cla.flag_marker() == std::string( "" ) );
    TTEST( cla.flag_name() == std::string( "" ) );
    TTEST( cla.flag() == "" );
    TSETUP( cla.next() );
    TTEST( ! cla.empty() );
    TTEST( cla.current() == std::string( "my-other-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( cla.empty() );
    }

    {
    // Test for sufficient rigor of flag testing
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_file_names ) ) );
    TTEST( cla == true );
    TTEST( ! cla.empty() );
    TTEST( cla.is_flag() == false );
    TTEST( cla.is_flag( "y-file.txt" ) == false );
    TTEST( cla.is_flag( "xmy-file.txt" ) == false );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_flag_and_single_file_name ) ) );
    TTEST( cla == true );
    TTEST( ! cla.empty() );
    TTEST( cla.is_flag() );
    TTEST( cla.is_flag( "o" ) );
    TTEST( cla.flag_marker() == std::string( "-" ) );
    TTEST( cla.flag_name() == std::string( "o" ) );
    TTEST( cla.flag() == "-o" );
    TTEST( cla.is_flag( "o", 0 ) );
    TTEST( cla.is_flag( "o", 1 ) );
    TTEST( cla.next() == std::string( "my-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_flag_and_single_file_name ) ) );
    TTEST( cla.is_flag( "o", 2 ) == false );  // Test sufficient arguments check
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_flag_and_file_names ) ) );
    TTEST( cla == true );
    TTEST( ! cla.empty() );
    TTEST( cla.is_flag() );
    TTEST( cla.is_flag( "o", 1 ) );
    TTEST( cla.next() == std::string( "my-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( ! cla.empty() );
    TTEST( cla.current() == std::string( "my-other-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_long_flag_and_file_names ) ) );
    TTEST( cla == true );
    TTEST( ! cla.empty() );
    TTEST( cla.is_flag() );
    TTEST( cla.is_flag( "output", 1 ) );
    TTEST( cla.flag_marker() == std::string( "-" ) );
    TTEST( cla.flag_name() == std::string( "output" ) );
    TTEST( cla.flag() == "-output" );
    TTEST( cla.next() == std::string( "my-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( ! cla.empty() );
    TTEST( cla.current() == std::string( "my-other-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_long_flag_and_file_names ) ) );
    TTEST( cla == true );
    TTEST( ! cla.empty() );
    TTEST( cla.is_flag() );
    TTEST( cla.is_flag( "o", "output", 1 ) );
    TTEST( cla.next() == std::string( "my-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( ! cla.empty() );
    TTEST( cla.current() == std::string( "my-other-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_double_dash_flag_and_file_names ) ) );
    TTEST( cla == true );
    TTEST( ! cla.empty() );
    TTEST( cla.is_flag() );
    TTEST( cla.is_flag( "o", "output", 1 ) );
    TTEST( cla.flag_marker() == std::string( "--" ) );
    TTEST( cla.flag_name() == std::string( "output" ) );
    TTEST( cla.flag() == "--output" );
    TTEST( cla.next() == std::string( "my-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( ! cla.empty() );
    TTEST( cla.current() == std::string( "my-other-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_flag_and_file_names ) ) );
    TTEST( cla == true );
    TTEST( ! cla.empty() );
    TTEST( cla.is_flag( "o" ) );
    TTEST( cla.ensure( 2, "-o flag requires 2 parameters" ) );
    TTEST( cla.is_flag( "o", 2, "-o flag requires 2 parameters" ) );
    TTEST( cla.next() == std::string( "my-file.txt" ) );
    TTEST( cla.next() == std::string( "my-other-file.txt" ) );
    TSETUP( cla.next() );
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_flag_and_file_names ) ) );
    TTEST( cla );
    TTEST( cla.is_flag( "o" ) );
    TTEST( cla.ensure( 3 ) == false );  // Test sufficient arguments check
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_flag_and_file_names ) ) );
    TTEST( cla );
    TTEST( cla.is_flag( "o", 3 ) == false );  // Test sufficient arguments check
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_flag_and_file_names ) ) );
    TTEST( cla );
    TTEST( cla.is_flag( "o" ) );
    TTEST( cla.ensure( 3, "-o flag requires 3 parameters" ) == false );  // Test sufficient arguments check
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_flag_and_file_names ) ) );
    TTEST( cla );
    TTEST( cla.is_flag( "o", 3, "-o flag requires 3 parameters" ) == false );  // Test sufficient arguments check
    TTEST( cla.empty() );
    }

    {
    TSETUP( CommandLineArgs cla( SIZED_ARGV( argv_help ) ) );
    TTEST( cla );
    TTEST( cla.ensure( 1 ) == false );  // Test sufficient arguments check
    TTEST( cla.empty() );
    }
}
