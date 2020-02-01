#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable 
{
public:
	vec3 center;
	float radius;


	inline sphere() {}
	inline sphere(vec3 cen, float r) : center(cen), radius(r) {};
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
};
#endif // !SPHEREH