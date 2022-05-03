#include "game/Entity.h"
#include "game/Components/Component.h"
#include "math/Rectangle2D.h"
#include "utils/UUID.h"

namespace Game
{
    Entity::Entity()
        : m_Uuid { Utils::UuidGenerator::generate() }
        , m_Rect {}
        , m_components {}
    {
    }

    Entity::Entity( const float x, const float y, const float width, const float height )
        : m_Uuid { Utils::UuidGenerator::generate() }
        , m_Rect { x, y, width, height }
        , m_components {}
    {
    }

    Entity::Entity( const Entity & other )
        : m_Uuid { Utils::UuidGenerator::generate() }
        , m_Rect { other.m_Rect }
    {
        copyComponents( other.m_components );
    }

    Entity & Entity::operator=( const Entity & other )
    {
        m_Rect = other.m_Rect;
        copyComponents( other.m_components );
        return *this;
    }

    Entity::~Entity()
    {
        clearComponents();
    }

    std::vector< Component * > Entity::getAllComponents()
    {
        std::vector< Component * > components;
        for( auto & kvp : m_components )
        {
            components.push_back( kvp.second );
        }
        return components;
    }

    void Entity::addComponent( const char classId )
    {
        auto component = ComponentFactory::create( this, classId );
        if( component )
        {
            std::type_index key = component->getTypeId();
            if( !m_components.contains( key ) )
            {
                addComponent( component->getTypeId(), component );
            }
            else
            {
                m_components[ key ]->copy( *component );
                SAFE_DELETE( component );
            }
        }
    }

    void Entity::addComponent( std::type_index key, Component * component )
    {
        if( m_components.contains( key ) )
        {
            // TODO: Warn to handle/delete existing component instance first.
        }
        m_components[ key ] = component;
    }

    void Entity::clearComponents()
    {
        for( auto & kvp : m_components )
        {
            SAFE_DELETE( kvp.second );
        }
        m_components.clear();
    }

    void Entity::copyComponents( const Entity::ComponentMap & other )
    {
        for( const auto & kvp : other )
        {
            if( !m_components.contains( kvp.first ) )
            {
                addComponent( kvp.second->getTypeId(), ComponentFactory::create( this, kvp.second->getClassId(), kvp.second ) );
            }
            else
            {
                m_components[ kvp.first ]->copy( *kvp.second );
            }
        }
    }
}