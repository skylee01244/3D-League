cmake_minimum_required(VERSION 3.16)
project(fps-game VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    AngleFunctions.cpp 
    Animation.cpp 
    Astar.cpp
    ConvertMapSketch.cpp 
    Decoration.cpp 
    Enemy.cpp 
    Game.cpp 
    GetCell.cpp 
    Main.cpp 
    MapCollision.cpp 
    Player.cpp 
    SpriteManager.cpp 
    Stripe.cpp
)

add_executable(main ${SOURCES})

set(SFML_STATIC_LIBRARIES TRUE)

target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_compile_features(main PRIVATE cxx_std_17)


if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)

    # Instruction for users to install Visual C++ Redistributable
    message(WARNING "Ensure that the Visual C++ Redistributable is installed: https://aka.ms/vs/17/release/vc_redist.x64.exe")
endif()

if(APPLE)
    add_custom_command(
        TARGET main
        COMMENT "Copy SFML Frameworks"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${SFML_SOURCE_DIR}/lib/Frameworks ${CMAKE_BINARY_DIR}/Frameworks
        VERBATIM)
    
    set_target_properties(main PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_FRAMEWORK_IDENTIFIER com.yourdomain.yourapp
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist)
endif()

if(UNIX AND NOT APPLE)
    add_custom_command(
        TARGET main
        COMMENT "Copy SFML Shared Libraries"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${SFML_SOURCE_DIR}/lib ${CMAKE_BINARY_DIR}/lib
        VERBATIM)

    set_target_properties(main PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "$ORIGIN/../lib")
endif()
