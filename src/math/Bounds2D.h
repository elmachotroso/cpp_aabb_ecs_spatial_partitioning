#ifndef Math_Bounds2D_h
#define Math_Bounds2D_h

/// 2D Bounds, a simple 2 point representing the bottom left and top right coordinates
/// of a rectangle in a 2D cartesian plane.

namespace Math
{
    struct Bounds2D
    {
        float xmin;     ///< x of bottom left point
        float ymin;     ///< y of bottom left point

        float xmax;     ///< x of top right point
        float ymax;     ///< y of top right point

        Bounds2D()
            : xmin{ 0.f }
            , ymin{ 0.f }
            , xmax{ 0.f }
            , ymax{ 0.f }
        {

        }
    };

    inline bool isIntersectAABB( const Bounds2D & box1, const Bounds2D & box2 )
    {
        // x-dimension
        if( box1.xmin > box2.xmax ) return false;
        if( box1.xmax < box2.xmin ) return false;
        

        // y-dimension
        if( box1.ymin > box2.ymax ) return false;
        if( box1.ymax < box2.ymin ) return false;

        return true;
    }
}

#endif // Math_Bounds2D_h