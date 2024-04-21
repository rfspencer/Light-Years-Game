add_executable(${LIGHT_YEARS_GAME_TARGET_NAME}
        include/gameFramework/GameApplication.h
        src/gameFramework/GameApplication.cpp

        src/spaceship/SpaceShip.cpp
        include/spaceship/SpaceShip.h

        src/player/PlayerSpaceShip.cpp
        include/player/PlayerSpaceShip.h

        src/weapon/Shooter.cpp
        include/weapon/Shooter.h

        src/weapon/BulletShooter.cpp
        include/weapon/BulletShooter.h

        src/weapon/Bullet.cpp
        include/weapon/Bullet.h

        src/gameplay/HealthComponent.cpp
        include/gameplay/HealthComponent.h

        src/VFX/Explosion.cpp
        include/VFX/Explosion.h

        src/Enemy/EnemySpaceship.cpp
        include/Enemy/EnemySpaceship.h

        src/Enemy/Vanguard.cpp
        include/Enemy/Vanguard.h

        src/Level/GameLevelOne.cpp
        include/Level/GameLevelOne.h

        src/Enemy/VanguardStage.cpp
        include/Enemy/VanguardStage.h

        src/Enemy/TwinBlade.cpp
        include/Enemy/TwinBlade.h

        src/Enemy/TwinBladeStage.cpp
        include/Enemy/TwinBladeStage.h

        src/Enemy/Hexagon.cpp
        include/Enemy/Hexagon.h

        src/Enemy/HexagonStage.cpp
        include/Enemy/HexagonStage.h
)

target_include_directories(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC
        include/
)

target_link_libraries(${LIGHT_YEARS_GAME_TARGET_NAME} PUBLIC ${LIGHT_YEARS_ENGINE_TARGET_NAME})

function(CopyLibDirToTarget LIB_NAME TARGET_NAME)
    add_custom_command(
            TARGET ${TARGET_NAME}
            POST_BUILD
            COMMAND
            ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:${LIB_NAME}>
            $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endfunction()

CopyLibDirToTarget(${LIGHT_YEARS_ENGINE_TARGET_NAME} ${LIGHT_YEARS_GAME_TARGET_NAME})

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
        TARGET ${LIGHT_YEARS_GAME_TARGET_NAME}
        POST_BUILD
        COMMAND
        ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_SRC_DIR}
        $<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
)

configure_file(
        "config.ini"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)