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

	#FOREACH( f ${USED_DLLS})
    #ADD_CUSTOM_COMMAND(TARGET ${CCUDA_SimpleKernel_exe} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${f} $<TARGET_FILE_DIR:${CCUDA_SimpleKernel_exe}> )  
	#ENDFOREACH()
#SET_TARGET_PROPERTIES(${CCUDA_SimpleKernel_exe} PROPERTIES LINKER_LANGUAGE CXX)

	#Add libs 
	#LIST(APPEND CUDALinkedLibraries ${CUDA_LIBRARIES} ${Culib})
	#LIST(REMOVE_DUPLICATES CUDALinkedLibraries)
	#TARGET_LINK_LIBRARIES(${CCUDA_SimpleKernel_exe} LINK_PUBLIC ${CUDALinkedLibraries})

ENDIF()