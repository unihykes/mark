PROJECT(use_std)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(VERSION 2.8)

INCLUDE($ENV{MK_MAKE}/begin.cmake)

SET(TARGET_TYPE RUNTIME)
SET(TARGET_NAME use_std)
SET(AUTO_RUN OFF)

#“¿¿µø‚
SET(NEED_GTEST TRUE)

# ±‡“Îƒø¬º
# ./0-Language;
                # ./UtilitiesLibrary;
                # ./AlgorithmsLibrary/Non-modifying_sequence_operations;
                # ./AlgorithmsLibrary/Modifying_sequence_operations;
                # ./AlgorithmsLibrary/Partitioning_operations;
                # ./AlgorithmsLibrary/Sorting_operations;
                # ./AlgorithmsLibrary/Binary_search_operations;
                # ./AlgorithmsLibrary/Set_operations;
                # ./AlgorithmsLibrary/Heap_operations;
                # ./AlgorithmsLibrary/Min_max_operations;
                # ./AlgorithmsLibrary/Comparison_operations;
                # ./AlgorithmsLibrary/Permutation_operations;
                # ./AlgorithmsLibrary/Numeric_operations;
                # ./AlgorithmsLibrary/Uninitialized_memory;
                # ./AlgorithmsLibrary/C_library;
ADD_SOURCE_DIRS(
                ./ThreadSupportLibrary;
                )
                
INCLUDE($ENV{MK_MAKE}/end.cmake)



