#ifndef Game_TileMap_h
#define Game_TileMap_h

/// TileMap partitions the scene into adjacent Buckets covering the scene.
/// A bucket will contain a list of Entities that "touch" that bucket's area.
/// This will aid in getting a subset of Entities in the scene provided the
/// buckets of interest.

#include <vector>
#include <map>
#include <limits.h>
#include "utils/macros.h"
#include "utils/UUID.h"
#include "math/Bounds2D.h"
#include "math/Rectangle2D.h"

namespace Game
{
    class Entity;

    class TileMap
    {
        public:
            typedef std::pair< unsigned int, unsigned int > BucketCoord;
            typedef std::map< Utils::UUID, Entity * > Bucket;            
            typedef std::map< BucketCoord, Bucket > Grid;
            
            
            TileMap() = delete;
            TileMap( const unsigned int divisions
                , const std::vector< Entity * > & listOfEntities = {}
                , const double sceneWidth = LIMIT_MAX_FLOAT * 2
                , const double sceneHeight = LIMIT_MAX_FLOAT * 2 );
            void addEntity( Entity & entity );
            void removeEntity( Entity & entity );
            Bucket & getBucketAt( const BucketCoord & bucketCoord );
            std::vector< BucketCoord > getBucketCoordsFor( const Entity & entity );
            TileMap::Bucket getEntitiesNear( const Entity & entity );

        protected:
            void initGrid( const unsigned int divisions
                , const double sceneWidth, const double sceneHeight );
            BucketCoord toCoord( const float x, const float y );

            VAR_SYNTHESIZE_READONLY( unsigned int, Divisions );
            VAR_SYNTHESIZE_READONLY( double, SceneWidth );
            VAR_SYNTHESIZE_READONLY( double, SceneHeight );
            VAR_SYNTHESIZE_READONLY( Grid, Buckets );
            double m_cellWidth;
            double m_cellHeight;
            Math::Bounds2D m_sceneExtents;     
    };
}

#endif // Game_TileMap_h