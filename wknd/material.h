
#ifndef MATERIALH
#define MATERIALH 

struct hit_record;

#include "ray.h"
#include "hitable.h"


float schlick(float cosine, float ref_idx) {
    float r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
        return true;
    }
    else 
        return false;
}


vec3 reflect(const vec3& v, const vec3& n) {
     return v - 2*dot(v,n)*n;
}


/*vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}*/


class material  {
    public:
        int r;
        int g;
        int b;
        float kd;
        float ks;
        float ke;
        float alpha;
        virtual bool scatter(int r, int g, int b, float kd, float ks, float ke, float alpha);
};

#endif


