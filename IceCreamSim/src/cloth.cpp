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
    //1. create an evenly spaced grid of masses
    //num_width_points by num_height_points total masses spanning
    //width and height lengths
    //calculate variance of height and width based on num points
    double wVariance = (double)width/(double)num_width_points;
    double hVariance = (double)height/(double)num_height_points;
    
    for (int j = 0; j < num_height_points; j++) { //row
        for (int i = 0; i < num_width_points; i++) {//column
            //store these point masses in point_masses vector IN ROW-MAJOR(X-AXIS) ORDER
            //A[row][col] which in my case is A[j][i]
            
            //if the cloth's orientation is HORIZONTAL then set the y coordinate for all
            //point masses to 1 while varying positions over xz plane
            if (orientation == HORIZONTAL) {
                Vector3D pm_coords = Vector3D(0.0, 0.0, 0.0);
                pm_coords.y = 1.0; //all y's are 1
                
                //calculate x and z
                pm_coords.x = i * wVariance;
                pm_coords.z = j * hVariance;
                
                PointMass *pm = new PointMass(pm_coords, false);
                
                //store in cloth's point_masses vector
                point_masses.emplace_back(*pm);
            } else {
                Vector3D pm_coords = Vector3D(0.0,0.0,0.0);
                //else generate a small random offset between -1/1000 and 1/1000 for each point
                //mass and use that as the z coordinate while varying positions over the xy plane
                //rand() is useful here
                /*
                 rand double calculation credit:
                 https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
                 first answer which is by rep_movsd
                 */
                double randVal = (double)rand() / RAND_MAX;
                randVal = -0.001 + randVal * (0.001 + 0.001);
                pm_coords.z = randVal;
                
                pm_coords.x = i * wVariance;
                pm_coords.y = j * hVariance;
                
                PointMass *pm = new PointMass(pm_coords, false);
                
                //store in cloth's point_masses vector
                point_masses.emplace_back(*pm);
            }
        }
    }
    //set the values to true for pinned point masses
    for (int j = 0; j < num_height_points; j++){
        for (int i = 0; i < num_width_points; i++) {
            //point mass and its x and y
            PointMass *pCurr = &point_masses[j * num_width_points + i];

            for (int elem = 0; elem < pinned.size(); elem++) {
                //get x and y of pinned
                int pX = pinned[elem][0];
                int pY = pinned[elem][1];

                if (i == pX && j == pY) {
                    pCurr -> pinned = true;
                }
            }
        }
    }
    
//    cout << "point masses created \n";
    
    //2.  create springs to apply the structural, shear, and blending constraints
    //between point masses
    for (int j = 0; j < num_height_points; j++) {
        for (int i = 0; i < num_width_points; i++) {
            //current point
            PointMass *pCurr = &point_masses[j * num_width_points + i];
//            cout << "pCurr: " << pCurr << "\n";
            
            //Structural
            if (i > 0) {
                //left point exists
                springs.push_back(Spring(pCurr, pCurr - 1, STRUCTURAL));
            }
            if (j > 0) {
                //above point exists
                springs.push_back(Spring(pCurr, pCurr - num_width_points, STRUCTURAL));
            }
            //Shearing
            if (i > 0 && j > 0) {
                //diagonal upper left
                springs.push_back(Spring(pCurr, pCurr - 1 - num_width_points, SHEARING));
            }
            if (i < num_width_points - 1 && j > 0) {
                //diagonal upper right
                springs.push_back(Spring(pCurr, pCurr + 1 - num_width_points, SHEARING));
            }
            //Bending
            if (i > 1) {
                //two to the left
                springs.push_back(Spring(pCurr, pCurr - 2, BENDING));
            }
            if (j > 1) {
                //two above
                springs.push_back(Spring(pCurr, pCurr - num_width_points - num_width_points, BENDING));
            }
        }
    }
}

void Cloth::simulate(double frames_per_sec, double simulation_steps, ClothParameters *cp,
                     vector<Vector3D> external_accelerations,
                     vector<CollisionObject *> *collision_objects) {
  double mass = width * height * cp->density / num_width_points / num_height_points;
  double delta_t = 1.0f / frames_per_sec / simulation_steps;

  // TODO (Part 2): Compute total force acting on each point mass
    
    for (int j = 0; j < num_height_points; j++) {
        for (int i = 0; i < num_width_points; i++) {
            //current point mass
            PointMass *pCurr = &point_masses[j * num_width_points + i];
            
            //reset forces
            pCurr -> forces = Vector3D(0.0, 0.0, 0.0);
            
            //compute total external force based on external_accelerations and mass
            //F = ma
            Vector3D externalForce = Vector3D(0.0, 0.0, 0.0);
            
            externalForce += external_accelerations[0] * mass;
            //loop through external_accelerations
//            for (int t = 0; t < external_accelerations.size(); t++) {
//                externalForce += external_accelerations[t] * mass;
//            }
            
            //add to forces
            pCurr -> forces = externalForce;
        }
    }
    
    //now to calculate spring correction forces
    for (int s = 0; s < springs.size(); s++) {
        //skip over spring if that spring's constraint type is currently
        //disabled
        //get current spring
        Spring sCurr = springs[s];
        int sType = sCurr.spring_type;
        
        //check if structural disabled
        if (sType == STRUCTURAL && !(cp -> enable_structural_constraints)) {
            continue;
        } else if (sType == SHEARING && !(cp -> enable_shearing_constraints)) {
            continue;
        } else if (sType == BENDING && !(cp -> enable_bending_constraints)) {
            continue;
        } else {
            //otherwise compute the force applied to the two masses on its ends
            //using Hooke's Law
            //get point mass a and b from springs
            PointMass *pA = sCurr.pm_a;
            PointMass *pB = sCurr.pm_b;
            
            //calculate the magnitude of these point masses
            double magnitude = (pB->position - pA->position).norm();
            Vector3D unitVector = (pB -> position - pA -> position);
            unitVector.normalize();
            
            //force
            double springForce = 0.0;
            double kS = cp -> ks;
            if (sType == BENDING) {
                kS *= 0.2;
            }
            
            double l = sCurr.rest_length;
            springForce = kS * (magnitude - l);
            
            //combo with pA and pB forces
            pA -> forces += springForce * unitVector;
            pB -> forces += (-1.0 * springForce) * unitVector;
        }
    }
    
  // TODO (Part 2): Use Verlet integration to compute new point mass positions
    for (int j = 0; j < num_height_points; j++) {
        for (int i = 0; i < num_width_points; i++) {
            //current point mass
            PointMass *pCurr = &point_masses[j * num_width_points + i];

            //first check if point mass is pinned -> don't adjust position if so
            if (pCurr->pinned) {
                continue;
            } else {
                //damping term
                double d = cp->damping;

                //adjust damping from percentage
                d /= (double)100;

                //get acceleration from all forces and mass
                Vector3D accelerationTotal = (pCurr -> forces);//mass;

                //calculate new position
                Vector3D newPosition = pCurr -> position  + (1.0 - d) * (pCurr -> position - pCurr -> last_position) + accelerationTotal * pow(delta_t, 2.0);

                //update positions
                pCurr -> last_position = pCurr -> position;
                pCurr -> position = newPosition;
            }
        }
    }

    build_spatial_map();
  // TODO (Part 4): Handle self-collisions.
    for (int j = 0; j < num_height_points; j++) {
        for (int i = 0; i < num_width_points; i++) {
            //for each point mass, make sure it collides with itself
            PointMass *pCurr = &point_masses[j * num_width_points + i];
            self_collide(*pCurr, simulation_steps);
        }
    }

  // TODO (Part 3): Handle collisions with other primitives.
    for (int j = 0; j < num_height_points; j++) {
        for (int i = 0; i < num_width_points; i++) {
            //for each point mass, make sure it collides with every possible CollisionObject
            PointMass *pCurr = &point_masses[j * num_width_points + i];
            
            for (int k = 0; k < collision_objects->size(); k++){
                collision_objects -> at(k) -> collide(*pCurr);
            }
        }
    }

  // TODO (Part 2): Constrain the changes to be such that the spring does not change
  // in length more than 10% per timestep [Provot 1995].
    for (int s = 0; s < springs.size(); s++) {
        //skip over spring if that spring's constraint type is currently
        //disabled
        //get current spring
        Spring sCurr = springs[s];
        //get point masses of the spring
        PointMass *pA = sCurr.pm_a;
        PointMass *pB = sCurr.pm_b;

        //spring rest length
        //double spRL = sCurr.rest_length;
        double spRL = sCurr.rest_length * 1.1;
        double scalarDist = (pA->position - pB->position).norm();
        if (spRL < scalarDist) {
            Vector3D unitVector = (pA -> position - pB -> position);
            unitVector.normalize();
            double magnitude = scalarDist - spRL;
            
            //if both are pinned (do nothing)
            if (pA -> pinned && pB -> pinned) {
                continue;
            } else if (pA -> pinned && !(pB -> pinned)) {
                //apply all of the correction to pA
                Vector3D directVector = magnitude * unitVector;
                pB -> position += spRL * directVector;
            } else if (!(pA -> pinned) && pB -> pinned) {
                //            //apply all of the correction to pB
                Vector3D directVector = magnitude * unitVector;
                pA -> position -= spRL * directVector;
            } else {
                //neither are pinned
                double adjust = magnitude/2.0;
                Vector3D directVector = adjust * unitVector;
                pA -> position -= spRL * directVector;
                pB -> position += spRL * directVector;
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
    //loop over all point masses
    //use hash_position to populate the map
    for (PointMass &pCurr: point_masses) {
        //pass position to hash_position
        float mapKey = hash_position(pCurr.position);
        
        if (map[mapKey] == NULL) {
            //if map doesn't exist
            map[mapKey] = new vector<PointMass *>();
            map[mapKey]->push_back(&pCurr);
        } else {
            //else:
            //add to map
            map[mapKey]->push_back(&pCurr);
        }
    }
}

void Cloth::self_collide(PointMass &pm, double simulation_steps) {
  // TODO (Part 4): Handle self-collision for a given point mass.
    //use hash table to find the potential collisions
    float hashKey = hash_position(pm.position);
    vector <PointMass *> *pmVector = map[hashKey];
    Vector3D correctionTotal = Vector3D(0.0, 0.0, 0.0);
    int count = 0;
    
    //if there are no other point masses
    if (pmVector->size() <= 1) {
        return;
    }
    //for each pair between the point mass and a candidate point mass
    //determine whether they are within 2 * thickness distance apart
    for (PointMass *pCurr: *map[hashKey]) {
        //DON'T COLLIDE A POINT MASS WITH ITSELF
        if (pCurr != &pm) {
            Vector3D distanceBtwn = (pCurr->position - pm.position);
            double dist = distanceBtwn.norm();
            
            if (dist < (2.0 * thickness)) {
                //if so, compute a correction vector that can be applied to the pm
                //such that the pair would be 2*thickness distance apart
                
                //normalize distance btween
//                distanceBtwn.normalize();
                
                //tangent point is the distance it should be at * current distance +
                //pm position
                double distAdjust = (2.0 * thickness) - dist;
                Vector3D correctionVector = pm.position - pCurr -> position;
                correctionVector.normalize();
                correctionVector *= distAdjust;
                correctionTotal += correctionVector;
                count += 1;
            }
        }
    }
    //final correction vector to pm's position is the average of all of these pairwise
    //correction vectors, scaled down by simulation_steps
    if (count > 0) {
        pm.position += (correctionTotal/(double)count)/simulation_steps;
    }
}

float Cloth::hash_position(Vector3D pos) {
  // TODO (Part 4): Hash a 3D position into a unique float identifier that represents membership in some 3D box volume.
    //partition the 3D space into 3D boxes with dimensions w * h * t
    //w = 3 * width/num_width_points
    //h = 3 * height/num_height_points
    //t = max(w,h)
    double w = 3.0 * (width/num_width_points);
    double h = 3.0 * (height/num_height_points);
    double t = max(w, h);
    
    //take the given position and truncate is coordinates to the closest 3D box (modulo)
    Vector3D truncatedPos = Vector3D(floor(pos.x/w), floor(pos.y/h), floor(pos.z/t));
    
    //float for weights
    float primeVal = 5.0;
    
    //compute a unique number from those updated coordinates and return it
    float hashKey = (float)(pow(primeVal, 1.0) * truncatedPos.x + pow(primeVal, 2.0) *truncatedPos.y + pow(primeVal, 3.0) * truncatedPos.z);
    
  return hashKey;
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
