# Distributed under the OpenDDS License. See accompanying LICENSE
# file or http://www.opendds.org/license.html for details.
#

project(OpenDDS_Messenger2_cmake CXX)
cmake_minimum_required(VERSION 3.8.2)

find_package(OpenDDS)

set(src "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(dst ${CMAKE_CURRENT_BINARY_DIR})
set(all_targets publisher subscriber messenger)

# Messenger library
add_library(messenger)
OPENDDS_TARGET_SOURCES(messenger ${src}/Messenger.idl)

# Publisher
add_executable(publisher
    ${src}/publisher.cpp
    ${src}/Writer.cpp
    ${src}/Writer.h
)

# Subscriber
add_executable(subscriber
    ${src}/subscriber.cpp
    ${src}/DataReaderListener.cpp
    ${src}/DataReaderListener.h

)

foreach(t ${all_targets})
  target_link_libraries(${t} OpenDDS::OpenDDS)

  if (NOT "${t}" STREQUAL "messenger")
    target_link_libraries(${t} messenger)
  endif()
endforeach()

# Copy configs/scripts into build-output directory
if (EXISTS ${DDS_ROOT}/tests/DCPS/Messenger)
  file(GLOB ini "${DDS_ROOT}/tests/DCPS/Messenger/*.ini")
  file(GLOB pl "${DDS_ROOT}/tests/DCPS/Messenger/*.pl")
  file(GLOB xml "${DDS_ROOT}/tests/DCPS/Messenger/*.xml")
  file(GLOB p7s "${DDS_ROOT}/tests/DCPS/Messenger/*.p7s")

  add_custom_target(Copy_ini_and_scripts
    ALL
    COMMAND_EXPAND_LISTS
    VERBATIM
    COMMENT "Copying configs/scripts into build-output directory"
    COMMAND ${CMAKE_COMMAND} -E copy ${ini} ${pl} ${xml} ${p7s} ${dst}/$<CONFIG>
  )

  add_dependencies(Copy_ini_and_scripts ${all_targets})
endif()
