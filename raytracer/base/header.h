#ifndef _RAYTRACER_HEADER_H_
#define _RAYTRACER_HEADER_H_

#include <cstdio>
#include <ctime>
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <cfloat>
#include <cassert>

#include <vector>
#include <algorithm>


#ifdef RT_WINDOWS
#include <Windows.h>
#include <omp.h>
#define _GLFW_WIN32
#elif RT_LINUX
#include <omp.h>
#define _GLFW_X11
#elif RT_MACOSX
#define _GLFW_COCOA
#endif

#define _GLFW_USE_OPENGL
#include "thirdpart/glfw/include/GLFW/glfw3.h"


typedef unsigned char u8;
typedef unsigned int u32;

#endif // !_RAYTRACER_HEADER_H_
