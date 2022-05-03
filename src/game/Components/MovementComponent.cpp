#include "game/Components/MovementComponent.h"
#include "game/Components/Component.h"
#include "game/Entity.h"

namespace Game
{
    MovementComponent::MovementComponent( Entity * owner )
        : Component { owner }
        , m_Speed {}
    {
    }

    MovementComponent::MovementComponent( const MovementComponent & other )
        : Component { other.m_Owner }
        , m_Speed { other.m_Speed }
    {
    }

    MovementComponent & MovementComponent::operator=( const MovementComponent & other )
    {
        // We don't permit changing of entity owner because we can copy from
        // other entities.
        m_Speed = other.m_Speed;
        return *this;
    }
}