#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "cloth.h"
#include "collision/plane.h"
#include "collision/sphere.h"

using namespace std;

Cloth::Cloth(double width, double height, int num_width_points,
             int num_height_points, float thickness) {
  this->width = width;
  this->height = height;
  this->num_width_points = num_width_points;
  this->num_height_points = num_height_points;
  this->thickness = thickness;

  buildGrid();
  buildClothMesh();
}

Cloth::~Cloth() {
  point_masses.clear();
  springs.clear();

  if (clothMesh) {
    delete clothMesh;
  }
}

void Cloth::buildGrid() {
  // TODO (Part 1): Build a grid of masses and springs.
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    
    double scaled_w = (double) width / (double) num_width_points;
    double scaled_h = (double) height / (double) num_height_points;
    
    // CREATE EVENLY SPACED GRID OF MASSES
    for (int h_p = 0; h_p < num_height_points; h_p++) {
        for (int w_p = 0; w_p < num_width_points; w_p++) {
            x = (double) w_p * scaled_w;
            
            // IF HORIZONTAL, ELSE VERTICAL
            if (this->orientation == 0) {
                y = 1.0;
                z = (double) h_p * scaled_h;
            } else {
                y = (double) h_p * scaled_h;
                z = -0.001 + (rand() / (double) RAND_MAX) * (0.002);
            }
            
            Vector3D position = Vector3D(x, y, z);
            bool pin = false;

            // CHECK IF PINNED
            for (int v = 0; v < pinned.size(); v++) {
                float xPin = pinned[v][0];
                float yPin = pinned[v][1];
                if (xPin == (float) w_p && yPin == (float) h_p) {
                    pin = true;
                }
            }
            PointMass mass = PointMass(position, pin);
            this->point_masses.emplace_back(mass);
        }
    }
        
    // CREATE SPRINGS
    for (int h = 0; h < num_height_points; h++) {
        for (int w = 0; w < num_width_points; w++) {
            int index = num_width_points * h + w;
            PointMass* p1 = &point_masses[index];
            
            
            // STRUCTURAL – EXIST B/W POINT MASS AND POINT MASS TO LEFT AND POINT MASS ABOVE
            if (w > 0) {
                Spring structuralLeft = Spring(p1, p1 - 1, STRUCTURAL);
                this->springs.emplace_back(structuralLeft);
            }
            if (h > 0) {
                Spring structuralUp = Spring(p1, p1 - num_width_points, STRUCTURAL);
                this->springs.emplace_back(structuralUp);
            }
            
            // SHEARING – EXIST B/W POINT MASS AND POINT MASS TO DIAGONAL UPPER LEFT AND DIAGONAL UPPER RIGHT
            if (w > 0 && h > 0) {
                Spring shearingDUL = Spring(p1, p1 - num_width_points - 1, SHEARING);
                this->springs.emplace_back(shearingDUL);
            }
            if (w < num_width_points - 1 && h > 0) {
                Spring shearingDUR = Spring(p1, p1 - num_width_points + 1, SHEARING);
                this->springs.emplace_back(shearingDUR);
            }
            
            // BENDING – EXIST B/W POINT MASS AND POINT MASS 2 AWAY TO LEFT AND 2 ABOVE IT
            if (w > 1) {
                Spring bendingLeft = Spring(p1, p1 - 2, BENDING);
                this->springs.emplace_back(bendingLeft);
            }
            if (h > 1) {
                Spring bendingUp = Spring(p1, p1 - (2 * num_width_points), BENDING);
                this->springs.emplace_back(bendingUp);
            }
        }
    }
}

void Cloth::simulate(double frames_per_sec, double simulation_steps, ClothParameters *cp,
                     vector<Vector3D> external_accelerations,
                     vector<CollisionObject *> *collision_objects) {
  double mass = width * height * cp->density / num_width_points / num_height_points;
  double delta_t = 1.0f / frames_per_sec / simulation_steps;

    
  // TODO (Part 2): Compute total force acting on each point mass.
    Vector3D extForce = Vector3D(0.0, 0.0, 0.0);
    for (int e = 0; e < external_accelerations.size(); e++) {
        extForce += external_accelerations[e];
    }
    extForce *= mass;
    
    // APPLY EXTERNAL FORCE TO EVERY POINT MASS V2
    for (int p = 0; p < this->point_masses.size(); p++) {
        PointMass &pm = this->point_masses[p];
        pm.forces = extForce;
    }
    
    // APPLY SPRING CORRECTION FORCES V2
    for (int s = 0; s < this->springs.size(); s++) {
        Spring sp = this->springs[s];
        if ((sp.spring_type == STRUCTURAL && !cp->enable_structural_constraints) ||(sp.spring_type == SHEARING && !cp->enable_shearing_constraints) ||(sp.spring_type == BENDING && !cp->enable_bending_constraints)) {
            continue;
        } else {
        // COMPUTE FORCE APPLIED TO 2 MASSES ON ENDS USING HOOKE'S LAW
            PointMass *pa = sp.pm_a;
            PointMass *pb = sp.pm_b;
            Vector3D fs = Vector3D(0.0, 0.0, 0.0);
            Vector3D dir = (pb->position - pa->position);
            double dir_norm = dir.norm();
            double ks = 0.0;
            if (cp->enable_bending_constraints && sp.spring_type == BENDING) {
                ks = cp->ks * 0.2;
            } else {
                ks = cp->ks;
            }
            dir.normalize();
            fs = ks * (dir_norm - sp.rest_length) * dir;
            pa->forces += fs;
            pb->forces -= fs;
        }
    }
    
  // TODO (Part 2): Use Verlet integration to compute new point mass positions
    // 2.2 V2
    for (int pp = 0; pp < this->point_masses.size(); pp++) {
        PointMass &point = this->point_masses[pp];
        
        if (!point.pinned) {
            Vector3D curr = point.position;
            double damp = 1.0 - ((cp->damping) / 100.0);
            Vector3D lastPos = point.last_position;
            Vector3D acceleration = (point.forces / mass);
            double dt2 = delta_t * delta_t;
            
            Vector3D newPos = curr + (damp * (curr - lastPos)) + (acceleration * dt2);
            point.last_position = curr;
            point.position = newPos;
        }
    }

  // TODO (Part 4): Handle self-collisions.
    build_spatial_map();
    
  // TODO (Part 3): Handle collisions with other primitives.
    for (PointMass &col : this->point_masses) {
        self_collide(col, simulation_steps);
        for (int c = 0; c < collision_objects->size(); c++) {
            CollisionObject *colObj = collision_objects->at(c);
            colObj->collide(col);
        }
    }

  // TODO (Part 2): Constrain the changes to be such that the spring does not change
  // in length more than 10% per timestep [Provot 1995].
    for (int ss = 0; ss < this->springs.size(); ss++) {
        Spring *sp = &this->springs[ss];
        PointMass *pmA = sp->pm_a;
        PointMass *pmB = sp->pm_b;
        double lenMax = 1.1 * sp->rest_length;
        Vector3D distance = (pmB->position - pmA->position);

        if ((!pmA->pinned || !pmB->pinned) && (distance.norm() > lenMax)) {
            Vector3D direction = distance;
            Vector3D correction = (1.0 / 2.0) * (distance.norm() - lenMax) * direction;

            if (pmA->pinned) {
                pmB->position -= correction * 2.0;
            } else if (pmB->pinned) {
                pmA->position += correction * 2.0;
            } else {
                pmA->position += correction;
                pmB->position -= correction;
            }
        }
    }
}

void Cloth::build_spatial_map() {
  for (const auto &entry : map) {
    delete(entry.second);
  }
  map.clear();

  // TODO (Part 4): Build a spatial map out of all of the point masses.
    for (PointMass &pm : this->point_masses) {
        // CREATE HASH
        float hash = hash_position(pm.position);
        // CHECK IF THERE IS A VALUE
        if (map.find(hash) == map.end()) {
            vector<PointMass *> *hashed = new vector<PointMass *>;
            hashed->push_back(&pm);
            map.insert(make_pair(hash, hashed));
        } else {
            vector<PointMass *> *hashed = map.at(hash);
            hashed->push_back(&pm);
        }
    }
}

void Cloth::self_collide(PointMass &pm, double simulation_steps) {
  // TODO (Part 4): Handle self-collision for a given point mass.
    double maxDist = 2.0 * this->thickness;
    float hash = hash_position(pm.position);
    
    if (map.find(hash) != map.end()) {
        // VECTOR OF ALL CANDIDATE POINT MASSES
        vector<PointMass *> *pms = map.at(hash);
        
        if (pms->size() > 1) {
            // CANDIDATE POINT MASS
            Vector3D correction = Vector3D();
            int collide = 0;
            for (int p = 0; p < pms->size(); p++) {
                PointMass *candidate = pms->at(p);
                
                // ONLY DO IF CANDIDATE IS NOT THE GIVEN POINT MASS
                if (!(&pm == candidate)) {
                    Vector3D direction = (pm.position - candidate->position);
                    double distance = direction.norm();
                    if (distance < maxDist) {
                        collide++;
//                        direction.normalize();
                        correction += (maxDist - distance) * direction.unit();
                    }
                }
            }
            if (collide != 0.0) {
                correction /= (double) collide;
                correction /= simulation_steps;
                pm.position += correction;
            }
        }
    }
}

float Cloth::hash_position(Vector3D pos) {
  // TODO (Part 4): Hash a 3D position into a unique float identifier that represents membership in some 3D box volume.
    
    // PARTITION 3D SPACE
    double w = 3.0 * width / num_width_points;
    double h = 3.0 * height / num_height_points;
    double t = std::max(w, h);
    
    double x_coord = pos.x;
    double y_coord = pos.y;
    double z_coord = pos.z;
    
    float trun_x = x_coord - fmod(x_coord, w);
    trun_x *= 7.0;
    float trun_y = y_coord - fmod(y_coord, h);
    trun_y *= 49.0;
    float trun_z = z_coord - fmod(z_coord, t);
    trun_z *= (7.0 * 7.0 * 7.0);
    
  return trun_x + trun_y + trun_z;
}

///////////////////////////////////////////////////////
/// YOU DO NOT NEED TO REFER TO ANY CODE BELOW THIS ///
///////////////////////////////////////////////////////

void Cloth::reset() {
  PointMass *pm = &point_masses[0];
  for (int i = 0; i < point_masses.size(); i++) {
    pm->position = pm->start_position;
    pm->last_position = pm->start_position;
    pm++;
  }
}

void Cloth::buildClothMesh() {
  if (point_masses.size() == 0) return;

  ClothMesh *clothMesh = new ClothMesh();
  vector<Triangle *> triangles;

  // Create vector of triangles
  for (int y = 0; y < num_height_points - 1; y++) {
    for (int x = 0; x < num_width_points - 1; x++) {
      PointMass *pm = &point_masses[y * num_width_points + x];
      // Get neighboring point masses:
      /*                      *
       * pm_A -------- pm_B   *
       *             /        *
       *  |         /   |     *
       *  |        /    |     *
       *  |       /     |     *
       *  |      /      |     *
       *  |     /       |     *
       *  |    /        |     *
       *      /               *
       * pm_C -------- pm_D   *
       *                      *
       */
      
      float u_min = x;
      u_min /= num_width_points - 1;
      float u_max = x + 1;
      u_max /= num_width_points - 1;
      float v_min = y;
      v_min /= num_height_points - 1;
      float v_max = y + 1;
      v_max /= num_height_points - 1;
      
      PointMass *pm_A = pm                       ;
      PointMass *pm_B = pm                    + 1;
      PointMass *pm_C = pm + num_width_points    ;
      PointMass *pm_D = pm + num_width_points + 1;
      
      Vector3D uv_A = Vector3D(u_min, v_min, 0);
      Vector3D uv_B = Vector3D(u_max, v_min, 0);
      Vector3D uv_C = Vector3D(u_min, v_max, 0);
      Vector3D uv_D = Vector3D(u_max, v_max, 0);
      
      
      // Both triangles defined by vertices in counter-clockwise orientation
      triangles.push_back(new Triangle(pm_A, pm_C, pm_B, 
                                       uv_A, uv_C, uv_B));
      triangles.push_back(new Triangle(pm_B, pm_C, pm_D, 
                                       uv_B, uv_C, uv_D));
    }
  }

  // For each triangle in row-order, create 3 edges and 3 internal halfedges
  for (int i = 0; i < triangles.size(); i++) {
    Triangle *t = triangles[i];

    // Allocate new halfedges on heap
    Halfedge *h1 = new Halfedge();
    Halfedge *h2 = new Halfedge();
    Halfedge *h3 = new Halfedge();

    // Allocate new edges on heap
    Edge *e1 = new Edge();
    Edge *e2 = new Edge();
    Edge *e3 = new Edge();

    // Assign a halfedge pointer to the triangle
    t->halfedge = h1;

    // Assign halfedge pointers to point masses
    t->pm1->halfedge = h1;
    t->pm2->halfedge = h2;
    t->pm3->halfedge = h3;

    // Update all halfedge pointers
    h1->edge = e1;
    h1->next = h2;
    h1->pm = t->pm1;
    h1->triangle = t;

    h2->edge = e2;
    h2->next = h3;
    h2->pm = t->pm2;
    h2->triangle = t;

    h3->edge = e3;
    h3->next = h1;
    h3->pm = t->pm3;
    h3->triangle = t;
  }

  // Go back through the cloth mesh and link triangles together using halfedge
  // twin pointers

  // Convenient variables for math
  int num_height_tris = (num_height_points - 1) * 2;
  int num_width_tris = (num_width_points - 1) * 2;

  bool topLeft = true;
  for (int i = 0; i < triangles.size(); i++) {
    Triangle *t = triangles[i];

    if (topLeft) {
      // Get left triangle, if it exists
      if (i % num_width_tris != 0) { // Not a left-most triangle
        Triangle *temp = triangles[i - 1];
        t->pm1->halfedge->twin = temp->pm3->halfedge;
      } else {
        t->pm1->halfedge->twin = nullptr;
      }

      // Get triangle above, if it exists
      if (i >= num_width_tris) { // Not a top-most triangle
        Triangle *temp = triangles[i - num_width_tris + 1];
        t->pm3->halfedge->twin = temp->pm2->halfedge;
      } else {
        t->pm3->halfedge->twin = nullptr;
      }

      // Get triangle to bottom right; guaranteed to exist
      Triangle *temp = triangles[i + 1];
      t->pm2->halfedge->twin = temp->pm1->halfedge;
    } else {
      // Get right triangle, if it exists
      if (i % num_width_tris != num_width_tris - 1) { // Not a right-most triangle
        Triangle *temp = triangles[i + 1];
        t->pm3->halfedge->twin = temp->pm1->halfedge;
      } else {
        t->pm3->halfedge->twin = nullptr;
      }

      // Get triangle below, if it exists
      if (i + num_width_tris - 1 < 1.0f * num_width_tris * num_height_tris / 2.0f) { // Not a bottom-most triangle
        Triangle *temp = triangles[i + num_width_tris - 1];
        t->pm2->halfedge->twin = temp->pm3->halfedge;
      } else {
        t->pm2->halfedge->twin = nullptr;
      }

      // Get triangle to top left; guaranteed to exist
      Triangle *temp = triangles[i - 1];
      t->pm1->halfedge->twin = temp->pm2->halfedge;
    }

    topLeft = !topLeft;
  }

  clothMesh->triangles = triangles;
  this->clothMesh = clothMesh;
}
