# This will define
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
        "Please install graspit or adjust CMAKE_PREFIX_PATH"
        "e.g. cmake -DCMAKE_PREFIX_PATH=/path-to-graspit/ ...")
    endif (graspit_INCLUDE_DIR)

    if (graspit_LINK_DIR)
        message(STATUS "Looking for graspit library include -- found " ${graspit_LINK_DIR})
        set(graspit_LINK_DIRS 
            ${graspit_LINK_DIR}/lib/ 
            ${graspit_LINK_DIR}/lib/graspit 
        )
    else (graspit_LINK_DIR)
        message(SEND_ERROR 
        "Looking for graspit library directories -- not found"
        "Please install graspit or adjust CMAKE_PREFIX_PATH"
        "e.g. cmake -DCMAKE_PREVIX_PATH=/path-to-graspit/ ...")
    endif (graspit_LINK_DIR)
    if (BUILD_SHARED_LIBS)
        include(${SELF_DIR}/graspit-targets.cmake)
    else (BUILD_SHARED_LIBS)
        include(${SELF_DIR}/graspit-static-targets.cmake)
    endif (BUILD_SHARED_LIBS)
    set (CMAKE_MODULE_PATH ${SELF_DIR})
else (NOT CATKIN_DEVEL_PREFIX)
    # catkin is going to handle the include directories
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
    "Please install graspit or adjust CMAKE_PREFIX_PATH"
    "e.g. cmake -DCMAKE_PREFIX_PATH=/path-to-graspit/ ...")
endif (graspit_LIBRARY_RELEASE)

# Find the dependencies:
find_package(Qhull REQUIRED)
find_package(SoQt4 REQUIRED)
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

MARK_AS_ADVANCED(
    graspit_CXXFLAGS
    graspit_LINK_FLAGS
    graspit_INCLUDE_DIRS
    graspit_LINK_DIRS
    graspit_LIBRARY
    graspit_LIBRARY_RELEASE
    graspit_LIBRARY_DEBUG
    graspit_LIBRARIES
)
