include(CMakeFindDependencyMacro)
find_dependency(PocoFoundation)
find_dependency(PocoEncodings)
find_dependency(PocoNet)
find_dependency(PocoNetSSL)

#find_dependency(PocoXML)
#find_dependency(PocoJSON)
include("${CMAKE_CURRENT_LIST_DIR}/mumuWorldTargets.cmake")

