# Try to find graspit
# 
# You can set the variable
#   graspit_PATH
# to point to the installation directory of graspit 
# (the folder which contains the include/ and lib/ dirs)
# in order to allow searching for it there in addition
# to /usr/ and /usr/local/
# 
# Once done this will define
# graspit_LIBRARY_FOUND - if graspit is found
# graspit_CXXFLAGS - extra flags
# graspit_INCLUDE_DIRS - include directories
# graspit_LINK_DIRS - link directories
# graspit_LIBRARY_RELEASE - the relase version
# graspit_LIBRARY_DEBUG - the debug version
# graspit_LIBRARY - a default library, with priority debug.
# graspit_LIBRARIES - all libraries required


message(STATUS "Looking for graspit includes...")

# When using catkin, the include dirs are determined by catkin itself
if (NOT CATKIN_DEVEL_PREFIX)
    get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
    # message("$$$$$$$ ${CMAKE_CURRENT_LIST_FILE} SELF_DIR = ${SELF_DIR}")
    get_filename_component(graspit_INCLUDE_DIR "${SELF_DIR}/../../include/" ABSOLUTE)
    get_filename_component(graspit_LINK_DIR "${SELF_DIR}/../../lib/" ABSOLUTE)

    # find_path(graspit_PATH ivmgr.h 
    #     ${CMAKE_INCLUDE_PATH}
    #     /usr/local/include
    #     /usr/local/graspit/include
    #     /usr/include
    #  )
    # if (not graspit_PATH)
    #  ... handle errors
    # endif (not graspit_PATH)

    if (graspit_INCLUDE_DIR)
        message(STATUS "Looking for graspit headers -- found " ${graspit_INCLUDE_DIR})
        set(graspit_INCLUDE_DIRS 
            ${graspit_INCLUDE_DIR} 
            ${graspit_INCLUDE_DIR}/graspit 
        )
    else (graspit_INCLUDE_DIR)
        message(SEND_ERROR 
        "Looking for graspit headers -- not found"
        "Please install graspit or adjust CMAKE_INCLUDE_PATH"
        "e.g. cmake -DCMAKE_INCLUDE_PATH=/path-to-graspit/include ...")
    endif (graspit_INCLUDE_DIR)

    if (graspit_LINK_DIR)
        message(STATUS "Looking for graspit library include -- found " ${graspit_LINK_DIR})
        set(graspit_LINK_DIRS 
            ${graspit_LINK_DIR}/include/ 
            ${graspit_LINK_DIR}/include/graspit 
        )
    else (graspit_LINK_DIR)
        message(SEND_ERROR 
        "Looking for graspit library directories -- not found"
        "Please install graspit or adjust CMAKE_LINK_PATH"
        "e.g. cmake -DCMAKE_LINK_PATH=/path-to-graspit/lib ...")
    endif (graspit_LINK_DIR)

    include(${SELF_DIR}/graspit-targets.cmake)
    set (CMAKE_MODULE_PATH ${SELF_DIR})
else (NOT CATKIN_DEVEL_PREFIX)
    # catkin is going to handle the include directories ?? XXX TODO check this
    include(${CATKIN_DEVEL_PREFIX}/lib/graspit/graspit-targets.cmake)
endif (NOT CATKIN_DEVEL_PREFIX)

find_library(graspit_LIBRARY_RELEASE
	NAMES graspit
	PATHS
	${CMAKE_LIBRARY_PATH}
    ${graspit_LINK_DIR}
	/usr/local/graspit/lib
	/usr/local/lib
	/usr/lib
    NO_DEFAULT_PATH
)

if (graspit_LIBRARY_RELEASE)
	message(STATUS "Looking for graspit library -- found " ${graspit_LIBRARY_RELEASE})
    set (graspit_LIBRARY ${graspit_LIBRARY_RELEASE})
    # there is no debug version yet
    set (graspit_LIBRARY_DEBUG ${graspit_LIBRARY_RELEASE})
else (graspit_LIBRARY_RELEASE)
 	message(SENDL_ERROR 
	"Looking for graspit library -- not found"
    "Please install graspit or adjust CMAKE_LIBRARY_PATH"
	"e.g. cmake -DCMAKE_LIBRARY_PATH=/path-to-graspit/lib ...")
endif (graspit_LIBRARY_RELEASE)

# Find the dependencies:
find_package(Qhull REQUIRED)
find_package(SoQt4 REQUIRED)
#find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(Threads REQUIRED)
#find_package(BULLET)

SET( QT_USE_QT3SUPPORT TRUE )
find_package(Qt4 COMPONENTS QtCore REQUIRED)
# include QT_USE_FILE.
include (${QT_USE_FILE})

set(graspit_INCLUDE_DIRS ${graspit_INCLUDE_DIRS} 
     ${SOQT_INCLUDE_DIRS}
     ${QT_INCLUDES}
     ${QT_INCLUDE_DIR}
     ${QT_QT3SUPPORT_INCLUDE_DIR}
     ${QHULL_INCLUDE_DIRS})
set(graspit_CXXFLAGS ${SOQT_CXXFLAGS} ${LAPACK_LINKER_FLAGS})
set(graspit_LINK_DIRS ${graspit_LINK_DIRS} ${SOQT_LINK_DIRS} ${QT_LIBRARY_DIR})
set(graspit_LIBRARIES ${graspit_LIBRARY} ${QT_LIBRARIES} ${QT_QT3SUPPORT_LIBRARY} ${QHULL_LIBRARIES}
    ${SOQT_LIBRARY} ${LAPACK_LIBRARIES} ${BULLET_LIBRARIES})
#set(graspit_FOUND true)

MARK_AS_ADVANCED(
    graspit_LIBRARY_FOUND
    graspit_CXXFLAGS
    graspit_LINK_FLAGS
    graspit_INCLUDE_DIRS
    graspit_LINK_DIRS
    graspit_LIBRARY
    graspit_LIBRARY_RELEASE
    graspit_LIBRARY_DEBUG
    graspit_LIBRARIES
)
