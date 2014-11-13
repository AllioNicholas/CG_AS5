#pragma once

#include <memory>
#include <vector>

#include "base/Math.hpp"

struct Ray;
struct Hit;
class Material;

// This is the base class for the all the kinds of objects in the scene.
// Its subclasses are Groups, Transforms, Triangles, Planes, Spheres, etc.
// The base class defines functions for intersecting rays with the contents.
class Object3D
{
public:
	Object3D() : material_(nullptr) {}
	Object3D(Material* m) : material_(m) {}
	virtual ~Object3D() {}

	// Intersect ray with the object.
	// You need to fill in the implementations for several types of objects.
	// Hit is the structure that maintains information about the closest hit found
	// so far. Tmin defines the starting point for the ray, which you can use
	// for dealing with those pesky epsilon issues.
	virtual bool intersect(const Ray& r, Hit& h, float tmin) const = 0;

	Material* material() const { return material_; }
	void set_material(Material* m) { material_ = m; }

protected:
	Material* material_;
};

class Box : public Object3D
{
public:
	Box(const FW::Vec3f& min, const FW::Vec3f& max, Material* m) :
		Object3D(m), min_(min), max_(max) {}

	bool intersect(const Ray& r, Hit& h, float tmin) const override;

private:
	FW::Vec3f	min_;
	FW::Vec3f	max_;
};

class Group : public Object3D
{
public:
	Group() {}

	bool intersect(const Ray& r, Hit& h, float tmin) const override;

	size_t size() const { return objects_.size(); }
	Object3D* operator[](int i) const;
	void insert(std::unique_ptr<Object3D> obj);

private:
	std::vector<std::unique_ptr<Object3D>> objects_;
};

class Plane : public Object3D
{
public:
	Plane(const FW::Vec3f& normal, float offset, Material* m) :
		Object3D(m), normal_(normal.normalized()), offset_(offset) {}

	bool intersect(const Ray& r, Hit& h, float tmin) const override;

	const FW::Vec3f& normal() const { return normal_; }
	float offset() const { return offset_; }

private:
	FW::Vec3f normal_;
	float offset_;
};

class Sphere : public Object3D
{
public:
	Sphere(const FW::Vec3f& center, float radius, Material* m) :
		Object3D(m), center_(center), radius_(radius) {}

	bool intersect(const Ray& r, Hit& h, float tmin) const override;

private:
	FW::Vec3f center_;
	float radius_;
};

// A Transform wraps an object. When intersecting it with
// a ray, you need to transform the ray into the coordinate
// system "inside" the transform as described in the lecture.
class Transform : public Object3D
{
public:
	Transform(const FW::Mat4f& m, Object3D* o);

	bool intersect(const Ray &r, Hit &h, float tmin) const override;  
private:
	FW::Mat4f matrix_;
	FW::Mat4f inverse_;
	FW::Mat4f inverse_transpose_;
	Object3D* object_;
};

class Triangle : public Object3D
{
public:
	// a triangle contains, in addition to the vertices, 2D texture coordinates,
	// often called "uv coordinates".
	Triangle(const FW::Vec3f& a, const FW::Vec3f& b, const FW::Vec3f &c,
			Material* m,
			const FW::Vec2f& ta = FW::Vec2f(0, 0),
			const FW::Vec2f& tb = FW::Vec2f(0, 0),
			const FW::Vec2f& tc = FW::Vec2f(0, 0));

	bool intersect(const Ray &r, Hit &h, float tmin) const override;

	const FW::Vec3f& vertex(int i) const;

private:
	FW::Vec3f vertices_[3];
	FW::Vec2f texcoords_[3];  
};
