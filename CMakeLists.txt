cmake_minimum_required(VERSION 2.8)

project(cv_http_mat)

set(src_cv_http_mat main.cpp CvHttpMat.cpp )

set( CMAKE_CXX_FLAGS "-g" )
set( CMAKE_C_FLAGS "-g"  )

find_package( OpenCV REQUIRED )
find_library( CURL_LIBRARY NAMES curl curllib libcurl_imp curllib_static)

add_executable( cv_http_mat ${src_cv_http_mat} )
include_directories( /usr/local/include ${OpenCV_INCLUDE_DIR} )
target_link_libraries( cv_http_mat ${CURL_LIBRARY} ${OpenCV_LIBS} )



