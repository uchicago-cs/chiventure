# Install script for directory: /home/kabirdubey/cs220/chiventure

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
  include("/home/kabirdubey/cs220/chiventure/src/action_management/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/battle/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/cli/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/common/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/custom-actions/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/game-state/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/libobj/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/quests/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/sound/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/npc/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/openworld/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/playerclass/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/skilltrees/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/ui/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/wdl/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/src/custom-scripts/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/action_management/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/battle/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/cli/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/custom-actions/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/game-state/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/libobj/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/quests/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/npc/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/openworld/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/playerclass/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/skilltrees/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/ui/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/wdl/cmake_install.cmake")
  include("/home/kabirdubey/cs220/chiventure/tests/custom-scripts/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/kabirdubey/cs220/chiventure/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
