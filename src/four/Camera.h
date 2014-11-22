#pragma once

#include "ray.hpp"
#include "base/Math.hpp"

#include <cassert>
#include <cfloat>
#include <cmath>

class Camera
{
public:
	// generate rays for each screen-space coordinate
	virtual Ray generateRay(const FW::Vec2f& point) = 0; 

	static inline FW::Vec2f normalizedImageCoordinateFromPixelCoordinate(const FW::Vec2f& pixel, const FW::Vec2i& imageSize) {
		// YOUR CODE HERE (R1)
		// Given floating-point pixel coordinates (px,py), you should return the corresponding normalized screen coordinates in [-1,1]^2
		// Pay attention to which direction is "up" :)
		FW::Vec2f normalized_coordinates = FW::Vec2f();

		normalized_coordinates.x = (pixel.x / ((float)imageSize.x/2)) - 1 ;
		normalized_coordinates.y = (-pixel.y / ((float)imageSize.y/2)) + 1;

		return normalized_coordinates;
	}
	
	virtual float getTMin() const = 0 ; 

protected:
	FW::Vec3f center; 
	FW::Vec3f direction;
	FW::Vec3f up;
	FW::Vec3f horizontal;
};


class OrthographicCamera: public Camera
{
public:
	OrthographicCamera(FW::Vec3f center, FW::Vec3f direction, FW::Vec3f up, float size) {
		this->center = center;
		this->direction = direction.normalized();	
		this->horizontal = cross(direction, up).normalized();
		// need to make an orthonormal vector to the projection
		this->up = cross(horizontal, direction).normalized(); 
		this->size = size;
	}

	virtual Ray generateRay(const FW::Vec2f& point) {
		// YOUR CODE HERE (R1)
		// Generate a ray with the given screen coordinates, which you should assume lie in [-1,1]^2
		
		auto orig = (this->center + point.y*(this->size * this->up) / 2 + point.x*(this->size * this->horizontal) / 2);

		return Ray(orig, this->direction);
	}

	virtual float getTMin() const {
		return -1.0f*FLT_MAX;
	}

private:
	float size ; 
};


class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(const FW::Vec3f& center_, const FW::Vec3f& direction_,const FW::Vec3f& up_ , float fov_angle)
	{
		this->center = center_;
		this->direction = direction_.normalized();
		this->horizontal = cross( direction_ , up_ ).normalized();
		this->up = cross(horizontal, direction_).normalized(); 
		this->fov_angle = fov_angle;
	}

	virtual Ray generateRay( const FW::Vec2f& point)
	{	
		// YOUR CODE HERE (R3)
		// Generate a ray with the given screen coordinates, which you should assume lie in [-1,1]^2
		// How to do this is described in the lecture notes.

		auto d = 1 / FW::tan(this->fov_angle / 2);
		auto dir = point.x * this->horizontal + point.y*this->up + d * this->direction;
		dir.normalized();

		return Ray(this->center, dir);
	}

	virtual float getTMin() const { 
		return 0.0f;
	}

private:
	float fov_angle;
};
