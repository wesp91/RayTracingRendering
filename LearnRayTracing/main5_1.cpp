#include <iostream>
#include <fstream>
#include "ray.h"

float hit_sphere5_1(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(r.direction(), oc);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	if (discriminant < 0)
		return -1.0;
	else
		return (-b - sqrt(discriminant)) / 2.0*a;
}

vec3 color5_1(const ray& r)
{
	vec3 sphereCenter = vec3(0, 0, -1);
	float t = hit_sphere5_1(sphereCenter, 0.5, r);

	// hit with sphere
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.point_at_parameter(t) - sphereCenter);
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}

	// no hit with sphere
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main5_1()
{
	int nx = 200;
	int ny = 100;

	std::ofstream imageFile;
	imageFile.open("ch5_normals.ppm");
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
			vec3 col = color5_1(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			imageFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	imageFile.close();

	return 0;
}