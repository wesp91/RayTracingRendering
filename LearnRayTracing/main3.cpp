#include <iostream>
#include <fstream>
#include "ray.h"

// sphere equation
// sphere equation in origin: x*x + y*y + z*z = R*R
// sphere equation in center c: (x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz) = R*R
// vector from center C = (cx,cy,cz) to p = (x,y,z) is (p-C)
// dot((p-C),(p-C)) = (x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz)
// so dot((p-C),(p-C)) = R*R
// we want to know if our ray p(t) = A + t*B hits the sphere anyware
// if it does hit the sphere, there is some t for which p(t) sitisfies the sphere equation
// dot((p(t)-C),(p(t)-C)) = R*R
// dot((A + t*B - C),(A + t*B - C)) = R*R
// t*t*dot(B,B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R = 0
// the only variable is t, so it's a quadratic equation
// if discriminant is positive, 2 real solutions (ray hit the sphere in two points. ray pass throuh the sphere)
// if discriminant is negative, 0 real solutions (ray doesn't hit the sphere)
// if discriminant is 0, 1 real solution (ray hit the sphere in one point. ray is tangent to the sphere)

bool hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(r.direction(), oc);
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b * b - 4 * a*c;
	return discriminant > 0;
}

vec3 color(const ray& r)
{
	//hit with sphere (red color)
	if (hit_sphere(vec3(0, 0, -1), 0.5, r))
		return vec3(1,0,0);

	//bg
	vec3 unit_direction = unity_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main3()
{
	int nx = 200;
	int ny = 100;

	std::ofstream imageFile;
	imageFile.open("ch3_sphere.ppm");
	imageFile << "P3\n" << nx << " " << ny << "\n255\n";

	//screen
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);

	//camera
	vec3 origin(0.0, 0.0, 0.0);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			imageFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	imageFile.close();

	return 0;
}