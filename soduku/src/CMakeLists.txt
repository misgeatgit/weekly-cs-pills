project("Soduku solver v 0.1")

add_executable(sodu-solve Solver.cc)

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
#build types

#ADD_CUSTOM_TARGET(DEBUG
#  ${CMAKE_COMMAND} -DMAKE_BUILD_TYPE:STRING=Debug ${PROJECT_SOURCE_DIR})
#ADD_CUSTOM_TARGET(RELEASE
#  ${CMAKE_COMMAND} -DMAKE_BUILD_TYPE:STRING=Release ${PROJECT_SOURCE_DIR})
set(CMAKE_BUILD_TYPE Debug)
  
#end of build types