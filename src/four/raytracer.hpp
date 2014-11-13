#pragma once

#include "hit.hpp"
#include "objects.hpp"
#include "ray.hpp"

struct Args;
class SceneParser;

class RayTracer
{
public:
	RayTracer(const SceneParser& scene, const Args& args) :
		args_(args),
		scene_(scene)
	{}

	// You need to fill in the implementation for this function.
	FW::Vec3f traceRay(Ray& ray, float tmin, int bounces, float refr_index, Hit& hit) const;

private:
	RayTracer& operator=(const RayTracer&); // squelch compiler warning
	FW::Vec3f computeShadowColor(Ray& ray, float distanceToLight) const;

	const SceneParser&	scene_;
	const Args&			args_;
};
