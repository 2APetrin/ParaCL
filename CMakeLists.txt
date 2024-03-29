cmake_minimum_required(VERSION 3.13.4)
project(ParaCL)

find_package(BISON REQUIRED)
find_package(FLEX  REQUIRED)

if (NOT DEFINED GRAMMAR)
  set(GRAMMAR "grammar.y" CACHE STRING "file with grammar" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -g -O0 -D DEBUG -DDUMP -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr") #-lgtest -lgmock -pthread
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

flex_target(scanner
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/lexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lexer.hh
)

bison_target(parser
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/grammar.y
  ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
  COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/grammar.tab.hh -Wcounterexamples")

add_flex_bison_dependency(scanner parser)

add_executable(${PROJECT_NAME}
${CMAKE_CURRENT_SOURCE_DIR}/main.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/parser/driver.cc
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ast)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/parser)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/symtab)

