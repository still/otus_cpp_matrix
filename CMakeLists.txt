cmake_minimum_required(VERSION 3.2)

project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(${PROJECT_NAME} "main.cpp")

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)


# for local build
target_link_libraries(${PROJECT_NAME} stdc++)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT stillarty@ya.ru)

include (CPack)
