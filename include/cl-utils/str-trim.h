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

#ifndef CLUTIL_STR_TRIM
#define CLUTIL_STR_TRIM

#include <string>

namespace clutils {

namespace detail {
    const char * default_trim_whitespace = " \t\n\r\f\v";
}

// in-place trim from beginning of string
inline std::string & ltrim( std::string * p_s, const char * p_what = detail::default_trim_whitespace )
{
    p_s->erase( 0, p_s->find_first_not_of( p_what ) );
    return *p_s;
}

// copy trim from beginning of string
inline std::string ltrim( const std::string & r_s, const char * p_what = detail::default_trim_whitespace )
{
    std::string s( r_s );
    return ltrim( &s, p_what );
}

// in-place trim from end of string
inline std::string & rtrim( std::string * p_s, const char * p_what = detail::default_trim_whitespace )
{
    p_s->erase( p_s->find_last_not_of( p_what ) + 1 );
    return *p_s;
}

// copy trim from end of string
inline std::string rtrim( const std::string & r_s, const char * p_what = detail::default_trim_whitespace )
{
    std::string s( r_s );
    return rtrim( &s, p_what );
}

// in-place trim from both ends of string
inline std::string & trim( std::string * p_s, const char * p_what = detail::default_trim_whitespace )
{
    rtrim( p_s, p_what );
    return ltrim( p_s, p_what );
}

// copy trim from both ends of string
inline std::string trim( const std::string & r_s, const char * p_what = detail::default_trim_whitespace )
{
    std::string s( r_s );
    return trim( &s, p_what );
}

}   // namespace clutils

#endif // CLUTIL_STR_TRIM
