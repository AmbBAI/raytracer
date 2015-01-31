#ifndef _HEADER_H_
#define _HEADER_H_

#include "base/header.h"
#include "base/application.h"
#include "base/canvas.h"
#include "base/mathf.h"
#include "geometry/geometry.h"
#include "geometry/sphere.h"
#include "geometry/plane.h"
#include "geometry/union.h"
#include "camera/camera.h"
#include "material/material.h"
#include "material/checker_material.h"
#include "material/phong_material.h"

void TestColor(rt::Canvas* canvas);
void RenderDepth(rt::Canvas* canvas, rt::Geometry& scene, rt::Camera& camera, float maxDepth);
void RenderNormal(rt::Canvas* canvas, rt::Geometry& scene, rt::Camera& camera);
void RenderMaterial(rt::Canvas* canvas, rt::Geometry& scene, rt::Camera& camera);
const rt::Color RayTraceRecursive(rt::Geometry& scene, const rt::Ray3& ray, int maxReflect);
void RenderRayTraceReflection(rt::Canvas* canvas, rt::Geometry& scene, rt::Camera& camera, int maxReflect);

#endif //!_HEADER_H_
