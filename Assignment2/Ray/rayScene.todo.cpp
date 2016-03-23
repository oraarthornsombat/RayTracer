#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>


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

	double heightAngle = (camera->heightAngle);
	//fovx = fovy * aspect
	double widthAngle = (heightAngle * camera->aspectRatio);
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
	//extra stuff to make it 3D
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
	RayIntersectionInfo* iInfo = new RayIntersectionInfo();
	double intersection =this->group->intersect(ray,*iInfo,-1);
	Point3D diffuse = Point3D(0,0,0);
	Point3D specular= Point3D(0,0,0);
	Point3D i = Point3D(0,0,0);
	int isInShadow =0;
	
	if (intersection>=0){
	//	Point3D ambient = iInfo->material->ambient;
	//	Point3D emissive = iInfo->material->emissive;
	i += iInfo->material->emissive + iInfo->material->ambient * this->ambient;
	
		for (int l = 0; l < lightNum; l++){
			
			//diffuse stuff
			diffuse += this->lights[l]->getDiffuse(camera->position, *iInfo);
			
			//specular stuff
			specular += this->lights[l]->getSpecular(camera->position, *iInfo);
		
			//shadow stuff
			int isectCount = 0;
			for(int s = 0; s < this->group->sNum; s++) {
			
				isInShadow += this->lights[l]->isInShadow(*iInfo, this->group->shapes[s], isectCount);
				
			}

			Point3D shadow = Point3D(1,1,1);
			
			if (isectCount>0){
				shadow = Point3D(0,0,0);
			}
			
			
			i = i + (diffuse + specular) *shadow;
			 i[0] = (i[0]<0)? 0: i[0];
			 i[0] = (i[0]>1)? 1: i[0];
			 i[1] = (i[1]<0)? 0: i[1];
			 i[1] = (i[1]>1)? 1: i[1];
			 i[2] = (i[2]<0)? 0: i[2];
			 i[2] = (i[2]>1)? 1: i[2];
			
		} //end for lights
			
	} else {
		i= this->background;
	}

	return i;
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
