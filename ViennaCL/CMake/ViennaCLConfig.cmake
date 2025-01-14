#- CMake configuration file for ViennaCL
# Sets the following variables if ViennaCL was found:
#  VIENNACL_FOUND         : TRUE if found
#  VIENNACL_INCLUDE_DIRS  : Include-directories to be used
#  VIENNACL_LIBRARIES     : Libraries to link against
# Although ViennaCL is a headers-only library, it still requires an OpenCL
# implementation, which is why it is necessary to link against a library.

# Compute paths
get_filename_component(VIENNACL_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${VIENNACL_CMAKE_DIR}/CMakeCache.txt")
   # in build tree
   get_filename_component(VIENNACL_INSTALL_PREFIX "${VIENNACL_CMAKE_DIR}" PATH)
   set(VIENNACL_INCLUDE_DIR "${_VIENNACL_PREFIX}")
else()
   set(VIENNACL_INSTALL_PREFIX "${VIENNACL_CMAKE_DIR}/../")
   set(VIENNACL_INCLUDE_DIR "${VIENNACL_CMAKE_DIR}/../include")
endif()

# Find OpenCL
set(_VIENNACL_CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")
list(INSERT CMAKE_MODULE_PATH 0 "${VIENNACL_CMAKE_DIR}")
if(ViennaCL_FIND_REQUIRED)
   find_package(OpenCL QUIET REQUIRED)
else()
   find_package(OpenCL QUIET)
endif()
set(CMAKE_MODULE_PATH "${_VIENNACL_CMAKE_MODULE_PATH}")

# Set up variables
set(VIENNACL_INCLUDE_DIRS ${VIENNACL_INCLUDE_DIR} ${OPENCL_INCLUDE_DIRS})
set(VIENNACL_LIBRARIES ${OPENCL_LIBRARIES})
