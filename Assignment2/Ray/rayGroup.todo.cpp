#include <stdlib.h>
#include <cfloat>
#include <GL/glut.h>
#include "rayGroup.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
	//Cast rays through scene-graph nodes. 
	//compute the intersection properties for the closest intersection within the list of RayShapes associated to the RayGroup.
	//(The number of shapes associated to the group is stored in RayShape::sNum and the list of shapes is stored in RayShape::shapes.)
	//This method should return return -1.0 if there is no intersection. 
	//Otherwise, it should return the (positive) distance to the intersection. 
	//If the value mx is bigger than zero, then only look for intersections whose distance is closer than mx from the beginning of the ray.
	int minI=-1;
	double minDist = DBL_MAX;
	for (int i=0; i<this->sNum; i++){
		RayShape** shapes = this->shapes;
		Point3D minPt = ray.position;
	
	//	double minDist = DBL_MAX;
		if (shapes[i]->intersect(ray,iInfo, mx)>=0){
			double tempDist = (iInfo.iCoordinate - ray.position).length();
			if (tempDist<minDist){
					minDist = tempDist;
					minI = i;
			}
			
			//nothing
		}
	}
	if (minI>-1){
//		shapes[minI]->intersect(ray,iInfo, mx);
		return minDist;
	} else {
		return -1;
	}
	
	
	//return -1;
}

BoundingBox3D RayGroup::setBoundingBox(void){
	return bBox;
}

int StaticRayGroup::set(void){
	return 1;
}
//////////////////
// OpenGL stuff //
//////////////////
int RayGroup::getOpenGLCallList(void){
	return 0;
}

int RayGroup::drawOpenGL(int materialIndex){
	return -1;
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
