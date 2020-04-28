INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_MUSIC music)

FIND_PATH(
    MUSIC_INCLUDE_DIRS
    NAMES music/api.h
    HINTS $ENV{MUSIC_DIR}/include
        ${PC_MUSIC_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    MUSIC_LIBRARIES
    NAMES gnuradio-music
    HINTS $ENV{MUSIC_DIR}/lib
        ${PC_MUSIC_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/musicTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MUSIC DEFAULT_MSG MUSIC_LIBRARIES MUSIC_INCLUDE_DIRS)
MARK_AS_ADVANCED(MUSIC_LIBRARIES MUSIC_INCLUDE_DIRS)
