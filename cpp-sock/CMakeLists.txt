CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


set( CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11" )
set( CMAKE_CXX_FLAGS_DEBUG "-g -O0" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )

ADD_LIBRARY(cppsock Address Server Socket)




