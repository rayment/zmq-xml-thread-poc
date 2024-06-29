get_filename_component(MINGW_BIN_DIRECTORY "${CMAKE_CXX_COMPILER}" DIRECTORY)

set(LIBGCC_DLL    "${MINGW_BIN_DIRECTORY}/libgcc_s_seh-1.dll")
set(LIBSTDCPP_DLL "${MINGW_BIN_DIRECTORY}/libstdc++-6.dll")

if(LIBGCC_DLL AND LIBSTDCPP_DLL)
    file(COPY ${LIBGCC_DLL} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    file(COPY ${LIBSTDCPP_DLL} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    message("MinGW DLLs have been copied to the libary output directory.")
else()
    message(FATAL_ERROR "MinGW DLLs not found. Please ensure the MinGW libraries are in the MinGW bin folder.")
endif()