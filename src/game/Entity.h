#ifndef Game_Entity_h
#define Game_Entity_h

#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <map>
#include <vector>

#include "math/Rectangle2D.h"
#include "utils/macros.h"
#include "utils/UUID.h"

namespace Game
{
    class Component;

    class Entity
    {
        public:
            typedef std::map< std::type_index, Component * > ComponentMap;

            Entity();
            Entity( const float x, const float y, const float width, const float height );
            Entity( const Entity & other );
            Entity & operator=( const Entity & other );
            ~Entity();

            inline std::size_t getComponentsCount() const
            {
                return m_components.size();
            }

            template< typename Component_t >
            inline Component_t * getComponent();

            std::vector< Component * > getAllComponents();

            template< typename Component_t >
            inline Component_t * addComponent();

            template< typename Component_t >
            inline void addComponent( Component_t * component );

            void addComponent( const char classId );
            void addComponent( std::type_index key, Component * component );

            template< typename Component_t >
            inline void removeComponent();

            void clearComponents();

            // less operator override for sorting
            bool operator<( const Entity & rhs )
            {
                return m_Uuid < rhs.m_Uuid;
            }

        protected:
            VAR_SYNTHESIZE_READONLY( Utils::UUID, Uuid );
            VAR_SYNTHESIZE_REF_READONLY( Math::Rectangle2D, Rect );

        private:
            void copyComponents( const ComponentMap & other );

            ComponentMap m_components;
    };

    template< typename Component_t >
    inline Component_t * Entity::getComponent()
    {
        static_assert( std::is_convertible< Component_t *, Component * >::value, "Must be derived from Component class." );
        std::type_index key = typeid( Component_t );
        if( m_components.contains( key ) )
        {
            return dynamic_cast< Component_t * >( m_components[ key ] );
        }
        return nullptr;
    }

    template< typename Component_t >
    inline Component_t * Entity::addComponent()
    {
        static_assert( std::is_convertible< Component_t *, Component * >::value, "Must be derived from Component class." );
        std::type_index key = typeid( Component_t );
        if( !m_components.contains( key ) )
        {
            m_components[ key ] = new Component_t( this );
        }
        return dynamic_cast< Component_t * >( m_components[ key ] );
    }

    template< typename Component_t >
    inline void Entity::addComponent( Component_t * component )
    {
        static_assert( std::is_convertible< Component_t *, Component * >::value, "Must be derived from Component class." );
        std::type_index key = typeid( Component_t );
        addComponent( key, component );
    }

    template< typename Component_t >
    inline void Entity::removeComponent()
    {
        static_assert( std::is_convertible< Component_t *, Component * >::value, "Must be derived from Component class." );
        std::type_index key = typeid( Component_t );
        if( m_components.contains( key ) )
        {
            SAFE_DELETE( m_components[ key ] );
            m_components.erase( key );
        }
    }
}

#endif // Game_Entity_h