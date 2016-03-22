#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySpotLight.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RaySpotLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	//computes the amount of diffuse light reaching the hit location and scales that using the material properties of the hit location. 
	Point3D normal = iInfo.normal;
	Point3D materialDiffuse = iInfo.material->diffuse;
	
	Point3D unitLightDir = (this->location-iInfo.iCoordinate).unit();
	Point3D unitNormalDir = normal.unit();

	double distance = (this->location-iInfo.iCoordinate).length();
	double dotProd = unitNormalDir.dot(unitLightDir);
	

	Point3D light = Point3D(0,0,0);
	Point3D L = (location-iInfo.iCoordinate).unit();	
//	if((L.dot(direction.unit()) / (L.length() * direction.length())) > cos(cutOffAngle) ){
	if (((this->direction.unit()).dot(L)) < cos(this->cutOffAngle)){
		double attenuation = (this->constAtten + (this->linearAtten*distance) + (this->quadAtten*pow(distance,2.0)));
		light = ((this->color * abs(pow(L.dot(direction.unit()),dropOffRate))) / attenuation);
	}
		
	double r = materialDiffuse[0] * light[0] * dotProd;
	double g = materialDiffuse[1] * light[1] * dotProd;
	double b = materialDiffuse[2] * light[2] * dotProd;


	return Point3D(r,g,b).scale(dotProd);

}
Point3D RaySpotLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	Point3D normal = iInfo.normal;
	Point3D unitCamDir = (iInfo.iCoordinate-cameraPosition).unit();
	Point3D unitNormalDir = iInfo.normal.unit();
	Point3D unitLightDir = (this->location-iInfo.iCoordinate).unit();
	//R = -L + 2(N dot L) N
	Point3D unitReflectedDir = (unitLightDir - (unitNormalDir).scale(2* (unitLightDir.dot(unitNormalDir)))).unit();
	double dotProd = unitCamDir.dot(unitReflectedDir);
	
	//Point3D materialSpecular = iInfo.material->specular;
	Point3D materialSpecular = (dotProd<0) ? Point3D(0,0,0) :  iInfo.material->specular;
	
	double distance = (this->location-iInfo.iCoordinate).length();
	double n = iInfo.material->specularFallOff;
	

	Point3D light = Point3D(0,0,0);
	Point3D L = (location-iInfo.iCoordinate).unit();	
//	if((L.dot(direction.unit()) / (L.length() * direction.length())) > cos(cutOffAngle) ){
	if (((this->direction.unit()).dot(L)) < cos(this->cutOffAngle)){
		double attenuation = (this->constAtten + (this->linearAtten*distance) + (this->quadAtten*pow(distance,2.0)));
		light = ((this->color * abs(pow(L.dot(direction.unit()),dropOffRate))) / attenuation);
	}
		
	double r = materialSpecular[0] * light[0] * (pow(dotProd, n));
	double g = materialSpecular[1] * light[1] * (pow(dotProd, n));
	double b = materialSpecular[2] * light[2] * (pow(dotProd, n));


	return Point3D(r,g,b).scale(pow(dotProd,n));
}
int RaySpotLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RaySpotLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RaySpotLight::drawOpenGL(int index){
}
