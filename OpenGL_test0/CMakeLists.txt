#CCUDA test case SimpleKernel by Xin

# -----------------------------------------------------------------------------
# ----------------------------- Project configuration -------------------------
# -----------------------------------------------------------------------------

# Environment
SET(CCUDA_OpenGLt0_exe CCUDA_OpenGLt0)
SET(CCUDA_OpenGLt0_exe ${CCUDA_OpenGLt0_exe} PARENT_SCOPE)

IF(TARGET ${CCUDA_OpenGLt0_exe})
  MESSAGE("${CCUDA_OpenGLt0_exe} is already defined.")
ELSE()
	#Add execute_process	
	LIST(APPEND CCUDA_OpenGLt0_exe_include_dir  ${CMAKE_CURRENT_SOURCE_DIR}/src)
	ADD_EXECUTABLE(${CCUDA_OpenGLt0_exe} ${CCUDA_OpenGLt0_exe_include_dir}/main.cpp)

	#Add include
	#LIST(APPEND CUDA_inlcude_dir ${CUDA_INCLUDE_DIRS})
	#INCLUDE_DIRECTORIES( ${CUDA_inlcude_dir} ${Culib_LIB_INCLUDE_DIR})
	SET(CCUDA_OpenGL_dll_list)
	LIST(APPEND CCUDA_OpenGL_dll_list ${CCUDA_OpenGLt0_exe_include_dir}/freeglut.dll)
	LIST(APPEND CCUDA_OpenGL_dll_list ${CCUDA_OpenGLt0_exe_include_dir}/FreeImage64.dll)
	LIST(APPEND CCUDA_OpenGL_dll_list ${CCUDA_OpenGLt0_exe_include_dir}/glew64.dll)
	COLLECT_DDL_FROM_FILES(CCUDA_OpenGL_dll_list)
	FOREACH( f ${USED_DLLS})
    ADD_CUSTOM_COMMAND(TARGET ${CCUDA_OpenGLt0_exe} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${f} $<TARGET_FILE_DIR:${CCUDA_OpenGLt0_exe}> )  
	ENDFOREACH()
#SET_TARGET_PROPERTIES(${CCUDA_OpenGLt0_exe} PROPERTIES LINKER_LANGUAGE CXX)

	#Add libs 
	#LIST(APPEND CUDALinkedLibraries ${CUDA_LIBRARIES} ${Culib})
	#LIST(REMOVE_DUPLICATES CUDALinkedLibraries)
	#TARGET_LINK_LIBRARIES(${CCUDA_OpenGLt0_exe} LINK_PUBLIC ${CUDALinkedLibraries})

ENDIF()