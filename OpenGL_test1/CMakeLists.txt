#CCUDA test case SimpleKernel by Xin

# -----------------------------------------------------------------------------
# ----------------------------- Project configuration -------------------------
# -----------------------------------------------------------------------------

# Environment
SET(CCUDA_OpenGLt1_exe CCUDA_OpenGLt1)
SET(CCUDA_OpenGLt1_exe ${CCUDA_OpenGLt1_exe} PARENT_SCOPE)

IF(TARGET ${CCUDA_OpenGLt1_exe})
  MESSAGE("${CCUDA_OpenGLt1_exe} is already defined.")
ELSE()
	#Add execute_process	
	LIST(APPEND CCUDA_OpenGLt1_exe_include_dir  ${CMAKE_CURRENT_SOURCE_DIR}/src)
	ADD_EXECUTABLE(${CCUDA_OpenGLt1_exe} ${CCUDA_OpenGLt1_exe_include_dir}/main.cpp)

	#Add include
	#LIST(APPEND CUDA_inlcude_dir ${CUDA_INCLUDE_DIRS})
	#INCLUDE_DIRECTORIES( ${CUDA_inlcude_dir} ${Culib_LIB_INCLUDE_DIR})
	SET(CCUDA_OpenGL_dll_list)
	LIST(APPEND CCUDA_OpenGL_dll_list ${CCUDA_OpenGLt1_exe_include_dir}/freeglut.dll)
	LIST(APPEND CCUDA_OpenGL_dll_list ${CCUDA_OpenGLt1_exe_include_dir}/FreeImage64.dll)
	LIST(APPEND CCUDA_OpenGL_dll_list ${CCUDA_OpenGLt1_exe_include_dir}/glew64.dll)
	COLLECT_DDL_FROM_FILES(CCUDA_OpenGL_dll_list)
	FOREACH( f ${USED_DLLS})
    ADD_CUSTOM_COMMAND(TARGET ${CCUDA_OpenGLt1_exe} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${f} $<TARGET_FILE_DIR:${CCUDA_OpenGLt1_exe}> )  
	ENDFOREACH()
#SET_TARGET_PROPERTIES(${CCUDA_OpenGLt1_exe} PROPERTIES LINKER_LANGUAGE CXX)

	#Add libs 
	LIST(APPEND CUDALinkedLibraries glew64.dll)
	LIST(APPEND CUDALinkedLibraries freeglut.dll)
	LIST(REMOVE_DUPLICATES CUDALinkedLibraries)
	TARGET_LINK_LIBRARIES(${CCUDA_OpenGLt1_exe} LINK_PUBLIC ${CUDALinkedLibraries})

ENDIF()