#include <iostream>
#include <fstream>
#include "ray.h"

vec3 color2(const ray& r)
{
	vec3 unit_direction = unity_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main3()
{
	int nx = 200;
	int ny = 100;

	std::ofstream imageFile;
	imageFile.open("ch3_bg.ppm");
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
			ray r(origin, lower_left_corner + u*horizontal + v*vertical);
			vec3 col = color2(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			imageFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	imageFile.close();

	return 0;
}