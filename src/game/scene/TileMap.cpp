#include <sstream>
#include <algorithm>
#include "utils/macros.h"
#include "game/scene/TileMap.h"
#include "game/Entity.h"
#include "math/Bounds2D.h"
#include "math/Rectangle2D.h"

#include <iostream>

namespace Game
{
    TileMap::TileMap( const unsigned int divisions
        , const std::vector< Entity * > & listOfEntities
        , const double sceneWidth
        , const double sceneHeight )
    {
        initGrid( divisions, sceneWidth, sceneHeight );
        for( Entity * entity : listOfEntities )
        {
            addEntity( *entity );
        }
    }

    void TileMap::addEntity( Entity & entity )
    {
        std::vector< BucketCoord > bucketCoords;
        getBucketCoordsFor( entity, bucketCoords );
        for( auto & coord : bucketCoords )
        {
            getBucketAt( coord )[ entity.getUuid() ] = &entity;
        }
    }

    void TileMap::removeEntity( Entity & entity )
    {
        std::vector< BucketCoord > bucketCoords;
        getBucketCoordsFor( entity, bucketCoords );
        for( auto & coord : bucketCoords )
        {
            getBucketAt( coord ).erase( entity.getUuid() );
        }
    }

    TileMap::Bucket & TileMap::getBucketAt( const TileMap::BucketCoord & bucketCoord )
    {
        if( !m_Buckets.contains( bucketCoord ) )
        {
            m_Buckets[ bucketCoord ] = {};
        }
        return m_Buckets[ bucketCoord ];
    }

    void TileMap::getBucketCoordsFor( const Entity & entity, std::vector< TileMap::BucketCoord > & outCoords )
    {
        const Math::Bounds2D & bounds { entity.getRect().getExtents() };
        BucketCoord min;
        toCoord( bounds.xmin, bounds.ymin, min );
        BucketCoord max;
        toCoord( bounds.xmax, bounds.ymax, max );

        for( auto y = min.second; y <= max.second; ++y )
        {
            for( auto x = min.first; x <= max.first; ++x )
            {
                outCoords.emplace_back( BucketCoord { x, y } );
            }
        }
    }

    void TileMap::getEntitiesNear( const Entity & entity, TileMap::Bucket & outBucket )
    {
        std::vector< BucketCoord > nearBucketCoords;
        getBucketCoordsFor( entity, nearBucketCoords );
        for( BucketCoord & coord : nearBucketCoords )
        {
            Bucket & bucket { getBucketAt( coord ) };
            outBucket.insert( bucket.begin(), bucket.end() );
        }
        outBucket.erase( entity.getUuid() );
    }

    void TileMap::initGrid( const unsigned int divisions
        , const double sceneWidth, const double sceneHeight )
    {
        m_Buckets.clear();
        m_Divisions = std::max( divisions , 1u );
        m_SceneWidth = std::clamp( sceneWidth, 1.0, LIMIT_MAX_FLOAT * 2.0 );
        m_SceneHeight = std::clamp( sceneHeight, 1.0, LIMIT_MAX_FLOAT * 2.0 );
        m_cellWidth = m_SceneWidth / m_Divisions;
        m_cellHeight = m_SceneHeight / m_Divisions;
        m_sceneExtents.xmin = - static_cast< float >( m_SceneWidth * 0.5f );
        m_sceneExtents.xmax = static_cast< float >( m_SceneWidth * 0.5f );
        m_sceneExtents.ymin = - static_cast< float >( m_SceneHeight * 0.5f );
        m_sceneExtents.ymax = static_cast< float >( m_SceneHeight * 0.5f );

        std::cerr << "\tDivisions: " << m_Divisions
            << "\n\tSceneWidth, SceneHeight: " << m_SceneWidth << ", " << m_SceneHeight
            << "\n\tcellWidth, cellHeight: " << m_cellWidth << ", " << m_cellHeight
            << "\n\txmin, ymin: " << m_sceneExtents.xmin << ", " << m_sceneExtents.ymin 
            << "\n\txmax, ymax: " << m_sceneExtents.xmax << ", " << m_sceneExtents.ymax
            << std::endl;
    }

    void TileMap::toCoord( const float x, const float y, TileMap::BucketCoord & outCoord )
    {
        outCoord.first = std::floor( ( x - m_sceneExtents.xmin ) / m_cellWidth );
        outCoord.second = std::floor( ( y - m_sceneExtents.ymin ) / m_cellHeight );
    }
}