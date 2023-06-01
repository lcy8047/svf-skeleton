set(CMAKE_OSX_ARCHITECTURES "x86_64")

llvm_map_components_to_libnames( llvm_libs bitwriter core ipo irreader instcombine instrumentation target linker analysis scalaropts support )

add_library( TestLib TestLib.cpp )

target_compile_options( TestLib PUBLIC -g -Wall )
target_link_libraries( TestLib ${SVF_LIB} ${llvm_libs} ${Z3_LIBRARIES} )
target_include_directories( TestLib PUBLIC "${PROJECT_SOURCE_DIR}/include" )