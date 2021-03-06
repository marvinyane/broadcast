PROJECT(broadcast)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

option(BASED_ON_UDP "based on udp or dbus" ON)

SET(CMAKE_C_FLAGS "-Wall -g -O2")
SET(CMAKE_CXX_FLAGS "-Wall -g -O2 -std=gnu++0x")

FILE(GLOB_RECURSE SRC_LIST "src/common/*.cpp")

INCLUDE_DIRECTORIES("include")
INCLUDE_DIRECTORIES("src/common")

if (BASED_ON_UDP)
    add_definitions("-DBASED_ON_UDP")
    INCLUDE_DIRECTORIES("src/udp")
else()
    INCLUDE_DIRECTORIES("/usr/include/dbus-1.0/")
    INCLUDE_DIRECTORIES("/usr/lib/x86_64-linux-gnu/dbus-1.0/include/")
    add_definitions("-DBASED_ON_DBUS")
    INCLUDE_DIRECTORIES("src/dbus")
endif()

ADD_LIBRARY(broadcast SHARED ${SRC_LIST})

ADD_EXECUTABLE(signal  "test/signal.cpp")
TARGET_LINK_LIBRARIES(signal broadcast)
TARGET_LINK_LIBRARIES(signal pthread)
TARGET_LINK_LIBRARIES(signal dbus-1)

ADD_EXECUTABLE(receive  "test/receive.cpp")
TARGET_LINK_LIBRARIES(receive broadcast)
TARGET_LINK_LIBRARIES(receive pthread)
TARGET_LINK_LIBRARIES(receive dbus-1)
