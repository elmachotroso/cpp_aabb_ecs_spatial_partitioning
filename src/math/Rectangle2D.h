#ifndef Math_Rectangle2D_h
#define Math_Rectangle2D_h

/// 2D Rectangle having the point of origin at the center of the rectangle
/// with specified size (width, height).

#include <limits>
#include <cmath>
#include "math/math.h"
#include "math/Bounds2D.h"

namespace Math
{
    class Rectangle2D
    {
        public:
            Rectangle2D()
                : m_x{ 0.f }
                , m_y{ 0.f }
                , m_width{ 0.f }
                , m_height{ 0.f }
            {
                updateBounds();
            }

            Rectangle2D( const float x, const float y, const float width, const float height )
            {
                setPositionAndSize( x, y, width, height );
            }

            inline void updateBounds( Bounds2D & outb, const float x, const float y, const float width, const float height )
            {
                const float halfWidth { width * 0.5f };
                const float halfHeight { height * 0.5f };

                // to ensure we don't overflow or underflow float range
                const float floatMin = std::numeric_limits< float >::lowest();
                const float floatMax = std::numeric_limits< float >::max();
                const double dx = x;
                const double dy = y;

                outb.xmin = ( dx - halfWidth < floatMin ) ? floatMin : x - halfWidth;
                outb.xmax = ( dx + halfWidth > floatMax ) ? floatMax : x + halfWidth;
                outb.ymin = ( dy - halfHeight < floatMin ) ? floatMin : y - halfHeight;
                outb.ymax = ( dy + halfHeight > floatMax ) ? floatMax : y + halfHeight;
            }

            inline void updateBounds()
            {
                updateBounds( m_extents, m_x, m_y, m_width, m_height );
            }

            inline const float & getX() const { return m_x; }
            inline const float & getY() const { return m_y; }
            inline const float & getWidth() const { return m_width; }
            inline const float & getHeight() const { return m_height; }
            inline const Bounds2D & getExtents() const { return m_extents; }
            
            inline void setPositionAndSize( const float x, const float y, const float width, const float height )
            {
                m_x = x;
                m_y = y;
                m_width = width;
                m_height = height;
                updateBounds();
            }

            // TODO: Other setters for Position & Size, which all cases calls updateBounds().

        private:
            float m_x;              ///< origin x (center of rect)
            float m_y;              ///< origin y (center of rect)
            float m_width;          ///< width of the rect
            float m_height;         ///< height of the rect
            Bounds2D m_extents;     ///< bottom left and top right points
    };    

    inline bool isIntersectAABB( const Rectangle2D & rect1, const Rectangle2D & rect2 )
    {
        return isIntersectAABB( rect1.getExtents(), rect2.getExtents() );
    }
}

#endif // Math_Rectangle2D_h