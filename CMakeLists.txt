cmake_minimum_required(VERSION 2.8.4)
project(LD35)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Engine ${CMAKE_CURRENT_BINARY_DIR}/engine)
include("Engine/includes.cmake")
include_directories(.)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/Zm256 /Gy /GR- /W2 /wd4275 /wd4530 /wd4566 /FS")
    set(CMAKE_CXX_FLAGS_DEBUG "/MDd /DDEBUG /RTCsu /Od /Zi")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/GL /GS- /O2 /MD /fp:fast /DNDEBUG /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "/GL /GS- /O2 /MD /fp:fast /DNDEBUG")

    set(CMAKE_C_FLAGS "/Zm256 /Gy /W2 /wd4566  /FS")
    set(CMAKE_C_FLAGS_DEBUG "/MDd /DDEBUG /RTCsu /Od /Zi /D_SECURE_SCL=0 /D_HAS_ITERATOR_DEBUGGING=0")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/GL /GS- /O2 /MD /fp:fast /DNDEBUG /Zi")
    set(CMAKE_C_FLAGS_RELEASE "/GL /GS- /O2 /MD /fp:fast /DNDEBUG")

    #
    # Workaround for "LINK : fatal error LNK1104: cannot open file 'XXX.map'" issue
    # see http://social.msdn.microsoft.com/Forums/en-US/vcprerelease/thread/19804537-05ba-4adf-8273-68d2450401e0
    #

    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /MAP /OPT:ICF /OPT:REF /INCREMENTAL:NO")
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} /MAP /DEBUG /OPT:ICF /OPT:REF /LTCG /INCREMENTAL:NO")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /MAP /OPT:ICF /OPT:REF /LTCG /INCREMENTAL:NO")

    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /MAP /OPT:ICF /OPT:REF /INCREMENTAL:NO")
    set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} /MAP /OPT:ICF /OPT:REF /LTCG /INCREMENTAL:NO")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /MAP /OPT:ICF /OPT:REF /LTCG /INCREMENTAL:NO")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -march=pentium4 -mmmx -msse -msse2 -std=c++11 -fno-exceptions -fno-rtti")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -g")
    set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

    set(CMAKE_C_FLAGS "-Wall -march=pentium4 -mmmx -msse -msse2")
    set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
    set(CMAKE_C_FLAGS_RELEASE "-O2")

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpmath=sse")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpmath=sse")
    endif ()
endif ()
set(SOURCE_FILES main.cpp LD35.cpp LD35.hpp Level.cpp Level.hpp Player.cpp Player.hpp Rune.cpp Rune.hpp misc.hpp Goal.cpp Goal.hpp Tip.cpp Tip.hpp MagicLight.cpp MagicLight.hpp OneWayPlatform.cpp OneWayPlatform.hpp Switch.cpp Switch.hpp)
add_executable(LD35 ${SOURCE_FILES})

target_link_libraries(LD35 Engine)
if (WIN32)
    set_target_properties(LD35 PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    set_target_properties(LD35 PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
    set_target_properties(LD35 PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    set_target_properties(LD35 PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
endif()