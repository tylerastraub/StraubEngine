cmake_minimum_required(VERSION 3.17.0)
project(StraubEngine VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

set(StraubEngine_VERSION "0.1a")

if(WIN32)
    set(SDL2_INCLUDE_DIR "C:/Program Files/mingw64/include/SDL2")
    set(SDL2_LIBRARY_DIR "C:/Program Files/mingw64/lib")
    set(SDL2_IMAGE_INCLUDE_DIR "C:/SDL_image/include/SDL2")
    set(SDL2_IMAGE_LIBRARY_DIR "C:/SDL_image/lib")
    set(SDL2_TTF_INCLUDE_DIR "C:/SDL_ttf/include/SDL2")
    set(SDL2_TTF_LIBRARY_DIR "C:/SDL_ttf/lib")
elseif(APPLE)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2TTF REQUIRED)
endif()

set(SOURCE_INCLUDES
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/Engine
    ${PROJECT_SOURCE_DIR}/src/Engine/RandomUtilities
    ${PROJECT_SOURCE_DIR}/src/Engine/Audio
    ${PROJECT_SOURCE_DIR}/src/States
    ${PROJECT_SOURCE_DIR}/src/Render
    ${PROJECT_SOURCE_DIR}/src/Render/Effects
    ${PROJECT_SOURCE_DIR}/src/Input
    ${PROJECT_SOURCE_DIR}/src/Localization
    ${PROJECT_SOURCE_DIR}/src/Level
    ${PROJECT_SOURCE_DIR}/src/Entity
    )
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/Engine/Game.cpp
    ${PROJECT_SOURCE_DIR}/src/Engine/FileIO.cpp
    ${PROJECT_SOURCE_DIR}/src/Engine/RandomUtilities/RandomGen.cpp
    ${PROJECT_SOURCE_DIR}/src/Engine/Audio/Audio.cpp
    ${PROJECT_SOURCE_DIR}/src/States/State.cpp
    ${PROJECT_SOURCE_DIR}/src/States/GameState.cpp
    ${PROJECT_SOURCE_DIR}/src/Render/Text.cpp
    ${PROJECT_SOURCE_DIR}/src/Render/Spritesheet.cpp
    ${PROJECT_SOURCE_DIR}/src/Render/Effects/ScreenShake.cpp
    ${PROJECT_SOURCE_DIR}/src/Input/Keyboard.cpp
    ${PROJECT_SOURCE_DIR}/src/Input/Mouse.cpp
    ${PROJECT_SOURCE_DIR}/src/Input/Controller.cpp
    ${PROJECT_SOURCE_DIR}/src/Input/Controls.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/Level.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/LevelParser.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/CollisionMap.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/RenderPlane.cpp
    ${PROJECT_SOURCE_DIR}/src/Level/Tilemap.cpp
    ${PROJECT_SOURCE_DIR}/src/Entity/Entity.cpp
    )

if(WIN32)
    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SOURCE_INCLUDES})
    add_executable(StraubEngine ${SOURCES})
    # remove -mconsole for release builds
    target_link_libraries(StraubEngine -lmingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a ${SDL2_LIBRARY_DIR}/libSDL2.dll.a ${SDL2_IMAGE_LIBRARY_DIR}/libSDL2_image.dll.a ${SDL2_TTF_LIBRARY_DIR}/libSDL2_ttf.dll.a -mwindows -mconsole)
    add_custom_command(TARGET StraubEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:StraubEngine>/res/)
    # add_custom_command(TARGET StraubEngine POST_BUILD
    #     COMMAND ${CMAKE_COMMAND} -E copy
    #     ${PROJECT_SOURCE_DIR}/controller_settings.cfg $<TARGET_FILE_DIR:StraubEngine>/controller_settings.cfg)
    # add_custom_command(TARGET StraubEngine POST_BUILD
    #     COMMAND ${CMAKE_COMMAND} -E copy
    #     ${PROJECT_SOURCE_DIR}/keyboard_settings.cfg $<TARGET_FILE_DIR:StraubEngine>/keyboard_settings.cfg)
elseif(APPLE)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR} ${SOURCE_INCLUDES})
    add_executable(StraubEngine MACOSX_BUNDLE ${SOURCES})
    target_link_libraries(StraubEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})
    set_target_properties(StraubEngine PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_EXECUTABLE_NAME StraubEngine
        MACOSX_BUNDLE_ICON_FILE icon.png
        MACOSX_BUNDLE_GUI_IDENTIFIER com.straub.StraubEngine
        MACOSX_BUNDLE_LONG_VERSION_STRING ${StraubEngine_VERSION}
        MACOSX_BUNDLE_BUNDLE_NAME StraubEngine
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${StraubEngine_VERSION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${StraubEngine_VERSION}
        MACOSX_BUNDLE_COPYRIGHT "© Tyler Straub 2022"
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/Info.plist.in)
    install(CODE "
        include(BundleUtilities)
        fixup_bundle(\"${CMAKE_BINARY_DIR}/StraubEngine.app\"   \"\"   \"${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY}\")
        " COMPONENT Runtime)
    file(COPY ${CMAKE_SOURCE_DIR}/cmake/icon.png DESTINATION StraubEngine.app/Contents/Resources)
    file(COPY ${CMAKE_SOURCE_DIR}/cmake/StraubEngine.entitlements DESTINATION StraubEngine.app/Contents)
    add_custom_command(TARGET StraubEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:StraubEngine>/../Resources/res/)
    add_custom_command(TARGET StraubEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/controller_settings.cfg $<TARGET_FILE_DIR:StraubEngine>/../Resources/controller_settings.cfg)
    add_custom_command(TARGET StraubEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/keyboard_settings.cfg $<TARGET_FILE_DIR:StraubEngine>/../Resources/keyboard_settings.cfg)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
