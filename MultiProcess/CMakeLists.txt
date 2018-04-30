#CCUDA test case SimpleKernel by Xin

# -----------------------------------------------------------------------------
# ----------------------------- Project configuration -------------------------
# -----------------------------------------------------------------------------

# Environment
SET(CCUDA_Mprocess_exe CCUDA_Mprocess)
SET(CCUDA_Mprocess_exe ${CCUDA_Mprocess_exe} PARENT_SCOPE)

IF(TARGET ${CCUDA_Mprocess_exe})
  MESSAGE("${CCUDA_Mprocess_exe} is already defined.")
ELSE()
	#Add execute_process	
	LIST(APPEND CCUDA_Mprocess_exe_include_dir  ${CMAKE_CURRENT_SOURCE_DIR}/src)
	ADD_EXECUTABLE(${CCUDA_Mprocess_exe} ${CCUDA_Mprocess_exe_include_dir}/main.cpp)

	#Add include
	LIST(APPEND CUDA_inlcude_dir ${CUDA_INCLUDE_DIRS})
	INCLUDE_DIRECTORIES( ${CUDA_inlcude_dir} ${Culib_LIB_INCLUDE_DIR})

	#FOREACH( f ${USED_DLLS})
    #ADD_CUSTOM_COMMAND(TARGET ${CCUDA_Mprocess_exe} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${f} $<TARGET_FILE_DIR:${CCUDA_Mprocess_exe}> )  
	#ENDFOREACH()
#SET_TARGET_PROPERTIES(${CCUDA_Mprocess_exe} PROPERTIES LINKER_LANGUAGE CXX)

	#Add libs 
	#LIST(APPEND CUDALinkedLibraries ${CUDA_LIBRARIES} ${Culib})
	#LIST(REMOVE_DUPLICATES CUDALinkedLibraries)
	#TARGET_LINK_LIBRARIES(${CCUDA_Mprocess_exe} LINK_PUBLIC ${CUDALinkedLibraries})

ENDIF()