#ifndef Game_TileMap_h
#define Game_TileMap_h

/// TileMap partitions the scene into adjacent Buckets covering the scene.
/// A bucket will contain a list of Entities that "touch" that bucket's area.
/// This will aid in getting a subset of Entities in the scene provided the
/// buckets of interest.

#include <map>
#include <limits.h>
#include "utils/macros.h"
#include "utils/UUID.h"
#include "math/Rectangle2D.h"

namespace Game
{
    class Entity;

    class TileMap
    {
        public:
            typedef std::map< Utils::UUID, Entity * > Bucket;
            typedef std::map< std::string, Bucket > Grid;
            
            TileMap() = delete;
            TileMap( const unsigned int divisions
                , const double sceneWidth = std::numeric_limits< double >::max()
                , const double sceneHeight = std::numeric_limits< double >::max() );
            void addEntity( Entity & entity );
            void getEntitiesNear( const Entity & entity, Bucket & outBucket );

        protected:
            void initGrid( const unsigned int divisions
                , const double sceneWidth, const double sceneHeight );
            Bucket & getBucketAt( const std::string & coordHash );
            std::string toCoordHash( const Entity & entity );
            std::string toCoordHash( const Math::Rectangle2D & rect );

            VAR_SYNTHESIZE_READONLY( unsigned int, Divisions );
            VAR_SYNTHESIZE_READONLY( double, SceneWidth );
            VAR_SYNTHESIZE_READONLY( double, SceneHeight );
            VAR_SYNTHESIZE_READONLY( Grid, Buckets );            
    };
}

#endif // Game_TileMap_h