FIND_PACKAGE(Snappy)

IF (SNAPPY_FOUND)
  GET_PROPERTY(dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
  LIST(REMOVE_ITEM dirs ${CMAKE_SOURCE_DIR}/include/providers)
  SET_PROPERTY(DIRECTORY PROPERTY INCLUDE_DIRECTORIES "${dirs}")

  INCLUDE_DIRECTORIES(${SNAPPY_INCLUDE_DIRS})

  MYSQL_ADD_PLUGIN(provider_snappy plugin.c COMPONENT provider-snappy
    LINK_LIBRARIES ${SNAPPY_LIBRARIES} CONFIG provider_snappy.cnf)
ENDIF()
