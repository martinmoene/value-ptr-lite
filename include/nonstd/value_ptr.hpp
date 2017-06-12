//
// Copyright (c) 2017 Martin Moene
//
// https://github.com/martinmoene/value-ptr-lite
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#ifndef NONSTD_VALUE_PTR_LITE_HPP
#define NONSTD_VALUE_PTR_LITE_HPP

#include <cassert>
#include <functional>
#include <memory>
#include <utility>

#define  value_ptr_lite_VERSION "0.0.0"

// value-ptr-lite configuration:

#ifndef  nsvp_CONFIG_COMPARE_POINTERS
# define nsvp_CONFIG_COMPARE_POINTERS  0
#endif

// Compiler detection (C++17 is speculative):

#define nsvp_CPP11_OR_GREATER  ( __cplusplus >= 201103L )
#define nsvp_CPP14_OR_GREATER  ( __cplusplus >= 201402L )
#define nsvp_CPP17_OR_GREATER  ( __cplusplus >= 201700L )

// half-open range [lo..hi):
#define nsvp_BETWEEN( v, lo, hi ) ( lo <= v && v < hi )

#if defined(_MSC_VER) && !defined(__clang__)
# define nsvp_COMPILER_MSVC_VERSION   (_MSC_VER / 100 - 5 - (_MSC_VER < 1900))
#else
# define nsvp_COMPILER_MSVC_VERSION   0
#endif

#if defined __GNUC__
# define nsvp_COMPILER_GNUC_VERSION  __GNUC__
#else
# define nsvp_COMPILER_GNUC_VERSION    0
#endif

#if nsvp_BETWEEN(nsvp_COMPILER_MSVC_VERSION, 7, 14 )
# pragma warning( push )
# pragma warning( disable: 4345 )   // initialization behavior changed
#endif

#if nsvp_COMPILER_MSVC_VERSION >= 14
# define nsvp_DECLSPEC_EMPTY_BASES  __declspec(empty_bases)
#else
# define nsvp_DECLSPEC_EMPTY_BASES
#endif

// Presence of C++11 language features:

#if nsvp_CPP11_OR_GREATER || nsvp_COMPILER_MSVC_VERSION >= 10
# define nsvp_HAVE_AUTO  1
# define nsvp_HAVE_NULLPTR  1
# define nsvp_HAVE_STATIC_ASSERT  1
#endif

#if nsvp_CPP11_OR_GREATER || nsvp_COMPILER_MSVC_VERSION >= 12
# define nsvp_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG  1
# define nsvp_HAVE_INITIALIZER_LIST  1
#endif

#if nsvp_CPP11_OR_GREATER || nsvp_COMPILER_MSVC_VERSION >= 14
# define nsvp_HAVE_ALIAS_TEMPLATE  1
# define nsvp_HAVE_CONSTEXPR_11  1
# define nsvp_HAVE_ENUM_CLASS  1
# define nsvp_HAVE_EXPLICIT_CONVERSION  1
# define nsvp_HAVE_IS_DEFAULT  1
# define nsvp_HAVE_IS_DELETE  1
# define nsvp_HAVE_NOEXCEPT  1
#endif

// Presence of C++14 language features:

#if nsvp_CPP14_OR_GREATER
# define nsvp_HAVE_CONSTEXPR_14  1
#endif

// Presence of C++17 language features:

#if nsvp_CPP17_OR_GREATER
# define nsvp_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE  1
#endif

// Presence of C++ library features:

#if nsvp_COMPILER_GNUC_VERSION
# define nsvp_HAVE_TR1_TYPE_TRAITS  1
# define nsvp_HAVE_TR1_ADD_POINTER  1
#endif

#if nsvp_CPP11_OR_GREATER || nsvp_COMPILER_MSVC_VERSION >= 9
# define nsvp_HAVE_TYPE_TRAITS  1
# define nsvp_HAVE_STD_ADD_POINTER  1
#endif

#if nsvp_CPP11_OR_GREATER || nsvp_COMPILER_MSVC_VERSION >= 11
# define nsvp_HAVE_ARRAY  1
#endif

#if nsvp_CPP11_OR_GREATER || nsvp_COMPILER_MSVC_VERSION >= 12
# define nsvp_HAVE_CONDITIONAL  1
#endif

#if nsvp_CPP11_OR_GREATER || nsvp_COMPILER_MSVC_VERSION >= 14 || (nsvp_COMPILER_MSVC_VERSION >= 9 && _HAS_CPP0X)
# define nsvp_HAVE_CONTAINER_DATA_METHOD  1
#endif

#if nsvp_CPP11_OR_GREATER || nsvp_COMPILER_MSVC_VERSION >= 12
# define nsvp_HAVE_REMOVE_CV  1
#endif

#if nsvp_CPP11_OR_GREATER || nsvp_COMPILER_MSVC_VERSION >= 14
# define nsvp_HAVE_SIZED_TYPES  1
#endif

// For the rest, consider VC14 as C++11 for value-ptr-lite:

#if nsvp_COMPILER_MSVC_VERSION >= 14
# undef  nsvp_CPP11_OR_GREATER
# define nsvp_CPP11_OR_GREATER  1
#endif

// C++ feature usage:

#if nsvp_HAVE_CONSTEXPR_11
# define nsvp_constexpr constexpr
#else
# define nsvp_constexpr /*constexpr*/
#endif

#if nsvp_HAVE_CONSTEXPR_14
# define nsvp_constexpr14 constexpr
#else
# define nsvp_constexpr14 /*constexpr*/
#endif

#if nsvp_HAVE_NOEXCEPT
# define nsvp_noexcept noexcept
# define nsvp_noexcept_op noexcept
#else
# define nsvp_noexcept /*noexcept*/
# define nsvp_noexcept_op(expr) /*noexcept(expr)*/
#endif

#if nsvp_HAVE_NULLPTR
# define nsvp_nullptr nullptr
#else
# define nsvp_nullptr NULL
#endif

// additional includes:

#if ! nsvp_CPP11_OR_GREATER
# include <algorithm>           // std::swap() until C++11
#endif

#if nsvp_HAVE_INITIALIZER_LIST
# include <initializer_list>
#endif

#if nsvp_HAVE_TYPE_TRAITS
# include <type_traits>
#elif nsvp_HAVE_TR1_TYPE_TRAITS
# include <tr1/type_traits>
#endif

// static assert:

#if nsvp_CPP11_OR_GREATER
# define nsvp_static_assert( expr, msg ) \
    static_assert( expr, msg )
#else
# define nsvp_static_assert( expr, msg ) \
    do { typedef int x[(expr) ? 1 : -1]; } while(0)
#endif

//
// in_place: code duplicated in any-lite, optional-lite, variant-lite, value-ptr-lite:
//

#if   ! nonstd_lite_HAVE_IN_PLACE_TYPES
#define nonstd_lite_HAVE_IN_PLACE_TYPES  1

namespace nonstd {

namespace detail {

template< class T >
struct in_place_type_tag {};

template< std::size_t I >
struct in_place_index_tag {};

} // namespace detail

struct in_place_t {};

template< class T >
inline in_place_t in_place( detail::in_place_type_tag<T> = detail::in_place_type_tag<T>() )
{
    return in_place_t();
}

template< std::size_t I >
inline in_place_t in_place( detail::in_place_index_tag<I> = detail::in_place_index_tag<I>() )
{
    return in_place_t();
}

// mimic templated typedef:

#define nonstd_lite_in_place_type_t( T)  nonstd::in_place_t(&)( nonstd::detail::in_place_type_tag<T>  )
#define nonstd_lite_in_place_index_t(T)  nonstd::in_place_t(&)( nonstd::detail::in_place_index_tag<I> )

} // namespace nonstd

#endif // nonstd_lite_HAVE_IN_PLACE_TYPES

namespace nonstd {

namespace detail {

#if nsvp_CPP11_OR_GREATER
using std::default_delete;
#else
template< class T >
struct default_delete
{
    nsvp_constexpr default_delete() nsvp_noexcept {};

    void operator()( T * ptr ) const nsvp_noexcept
    {
        nsvp_static_assert( sizeof(T) > 0, "default_delete cannot delete incomplete type");
#if nsvp_CPP11_OR_GREATER
        nsvp_static_assert( ! std::is_void<T>::value, "default_delete cannot delete incomplete type");
#endif
        delete ptr;
    }
};
#endif

template< class T >
struct default_clone
{
#if nsvp_CPP11_OR_GREATER
    default_clone() = default;
#else
    default_clone() {};
#endif

    T * operator()( T const & x ) const
    {
        nsvp_static_assert( sizeof(T) > 0, "default_clone cannot clone incomplete type");
#if nsvp_CPP11_OR_GREATER
        nsvp_static_assert( ! std::is_void<T>::value, "default_clone cannot clone incomplete type");
#endif
        return new T( x );
    }

#if nsvp_CPP11_OR_GREATER
    T * operator()( T && x ) const
    {
        return new T( std::move( x ) );
    }

    template< class... Args >
    T * operator()( nonstd_lite_in_place_type_t(T), Args&&... args ) const
    {
        return new T( std::forward<Args>(args)...);
    }

    template< class U, class... Args >
    T * operator()( nonstd_lite_in_place_type_t(T), std::initializer_list<U> il, Args&&... args ) const
    {
        return new T( il, std::forward<Args>(args)...);
    }
#endif
};

template <class T, class Cloner, class Deleter>
struct nsvp_DECLSPEC_EMPTY_BASES compressed_ptr : Cloner, Deleter
{
    typedef T       element_type;
    typedef T *     pointer;

    typedef Cloner  cloner_type;
    typedef Deleter deleter_type;

    // Lifetime:

    ~compressed_ptr()
    {
        deleter_type()( ptr );
    }

    compressed_ptr()
    : ptr( nsvp_nullptr )
    {}

    compressed_ptr( pointer p )
    : ptr( p )
    {}

    compressed_ptr( compressed_ptr const & other )
    : cloner_type ( other )
    , deleter_type( other )
    , ptr( other.ptr ? cloner_type()( *other.ptr ) : nsvp_nullptr )
    {}

#if  nsvp_CPP11_OR_GREATER
    compressed_ptr( compressed_ptr && other )
    : cloner_type ( std::move( other ) )
    , deleter_type( std::move( other ) )
    , ptr( std::move( other.ptr ) )
    {
        other.ptr = nullptr;
    }
#endif

    compressed_ptr( element_type const & value )
    : ptr( cloner_type()( value ) )
    {}

#if  nsvp_CPP11_OR_GREATER

    compressed_ptr( element_type && value )
    : ptr( cloner_type()( std::move( value ) ) )
    {}

    template< class... Args >
    explicit compressed_ptr( nonstd_lite_in_place_type_t(T), Args&&... args )
    : ptr( cloner_type()( in_place, std::forward<Args>(args)...) )
    {}

    template< class U, class... Args >
    explicit compressed_ptr( nonstd_lite_in_place_type_t(T), std::initializer_list<U> il, Args&&... args )
    : ptr( cloner_type()( in_place, il, std::forward<Args>(args)...) )
    {}

#endif

    compressed_ptr( element_type const & value, cloner_type const & cloner )
    : cloner_type ( cloner  )
    , ptr( cloner_type()( value ) )
    {}

#if  nsvp_CPP11_OR_GREATER
    compressed_ptr( element_type && value, cloner_type && cloner )
    : cloner_type ( std::move( cloner  ) )
    , ptr( cloner_type()( std::move( value ) ) )
    {}
#endif

    compressed_ptr( element_type const & value, cloner_type const & cloner, deleter_type const & deleter )
    : cloner_type ( cloner  )
    , deleter_type( deleter )
    , ptr( cloner_type()( value ) )
    {}

#if  nsvp_CPP11_OR_GREATER
    compressed_ptr( element_type && value, cloner_type && cloner, deleter_type && deleter )
    : cloner_type ( std::move( cloner  ) )
    , deleter_type( std::move( deleter ) )
    , ptr( cloner_type()( std::move( value ) ) )
    {}
#endif

    compressed_ptr( cloner_type const & cloner )
    : cloner_type( cloner )
    , ptr( nsvp_nullptr )
    {}

#if  nsvp_CPP11_OR_GREATER
    compressed_ptr( cloner_type && cloner )
    : cloner_type( std::move( cloner ) )
    , ptr( nsvp_nullptr )
    {}
#endif

    compressed_ptr( deleter_type const & deleter )
    : deleter_type( deleter )
    , ptr( nsvp_nullptr )
    {}

# if  nsvp_CPP11_OR_GREATER
    compressed_ptr( deleter_type && deleter )
    : deleter_type( std::move( deleter ) )
    , ptr( nsvp_nullptr )
    {}
#endif

    compressed_ptr( cloner_type const & cloner, deleter_type const & deleter )
    : cloner_type ( cloner  )
    , deleter_type( deleter )
    , ptr( nsvp_nullptr )
    {}

#if  nsvp_CPP11_OR_GREATER
    compressed_ptr( cloner_type && cloner, deleter_type && deleter )
    : cloner_type ( std::move( cloner  ) )
    , deleter_type( std::move( deleter ) )
    , ptr( nsvp_nullptr )
    {}
#endif

    // Observers:

    pointer get() const nsvp_noexcept
    {
        return ptr;
    }

    cloner_type & get_cloner() nsvp_noexcept
    {
        return *this;
    }

    deleter_type & get_deleter() nsvp_noexcept
    {
        return *this;
    }

    // Modifiers:

    pointer release() nsvp_noexcept
    {
        using std::swap;
        pointer result = nsvp_nullptr;
        swap( result, ptr );
        return result;
    }

    void reset( pointer p ) nsvp_noexcept
    {
        get_deleter()( ptr );
        ptr = p;
    }

    void reset( element_type const & v ) nsvp_noexcept
    {
        reset( get_cloner()( v ) );
    }

#if  nsvp_CPP11_OR_GREATER
    void reset( element_type && v ) nsvp_noexcept
    {
        reset( get_cloner()( std::move( v ) ) );
    }
#endif

    void swap( compressed_ptr & other ) nsvp_noexcept
    {
        using std::swap;
        swap( ptr, other.ptr );
    }

    pointer ptr;
};

} // namespace detail

//
// class value_ptr:
//
template
<
    class T
    , class Cloner  = detail::default_clone<T>
    , class Deleter = detail::default_delete<T>
>
class value_ptr
{
public:
    typedef T         element_type;
    typedef T *       pointer;
    typedef T &       reference;
    typedef T const * const_pointer;
    typedef T const & const_reference;

    typedef Cloner   cloner_type;
    typedef Deleter  deleter_type;

    // Lifetime

#if nsvp_HAVE_IS_DEFAULT
    ~value_ptr() = default;
#endif

    nsvp_constexpr value_ptr() nsvp_noexcept
    : ptr( cloner_type(), deleter_type() )
    {}

#if nsvp_HAVE_NULLPTR
    nsvp_constexpr value_ptr( std::nullptr_t ) nsvp_noexcept
    : ptr( cloner_type(), deleter_type() )
    {}
#endif

    value_ptr( element_type const & value ) nsvp_noexcept
    : ptr( value )
    {}

#if nsvp_CPP11_OR_GREATER

    value_ptr( element_type && value ) nsvp_noexcept
    : ptr( std::move( value ) )
    {}

    template< class... Args >
    explicit value_ptr( nonstd_lite_in_place_type_t(T), Args&&... args )
    : ptr( in_place, std::forward<Args>(args)...)
    {}

    template< class U, class... Args >
    explicit value_ptr( nonstd_lite_in_place_type_t(T), std::initializer_list<U> il, Args&&... args )
    : ptr( in_place, il, std::forward<Args>(args)...)
    {}

#endif // nsvp_CPP11_OR_GREATER

    value_ptr( cloner_type const & cloner )
    : ptr( cloner )
    {}

#if  nsvp_CPP11_OR_GREATER
    value_ptr( cloner_type && cloner )
    : ptr( std::move( cloner ) )
    {}
#endif

    value_ptr( deleter_type const & deleter )
    : ptr( deleter )
    {}

#if  nsvp_CPP11_OR_GREATER
    value_ptr( deleter_type && deleter )
    : ptr( std::move( deleter ) )
    {}
#endif

#if  nsvp_CPP11_OR_GREATER
    template< class V, class ClonerOrDeleter >
    value_ptr( V && value, ClonerOrDeleter && cloner_or_deleter )
    : ptr( std::forward<V>( value ), std::forward<ClonerOrDeleter>( cloner_or_deleter ) )
    {}
#else
    template< class V, class ClonerOrDeleter >
    value_ptr( V const & value, ClonerOrDeleter const & cloner_or_deleter )
    : ptr( value, cloner_or_deleter )
    {}
#endif

#if  nsvp_CPP11_OR_GREATER
    template< class V, class C, class D >
    value_ptr( V && value, C && cloner, D && deleter )
    : ptr( std::forward<V>( value ), std::forward<C>( cloner ), std::forward<D>( deleter ) )
    {}
#else
    template< class V, class C, class D >
    value_ptr( V const & value, C const & cloner, D const & deleter )
    : ptr( value, cloner, deleter )
    {}
#endif

    value_ptr( pointer p )
    : ptr( p )
    {}

    value_ptr( value_ptr const & other )
    : ptr( other.ptr )
    {}

#if nsvp_CPP11_OR_GREATER
    value_ptr( value_ptr && other )
    : ptr( std::move( other.ptr ) )
    {}
#endif // optional_CPP11_OR_GREATER

#if nsvp_HAVE_NULLPTR
    value_ptr & operator=( std::nullptr_t )
    {
        ptr.reset( nullptr );
        return *this;
    }
#endif

    value_ptr & operator=( T const & value )
    {
        ptr.reset( value );
        return *this;
    }

#if nsvp_CPP11_OR_GREATER
    template< class U,
        typename = typename std::enable_if< std::is_same< typename std::decay<U>::type, T>::value >::type >
    value_ptr & operator=( U && value )
    {
        ptr.reset( std::forward<U>( value ) );
        return *this;
    }
#endif

    value_ptr & operator=( value_ptr const & rhs )
    {
        if ( this == &rhs )
            return *this;

        if ( rhs ) ptr.reset( *rhs );
#if nsvp_HAVE_NULLPTR
        else       ptr.reset( nullptr );
#else
        else       ptr.reset( pointer(0) );
#endif
        return *this;
    }

#if  nsvp_CPP11_OR_GREATER

    value_ptr & operator=( value_ptr && rhs ) nsvp_noexcept
    {
        if ( this == &rhs )
            return *this;

        ptr.reset( std::move( rhs.ptr ) );

        return *this;
    }

    template< class... Args >
    void emplace( Args&&... args )
    {
        ptr.reset( T( std::forward<Args>(args)...) );
    }

    template< class U, class... Args >
    void emplace( std::initializer_list<U> il, Args&&... args )
    {
        ptr.reset( T( il, std::forward<Args>(args)...) );
    }

#endif // optional_CPP11_OR_GREATER

    // Observers:

    pointer get() nsvp_noexcept
    {
        return ptr.get();
    }

    const_pointer get() const nsvp_noexcept
    {
        return ptr.get();
    }

    cloner_type & get_cloner() nsvp_noexcept
    {
        return ptr.get_cloner();
    }

    deleter_type & get_deleter() nsvp_noexcept
    {
        return ptr.get_deleter();
    }

#if  nsvp_CPP11_OR_GREATER
    explicit operator bool() const nsvp_noexcept
    {
        return !! get();
    }
#else
private:
    typedef void (value_ptr::*safe_bool)() const;
    void this_type_does_not_support_comparisons() const {}

public:
    nsvp_constexpr operator safe_bool() const nsvp_noexcept
    {
        return (!! get() ) ? &value_ptr::this_type_does_not_support_comparisons : 0;
    }
#endif

    reference operator*()
    {
        assert( get() != nsvp_nullptr ); return *get();
    }

    const_reference operator*() const
    {
        assert( get() != nsvp_nullptr ); return *get();
    }

    pointer operator->() nsvp_noexcept
    {
        assert( get() != nsvp_nullptr ); return get();
    }

    const_pointer operator->() const nsvp_noexcept
    {
        assert( get() != nsvp_nullptr ); return get();
    }

    // Modifiers:

    pointer release() nsvp_noexcept
    {
        return ptr.release();
    }

    void reset( pointer p = pointer() ) nsvp_noexcept
    {
        ptr.reset( p );
    }

    void swap( value_ptr & other ) nsvp_noexcept
    {
        ptr.swap( other.ptr );
    }

private:
    detail::compressed_ptr<T, Cloner, Deleter> ptr;
};

// Non-member functions:

#if nsvp_CPP11_OR_GREATER

template< class T >
inline value_ptr< typename std::decay<T>::type > make_value( T && v )
{
    return value_ptr< typename std::decay<T>::type >( std::forward<T>( v ) );
}

template< class T, class... Args >
inline value_ptr<T> make_value( Args&&... args )
{
    return value_ptr<T>( in_place, std::forward<Args>(args)...);
}

template< class T, class U, class... Args >
inline value_ptr<T> make_value( std::initializer_list<U> il, Args&&... args )
{
    return value_ptr<T>( in_place, il, std::forward<Args>(args)...);
}

#else

template< typename T >
inline value_ptr<T> make_value( T const & v )
{
    return value_ptr<T>( v );
}

#endif // optional_CPP11_OR_GREATER

// Comparison between value_ptr-s:

#if nsvp_CONFIG_COMPARE_POINTERS

// compare pointers:

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator==(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
    return lhs.get() == rhs.get();
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator!=(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
    return ! ( lhs == rhs );
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator<(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
#if nsvp_CPP11_OR_GREATER
    using P1 = typename value_ptr<T1, D1, C1>::const_pointer;
    using P2 = typename value_ptr<T2, D2, C2>::const_pointer;
    using CT = typename std::common_type<P1, P2>::type;
    return std::less<CT>()( lhs.get(), rhs.get() );
#else
    return std::less<T1 const *>()( lhs.get(), rhs.get() );
#endif
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator<=(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
    return !( rhs < lhs );
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator>(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
    return rhs < lhs;
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator>=(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
    return !( lhs < rhs );
}

// Comparison with std::nullptr_t:

#if nsvp_HAVE_NULLPTR

template< class T, class D, class C  >
inline bool operator==( value_ptr<T, D, C> const & lhs, std::nullptr_t ) nsvp_noexcept
{
    return ! lhs;
}

template< class T, class D, class C  >
inline bool operator==( std::nullptr_t, value_ptr<T, D, C> const & rhs ) nsvp_noexcept
{
    return ! rhs;
}

template< class T, class D, class C  >
inline bool operator!=( value_ptr<T, D, C> const & lhs, std::nullptr_t ) nsvp_noexcept
{
    return static_cast<bool>( lhs );
}

template< class T, class D, class C  >
inline bool operator!=( std::nullptr_t, value_ptr<T, D, C> const & rhs ) nsvp_noexcept
{
    return static_cast<bool>( rhs );
}

template< class T, class D, class C  >
inline bool operator<( value_ptr<T, D, C> const & lhs, std::nullptr_t )
{
    typedef typename value_ptr<T, D, C>::const_pointer P;
    return std::less<P>()( lhs.get(), nullptr );
}

template< class T, class D, class C  >
inline bool operator<( std::nullptr_t, value_ptr<T, D, C> const & rhs )
{
    typedef typename value_ptr<T, D, C>::const_pointer P;
    return std::less<P>()( nullptr, rhs.get() );
}

template< class T, class D, class C  >
inline bool operator<=( value_ptr<T, D, C> const & lhs, std::nullptr_t )
{
    return !( nullptr < lhs );
}

template< class T, class D, class C  >
inline bool operator<=( std::nullptr_t, value_ptr<T, D, C> const & rhs )
{
    return !( rhs < nullptr );
}

template< class T, class D, class C  >
inline bool operator>( value_ptr<T, D, C> const & lhs, std::nullptr_t )
{
    return nullptr < lhs;
}

template< class T, class D, class C  >
inline bool operator>( std::nullptr_t, value_ptr<T, D, C> const & rhs )
{
    return rhs < nullptr;
}

template< class T, class D, class C  >
inline bool operator>=( value_ptr<T, D, C> const & lhs, std::nullptr_t )
{
    return !( lhs < nullptr );
}

template< class T, class D, class C  >
inline bool operator>=( std::nullptr_t, value_ptr<T, D, C> const & rhs )
{
    return !( nullptr < rhs );
}

#endif // nsvp_HAVE_NULLPTR

#else  // nsvp_CONFIG_COMPARE_POINTERS

// compare content:

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator==(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
//    return *lhs == *rhs;
    return bool(lhs) != bool(rhs) ? false : bool(lhs) == false ? true : *lhs == *rhs;
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator!=(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
    return ! ( lhs == rhs );
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator<(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
//#if nsvp_CPP11_OR_GREATER
//    using E1 = typename value_ptr<T1, D1, C1>::element_type;
//    using E2 = typename value_ptr<T2, D2, C2>::element_type;
//    using CT = typename std::common_type<E1, E2>::type;
//    return std::less<CT>()( *lhs, *rhs );
//#else
//    return std::less<T1>()( *lhs, *rhs );
//#endif

    return (!rhs) ? false : (!lhs) ? true : *lhs < *rhs;
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator<=(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
    return !( rhs < lhs );
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator>(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
    return rhs < lhs;
}

template<
    class T1, class D1, class C1,
    class T2, class D2, class C2
>
inline bool operator>=(
    value_ptr<T1, D1, C1> const & lhs,
    value_ptr<T2, D2, C2> const & rhs )
{
    return !( lhs < rhs );
}

// compare with value:

template< class T, class C, class D >
bool operator==( value_ptr<T,C,D> const & x, const T & v )
{
    return bool(x) ? *x == v : false;
}

template< class T, class C, class D >
bool operator==( T const & v, value_ptr<T,C,D> const & x )
{
    return bool(x) ? v == *x : false;
}

template< class T, class C, class D >
bool operator!=( value_ptr<T,C,D> const & x, const T & v )
{
    return bool(x) ? *x != v : true;
}

template< class T, class C, class D >
bool operator!=( T const & v, value_ptr<T,C,D> const & x )
{
    return bool(x) ? v != *x : true;
}

template< class T, class C, class D >
bool operator<( value_ptr<T,C,D> const & x, const T & v )
{
    return bool(x) ? *x < v : true;
}

template< class T, class C, class D >
bool operator<( T const & v, value_ptr<T,C,D> const & x )
{
    return bool(x) ? v < *x : false;
}

template< class T, class C, class D >
bool operator<=( value_ptr<T,C,D> const & x, const T & v )
{
    return bool(x) ? *x <= v : true;
}

template< class T, class C, class D >
bool operator<=( T const & v, value_ptr<T,C,D> const & x )
{
    return bool(x) ? v <= *x : false;
}

template< class T, class C, class D >
bool operator>( value_ptr<T,C,D> const & x, const T & v )
{
    return bool(x) ? *x > v : false;
}

template< class T, class C, class D >
bool operator>( T const & v, value_ptr<T,C,D> const & x )
{
    return bool(x) ? v > *x : true;
}

template< class T, class C, class D >
bool operator>=( value_ptr<T,C,D> const & x, const T & v )
{
    return bool(x) ? *x >= v : false;
}

template< class T, class C, class D >
bool operator>=( T const & v, value_ptr<T,C,D> const & x )
{
    return bool(x) ? v >= *x : true;
}

#endif // nsvp_CONFIG_COMPARE_POINTERS

// swap:

template< class T, class D, class C >
inline void swap(
    value_ptr<T, D, C> & lhs,
    value_ptr<T, D, C> & rhs ) nsvp_noexcept
{
    lhs.swap( rhs );
}

} // namespace nonstd

#if nsvp_CPP11_OR_GREATER

// Specialize the std::hash algorithm:

namespace std
{

template< class T, class D, class C >
struct hash< nonstd::value_ptr<T, D, C> >
{
    typedef nonstd::value_ptr<T, D, C> argument_type;
    typedef size_t result_type;

    result_type operator()( argument_type const & p ) const nsvp_noexcept
    {
        return hash<typename argument_type::const_pointer>()( p.get() );
    }
};

} // namespace std

#endif // nsvp_CPP11_OR_GREATER

#endif // NONSTD_VALUE_PTR_LITE_HPP
