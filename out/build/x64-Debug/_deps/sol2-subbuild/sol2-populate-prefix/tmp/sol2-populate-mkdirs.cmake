# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/budget/DAE/2024-2025/Semester 5/Software Engineering/Assignments/Exam/SE_Exam_2GD10E_Last_First/Project/out/build/x64-Debug/_deps/sol2-src"
  "C:/Users/budget/DAE/2024-2025/Semester 5/Software Engineering/Assignments/Exam/SE_Exam_2GD10E_Last_First/Project/out/build/x64-Debug/_deps/sol2-build"
  "C:/Users/budget/DAE/2024-2025/Semester 5/Software Engineering/Assignments/Exam/SE_Exam_2GD10E_Last_First/Project/out/build/x64-Debug/_deps/sol2-subbuild/sol2-populate-prefix"
  "C:/Users/budget/DAE/2024-2025/Semester 5/Software Engineering/Assignments/Exam/SE_Exam_2GD10E_Last_First/Project/out/build/x64-Debug/_deps/sol2-subbuild/sol2-populate-prefix/tmp"
  "C:/Users/budget/DAE/2024-2025/Semester 5/Software Engineering/Assignments/Exam/SE_Exam_2GD10E_Last_First/Project/out/build/x64-Debug/_deps/sol2-subbuild/sol2-populate-prefix/src/sol2-populate-stamp"
  "C:/Users/budget/DAE/2024-2025/Semester 5/Software Engineering/Assignments/Exam/SE_Exam_2GD10E_Last_First/Project/out/build/x64-Debug/_deps/sol2-subbuild/sol2-populate-prefix/src"
  "C:/Users/budget/DAE/2024-2025/Semester 5/Software Engineering/Assignments/Exam/SE_Exam_2GD10E_Last_First/Project/out/build/x64-Debug/_deps/sol2-subbuild/sol2-populate-prefix/src/sol2-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/budget/DAE/2024-2025/Semester 5/Software Engineering/Assignments/Exam/SE_Exam_2GD10E_Last_First/Project/out/build/x64-Debug/_deps/sol2-subbuild/sol2-populate-prefix/src/sol2-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/budget/DAE/2024-2025/Semester 5/Software Engineering/Assignments/Exam/SE_Exam_2GD10E_Last_First/Project/out/build/x64-Debug/_deps/sol2-subbuild/sol2-populate-prefix/src/sol2-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
