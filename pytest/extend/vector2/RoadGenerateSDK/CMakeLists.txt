#-----------------------------------------------------------
#CMake		RoadGenerateSDK工程配置文件
#Author:	lb108197
#Date:		2016-07-04	
#-----------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

#整个工程名字
PROJECT(RoadGenerateSDK)


IF(WIN32)
	SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -MTd -Zi -Ob0 -Od -RTC1 -D_DEBUG ")
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -Wall -MT -O2 -Ob2 -DNDEBUG")
ELSEIF(UNIX)
	SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -g -ggdb -fpermissive -D_DEBUG ")
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -fpermissive")
ELSEIF(APPLE)

ELSE()
	MESSAGE(FATAL_ERROR "### Undefine OS platform! cmake force terminated!")
ENDIF()




FILE(GLOB_RECURSE HEADER_FILES "./*.h")
FILE(GLOB_RECURSE SOURCE_FILES "./*.cpp")




LINK_DIRECTORIES(${_LIB_INSTALL_DIR})
INCLUDE_DIRECTORIES(${_INCLUDE_INSTALL_DIR}/utility)

#生成静态库
ADD_LIBRARY(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
MESSAGE(STATUS "### Library [ ${PROJECT_NAME} ] Output Directory: " ${_LIB_INSTALL_DIR})

ADD_DEPENDENCIES(${PROJECT_NAME} utility)



FILE(COPY  ${_SOLUTION_DIR}/${PROJECT_NAME}  
DESTINATION ${_INCLUDE_INSTALL_DIR} 
FILES_MATCHING  PATTERN "*.h"  )




