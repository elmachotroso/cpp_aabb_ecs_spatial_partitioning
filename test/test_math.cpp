#include <gtest/gtest.h>
#include <limits>
#include "utils/macros.h"
#include "math/Rectangle2D.h"

TEST( Math, Epsilon_Test ) {
    float a { 1.f };
    float b { 0.f };

    bool expected = false;
    bool actual = Math::isEqualEpsilon( a, b );
    EXPECT_EQ( expected, actual );
    
    // result symmetry check
    actual = Math::isEqualEpsilon( b, a );
    EXPECT_EQ( expected, actual );

    a = 2.f;
    b = 1.999999999999f;
    expected = true;
    actual = Math::isEqualEpsilon( a, b );
    EXPECT_EQ( expected, actual );
    
    // result symmetry check
    actual = Math::isEqualEpsilon( b, a );
    EXPECT_EQ( expected, actual );
}

TEST( Rectangle2D, Two_Boxes_Intersect ) {
    const Math::Rectangle2D rect1{ -0.5f, -0.5f, 2.f, 2.f };
    const Math::Rectangle2D rect2{ 0.5f, 0.5f, 2.f, 2.f };
    bool expected = true;
    bool actual = Math::isIntersectAABB( rect1, rect2 );
    EXPECT_EQ( expected, actual );

    // result symmetry check
    actual = Math::isIntersectAABB( rect2, rect1 );
    EXPECT_EQ( expected, actual );
}

TEST( Rectangle2D, Two_Boxes_Edge_Intersect ) {
    const Math::Rectangle2D rect1{ -1.0f, -1.0f, 2.f, 2.f };
    const Math::Rectangle2D rect2{ 0.0f, 0.0f, 2.f, 2.f };
    bool expected = true;
    bool actual = Math::isIntersectAABB( rect1, rect2 );
    EXPECT_EQ( expected, actual );
    
    // result symmetry check
    actual = Math::isIntersectAABB( rect2, rect1 );
    EXPECT_EQ( expected, actual );
}

TEST( Rectangle2D, Box_Within_Box_Intersect ) {
    const Math::Rectangle2D rect1{ 1.f, 2.f, 2.f, 2.f };
    const Math::Rectangle2D rect2{ 0.f, 0.f, 6.f, 6.f };
    bool expected = true;
    bool actual = Math::isIntersectAABB( rect1, rect2 );
    EXPECT_EQ( expected, actual );

    // result symmetry check
    actual = Math::isIntersectAABB( rect2, rect1 );
    EXPECT_EQ( expected, actual );
}

TEST( Rectangle2D, Two_Boxes_No_Intersect ) {
    const Math::Rectangle2D rect1{ -4.f, 0.f, 1.f, 1.f };
    const Math::Rectangle2D rect2{ 4.f, 0.f, 1.f, 1.f };
    bool expected = false;
    bool actual = Math::isIntersectAABB( rect1, rect2 );
    EXPECT_EQ( expected, actual );

    // result symmetry check
    actual = Math::isIntersectAABB( rect2, rect1 );
    EXPECT_EQ( expected, actual );
}

TEST( Rectangle2D, Point_And_Box_Intersect ) {
    const Math::Rectangle2D rect1{ 0.f, 0.f, 0.f, 0.f }; // considered to be a point
    const Math::Rectangle2D rect2{ 0.f, 0.f, 3.f, 3.f };
    bool expected = true;
    bool actual = Math::isIntersectAABB( rect1, rect2 );
    EXPECT_EQ( expected, actual );

    // result symmetry check
    actual = Math::isIntersectAABB( rect2, rect1 );
    EXPECT_EQ( expected, actual );
}

TEST( Rectangle2D, Limits_TopLeft_vs_BottomRight_Small ) {
    const float floatMax { LIMIT_MAX_FLOAT };
    const float halfFloatMax { floatMax * 0.5f };
    const Math::Rectangle2D rect1{ -floatMax, floatMax, halfFloatMax, halfFloatMax }; // top left
    const Math::Rectangle2D rect2{ floatMax, -floatMax, halfFloatMax, halfFloatMax }; // bottom right
    bool expected = false;
    bool actual = Math::isIntersectAABB( rect1, rect2 );
    EXPECT_EQ( expected, actual );

    // result symmetry check
    actual = Math::isIntersectAABB( rect2, rect1 );
    EXPECT_EQ( expected, actual );
}

TEST( Rectangle2D, Limits_TopLeft_vs_BottomRight_Big ) {
    const float floatMax { LIMIT_MAX_FLOAT };
    const float halfFloatMax { floatMax * 0.5f };
    const Math::Rectangle2D rect1{ -halfFloatMax, halfFloatMax, floatMax, floatMax }; // top left
    const Math::Rectangle2D rect2{ halfFloatMax, -halfFloatMax, floatMax, floatMax }; // bottom right
    bool expected = true;
    bool actual = Math::isIntersectAABB( rect1, rect2 );
    EXPECT_EQ( expected, actual );

    // result symmetry check
    actual = Math::isIntersectAABB( rect2, rect1 );
    EXPECT_EQ( expected, actual );
}