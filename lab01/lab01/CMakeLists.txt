# ВНИМАНИЕ: этот файл НЕ проверялся сборкой при подготовке комплекта —
# в среде подготовки отсутствовал CMake. Синтаксис выверен вручную.
# Перед раздачей группе выполните:
#   cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build
# Гарантированно рабочий путь сборки — Makefile рядом.

cmake_minimum_required(VERSION 3.20)
project(mp_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Build with AddressSanitizer and UBSan" ON)

file(GLOB LAB_SRC CONFIGURE_DEPENDS src/*.cpp)
file(GLOB LAB_TESTS CONFIGURE_DEPENDS tests/*.cpp)
file(GLOB LAB_APPS CONFIGURE_DEPENDS apps/*.cpp)

add_library(lab INTERFACE)
target_include_directories(lab INTERFACE include ../common)

set(ALL_TARGETS "")

if(LAB_SRC)
  add_library(lab_impl STATIC ${LAB_SRC})
  target_include_directories(lab_impl PUBLIC include ../common)
  target_link_libraries(lab INTERFACE lab_impl)
  list(APPEND ALL_TARGETS lab_impl)
endif()

add_executable(lab_tests ${LAB_TESTS})
target_link_libraries(lab_tests PRIVATE lab)
list(APPEND ALL_TARGETS lab_tests)

foreach(app_path ${LAB_APPS})
  get_filename_component(app_name ${app_path} NAME_WE)
  add_executable(${app_name} ${app_path})
  target_link_libraries(${app_name} PRIVATE lab)
  list(APPEND ALL_TARGETS ${app_name})
endforeach()

foreach(tgt ${ALL_TARGETS})
  target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic -g)
  if(ENABLE_SANITIZERS)
    target_compile_options(${tgt} PRIVATE
      -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(${tgt} PRIVATE -fsanitize=address,undefined)
  endif()
endforeach()

enable_testing()
add_test(NAME unit COMMAND lab_tests)
