cmake_minimum_required(VERSION 2.8.2)

project(DP_Example)

include(CTest)
include(utilities.cmake)
add_compile_options(-std=c++14)

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})


set( UNIT_TESTS_DIRECTORY                "${CMAKE_CURRENT_SOURCE_DIR}/ut/tests")
set( MOCKS_DIRECTORY                     "${CMAKE_CURRENT_SOURCE_DIR}/ut/mocks")
set( COMMON_APPLICATION_FILES_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/application/")
GetListOfSubDirectories( UNIT_TESTS_SUBDIRECTORIES               ${UNIT_TESTS_DIRECTORY})
GetListOfSubDirectories( MOCKS_SUBDIRECTORIES                    ${MOCKS_DIRECTORY})
GetListOfSubDirectories( COMMON_APPLICATION_FILES_SUBDIRECTORIES ${COMMON_APPLICATION_FILES_DIRECTORY})


file(GLOB UNIT_TEST_SOURCES     ${UNIT_TESTS_DIRECTORY}/*.cpp)
file(GLOB COMMON_HEADER_FILES   ${COMMON_APPLICATION_FILES_DIRECTORY}/*/*.h)
file(GLOB COMMON_SOURCE_FILES   ${COMMON_APPLICATION_FILES_DIRECTORY}/*/*.cpp)
file(GLOB UNIT_TEST_SOURCES     ${UNIT_TEST_SOURCES}    ${UNIT_TESTS_DIRECTORY}/*/*.cpp)
file(GLOB COMMON_HEADER_FILES   ${COMMON_HEADER_FILES}  ${COMMON_APPLICATION_FILES_DIRECTORY}/*/*/*.h)
file(GLOB COMMON_SOURCE_FILES   ${COMMON_SOURCE_FILES}  ${COMMON_APPLICATION_FILES_DIRECTORY}/*/*/*.cpp)


GetListOfAllFilesInSubDirectories(  COMMON_APPLICATION_ALL_SOURCES
                                    COMMON_APPLICATION_FILES_SUBDIRECTORIES
                                    "*.cpp")
print_foreach(COMMON_APPLICATION_ALL_SOURCES)


add_executable(unit_tests ${UNIT_TEST_SOURCES} ${COMMON_SOURCE_FILES})
add_executable(main main.cpp ${COMMON_SOURCE_FILES})

target_include_directories(unit_tests PUBLIC ${COMMON_APPLICATION_FILES_SUBDIRECTORIES})
target_include_directories(main PUBLIC ${COMMON_APPLICATION_FILES_SUBDIRECTORIES})

target_link_libraries(unit_tests gtest gmock_main)
add_test(NAME unit_tests COMMAND unit_tests)
