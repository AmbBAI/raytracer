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

#include <omp.h>

#ifdef RT_WINDOWS
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "thirdpart/glut/glut.h"
#elif RT_LINUX
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#elif RT_MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

typedef unsigned char u8;
typedef unsigned int u32;

#endif // !_RAYTRACER_HEADER_H_
