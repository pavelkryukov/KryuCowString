// CATCH2
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../kryucow_string.h"

#include <cstring>
#include <sstream>

TEST_CASE( "Equality", "Cow_String")
{
    const KryuCowString a ("Something");
    std::string a_s = "Something_strange";
    REQUIRE( a != a_s);
    a_s.erase( a_s.find('_'));
    REQUIRE( a == a_s); 

    const std::string_view a_v = "Something_else";
    REQUIRE( a != a_v);
    const auto a_v1 = a_v.substr(0, 9);
    REQUIRE( a == a_v1);
}

TEST_CASE( "Copy_Check", "Cow_String")
{
    KryuCowString a {"Hello"};
    KryuCowString b = a;
    REQUIRE( a == b);
    REQUIRE( a.data() == b.data());

    b += " World!";
    REQUIRE( a == "Hello");
    REQUIRE( b != "Hello");
    REQUIRE( b == "Hello World!");
    REQUIRE( a != b);
    REQUIRE( a.data() != b.data());
}

TEST_CASE( "Assignment_Check", "Cow_String")
{
    KryuCowString a {"Hello"};
    const KryuCowString b = a;
    REQUIRE( a == b);
    REQUIRE( a.data() == b.data());

    a = "Goodbye!";
    REQUIRE( a == "Goodbye!");
    REQUIRE( b == "Hello");
    REQUIRE( a != b);
    REQUIRE( a.data() != b.data());
}

TEST_CASE( "Empty_String", "Cow_String")
{
    KryuCowString a;
    REQUIRE( a == "");
    REQUIRE( a.empty() );
    KryuCowString b = a;
    REQUIRE( b == "");
    REQUIRE( b.empty() );

    a = "Hello!";
    REQUIRE( a == "Hello!");
    REQUIRE( !a.empty() );
    REQUIRE( b == "");
    REQUIRE( b.empty() );
    REQUIRE( a != b);

    a = "";
    REQUIRE( a == "");
    REQUIRE( a.empty() );

    b = "Goodbye!";
    REQUIRE( b == "Goodbye!");
    REQUIRE( a != b);

    KryuCowString c;
    const KryuCowString d = c;
    REQUIRE( c == "");
    REQUIRE( c.empty() );
    c += "World!";
    REQUIRE( c == "World!");
    REQUIRE( d == "");
}

TEST_CASE( "Initializing_Checks", "Wide_Cow_String")
{
    WKryuCowString a;
    const WKryuCowString b = a;
    REQUIRE( a == b);

    WKryuCowString c( L"Hello!");
    REQUIRE( c == L"Hello!");

    a += c;
    REQUIRE( a == c);
    REQUIRE( a != b);
    REQUIRE( a == L"Hello!");

    c += a;
    REQUIRE( c == L"Hello!Hello!");
    REQUIRE( a == L"Hello!");
}

TEST_CASE( "At", "Cow_String")
{
    const KryuCowString a("Hello Goodbye!");
    REQUIRE( a.length() == std::strlen("Hello Goodbye!"));
    REQUIRE( a[0] == 'H');
    REQUIRE( a.front() == 'H');
    REQUIRE( a.back() == '!');
    REQUIRE( a.at(3) == 'l');
    REQUIRE( a[4] == 'o');
    REQUIRE_THROWS_AS( a.at(15), std::out_of_range );
}

TEST_CASE( "At_Empty", "Cow_String")
{
    const KryuCowString a;
    REQUIRE_THROWS_AS( a.at(0), std::out_of_range );
    REQUIRE_THROWS_AS( a.at(15), std::out_of_range );
}

TEST_CASE( "Output", "Cow_String")
{
    const KryuCowString a("Vasya ne lokh!");
    std::ostringstream oss;
    oss << a;
    REQUIRE( oss.str() == "Vasya ne lokh!");
    REQUIRE( oss.str() == a);
}

TEST_CASE( "Oveflow", "Cow_String")
{
    const std::string long_s("anextremelylongstringwhichhasduplicationnameinsideitselftoletteststofail");
    const std::string very_long_s = long_s + long_s;
    REQUIRE_THROWS_AS( BasicKryuCowString(very_long_s), std::length_error);
    REQUIRE_THROWS_AS( BasicKryuCowString() = very_long_s, std::length_error);
    REQUIRE_THROWS_AS( BasicKryuCowString() += very_long_s, std::length_error);
    REQUIRE_THROWS_AS( BasicKryuCowString(long_s) += long_s, std::length_error);
}
