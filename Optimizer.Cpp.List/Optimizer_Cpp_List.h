#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the Optimizer_Cpp_List_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// Optimizer_Cpp_List_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef Optimizer_Cpp_List_EXPORTS
#define Optimizer_Cpp_List_API __declspec(dllexport)
#else
#define Optimizer_Cpp_List_API __declspec(dllimport)
#endif

// This is an example of a class exported from the Optimizer_Cpp_List.dll
class Optimizer_Cpp_List_API COptimizer_Cpp_List
{
public:
    COptimizer_Cpp_List();
    // TODO: add your methods here.
};

// This is an example of an exported variable
extern Optimizer_Cpp_List_API int nOptimizer_Cpp_List;

// This is an example of an exported function.
Optimizer_Cpp_List_API int fnOptimizer_Cpp_List(void);
