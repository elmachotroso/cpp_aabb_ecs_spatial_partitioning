#include "game/Components/HealthComponent.h"
#include "game/Components/Component.h"
#include "game/Entity.h"

namespace Game
{
    HealthComponent::HealthComponent( Entity * owner )
        : Component { owner }
        , m_Health {}
    {
    }

    HealthComponent::HealthComponent( const HealthComponent & other )
        : Component { other.m_Owner }
        , m_Health { other.m_Health }
    {
    }

    HealthComponent & HealthComponent::operator=( const HealthComponent & other )
    {
        // We don't permit changing of entity owner because we can copy from
        // other entities.
        m_Health = other.m_Health;
        return *this;
    }
}