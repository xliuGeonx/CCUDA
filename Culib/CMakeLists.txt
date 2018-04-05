#CCUDA test by XL
#Cu library
# -----------------------------------------------------------------------------
# ----------------------------- Project configuration -------------------------
# -----------------------------------------------------------------------------

# -- library Name name
SET(Culib "${PROJECT_NAME}Culib")
SET(Culib ${Culib} PARENT_SCOPE)
# -- Include directories --
LIST(APPEND Culib_LIB_INCLUDE_DIRS  ${CMAKE_CURRENT_SOURCE_DIR}/src)
LIST(APPEND Culib_LIB_INCLUDE_DIR ${Culib_LIB_INCLUDE_DIRS})
SET(Culib_LIB_INCLUDE_DIR ${Culib_LIB_INCLUDE_DIR} PARENT_SCOPE)
IF(TARGET ${Culib})
  MESSAGE("${Culib} is already defined")
ELSE()
  # -- Source files list ---
  COLLECT_SRC_FROM_DIRS(Culib_LIB_INCLUDE_DIR)
  
  CUDA_ADD_LIBRARY(${Culib} ${SOURCE_FILES})
  # -- Target --
  TARGET_INCLUDE_DIRECTORIES(${Culib} PUBLIC
    $<BUILD_INTERFACE:${Culib_LIB_INCLUDE_DIR}>
	$<BUILD_INTERFACE:${CUDA_INCLUDE_DIRS}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/>  # <prefix>/include
  )
  #LIST(APPEND CUDALinkedLibraries ${CUDA_LIBRARIES})
  #LIST(REMOVE_DUPLICATES CUDALinkedLibraries ) 
  #SET_TARGET_PROPERTIES(${Culib} PROPERTIES LINKER_LANGUAGE CXX)
  #TARGET_LINK_LIBRARIES(${Culib} LINK_PUBLIC ${CUDALinkedLibraries} )
  

#  SET_TARGET_PROPERTIES(${Culib} PROPERTIES COMPILE_DEFINITIONS "${DefinitionFlags}")
#  SET_PROPERTY(TARGET ${Culib} PROPERTY CXX_STANDARD 98)
#  ADD_SUBDIRECTORY(TestCases)
#  ADD_SUBDIRECTORY(Validations)
ENDIF()