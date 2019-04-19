#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../misc/sphere_drawing.h"
#include "sphere.h"

using namespace nanogui;
using namespace CGL;

void Sphere::collide(PointMass &pm) {
  // TODO (Part 3): Handle collisions with spheres.
    Vector3D pm_pos = pm.position;
    Vector3D distance = pm_pos - this->origin;
    double dist_norm = distance.norm();
    Vector3D direction = distance;
    direction.normalize();
    
    // CHECK IF INTERSECTS OR INSIDE SPHERE
    if (dist_norm < this->radius) {
//        direction.normalize();
        Vector3D tangentP = this->origin + (direction * this->radius);
        Vector3D lastPos = pm.last_position;
        Vector3D correction = (1.0 - this->friction) * (tangentP - lastPos);
        
        Vector3D newPos = lastPos + correction;
        pm.position = newPos;
    }
}

void Sphere::render(GLShader &shader) {
  // We decrease the radius here so flat triangles don't behave strangely
  // and intersect with the sphere when rendered
  m_sphere_mesh.draw_sphere(shader, origin, radius * 0.92);
}
