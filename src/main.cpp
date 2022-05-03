#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "math/Rectangle2D.h"
#include "game/Entity.h"
#include "game/Components/Component.h"

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

    const auto start = std::chrono::high_resolution_clock::now();

    std::map< std::string, unsigned int > intersections;
    for( unsigned int a { 0 }; a < numberOfEntities - 1; ++a )
    {
        for( unsigned int b { a + 1 }; b < numberOfEntities; ++ b )
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
                if( !intersections.contains( key ) )
                    intersections[ key ] = 0;
                intersections[ key ] += 1;
            }
        }
    }
    std::cerr << "There are " << intersections.size() 
        << " unique intersections between " << numberOfEntities
        << " entities.\n";

    const auto end = std::chrono::high_resolution_clock::now();
    const auto runMS = std::chrono::duration_cast< std::chrono::milliseconds >( end - start );
    std::cout << "Algorithm executed in " << runMS.count() << "ms.\n";

    return 0;
}