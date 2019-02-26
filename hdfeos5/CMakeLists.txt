cmake_minimum_required (VERSION 3.12)

project (HDFSwathLoad)

find_package(HDF5 REQUIRED)

# export HDFEOS5_HOME=/home/mrilee/src/hdfeos/hdfeos5

message( "HDFEOS5_INC $ENV{HDFEOS5_INC}" )

# add_library(           HDF5_EOS_LIBRARY STATIC IMPORTED GLOBAL ) 
# set_target_properties( HDF5_EOS_LIBRARY PROPERTIES IMPORTED_LOCATION "$ENV{HDFEOS5_LIB}/libhe5_hdfeos.a" ) 
# add_library(           HDF5_EOS_GCTP_LIBRARY STATIC IMPORTED GLOBAL ) 
# set_target_properties( HDF5_EOS_GCTP_LIBRARY PROPERTIES IMPORTED_LOCATION "$ENV{HDFEOS5_LIB}/libGctp.a" )
# set( HDF5_EOS_LINKER_FLAGS "-L$ENV{HDFEOS5_LIB} -lhe5_hdfeos -lGctp ")
# set( HDF5_EOS_LINKER_FLAGS " $ENV{HDFEOS5_LIB}/libhe5_hdfeos.a $ENV{HDFEOS5_LIB}/libGctp.a " )

set( HDF5_EOS_LIBRARIES $ENV{HDFEOS5_LIB}/libhe5_hdfeos.a $ENV{HDFEOS5_LIB}/libGctp.a )

# set( HDF5_EOS_LINKER_FLAGS " -L/usr/local/hdf5/lib -lhe5_hdfeos -lGctp " )
# set( CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${HDF5_EOS_LINKER_FLAGS} ) 
# set( CMAKE_EXE_LINKER_FLAGS ${HDF5_EOS_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS} )

string( REPLACE ";" " " HDF5_C_LIBRARIES_TMP ${HDF5_C_LIBRARIES} ) 

if( FALSE )
get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
endif()

add_executable(             read_fields_swath "read_fields_swath.c" )
target_include_directories( read_fields_swath PUBLIC $ENV{HDFEOS5_INC} /usr/local/hdf5/include )
target_link_libraries(      read_fields_swath ${HDF5_EOS_LIBRARIES} /usr/local/hdf5/lib/libhdf5_hl.a ${HDF5_C_LIBRARIES} ) 


