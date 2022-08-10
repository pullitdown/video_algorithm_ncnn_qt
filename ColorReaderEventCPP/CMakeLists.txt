
project(ColorReaderEventCPP)

set (_projname "ColorReaderEventCPP")

set (${_projname}_SOURCES
  astra_cap.cpp
  )



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(OpenCV REQUIRED)

find_package(Astra REQUIRED)

# include_directories(
#     ${OpenCV_INCLUDE_DIRS}
#     ${ASTRA_INCLUDE_DIR}
#     #${CMAKE_CURRENT_SOURCE_DIR}
# )

add_library(astra_ SHARED ${${_projname}_SOURCES})

# set_target_properties(${_projname} PROPERTIES FOLDER "${SAMPLE_DIR_FOLDER}cpp-api")
target_include_directories(astra_ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${ASTRA_INCLUDE_DIR})
target_link_libraries(astra_ ${ASTRA_LIBRARIES} ${OpenCV_LIBS} )




include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${ASTRA_INCLUDE_DIR}
)

add_executable(test_ mian.cpp astra_cap.cpp)
target_link_libraries(test_ PUBLIC ${ASTRA_LIBRARIES} ${OpenCV_LIBS})