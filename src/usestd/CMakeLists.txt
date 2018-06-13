PROJECT(usestd)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MONK_MAKE}/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME usestd)
SET(AUTO_RUN OFF)

#“¿¿µø‚
SET(NEED_GTEST TRUE)

# ±‡“Îƒø¬º
ADD_SOURCE_DIRS(./0-Language;
                ./UtilitiesLibrary;
                ./AlgorithmsLibrary/Non-modifying_sequence_operations;
                ./AlgorithmsLibrary/Modifying_sequence_operations;
                ./AlgorithmsLibrary/Partitioning_operations;
                ./AlgorithmsLibrary/Sorting_operations;
                ./AlgorithmsLibrary/Binary_search_operations;
                ./AlgorithmsLibrary/Set_operations;
                )

INCLUDE($ENV{MONK_MAKE}/end.cmake)



