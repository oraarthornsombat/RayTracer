#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void){
}
double RayTriangle::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	
	Point3D t0 = this->v[0]->position;
	Point3D t1 = this->v[1]->position;
	Point3D t2 = this->v[2]->position;
	Point3D	line0 = t0-t1;
	Point3D line1 = t2-t1;
	Point3D normal = line0.crossProduct(line1);
	//N • (ray.position - a point on the plane)
	double d = normal.dot(ray.position- t0);
	//t = -(P0 • N + d) / (V • N)
	double t = -1*(ray.position.dot(normal)+d) / (ray.direction.dot(normal));
	
	// P = P0 + tV
	Point3D p = ray.position + ray.direction*t;
	
	
	Point3D v1 = t0 - ray.position;
	Point3D v2 = t1 - ray.position;
	Point3D triangleNormal = v2.crossProduct(v1).unit();
	v1 = t2 - ray.position;
	v2 = t0 - ray.position;
	Point3D triangleNormal1 = v2.crossProduct(v1).unit();
	v1 = t1 - ray.position;
	v2 = t2 - ray.position;
	Point3D triangleNormal2 = v2.crossProduct(v1).unit();
	if ((p - ray.position).dot(triangleNormal) < 0 || (p - ray.position).dot(triangleNormal1) < 0 || (p - ray.position).dot(triangleNormal2) < 0){
 		return -1;
	} else {
		iInfo.iCoordinate = p;
		iInfo.normal = normal;
		return t;
	}
	

}
BoundingBox3D RayTriangle::setBoundingBox(void){
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	return -1;
}
