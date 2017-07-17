cl-utils
========

cl-utils is a set of utilities that are helpful when coding, but
really too small to justify their own project.

The library will be added to over time as needs arise.

The following are in the `clutils` namespace.

ptr_vector
----------

`ptr_vector` is a container that stores a vector of pointers.  The benefits
using it over `vector<T*>` is that it will deep-copy, the iterators return
`T&` rather than `T*`, and it will delete the pointed to objects when the
container is destroyed.  The benefits over `deque<T>` are that you can
`push_back()` an independently new-ed object, rather than having to do a copy
into place operation.

iterator_range
--------------

`iterator_range` and `const_iterator_range` allow code like:


    ...

    for( const_iterator_range< std::vector< std::string > > ir( my_container ); ir; ++ir )
        total_string_length += ir->size();

You can also use `*ir` as per normal iterators.

str_args
--------
Allows string interpolation by positional argument.

The primary function is:

    std::string expand( const char format[], const str_args & r_args )

`format` describes the format of the output string and where values should
be interpolated.

The basic format for indicating a parameter to be interpolsated is
`%<index-number>`.  For example, `%0`.  The indexing is `0` based.
Only a single decimal digit is allowed after the `%` sign, so only the
values `0` to `9` can be specified.

For larger indexes a long form of `%{<index-number>}` can be used.
For example `%{10}`.  In this long form, a description of the positional
parameter can be included by including a `:` and then a description name.
For example `%{0:number of files}.  This can help with documentation and
translation.

Named parameters are supported using the format `%{<parameter-name>}`.
For example `%{line}`.

Constructors to `str_args` allow inclusion of various types as the arguments
to be interpolated by `expand()`.  For example:

    std::string s = expand( "File: %0, Line: %1", "my-file.txt", 10 );

Variants of `expand()` are available for 1 and 2 parameter substitutions.
To interpolate more parameters use the form:

    s = expand( "File: %0, Line: %1, Col: %2", str_args( "my-file.txt" ) << 10 << 2 );

Or:

    s = expand( "File: %0, Line: %1, Col: %2", str_args() << "my-file.txt" << 10 << 2 );

When named parameters are used, a pair of `str_args` arguments are used to
provide the data to `expand`.  The first in the pair is the name of the
parameter, and the second is the value to be used for the parameter.
When a named parameter is looked up, a search is made for an argument that
has a value of the name of the parameter indicated in the `format`.  If
such an argument is found, then the argument following the found argument
is used as the value for string interpolation.  For example:

    s = expand( "File: %{file}, Line: %{line}, Col: %{col}", str_args() <<
                    "file" << "my-file.txt" <<
                    "line" << 10 <<
                    "col" << 2 );

To add a formatted string to the end of a existing string, `expand_append`
following can be used:

    std::string & expand_append( std::string * p_out, const char format[], const str_args & r_args );
    std::string & expand_append( std::string * p_out, const char format[], const str_args & r_arg_1, const str_args & r_arg_2 );

For example:

    expand_append( &s, "File: %0, Line: %1", "my-file.txt", 10 );

str_convert
-----------

`str_convert` performs conversion of values to and from strings using
`sstream`.

`to_string` will convert a value to a string representation.  `bool`
values will be converted to either `true` or `false`.

`from_string` has both checked and unchecked forms.

The unchecked form will return `T()` if the conversion fails due to
malformed input.  Use as:

    int i = from_string<int>( "123" );

The checked form returns `true` if the conversion succeeds and `false`
otherwise.  Use as:

    int i;
    if( from_string( i, "123" ) )
    {
        ...
    }

When `from_string` is applied to `bool` values, the unchecked
form will return `false` for the strings `0`, `false`, `False` and `FALSE`.
All other values will return `true`.  For the checked version,
`false` is supplied for `0`, `false`, `False` and `FALSE`, while `true`
is supplied for `1`, `true`, `True`, and `TRUE`.  The check function will
return `false` for any other input value.

str_ops
-------

`str_ops` contains common string operations.

Currently this consists of `ltrim`, `rtrim` and `trim`.  Variants that take a
pointer to a string modify the string in-place.  A reference to the in-place
modified string is returned.  Variants that take a const reference to a string,
take a copy the input string, modify it and return the result.  All variants
can take an additional parameter that is a string of the characters to be
trimmed.

CommandLineArgs
---------------

`CommandLineArgs` is a cheap and cheerful utility class to help make
processing command line arguments passed to main() easier.

Create an instance of the class as follows:

    CommandLineArgs cla( argc, argv )

It has the following methods:

`CommandLineArgs( int argc, char ** argv, std::ostream & r_os = std::cerr )` is
the constructor. `argc` and `argv` are the parameters received by `main()`.
The `r_os` parameter allows any error messages to be re-directed to an
alternative destination to `std::cerr`.

`is_flag() const` tests if the currently selected parameter looks like a flag.
Flags can start with `-` or `--`.

`is_flag( const char * p_option_1 ) const` tests if the current input flag
matches `p_option_1`.  Do NOT include the flag marker character(s) (i.e. `-`
or `--`) in `p_option_1`.  e.g. use `is_flag( "o" )`.

`is_flag( const char * p_option_1, const char * p_option_2 )` similar to the
above for two variations of a flag name.  Tests if the current input flag is
either `p_option_1` or `p_option_2`.

`is_flag( const char * p_option_1, int desired_extra_count, const char * p_on_insufficient_message = 0 )`
tests if the current input flag is `p_option_1` and that there are a minimum of
`desired_extra_count` additional input parameters available for processing.
If there are insufficient parameters, if present, the `p_on_insufficient_message`
error message will be written to `r_os` as setup during construction and the
set of input flags will be deemed `empty()`.

`is_flag( const char * p_option_1, const char * p_option_2, int desired_extra_count, const char * p_on_insufficient_message = 0 )`
is similar to the previous method, but allows matching of either `p_option_1`
or `p_option_2`.

`bool ensure( int desired_extra_count, const char * p_on_insufficient_message = 0 )` tests
that there are `desired_extra_count` extra arguments after the current argument.
If not, the error message is output to `r_os` as setup during construction,
and the remaining argument count is set to `0`.

`current()` returns a pointer to the current input parameter.  For example,
if the current input parameter is a stand-alone file name, use this method
to retrieve it.

`flag_marker()` returns either `-` or `--` depending on which of these two the
current flag was indicated by.  If the input is deemed not to be a flag, then
it returns an empty string.

`flag_name()` returns the name of the current input flag.  For example, it
returns `output` if the input flag is `--output`.  If the input is deemed not
to be a flag, then it returns an empty string.

`flag()` returns the combination of `flag_marker()` and `flag_name()`.  This
is the preferred method to using `current()` for displaying the name of the
current input flag.  (In future it is hoped to support grouped short flags,
such as in `tar -xvf foo`, and `flag()` will hopefully be able to return
`-v` on handling the second flag. Hence the result of `flag()` may actually
be computed based on the current state, rather than refer directly to any
input.  Under such circumstances using `current()` would return an undesired
result.)

`next()` moves to the next parameter and returns a pointer to it.  `++` on the
object may also be used.

`empty()` returns `true` if there are no more arguments to be processed.

The class also has an `operator bool ()` method that will return `true` if
there are more arguments available.

Example usage:

    clutils::CommandLineArgs cla( argc, argv );

    if( ! cla )
    {
        help();
        return false;
    }

    for( ; cla; ++cla )
    {
        if( cla.is_flag( "h", "?" ) )
        {
            help();
            return false;
        }
        else if( cla.is_flag( "j", "json", 1, "-json flag must include name of JSON file to validate" ) )
            p_config->set_json( cla.next() );
        else if( cla.is_flag() )
            std::cerr << "Unknown flag: " << cla.flag() << "\n";
        else
            p_config->add_jcr( cla.current() );
    }
