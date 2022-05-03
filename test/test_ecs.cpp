#include <gtest/gtest.h>
#include <iostream>
#include "utils/UUID.h"
#include "game/Entity.h"
#include "game/Components/Component.h"
#include "game/Components/AttackComponent.h"
#include "game/Components/HealthComponent.h"
#include "game/Components/MovementComponent.h"

TEST( EntityComponentSystem, Entity_Creation ) {
    Game::Entity test;
    EXPECT_NE( Utils::UUID_INVALID, test.getUuid() );
}

TEST( EntityComponentSystem, Entity_Add_MovementComponent ) {
    Game::Entity test;
    EXPECT_NE( Utils::UUID_INVALID, test.getUuid() );
    
    // Add MovementComponent
    test.addComponent< Game::MovementComponent >();
    auto mover = test.getComponent< Game::MovementComponent >();
    EXPECT_NE( nullptr, mover );
    
    // Test MovementComponent
    const auto speed = 54.f;
    mover->setSpeed( speed );
    EXPECT_EQ( speed, mover->getSpeed() );
}

TEST( EntityComponentSystem, Entity_Add_HealthComponent ) {
    Game::Entity test;
    EXPECT_NE( Utils::UUID_INVALID, test.getUuid() );

    // Add HealthComponent
    test.addComponent< Game::HealthComponent >();
    auto health = test.getComponent< Game::HealthComponent >();
    EXPECT_NE( nullptr, health );
    
    // Test HealthComponent
    const auto hp = 2500;
    health->setHealth( hp );
    EXPECT_EQ( hp, health->getHealth() );
}

TEST( EntityComponentSystem, Entity_Add_AttackComponent ) {
    Game::Entity test;
    EXPECT_NE( Utils::UUID_INVALID, test.getUuid() );
    
    // Add AttackComponent
    test.addComponent< Game::AttackComponent >();
    auto attack = test.getComponent< Game::AttackComponent >();
    EXPECT_NE( nullptr, attack );
    
    // Test AttackComponent
    const auto power = 999999999u;
    attack->setAttackPower( power );
    EXPECT_EQ( power, attack->getAttackPower() );
}

TEST( EntityComponentSystem, Entity_Check_ComponentsCount ) {
    Game::Entity test;
    EXPECT_NE( Utils::UUID_INVALID, test.getUuid() );
    
    // Add MovementComponent
    test.addComponent< Game::MovementComponent >();
    auto mover = test.getComponent< Game::MovementComponent >();
    EXPECT_NE( nullptr, mover );
    
    // Add HealthComponent
    test.addComponent< Game::HealthComponent >();
    auto health = test.getComponent< Game::HealthComponent >();
    EXPECT_NE( nullptr, health );
    
    // Add AttackComponent
    test.addComponent< Game::AttackComponent >();
    auto attack = test.getComponent< Game::AttackComponent >();
    EXPECT_NE( nullptr, attack );
    
    // Check components size
    EXPECT_EQ( 3, test.getComponentsCount() );
    EXPECT_EQ( 3, test.getAllComponents().size() );
}

TEST( EntityComponentSystem, Entity_Add_Already_Existing ) {
    Game::Entity test;
    EXPECT_NE( Utils::UUID_INVALID, test.getUuid() );
    
    // Add MovementComponent
    test.addComponent< Game::MovementComponent >();
    auto mover = test.getComponent< Game::MovementComponent >();
    EXPECT_NE( nullptr, mover );

    // Add HealthComponent
    test.addComponent< Game::HealthComponent >();
    auto health = test.getComponent< Game::HealthComponent >();
    EXPECT_NE( nullptr, health );

    // Add AttackComponent
    test.addComponent< Game::AttackComponent >();
    auto attack = test.getComponent< Game::AttackComponent >();
    EXPECT_NE( nullptr, attack );

    // Check components size
    EXPECT_EQ( 3, test.getComponentsCount() );
    EXPECT_EQ( 3, test.getAllComponents().size() );

    // Try to add already existing component, which should do nothing.
    test.addComponent< Game::AttackComponent >();
    auto attack2 = test.getComponent< Game::AttackComponent >();
    EXPECT_EQ( attack, attack2 );
    EXPECT_EQ( 3, test.getComponentsCount() );
}

TEST( EntityComponentSystem, Entity_Remove_Component ) {
    Game::Entity test;
    EXPECT_NE( Utils::UUID_INVALID, test.getUuid() );
    
    // Add MovementComponent
    test.addComponent< Game::MovementComponent >();
    auto mover = test.getComponent< Game::MovementComponent >();
    EXPECT_NE( nullptr, mover );

    // Add HealthComponent
    test.addComponent< Game::HealthComponent >();
    auto health = test.getComponent< Game::HealthComponent >();
    EXPECT_NE( nullptr, health );

    // Add AttackComponent
    test.addComponent< Game::AttackComponent >();
    auto attack = test.getComponent< Game::AttackComponent >();
    EXPECT_NE( nullptr, attack );

    // Check components size
    EXPECT_EQ( 3, test.getComponentsCount() );
    EXPECT_EQ( 3, test.getAllComponents().size() );

    // Remove existing component, should reduce the size of components.
    test.removeComponent< Game::AttackComponent >();
    auto removedAttackComponent = test.getComponent< Game::AttackComponent >();
    EXPECT_EQ( nullptr, removedAttackComponent );
    EXPECT_EQ( 2, test.getComponentsCount() );

    // Remove non-existing component, components size should be the same.
    test.removeComponent< Game::AttackComponent >();
    auto removedAttackComponent2 = test.getComponent< Game::AttackComponent >();
    EXPECT_EQ( nullptr, removedAttackComponent2 );
    EXPECT_EQ( 2, test.getComponentsCount() );
}

TEST( EntityComponentSystem, Entity_ClearComponents ) {
    Game::Entity test;
    EXPECT_NE( Utils::UUID_INVALID, test.getUuid() );
    
    // Add MovementComponent
    test.addComponent< Game::MovementComponent >();
    auto mover = test.getComponent< Game::MovementComponent >();
    EXPECT_NE( nullptr, mover );

    // Add HealthComponent
    test.addComponent< Game::HealthComponent >();
    auto health = test.getComponent< Game::HealthComponent >();
    EXPECT_NE( nullptr, health );

    // Add AttackComponent
    test.addComponent< Game::AttackComponent >();
    auto attack = test.getComponent< Game::AttackComponent >();
    EXPECT_NE( nullptr, attack );

    // Check components size
    EXPECT_EQ( 3, test.getComponentsCount() );
    EXPECT_EQ( 3, test.getAllComponents().size() );

    // Clear all components
    test.clearComponents();
    EXPECT_EQ( 0, test.getComponentsCount() );
}

TEST( EntityComponentSystem, Entity_Deep_Copy ) {
    Game::Entity test;
    EXPECT_NE( Utils::UUID_INVALID, test.getUuid() );
    
    // Add MovementComponent
    test.addComponent< Game::MovementComponent >();
    auto mover = test.getComponent< Game::MovementComponent >();
    EXPECT_NE( nullptr, mover );

    // Add HealthComponent
    test.addComponent< Game::HealthComponent >();
    auto health = test.getComponent< Game::HealthComponent >();
    EXPECT_NE( nullptr, health );

    // Add AttackComponent
    test.addComponent< Game::AttackComponent >();
    auto attack = test.getComponent< Game::AttackComponent >();
    EXPECT_NE( nullptr, attack );
    
    // Check components size
    EXPECT_EQ( 3, test.getComponentsCount() );
    EXPECT_EQ( 3, test.getAllComponents().size() );

    // Create new Entity that copies first entity.
    Game::Entity clone( test );
    EXPECT_NE( &test, &clone );
    EXPECT_EQ( test.getComponentsCount(), clone.getComponentsCount() );
    EXPECT_NE( nullptr, clone.getComponent< Game::HealthComponent >() );
    EXPECT_NE( nullptr, clone.getComponent< Game::MovementComponent >() );
    EXPECT_NE( test.getComponent< Game::HealthComponent >(), clone.getComponent< Game::HealthComponent >() );
    EXPECT_EQ( test.getComponent< Game::HealthComponent >()->getHealth(), clone.getComponent< Game::HealthComponent >()->getHealth() );
    EXPECT_NE( test.getComponent< Game::MovementComponent >(), clone.getComponent< Game::MovementComponent >() );
    EXPECT_EQ( test.getComponent< Game::MovementComponent >()->getSpeed(), clone.getComponent< Game::MovementComponent >()->getSpeed() );
}
