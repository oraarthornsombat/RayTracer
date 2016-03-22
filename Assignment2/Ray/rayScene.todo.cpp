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
	Point3D i = Point3D(0,0,0);
	if (intersection>=0){
	//	Point3D ambient = iInfo->material->ambient;
	//	Point3D emissive = iInfo->material->emissive;
	i += iInfo->material->emissive + iInfo->material->ambient * this->ambient;
	
	//point+=iInfo.material->specular;
	//Point3D emissive = iInfo.material->emissive;
	//Reflected light direction	R = -L + 2(N ⋅ L)N
	//	Point3D r= ray.direction*-1 + iInfo->normal*2*(iInfo->normal.dot(ray.direction));
	//i=ie + ks(v dot r)^n*il
		for (int l = 0; l < lightNum; l++){
//		i += emissive + ambient*Ial);
			
			i += this->lights[l]->getDiffuse(camera->position, *iInfo);
			i += this->lights[l]->getSpecular(camera->position, *iInfo);
		}
	} else {
		i= this->background;
	}
	
/*	//first sample image
	if (intersection>=0){
		return Point3D(1,1,1);
	}
	return Point3D(0,0,0);*/
	return i;
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
