#ifndef _HEADER_H_
#define _HEADER_H_

#include "base/header.h"
#include "base/application.h"
#include "base/canvas.h"
#include "object/sphere.h"
#include "camera/camera.h"
#include "base/mathf.h"

void TestColor(rt::Canvas* canvas);
void RenderDepth(rt::Canvas* canvas, rt::Object& scene, rt::Camera& camera, float maxDepth);
void RenderNormal(rt::Canvas* canvas, rt::Object& scene, rt::Camera& camera);

#endif //!_HEADER_H_
