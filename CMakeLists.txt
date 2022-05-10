cmake_minimum_required (VERSION 3.0)
project (ImageBinalize)

file(GLOB SOURCE_FILES *.cpp *.h)

include_directories(${ImageBinalize_SOURCE_DIR})
add_executable(ImageBinalize ${SOURCE_FILES})