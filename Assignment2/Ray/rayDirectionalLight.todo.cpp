#include <math.h>
#include <GL/glut.h>
#include "rayDirectionalLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayDirectionalLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	
	Point3D normal = iInfo.normal;
	Point3D materialDiffuse = iInfo.material->diffuse;
	double dotProd = normal.unit().dot(direction.unit()*-1);
	
	//implements RayLight (public attribute color)
	double redLight = this->color[0];
	double greenLight = this->color[1];
	double blueLight = this->color[2];

	double r = materialDiffuse[0] * redLight * dotProd;
	double g = materialDiffuse[1] * greenLight * dotProd;
	double b = materialDiffuse[2] * blueLight * dotProd;


	return Point3D(r,g,b).scale(dotProd);
}
Point3D RayDirectionalLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D normal = iInfo.normal;
	Point3D unitCamDir = (iInfo.iCoordinate-cameraPosition).unit();
	Point3D unitLightDir = this->direction.unit();
	Point3D unitNormalDir = iInfo.normal.unit();
	//R = -L + 2(N dot L) N
	Point3D unitReflectedDir = (unitLightDir - (unitNormalDir).scale(2* (unitLightDir.dot(unitNormalDir)))).unit();
	double dotProd = unitCamDir.dot(unitReflectedDir);
	Point3D materialSpecular = iInfo.material->specular;
//	Point3D materialSpecular = (dotProd<0) ? Point3D(0,0,0) :  iInfo.material->specular;
	
	double redLight = this->color[0];
	double greenLight = this->color[1];
	double blueLight = this->color[2];

	double n = iInfo.material->specularFallOff;

	double r = materialSpecular[0] * redLight * (pow(dotProd, n));
	double g = materialSpecular[1] * greenLight * (pow(dotProd, n));
	double b = materialSpecular[2] * blueLight * (pow(dotProd, n));
	
	return Point3D(r,g,b).scale(pow(dotProd,n));
	
}
int RayDirectionalLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RayDirectionalLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RayDirectionalLight::drawOpenGL(int index){
}
