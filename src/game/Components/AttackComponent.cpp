#include "game/Components/AttackComponent.h"
#include "game/Components/Component.h"
#include "game/Entity.h"

namespace Game
{
    AttackComponent::AttackComponent( Entity * owner )
        : Component { owner }
        , m_AttackPower {}
    {
    }

    AttackComponent::AttackComponent( const AttackComponent & other )
        : Component { other.m_Owner }
        , m_AttackPower { other.m_AttackPower }
    {
    }

    AttackComponent & AttackComponent::operator=( const AttackComponent & other )
    {
        // We don't permit changing of entity owner because we can copy from
        // other entities.
        m_AttackPower = other.m_AttackPower;
        return *this;
    }
}