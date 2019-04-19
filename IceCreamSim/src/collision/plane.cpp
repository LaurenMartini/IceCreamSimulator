#include "iostream"
#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../clothSimulator.h"
#include "plane.h"

using namespace std;
using namespace CGL;

#define SURFACE_OFFSET 0.0001

void Plane::collide(PointMass &pm) {
  // TODO (Part 3): Handle collisions with planes.
    //1. Compute where the point mass should have intersected the plane
    //   if it had travelled in a straight line from its position towards
    //   the plane.  Call this the tangent point.
    
    //check if the current position of pm is on other side of the plane
    //dot product of normal and current pm position
    double pmPosition = dot(normal, pm.position);
    //if less then zero on other side of the plane
    if (pmPosition < 0) {
        //normal - pm.position and normalize (unit vector) -> in the direction of the normal
        Vector3D newDirection = (normal - pm.position).unit();
        Vector3D tangentPoint = newDirection * SURFACE_OFFSET + pm.position;
        
        //2. Compute the correction vector needed to be applied to the point mass's
        //   last_position in order to reach a point slightly above the tangent point
        //   on the same side of the plane that the point mass was before crossing over
        //   Provided is a small constant SURFACE_OFFSET for this small displacement
        //tangent subracted by last_position
        Vector3D correctionVector = tangentPoint - pm.last_position;
        
        //3. Finally let the point mass's new position be its last_position adjusted
        //   by the above correction vector, scaled down by friction (1 - f)
        pm.position = (1.0 - friction) * correctionVector + pm.last_position;
    }
}

void Plane::render(GLShader &shader) {
  nanogui::Color color(0.7f, 0.7f, 0.7f, 1.0f);

  Vector3f sPoint(point.x, point.y, point.z);
  Vector3f sNormal(normal.x, normal.y, normal.z);
  Vector3f sParallel(normal.y - normal.z, normal.z - normal.x,
                     normal.x - normal.y);
  sParallel.normalize();
  Vector3f sCross = sNormal.cross(sParallel);

  MatrixXf positions(3, 4);
  MatrixXf normals(3, 4);

  positions.col(0) << sPoint + 2 * (sCross + sParallel);
  positions.col(1) << sPoint + 2 * (sCross - sParallel);
  positions.col(2) << sPoint + 2 * (-sCross + sParallel);
  positions.col(3) << sPoint + 2 * (-sCross - sParallel);

  normals.col(0) << sNormal;
  normals.col(1) << sNormal;
  normals.col(2) << sNormal;
  normals.col(3) << sNormal;

  if (shader.uniform("u_color", false) != -1) {
    shader.setUniform("u_color", color);
  }
  shader.uploadAttrib("in_position", positions);
  if (shader.attrib("in_normal", false) != -1) {
    shader.uploadAttrib("in_normal", normals);
  }

  shader.drawArray(GL_TRIANGLE_STRIP, 0, 4);
}
