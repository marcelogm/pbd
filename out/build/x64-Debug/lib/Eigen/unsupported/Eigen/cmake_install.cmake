# Install script for directory: C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/marce/UFRGS/pbd/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/AdolcForward"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/AlignedVector3"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/ArpackSupport"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/AutoDiff"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/BVH"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/EulerAngles"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/FFT"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/IterativeSolvers"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/KroneckerProduct"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/LevenbergMarquardt"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/MatrixFunctions"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/MoreVectorization"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/MPRealSupport"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/NonLinearOptimization"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/NumericalDiff"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/OpenGLSupport"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/Polynomials"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/Skyline"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/SparseExtra"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/SpecialFunctions"
    "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/Splines"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "C:/Users/marce/UFRGS/pbd/lib/Eigen/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/marce/UFRGS/pbd/out/build/x64-Debug/lib/Eigen/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

