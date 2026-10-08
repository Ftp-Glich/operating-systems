file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(lab1 ${SOURCES})

target_compile_options(lab1 PUBLIC -Werror -Wall)

target_include_directories(lab1 PUBLIC "${PROJECT_SOURCE_DIR}/include")
