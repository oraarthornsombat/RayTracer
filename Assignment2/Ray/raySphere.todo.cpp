#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySphere.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	//If the ray hits the shape and either mx is less than zero or the intersection occurs
	//at a distance less than t along the ray the intersection information in iInfo is set 
	//and a value greater than 0 is returned. Otherwise, -1 is returned. 
	
	bool intersects = false;
 	//|P - O|^2 - r^2 = 0 
	double rsquare = pow(radius,2);

	//L = O - P0
	Point3D l = center - ray.position;
	
	//tca = L • V
	double tca = l.dot(ray.direction);
	
	//d^2 = L • L - tca^2
	double dsquare = l.dot(l) - (pow(tca,2));

	//Instersection with sphere? No.
	if (dsquare > rsquare){
		intersects=false;
		return -1;
	} else {
		//Else, intersects
		intersects=true;
		//thc = sqrt(r^2 - d^2)
		double thc = sqrt(rsquare - dsquare);
		double t1 = tca - thc;
		double t2 = tca + thc;

		double t = -1;
		//return first intersection point
		if (t1 > t2)
		{
			t = t2;
		}
		else
		{
			t = t1;
		}
	
	//Ray: P = P0 + tV
	Point3D p = ray.position + ray.direction*t;
	//||P-O||
	double magnitude = sqrt(pow(p.p[0] - center.p[0],2) + pow(p.p[1] - center.p[1],2) + pow(p.p[2] - center.p[2],2));

	//N = (P - O) / ||P - O||
	Point3D normal = (p - center) / magnitude;
	
	if ((intersects && mx<0)){
		iInfo.iCoordinate = p;
		iInfo.normal = normal;
	}
	
	return t;
	}
}
BoundingBox3D RaySphere::setBoundingBox(void){
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RaySphere::drawOpenGL(int materialIndex){
	return -1;
}
