cmake_minimum_required (VERSION 3.12)

project (HDFSwathLoad)

if( FALSE )
get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
endif()

# HDF4 for gcc
set( HDF4_DIR                 /usr/local/hdf4 )
set( HDF4_INCLUDE_DIRECTORIES ${HDF4_DIR}/include ) 
set( HDF4_CFLAGS  "-I/usr/include/tirpc -O3 -fomit-frame-pointer" )  
set( HDF4_LDFLAGS "-L/usr/local/lib:/usr/lib64 -L/usr/lib64 -L/usr/local/lib -L/usr/local/hdf4/lib " )
set( HDF4_LIBS    "/usr/local/hdf4/lib/libmfhdf.a /usr/local/hdf4/lib/libdf.a -lsz -ljpeg -lz -ltirpc " )
set( HDF4_LIBRARIES /usr/local/hdf4/lib/libmfhdf.a /usr/local/hdf4/lib/libdf.a /usr/local/lib/libsz.so /usr/lib64/libjpeg.so /usr/lib64/libz.so /usr/lib64/libtirpc.so )

set( HDFEOS2_DIR     /usr/local/hdfeos2 )
set( HDFEOS2_CFLAGS  "-I${HDFEOS2_DIR}/include" )
set( HDFEOS2_LDFLAGS "-L${HDFEOS2_DIR}/lib" )
set( HDFEOS2_LIBS "-lhdfeos -lGctp " )
set( HDFEOS2_LIBRARIES /usr/local/hdfeos2/lib/libhdfeos.a /usr/local/hdfeos2/lib/libGctp.a )
set( HDFEOS2_INCLUDE_DIRECTORIES "${HDFEOS2_DIR}/include" )

# set( CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${HDF5_EOS_LINKER_FLAGS} ) 
set( CMAKE_EXE_LINKER_FLAGS "${HDFEOS2_CFLAGS} ${HDF4_CFLAGS} ${HDFEOS2_LDFLAGS} ${HDF4_LDFLAGS} ${CMAKE_EXE_LINKER_FLAGS} ${HDFEOS2_LIBS} ${HDF4_LIBS}" )

add_executable(             HDFSwathLoad HDFSwathLoad.cpp)
target_include_directories( HDFSwathLoad PUBLIC ${HDFEOS2_INCLUDE_DIRECTORIES} ${HDF4_INCLUDE_DIRECTORIES} )
target_link_libraries(      HDFSwathLoad ${HDFEOS2_LIBRARIES} ${HDF4_LIBRARIES} )  

