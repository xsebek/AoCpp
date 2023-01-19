cmake_minimum_required(VERSION 3.15)
project(aocpp CXX)

###########################################################
# LIBRARY
###########################################################
find_package(fmt REQUIRED)
find_package(lexy REQUIRED)

file(GLOB DAYS_SOURCE
    CONFIGURE_DEPENDS
    "src/day*.cpp"
)
message(STATUS "Found days: ${DAYS_SOURCE}")

add_library(aoclib
		STATIC
		${DAYS_SOURCE}
)

target_link_libraries(aoclib PRIVATE fmt::fmt foonathan::lexy)

###########################################################
# BINARY
###########################################################

add_executable(aocpp
		src/aocpp.cpp
		src/main.cpp
)
target_link_libraries(aocpp PRIVATE aoclib)

install(TARGETS aocpp DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

###########################################################
# TESTS
###########################################################
find_package(GTest REQUIRED)

file(GLOB TESTS_SOURCE
    CONFIGURE_DEPENDS
    "tests/*.cpp"
)
message(STATUS "Found tests: ${TESTS_SOURCE}")

add_executable(aoctest ${TESTS_SOURCE})
target_link_libraries(aoctest aoclib GTest::Main)

