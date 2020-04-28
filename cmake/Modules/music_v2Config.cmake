INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_MUSIC_V2 music_v2)

FIND_PATH(
    MUSIC_V2_INCLUDE_DIRS
    NAMES music_v2/api.h
    HINTS $ENV{MUSIC_V2_DIR}/include
        ${PC_MUSIC_V2_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    MUSIC_V2_LIBRARIES
    NAMES gnuradio-music_v2
    HINTS $ENV{MUSIC_V2_DIR}/lib
        ${PC_MUSIC_V2_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MUSIC_V2 DEFAULT_MSG MUSIC_V2_LIBRARIES MUSIC_V2_INCLUDE_DIRS)
MARK_AS_ADVANCED(MUSIC_V2_LIBRARIES MUSIC_V2_INCLUDE_DIRS)

