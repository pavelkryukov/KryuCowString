#include <cstring>

// Google test
#include <gtest/gtest.h>

// uArchSim modules
#include "../kryucow_string.h"

TEST( Cow_String, Equality)
{
    const KryuCowString a ("Something");
    std::string a_s = "Something_strange";
    ASSERT_NE( a, a_s);
    a_s.erase( a_s.find('_'));
    ASSERT_EQ( a, a_s); 

    const std::string_view a_v = "Something_else";
    ASSERT_NE( a, a_v);
    const auto a_v1 = a_v.substr(0, 9);
    ASSERT_EQ( a, a_v1);
}

TEST( Cow_String, Copy_Check)
{
    KryuCowString a {"Hello"};
    KryuCowString b = a;
    ASSERT_EQ( a, b);
    ASSERT_EQ( a.data(), b.data());

    b += " World!";
    ASSERT_EQ( a, "Hello");
    ASSERT_NE( b, "Hello");
    ASSERT_EQ( b, "Hello World!");
    ASSERT_NE( a, b);
    ASSERT_NE( a.data(), b.data());
}

TEST( Cow_String, Assignment_Check)
{
    KryuCowString a {"Hello"};
    const KryuCowString b = a;
    ASSERT_EQ( a, b);
    ASSERT_EQ( a.data(), b.data());

    a = "Goodbye!";
    ASSERT_EQ( a, "Goodbye!");
    ASSERT_EQ( b, "Hello");
    ASSERT_NE( a, b);
    ASSERT_NE( a.data(), b.data());
}

TEST( Cow_String, Empty_String)
{
    KryuCowString a;
    ASSERT_EQ( a, "");
    ASSERT_TRUE( a.empty());
    KryuCowString b = a;
    ASSERT_EQ( b, "");
    ASSERT_TRUE( b.empty());

    a = "Hello!";
    ASSERT_EQ( a, "Hello!");
    ASSERT_FALSE( a.empty());
    ASSERT_EQ( b, "");
    ASSERT_TRUE( b.empty());
    ASSERT_NE( a, b);

    a = "";
    ASSERT_EQ( a, "");
    ASSERT_TRUE( a.empty());

    b = "Goodbye!";
    ASSERT_EQ( b, "Goodbye!");
    ASSERT_NE( a, b);

    KryuCowString c;
    const KryuCowString d = c;
    ASSERT_EQ( c, "");
    ASSERT_TRUE( c.empty());
    c += "World!";
    ASSERT_EQ( c, "World!");
    ASSERT_EQ( d, "");
}

TEST( Wide_Cow_String, Initializing_Checks)
{
    WKryuCowString a;
    const WKryuCowString b = a;
    ASSERT_EQ( a, b);

    WKryuCowString c( L"Hello!");
    ASSERT_EQ( c, L"Hello!");

    a += c;
    ASSERT_EQ( a, c);
    ASSERT_NE( a, b);
    ASSERT_EQ( a, L"Hello!");

    c += a;
    ASSERT_EQ( c, L"Hello!Hello!");
    ASSERT_EQ( a, L"Hello!");
}

TEST( Cow_String, At)
{
    const KryuCowString a("Hello Goodbye!");
    ASSERT_EQ( a.length(), std::strlen("Hello Goodbye!"));
    ASSERT_EQ( a[0], 'H');
    ASSERT_EQ( a.front(), 'H');
    ASSERT_EQ( a.back(), '!');
    ASSERT_EQ( a.at(3), 'l');
    ASSERT_EQ( a[4], 'o');
}

int main( int argc, char* argv[])
{
    ::testing::InitGoogleTest( &argc, argv);
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}

