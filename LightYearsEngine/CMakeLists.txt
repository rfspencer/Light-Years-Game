add_library(${LIGHT_YEARS_ENGINE_TARGET_NAME} STATIC
        src/framework/Application.cpp
        include/framework/Application.h

        src/EntryPoint.cpp
        include/EntryPoint.h

        src/framework/Core.cpp
        include/framework/Core.h

        include/framework/World.h
        src/framework/World.cpp

        include/framework/Actor.h
        src/framework/Actor.cpp

        include/framework/Object.h
        src/framework/Object.cpp

        src/framework/AssetManager.cpp
        include/framework/AssetManager.h

        include/framework/MathUtility.h
        src/framework/MathUtility.cpp

        src/framework/PhysicsSystem.cpp
        include/framework/PhysicsSystem.h

        src/framework/Delegate.cpp
        include/framework/Delegate.h

        include/VFX/Particle.h
        src/VFX/Particle.cpp

        src/framework/TimerManager.cpp
        include/framework/TimerManager.h
)

target_include_directories(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC
    include/
)

include(FetchContent)
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
        ${SFML_LIB_NAME}
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
        GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC sfml-audio)

set(BOX2D_LIB_NAME Box2D)
FetchContent_Declare(
        ${BOX2D_LIB_NAME}
        GIT_REPOSITORY https://github.com/erincatto/box2d
        GIT_TAG v2.4.1
        GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${BOX2D_LIB_NAME})
target_link_libraries(${LIGHT_YEARS_ENGINE_TARGET_NAME} PUBLIC box2d)

function(CopyLibToTarget LIB_NAME TARGET_NAME)
    add_custom_command(
            TARGET ${TARGET_NAME}
            POST_BUILD
            COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${LIB_NAME}>
            $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endfunction()

CopyLibToTarget(sfml-graphics ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-window ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-system ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-audio ${LIGHT_YEARS_ENGINE_TARGET_NAME})
CopyLibToTarget(box2d ${LIGHT_YEARS_ENGINE_TARGET_NAME})