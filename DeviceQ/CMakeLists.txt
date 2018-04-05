#CCUDA test case SimpleKernel by Xin

# -----------------------------------------------------------------------------
# ----------------------------- Project configuration -------------------------
# -----------------------------------------------------------------------------

# Environment
SET(DeviceQ_exe DeviceQ)
SET(DeviceQ_exe ${DeviceQ_exe} PARENT_SCOPE)

IF(TARGET ${DeviceQ_exe})
  MESSAGE("${DeviceQ_exe} is already defined.")
ELSE()
	#Add execute_process	
	LIST(APPEND DeviceQ_exe_include_dir  ${CMAKE_CURRENT_SOURCE_DIR}/src)
	CUDA_ADD_EXECUTABLE(${DeviceQ_exe} ${DeviceQ_exe_include_dir}/deviceQ.cu)

	#Add include
	SET(DeviceQ_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/inc)
	LIST(APPEND CUDA_inlcude_dir ${CUDA_INCLUDE_DIRS} ${DeviceQ_include_dir})
	INCLUDE_DIRECTORIES( ${CUDA_inlcude_dir} ${DeviceQ_exe_include_dir})

	#FOREACH( f ${USED_DLLS})
    #ADD_CUSTOM_COMMAND(TARGET ${DeviceQ_exe} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${f} $<TARGET_FILE_DIR:${DeviceQ_exe}> )  
	#ENDFOREACH()
#SET_TARGET_PROPERTIES(${DeviceQ_exe} PROPERTIES LINKER_LANGUAGE CXX)

	#Add libs 
	#LIST(APPEND CUDALinkedLibraries ${CUDA_LIBRARIES} ${Culib})
	#LIST(REMOVE_DUPLICATES CUDALinkedLibraries)
	#TARGET_LINK_LIBRARIES(${DeviceQ_exe} LINK_PUBLIC ${CUDALinkedLibraries})

ENDIF()