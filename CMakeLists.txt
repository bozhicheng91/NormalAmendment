cmake_minimum_required (VERSION 2.4) 
project (NA)
ADD_DEFINITIONS(-std=c++11)

AUX_SOURCE_DIRECTORY(./src SOURCES)

ADD_EXECUTABLE(NormalAmendment ${SOURCES})

