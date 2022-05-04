#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "math/Rectangle2D.h"
#include "game/Entity.h"
#include "game/components/Component.h"
#include "game/scene/TileMap.h"

namespace SimpleAlgorithm
{
    void findUniqueIntersections(
        const std::vector< Game::Entity * > & entities
        , std::map< std::string, unsigned int > & outIntersections )
    {
        outIntersections.clear();
        std::size_t numberOfEntities = entities.size();
        for( unsigned int a { 0 }; a < numberOfEntities - 1; ++a )
        {
            for( unsigned int b { a + 1 }; b < numberOfEntities; ++b )
            {
                Game::Entity * entityA { entities[ a ] };
                Game::Entity * entityB { entities[ b ] };

                if( entityA->getUuid() == entityB->getUuid() )
                    continue;

                if( Math::isIntersectAABB( entityA->getRect(), entityB->getRect() ) )
                {
                    std::ostringstream oss;
                    oss << entityA->getUuid() << entityB->getUuid();
                    std::string key = oss.str();
                    
                    if( !outIntersections.contains( key ) )
                    {
                        outIntersections[ key ] = 0;
                    }                        
                    outIntersections[ key ] += 1;
                }
            }
        }
    }
}

namespace SpacePartitionAlgorithm
{
    void findUniqueIntersections(
        const std::vector< Game::Entity * > & entities
        , Game::TileMap & scene
        , std::map< std::string, unsigned int > & outIntersections )
    {
        outIntersections.clear();
        for( Game::Entity * entity : entities )
        {
            Game::TileMap::Bucket nearEntities;
            scene.getEntitiesNear( *entity, nearEntities );
            for( auto & kvp : nearEntities )
            {
                Game::Entity * entityA = entity;
                Game::Entity * entityB = kvp.second;
                if( kvp.second->getUuid() < entity->getUuid() )
                {
                    entityA = kvp.second;
                    entityB = entity;
                }

                if( entityA == entityB )
                {
                    continue;
                }

                if( Math::isIntersectAABB( entityA->getRect(), entityB->getRect() ) )
                {
                    std::ostringstream oss;
                    oss << entityA->getUuid() << " " << entityB->getUuid();
                    std::string key = std::move( oss.str() );

                    if( !outIntersections.contains( key ) )
                    {
                        outIntersections[ key ] = 0;
                    }                        
                    outIntersections[ key ] += 1;
                }
            }
        }
    }
}

int main( int argc, const char * argv[] )
{
    if( argc < 2 )
    {
        std::cerr << "Specify a file to run this program.\n";
        return 1;
    }

    std::string fileOpened { argv[1] };    
    std::cout << "Running program against file: " << fileOpened << "\n";
    
    std::size_t numberOfEntities { 0 };
    Math::Bounds2D minmax {};
    std::vector< Game::Entity * > entities;

    // RAII scope for file
    {
        std::ifstream file( fileOpened, std::ios::binary );
        if( !file.is_open() )
        {
            std::cerr << "Failed to open file.\n";
            return 2;
        }

        // the entityblueprints.txt provided to me have weird characters at the
        // beginning, probably some kind of header information from where this
        // file originally came from? Hence, I'm skipping those.
        char eatChar;
        auto digitPos = file.tellg();
        while( file >> eatChar && !std::isdigit( eatChar ) )
        {
            digitPos = file.tellg();
        }
        file.seekg( digitPos );

        if( !( file >> numberOfEntities ) )
        {
            std::cerr << "Failed to get number of Entities from file.\n";
            return 3;
        }
        else
        {
            std::cerr << "Loading up " << numberOfEntities << " entities...\n";
        }

        // Scene preparation
        entities.reserve( numberOfEntities );
        entities.clear();

        for( unsigned int i { 0 }; i < numberOfEntities; ++i )
        {
            float x { 0.f };
            float y { 0.f };
            float width { 0.f };
            float height { 0.f };

            if( !( file >> x >> y >> width >> height ) )
            {
                std::cerr << "Error getting bounds on line " << i + 1 << ".\n";
                return 4;
            }

            //std::cerr << "\n\tLoaded Entity: " << x << " " << y << " " << width << " " << height;

            Game::Entity * entity = new Game::Entity( x, y, width, height );
            entities.push_back( entity );
            const Math::Bounds2D & entityBounds { entity->getRect().getExtents() };
            
            //std::cerr << "\n\t\tBounds: " << entityBounds.xmin << ", " << entityBounds.ymin << " " << entityBounds.xmax << ", " << entityBounds.ymax;
            minmax.xmin = std::min( minmax.xmin, entityBounds.xmin );
            minmax.ymin = std::min( minmax.ymin, entityBounds.ymin );
            minmax.xmax = std::max( minmax.xmax, entityBounds.xmax );
            minmax.ymax = std::max( minmax.ymax, entityBounds.ymax );

            // Not every Entity has Components.
            std::string componentTypes;
            const auto currentPos = file.tellg();
            file >> componentTypes;
            if( !componentTypes.empty() && !std::isalpha( componentTypes.back() ) )
            {
                file.seekg( currentPos );
                componentTypes.clear();
            }
            
            for( const char type : componentTypes )
            {
                entity->addComponent( type );
            }
        }
        file.close();
    }

    double sceneWidth { std::max( std::fabs( minmax.xmin ), std::fabs( minmax.xmax ) ) * 2.0 };
    double sceneHeight { std::max( std::fabs( minmax.ymin ), std::fabs( minmax.ymax ) ) * 2.0 };
    std::cerr << "\n\n\tEntities Stats:"
        << "\n\tminx: " << minmax.xmin
        << "\n\tminy: " << minmax.ymin
        << "\n\tmaxx: " << minmax.xmax
        << "\n\tmaxy: " << minmax.ymax
        << "\n\twidth: " << sceneWidth
        << "\n\theight: " << sceneHeight
        << "\n\n";

    std::sort( entities.begin(), entities.end() );
    Game::TileMap scene( numberOfEntities, entities, sceneWidth, sceneHeight );

    auto start = std::chrono::high_resolution_clock::now();

    std::cerr << "\nRunning SimpleAlgorithm...\n";
    std::map< std::string, unsigned int > intersections1;
    SimpleAlgorithm::findUniqueIntersections( entities, intersections1 );
    std::cerr << "There are " << intersections1.size() 
        << " unique intersections between " << entities.size()
        << " entities.\n";

    auto end = std::chrono::high_resolution_clock::now();
    auto runMS1 = std::chrono::duration_cast< std::chrono::milliseconds >( end - start );
    std::cerr << "SimpleAlgorithm executed in " << runMS1.count() << "ms.\n";

    start = std::chrono::high_resolution_clock::now();
    std::cerr << "\nRunning SpacePartitionAlgorithm...\n";
    std::map< std::string, unsigned int > intersections2;
    SpacePartitionAlgorithm::findUniqueIntersections( entities, scene, intersections2 );
    std::cerr << "There are " << intersections2.size() 
        << " unique intersections between " << entities.size()
        << " entities.\n";

    end = std::chrono::high_resolution_clock::now();
    auto runMS2 = std::chrono::duration_cast< std::chrono::milliseconds >( end - start );
    std::cerr << "SpacePartitionAlgorithm executed in " << runMS2.count() << "ms.\n";

    // std::map< std::string, unsigned int > u;
    // u.merge( intersections1 );
    // u.merge( intersections2 );
    // for( auto & kvp : intersections2 )
    // {
    //     std::cerr << "\tExtra: " << kvp.first << " (" << kvp.second << ")\n";
    // }

    for( Game::Entity * entity : entities )
    {
        SAFE_DELETE( entity );
    }
    entities.clear();

    return 0;
}