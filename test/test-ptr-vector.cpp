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

#include "cl-utils/ptr-vector.h"

#include <string>

#include "clunit.h"

using namespace clutils;

TFEATURE( "ptr_vector - create, push_back" )
{
    ptr_vector< std::string > pv;
    TTEST( pv.size() == 0 );
    TTEST( pv.empty() );

    // Test can store a single member
    pv.push_back( "s0" );
    TTEST( pv.size() == 1 );
    TTEST( ! pv.empty() );
    TTEST( pv[0] == "s0" );
    TTEST( pv.at(0) == "s0" );

    // Test can store two independent members
    pv.push_back( "s1" );
    TTEST( pv.size() == 2 );
    TTEST( ! pv.empty() );
    TTEST( pv[0] == "s0" );
    TTEST( pv.at(0) == "s0" );
    TTEST( pv[1] == "s1" );
    TTEST( pv.at(1) == "s1" );

    // Push back a pointer
    std::string * p_s = new std::string( "s2" );
    pv.push_back( p_s );
    TTEST( pv.size() == 3 );
    TTEST( ! pv.empty() );
    TTEST( pv[0] == "s0" );
    TTEST( pv.at(0) == "s0" );
    TTEST( pv[1] == "s1" );
    TTEST( pv.at(1) == "s1" );
    TTEST( pv[2] == "s2" );
    TTEST( pv.at(2) == "s2" );
}

TFEATURE( "ptr_vector - copy, assign, swap" )
{
    ptr_vector< std::string > pv;
    pv.push_back( "s0" );
    pv.push_back( "s1" );
    pv.push_back( "s2" );

    // Copy construction
    ptr_vector< std::string > pv2( pv );
    TTEST( pv2.size() == 3 );
    TTEST( ! pv2.empty() );
    TTEST( pv2[0] == "s0" );
    TTEST( pv2.at(0) == "s0" );
    TTEST( pv2[1] == "s1" );
    TTEST( pv2.at(1) == "s1" );
    TTEST( pv2[2] == "s2" );
    TTEST( pv2.at(2) == "s2" );

    // Test the copy constructed vector is independent of the first
    TTEST( pv2[0] == pv[0] );
    pv2[0] = "other s0";
    TTEST( pv2[0] == "other s0" );
    TTEST( pv[0] == "s0" );

    // Container assignment
    TTEST( pv2[0] != pv[0] );   // Changed above
    pv2 = pv;
    TTEST( pv2[0] == pv[0] );
    pv2[0] = "yet another s0";
    TTEST( pv2[0] != pv[0] );

    //Swap
    pv[1] = "c1s1";
    pv2[1] = "c2s1";
    pv.swap( pv2 );
    TTEST( pv[1] == "c2s1" );
    TTEST( pv2[1] == "c1s1" );
}

TFEATURE( "ptr_vector - iterators" )
{
    ptr_vector< std::string > pv;
    pv.push_back( "s0" );
    pv.push_back( "s1" );
    pv.push_back( "s2" );

    {
    // non-const iterator from non-const object
    ptr_vector< std::string >::iterator i = pv.begin(), end = pv.end();
    TTEST( i != end );
    TTEST( *i == "s0" );
    TTEST( i->at(1) == '0' );
    ++i;
    TTEST( i != end );
    TTEST( *i == "s1" );
    TTEST( i->at(1) == '1' );
    ++i;
    TTEST( i != end );
    TTEST( *i == "s2" );
    TTEST( i->at(1) == '2' );
    ++i;
    TTEST( i == end );
    }

    {
    // const_iterator from non-const object
    ptr_vector< std::string >::const_iterator i = pv.begin(), end = pv.end();
    TTEST( i != end );
    TTEST( *i == "s0" );
    TTEST( i->at(1) == '0' );
    ++i;
    TTEST( i != end );
    TTEST( *i == "s1" );
    TTEST( i->at(1) == '1' );
    ++i;
    TTEST( i != end );
    TTEST( *i == "s2" );
    TTEST( i->at(1) == '2' );
    ++i;
    TTEST( i == end );
    }

    {
    // const_iterator from const object
    const ptr_vector< std::string > cpv( pv );
    ptr_vector< std::string >::const_iterator i = cpv.begin(), end = cpv.end();
    TTEST( i != end );
    TTEST( *i == "s0" );
    TTEST( i->at(1) == '0' );
    ++i;
    TTEST( i != end );
    TTEST( *i == "s1" );
    TTEST( i->at(1) == '1' );
    ++i;
    TTEST( i != end );
    TTEST( *i == "s2" );
    TTEST( i->at(1) == '2' );
    ++i;
    TTEST( i == end );
    }
}
