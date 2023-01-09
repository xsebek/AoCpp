#pragma once


#ifdef _WIN32
  #define AOCPP_EXPORT __declspec(dllexport)
#else
  #define AOCPP_EXPORT
#endif

AOCPP_EXPORT void aocpp();
