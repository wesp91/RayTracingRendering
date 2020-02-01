#include <iostream>
#include <fstream>
#include "vec3.h"

int main1()
{
	int nx = 200;
	int ny = 100;

	std::ofstream imageFile;
	imageFile.open("ch2_hellovec.ppm");
	imageFile << "P3\n" << nx << " " << ny << "\n255\n";

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			imageFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	imageFile.close();

	return 0;
}