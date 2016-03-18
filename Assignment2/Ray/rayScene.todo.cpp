#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>


///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v,Point3D n){
	return Point3D();
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
	return 0;
}

Ray3D RayScene::GetRay(RayCamera* camera,int i,int j,int width,int height){
	
	//distance to view plane

	double heightAngle = camera->heightAngle;
	//fovx = fovy * aspect
	double widthAngle = heightAngle * camera->aspectRatio;
	double d = ((height / 2) / tan(heightAngle));
	
	Point3D p0 = camera->position;
	Point3D towards = camera->direction;
	Point3D r = camera->right;
	Point3D up = camera->up;
	
	Point3D left,right,bottom,top,p,u,v;
	Ray3D myRay;
	//p2 in slides
	top = p0 + (towards*d) + (up*d*tan(heightAngle));
	//p1 in slides
	bottom = p0 + (towards*d) - (up*d*tan(heightAngle));
	left = p0 + (towards*d) - (r*d*tan(widthAngle));
	right = p0 + (towards*d) + (r*d*tan(widthAngle));

	u = left + (right-left)*((i + 0.5)/width); 
	v = bottom + (top-bottom)*((j + 0.5)/height); 

	p = u + v;

	myRay.position = p0;
	myRay.direction = p.unit();

	return myRay;
}

Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit){
	return Point3D();
	
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
