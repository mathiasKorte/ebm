cmake_minimum_required(VERSION 3.20)

include(cmake/prelude.cmake)

project(
    ebm
    VERSION 0.1.0
    DESCRIPTION "Explorator Belli Mechani (ebm) is a Monte-Carlo-based engine/simulator/analyzer for the game 'Mechabellum' by game-river / paradox."
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

find_package(Qt6 REQUIRED COMPONENTS Widgets)


# ---- Declare executable ----

add_executable(ebm_exe src/main.cpp src/common.cpp src/gui.cpp src/mech.cpp src/board.cpp src/item.cpp src/unit.cpp src/weapon.cpp src/mechs/crawler.cpp src/mechs/meltingpoint.cpp src/mechs/arclight.cpp)
add_executable(ebm::exe ALIAS ebm_exe)

set_property(TARGET ebm_exe PROPERTY OUTPUT_NAME ebm)

target_compile_features(ebm_exe PRIVATE cxx_std_11)

target_link_libraries(ebm_exe PRIVATE Qt6::Core Qt6::Widgets)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT ebm_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of ebm"
  )
endif()

include(cmake/dev-mode.cmake)
