set(SOURCE_FILES main.cpp Node/Node.cpp Parser/Parser.cpp)

add_executable(SNU_Spice ${SOURCE_FILES})
add_library(SNU_Spice_lib ${SOURCE_FILES})
