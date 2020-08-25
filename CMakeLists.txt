cmake_minimum_required(VERSION 3.0.0)
project(rdt_giac VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(rdt_giac
    main.cpp
    giac_helper.cpp
    common.cpp
    pretty_stream.cpp
    brackets.cpp
    hterms.cpp
    giac_console.cpp
    forced_rdts.cpp

)
set_target_properties(rdt_giac PROPERTIES CXX_STANDARD 17)
target_include_directories(rdt_giac PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rdt_giac
    giac
    gmp
 )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
