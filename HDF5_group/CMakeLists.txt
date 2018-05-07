#CCUDA test case SimpleKernel by Xin

# -----------------------------------------------------------------------------
# ----------------------------- Project configuration -------------------------
# -----------------------------------------------------------------------------

# Environment
SET(CCUDA_HDF5_Group_exe CCUDA_HDF5_Group)
SET(CCUDA_HDF5_Group_exe ${CCUDA_HDF5_Group_exe} PARENT_SCOPE)

IF(TARGET ${CCUDA_HDF5_Group_exe})
  MESSAGE("${CCUDA_HDF5_Group_exe} is already defined.")
ELSE()
	#Add execute_process	
	LIST(APPEND CCUDA_HDF5_Group_exe_include_dir  ${CMAKE_CURRENT_SOURCE_DIR}/src)
	ADD_EXECUTABLE(${CCUDA_HDF5_Group_exe} ${CCUDA_HDF5_Group_exe_include_dir}/main.cpp)
	
	IF(CCUDA_USE_HDF5)    
		TARGET_LINK_LIBRARIES(${CCUDA_HDF5_Group_exe} LINK_PUBLIC ${HDF5_LINK_LIBS})
	ENDIF(CCUDA_USE_HDF5)
	
	SET_TARGET_PROPERTIES(${CCUDA_HDF5_Group_exe} PROPERTIES COMPILE_DEFINITIONS "${DefinitionFlags}")
	
	MESSAGE(STATUS "Libraries that will be copied: ${USED_DLLS}")
	FOREACH( f ${USED_DLLS})
		ADD_CUSTOM_COMMAND(TARGET ${CCUDA_HDF5_Group_exe} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${f} $<TARGET_FILE_DIR:${CCUDA_HDF5_Group_exe}> )  
	ENDFOREACH() 
  

ENDIF()