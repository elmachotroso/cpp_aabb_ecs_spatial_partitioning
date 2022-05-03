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

namespace SlowAlgorithm
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

                std::ostringstream oss;
                oss << entityA->getUuid() << entityB->getUuid();
                std::string key = oss.str();

                if( Math::isIntersectAABB( entityA->getRect(), entityB->getRect() ) )
                {
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

                std::ostringstream oss;
                oss << entityA->getUuid() << entityB->getUuid();
                std::string key = oss.str();

                if( Math::isIntersectAABB( entityA->getRect(), entityB->getRect() ) )
                {
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
    std::vector< Game::Entity * > entities;
    Game::TileMap scene( 1 );

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

            Game::Entity * entity = new Game::Entity( x, y, width, height );
            entities.push_back( entity );
            scene.addEntity( *entity );

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

    std::sort( entities.begin(), entities.end() );

    auto start = std::chrono::high_resolution_clock::now();

    std::map< std::string, unsigned int > intersections1;
    SlowAlgorithm::findUniqueIntersections( entities, intersections1 );
    std::cerr << "There are " << intersections1.size() 
        << " unique intersections between " << entities.size()
        << " entities.\n";

    auto end = std::chrono::high_resolution_clock::now();
    auto runMS1 = std::chrono::duration_cast< std::chrono::milliseconds >( end - start );
    std::cerr << "SlowAlgorithm executed in " << runMS1.count() << "ms.\n";

    start = std::chrono::high_resolution_clock::now();

    std::map< std::string, unsigned int > intersections2;
    SpacePartitionAlgorithm::findUniqueIntersections( entities, scene, intersections1 );
    std::cerr << "There are " << intersections2.size() 
        << " unique intersections between " << entities.size()
        << " entities.\n";

    end = std::chrono::high_resolution_clock::now();
    auto runMS2 = std::chrono::duration_cast< std::chrono::milliseconds >( end - start );
    std::cerr << "SpacePartitionAlgorithm executed in " << runMS2.count() << "ms.\n";

    for( Game::Entity * entity : entities )
    {
        SAFE_DELETE( entity );
    }
    entities.clear();

    return 0;
}