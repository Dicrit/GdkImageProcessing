cmake_minimum_required(VERSION 3.15)

project(GdkIamgeProcessingCoreLib VERSION 1.0)

add_library(GdkIamgeProcessingCoreLib STATIC 
Image.cpp
Watermark.cpp
ImageBuffer.cpp
)

target_include_directories(GdkIamgeProcessingCoreLib PRIVATE ${ImageMagick_INCLUDE_DIRS})

