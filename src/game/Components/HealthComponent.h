#ifndef Game_HealthComponent_h
#define Game_HealthComponent_h

#include "game/Components/Component.h"
#include "utils/macros.h"

namespace Game
{
    class Entity;

    class HealthComponent : public Component
    {
        public:
            HealthComponent() = delete;
            HealthComponent( Entity * owner );
            HealthComponent( const HealthComponent & other );
            HealthComponent & operator=( const HealthComponent & other );

            static const char CLASS_ID = 'H';            
            char getClassId() const override
            {
                return CLASS_ID;
            }

            std::type_index getTypeId() const override
            {
                return typeid( HealthComponent );
            }

            void copy( const Component & other ) override
            {
                auto original = dynamic_cast< const HealthComponent * >( &other );
                if( original )
                {
                    *this = *original;
                }
            }

        protected:
            VAR_SYNTHESIZE( int, Health );
    };
}

#endif // Game_HealthComponent_h