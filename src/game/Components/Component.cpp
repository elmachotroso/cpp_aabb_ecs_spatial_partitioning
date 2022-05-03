#include <iostream>
#include <string>

#include "game/Entity.h"
#include "game/Components/Component.h"
#include "game/Components/AttackComponent.h"
#include "game/Components/HealthComponent.h"
#include "game/Components/MovementComponent.h"

namespace Game
{
    Component::Component( Entity * owner )
        : m_Owner( owner )
    {
    }

    Component * ComponentFactory::create( Entity * owner, Component * existingComponent )
    {
        if( !existingComponent )
            return nullptr;

        return create( owner, existingComponent->getClassId() );
    }

    Component * ComponentFactory::create( Entity * owner, const char classId, Component * toCopy /*= nullptr*/ )
    {
        switch( classId )
        {
            case HealthComponent::CLASS_ID:
                return createOrClone< HealthComponent >( owner, toCopy );
                break;
            case AttackComponent::CLASS_ID:
                return createOrClone< AttackComponent >( owner, toCopy );
                break;
            case MovementComponent::CLASS_ID:
                return createOrClone< MovementComponent >( owner, toCopy );
                break;
            default:
                {
                    std::cerr << "Encountered unknown Component with class id: " << classId << std::endl;
                }
                break;
        }
        
        return nullptr;
    }
}