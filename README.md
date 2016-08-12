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
