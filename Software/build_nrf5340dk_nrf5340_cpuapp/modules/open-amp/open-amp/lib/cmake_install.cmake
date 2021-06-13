# Install script for directory: /opt/Nordic/connect-sdk/modules/lib/open-amp/open-amp/lib

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/opt/Nordic/connect-sdk/modules/lib/open-amp/open-amp/lib/include/openamp")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/opt/Nordic/connect-sdk/nrf/samples/bluetooth/peripheral_lbs/build_nrf5340dk_nrf5340_cpuapp/modules/open-amp/open-amp/lib/virtio/cmake_install.cmake")
  include("/opt/Nordic/connect-sdk/nrf/samples/bluetooth/peripheral_lbs/build_nrf5340dk_nrf5340_cpuapp/modules/open-amp/open-amp/lib/rpmsg/cmake_install.cmake")
  include("/opt/Nordic/connect-sdk/nrf/samples/bluetooth/peripheral_lbs/build_nrf5340dk_nrf5340_cpuapp/modules/open-amp/open-amp/lib/remoteproc/cmake_install.cmake")

endif()
