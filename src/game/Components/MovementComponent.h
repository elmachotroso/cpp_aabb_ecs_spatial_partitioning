#ifndef Game_MovementComponent_h
#define Game_MovementComponent_h

#include "game/Components/Component.h"
#include "utils/macros.h"

namespace Game
{
    class MovementComponent : public Component
    {
        public:
            MovementComponent() = delete;
            MovementComponent( Entity * owner );
            MovementComponent( const MovementComponent & other );
            MovementComponent & operator=( const MovementComponent & other );

            static const char CLASS_ID = 'M';            
            char getClassId() const override
            {
                return CLASS_ID;
            }

            std::type_index getTypeId() const override
            {
                return typeid( MovementComponent );
            }

            void copy( const Component & other ) override
            {
                auto original = dynamic_cast< const MovementComponent * >( &other );
                if( original )
                {
                    *this = *original;
                }
            }

        protected:
            VAR_SYNTHESIZE( float, Speed );
    };
}

#endif // Game_MovementComponent_h