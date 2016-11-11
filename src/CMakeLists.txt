
add_library ( FastaReader FastaReader.cpp Utils.cpp )
target_include_directories ( FastaReader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

add_library ( Utils Utils.cpp )
target_include_directories ( Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
