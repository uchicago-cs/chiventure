# Install script for directory: /home/elizabethli/cmsc220/chiventure

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/elizabethli/cmsc220/chiventure/tests/src/action_management/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/battle/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/cli/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/common/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/custom-actions/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/game-state/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/libobj/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/quests/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/sound/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/npc/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/openworld/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/playerclass/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/skilltrees/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/ui/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/wdl/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/src/custom-scripts/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/action_management/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/battle/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/cli/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/custom-actions/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/game-state/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/libobj/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/quests/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/npc/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/openworld/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/playerclass/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/skilltrees/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/ui/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/wdl/cmake_install.cmake")
  include("/home/elizabethli/cmsc220/chiventure/tests/tests/custom-scripts/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/elizabethli/cmsc220/chiventure/tests/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
