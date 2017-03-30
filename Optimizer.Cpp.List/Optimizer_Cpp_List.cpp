// Optimizer_Cpp_List.cpp : Defines the exported functions for the DLL application.
//

#include "Optimizer_Cpp_List.h"

// This is an example of an exported variable
Optimizer_Cpp_List_API int nOptimizer_Cpp_List=0;

// This is an example of an exported function.
Optimizer_Cpp_List_API int fnOptimizer_Cpp_List(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see Optimizer_Cpp_List.h for the class definition
COptimizer_Cpp_List::COptimizer_Cpp_List()
{
    return;
}
