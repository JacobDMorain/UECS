cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(UECS VERSION 0.16.2)
message(STATUS "[Project] ${PROJECT_NAME}")

include(cmake/InitUCMake.cmake)
Ubpa_InitUCMake(VERSION 0.6.4)

Ubpa_InitProject()

Ubpa_AddDep(UTemplate 0.7.2)
Ubpa_AddDep(UGraphviz 0.3.0)
Ubpa_AddDep(USmallFlat 0.2.3)

Ubpa_AddSubDirsRec(include)
Ubpa_AddSubDirsRec(src)

Ubpa_Export(
  TARGET
  DIRECTORIES
    "include"
)
