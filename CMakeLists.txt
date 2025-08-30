cmake_minimum_required(VERSION 3.10.0)

project(myContainers VERSION 0.1.0 LANGUAGES C CXX)

set(PROJECT_SOURCE 
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

option(BUILD_TESTS "Whether to build tests or not" ON)
if (BUILD_TESTS)
    set(TESTS_SOURCE
        tests/containertest.cpp
    )
    add_executable(container_test ${TESTS_SOURCE})
    set_target_properties(container_test 
        PROPERTIES CXX_STANDARD 17 
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONNS OFF
    )

    target_compile_options(container_test PRIVATE --coverage)
    target_link_options(container_test PRIVATE --coverage)

    function(generate_coverage_script TARGET_NAME)
        set(SCRIPT_NAME "run_coverage.sh")
        file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${SCRIPT_NAME}
"#!/bin/bash
set -e

echo 'Running tests...'
./${TARGET_NAME}

echo 'Capturing coverage...'
lcov --capture --directory . --output-file coverage.info

echo 'Generating HTML report...'
genhtml coverage.info --output-directory out

echo 'Opening report...'
xdg-open out/index.html"
)
    file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/${SCRIPT_NAME} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    message(STATUS "Coverage script generated: ${CMAKE_CURRENT_BINARY_DIR}/${SCRIPT_NAME}")
endfunction()

    generate_coverage_script(container_test)
endif()



