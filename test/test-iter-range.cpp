//----------------------------------------------------------------------------
// Copyright (c) 2015, Codalogic Ltd (http://www.codalogic.com)
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

#include "cl-utils/iter-range.h"

#include "clunit.h"

#include <vector>
#include <string>

using namespace clutils;

TFEATURE( "iter_range" )
{
    typedef std::vector< std::string > container_t;
    container_t v;
    v.push_back( "0" );
    v.push_back( "1" );
    v.push_back( "2" );

    iter_range< container_t > ir( v );
    TTEST( ir );
    TTEST( *ir == "0" );
    TTEST( ir->at(0) == '0' );
    ++ir;
    TTEST( ir );
    TTEST( *ir == "1" );
    TTEST( ir->at(0) == '1' );
    ++ir;
    TTEST( ir );
    TTEST( *ir == "2" );
    TTEST( ir->at(0) == '2' );
    ++ir;
    TTEST( ! ir );
}

TFEATURE( "const_iter_range" )
{
    {
    typedef std::vector< std::string > container_t;
    container_t v;
    v.push_back( "0" );
    v.push_back( "1" );
    v.push_back( "2" );

    const_iter_range< container_t > ir( v );
    TTEST( ir );
    TTEST( *ir == "0" );
    TTEST( ir->at(0) == '0' );
    ++ir;
    TTEST( ir );
    TTEST( *ir == "1" );
    TTEST( ir->at(0) == '1' );
    ++ir;
    TTEST( ir );
    TTEST( *ir == "2" );
    TTEST( ir->at(0) == '2' );
    ++ir;
    TTEST( ! ir );
    }

    {
    // From const container
    typedef std::vector< std::string > container_t;
    container_t vs;
    vs.push_back( "0" );
    vs.push_back( "1" );
    vs.push_back( "2" );
    const container_t v( vs );

    const_iter_range< container_t > ir( v );
    TTEST( ir );
    TTEST( *ir == "0" );
    TTEST( ir->at(0) == '0' );
    ++ir;
    TTEST( ir );
    TTEST( *ir == "1" );
    TTEST( ir->at(0) == '1' );
    ++ir;
    TTEST( ir );
    TTEST( *ir == "2" );
    TTEST( ir->at(0) == '2' );
    ++ir;
    TTEST( ! ir );
    }
}

TFEATURE( "iter_range example in loop" )
{
    typedef std::vector< std::string > container_t;
    container_t my_container;
    my_container.push_back( "0" );
    my_container.push_back( "1" );
    my_container.push_back( "2" );

    // With iter_range
    size_t total_string_length = 0;
    for( const_iter_range< container_t > ir( my_container ); ir; ++ir )
        total_string_length += ir->size();
    TTEST( total_string_length == 3 );

    // Vs. With normal iterators
    total_string_length = 0;
    for( container_t::const_iterator i( my_container.begin() ), end( my_container.end() ); i != end; ++i )
        total_string_length += i->size();
    TTEST( total_string_length == 3 );
}
