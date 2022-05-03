#include <sstream>
#include "game/scene/TileMap.h"
#include "game/Entity.h"

namespace Game
{
    TileMap::TileMap( const unsigned int divisions
        , const double sceneWidth
        , const double sceneHeight )
        : m_Divisions {}
        , m_SceneWidth {}
        , m_SceneHeight {}
        , m_Buckets {}
    {
        initGrid( divisions, sceneWidth, sceneHeight );
    }

    void TileMap::addEntity( Entity & entity )
    {
        const std::string coordHash { toCoordHash( entity ) };
        TileMap::Bucket & bucket { getBucketAt( coordHash ) };
        bucket[ entity.getUuid() ] = &entity;
    }

    void TileMap::getEntitiesNear( const Entity & entity, TileMap::Bucket & outBucket )
    {
        const std::string coordHash { toCoordHash( entity ) };
        TileMap::Bucket & bucket { getBucketAt( coordHash ) };
        outBucket.insert( bucket.begin(), bucket.end() );
    }

    void TileMap::initGrid( const unsigned int divisions
        , const double sceneWidth, const double sceneHeight )
    {
        m_Buckets.clear();
        m_Divisions = divisions;
        m_SceneWidth = sceneWidth;
        m_SceneHeight = sceneHeight;
    }

    TileMap::Bucket & TileMap::getBucketAt( const std::string & coordHash )
    {
        if( !m_Buckets.contains( coordHash ) )
        {
            m_Buckets[ coordHash ] = {};
        }
        return m_Buckets[ coordHash ];
    }

    std::string TileMap::toCoordHash( const Entity & entity )
    {
        return toCoordHash( entity.getRect() );
    }

    std::string TileMap::toCoordHash( const Math::Rectangle2D & rect )
    {
        std::ostringstream oss;
        return oss.str();
    }
}