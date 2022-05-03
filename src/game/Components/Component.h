#ifndef Game_Component_h
#define Game_Component_h

#include <typeindex>
#include <typeinfo>
#include "utils/macros.h"

namespace Game
{
    class Entity;

    class Component
    {
        public:
            Component() = delete;
            Component( Entity * owner );
            virtual ~Component() = default;

            virtual char getClassId() const = 0;
            virtual std::type_index getTypeId() const = 0;
            virtual void copy( const Component & other ) = 0;

            virtual void start() {}
            virtual void update() {}

        protected:
            VAR_SYNTHESIZE( Entity *, Owner );
    };

    class ComponentFactory
    {
        public:
            static Component * create( Entity * owner, Component * existingComponent );
            static Component * create( Entity * owner, const char classId, Component * toCopy = nullptr );

        private:
            template< typename Component_t >
            static Component_t * createOrClone( Entity * owner, Component * toCopy = nullptr )
            {
                auto original = dynamic_cast< Component_t * >( toCopy );
                if( original != nullptr )
                {
                    auto clone = new Component_t( *original );
                    clone->setOwner( owner );
                    return clone;
                }
                return new Component_t( owner );
            }
    };
}

#endif // Game_Component_h