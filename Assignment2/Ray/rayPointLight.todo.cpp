#include <math.h>
#include <GL/glut.h>
#include "rayPointLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayPointLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D normal = iInfo.normal;
	Point3D materialDiffuse = iInfo.material->diffuse;
	Point3D unitLightDir = (this->location-iInfo.iCoordinate).unit();
	Point3D unitNormalDir = normal.unit();

	double distance = (this->location-iInfo.iCoordinate).length();
	double attenuation = (this->constAtten + (this->linearAtten*distance) + (this->quadAtten*pow(distance,2.0)));
	double dotProd = unitNormalDir.dot(unitLightDir);

	double redLight = this->color[0];
	double greenLight = this->color[1];
	double blueLight = this->color[2];

	double r = materialDiffuse[0] * (redLight / attenuation) * dotProd;
	double g = materialDiffuse[1] * (greenLight / attenuation) * dotProd;
	double b = materialDiffuse[2] * (blueLight / attenuation) * dotProd;

	return Point3D(r,g,b).scale(dotProd);
}
Point3D RayPointLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D normal = iInfo.normal;
	Point3D unitLightDir = (this->location-iInfo.iCoordinate).unit();
	Point3D unitNormalDir = normal.unit();

	double distance = (this->location-iInfo.iCoordinate).length();
	double attenuation = (this->constAtten + (this->linearAtten*distance) + (this->quadAtten*pow(distance,2.0)));
	double n = iInfo.material->specularFallOff;
	
	Point3D unitCamDir = (iInfo.iCoordinate-cameraPosition).unit();
	//R = -L + 2(N dot L) N
	Point3D unitReflectedDir = (unitLightDir - (unitNormalDir).scale(2* (unitLightDir.dot(unitNormalDir)))).unit();
	double dotProd = unitCamDir.dot(unitReflectedDir);
//	Point3D materialSpecular = iInfo.material->specular;
	Point3D materialSpecular = (dotProd<0) ? Point3D(0,0,0) :  iInfo.material->specular;

	double redLight = this->color[0];
	double greenLight = this->color[1];
	double blueLight = this->color[2];

	double r = materialSpecular[0] * (redLight / attenuation) * (pow(dotProd,n));
	double g = materialSpecular[1] * (greenLight / attenuation) * (pow(dotProd,n));
	double b = materialSpecular[2] * (blueLight / attenuation) * (pow(dotProd,n));
	
	return Point3D(r,g,b).scale(pow(dotProd,n));
}
int RayPointLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RayPointLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}


//////////////////
// OpenGL stuff //
//////////////////
void RayPointLight::drawOpenGL(int index){
}
