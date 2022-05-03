#ifndef Game_AttackComponent_h
#define Game_AttackComponent_h

#include <typeindex>
#include <typeinfo>
#include "game/Components/Component.h"
#include "utils/macros.h"

namespace Game
{
    class Entity;
    
    class AttackComponent : public Component
    {
        public:
            AttackComponent() = delete;
            AttackComponent( Entity * owner );
            AttackComponent( const AttackComponent & other );
            AttackComponent & operator=( const AttackComponent & other );

            static const char CLASS_ID = 'A';            
            char getClassId() const override
            {
                return CLASS_ID;
            }

            std::type_index getTypeId() const override
            {
                return typeid( AttackComponent );
            }

            void copy( const Component & other ) override
            {
                auto original = dynamic_cast< const AttackComponent * >( &other );
                if( original )
                {
                    *this = *original;
                }
            }

        protected:
            VAR_SYNTHESIZE( unsigned int, AttackPower );
    };
}

#endif // Game_AttackComponent_h