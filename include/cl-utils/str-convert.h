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

#ifndef CLUTIL_CONVERT
#define CLUTIL_CONVERT

#include <sstream>
#include <string>
#include <iostream>

namespace clutils {

template< typename T >
T from_string( const std::string & s )
{
    T result = T();
    std::istringstream( s ) >> result;
    return result;
}

template<>
bool from_string<bool>( const std::string & s )
{
    std::string input;
    std::istringstream iss( s );
    iss >> input;
    if( input == "0" || input == "false" || input == "False" || input == "FALSE" )
        return false;
    return true;
}

template< typename T >
bool from_string( T & r_result, const std::string & s )
{
    r_result = T();
    if( std::istringstream( s ) >> r_result )
        return true;
    return false;
}

template<>
bool from_string<bool>( bool & r_result, const std::string & s )
{
    std::string input;
    std::istringstream iss( s );
    iss >> input;
    if( input == "0" || input == "false" || input == "False" || input == "FALSE" )
    {
        r_result = false;
        return true;
    }
    else if( input == "1" || input == "true" || input == "True" || input == "TRUE" )
    {
        r_result = true;
        return true;
    }
    return false;
}

template< typename T >
std::string to_string( const T & r_input )
{
    std::ostringstream oss;
    oss << r_input;
    return oss.str();
}

template<>
std::string to_string<bool>( const bool & r_input )
{
    return r_input ? "true" : "false";
}

}   // namespace clutils

#endif // CLUTIL_CONVERT
