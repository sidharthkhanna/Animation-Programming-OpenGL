/*
NOTE: This is the file you will need to begin working with
You will need to implement the RayTrace::CalculatePixel () function

This file defines the following:
RayTrace Class
*/

#ifndef RAYTRACE_H
#define RAYTRACE_H

#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"

/*
RayTrace Class - The class containing the function you will need to implement

This is the class with the function you need to implement
*/
float x=2.0;
float z=6.0;
float z2=-7;
float angle=0.0;
float x2=-1.0;
float f=0.3;
int light1=1;
int light2=0;

// function for sphere intersection
float sphereintersection(SceneSphere* sphere,Vector point,Vector raydir)
{   float t;
float a=raydir.Dot(raydir);
float b=((point-sphere->center).Dot(raydir))*2;
float d=(point.Dot(point)-((sphere->center).Dot(point)*(2))+(sphere->center).Dot(sphere->center))-(sphere->radius)*(sphere->radius);
float f=(b*b)-(d*a*4);


if(f<0)
{   
	t=-1;
}


else if(f>0)
{  
	t=(-b-sqrt(f))/(2*a);
	if(t<0)
		t=(-b+sqrt(f))/(2*a);
}
else if(f==0)
	t=-b/(2*a);

return t;


}
// function for triangle intersection
float triangleintersection(Vector v1,Vector v2,Vector v3,Vector pointorigin,Vector raydir)
{   
	float epsilon1 =0.000001;
	float inv_det;
	float det;
	float u;
	float t;
	Vector Q;
	Vector T;
	Vector e1=v2-v1;
	Vector e2=v3-v1;
	float v;

	Vector p=raydir.Cross(e2);
	det=e1.Dot(p);
	if(det>-epsilon1  && det<epsilon1)
		return 0;
	inv_det=1.f/det;
	T=pointorigin-v1;
	u=T.Dot(p)*inv_det;

	if(u<0.f||u>1.f)
		return 0;
	Q=T.Cross(e1);
	v=raydir.Dot(Q)*inv_det;
	if(v<0.f|| u+v > 1.f)
		return 0;
	t=e2.Dot(Q)*inv_det;
	if(t>epsilon1)
		return t;
	else
		return -1;


}


class RayTrace
{
public:
	/* - Scene Variable for the Scene Definition - */

	Scene m_Scene;
	Camera m_Camera;
	SceneLight m_light;
	SceneBackground m_background;
	SceneMaterial m_material;


	// -- Constructors & Destructors --
	RayTrace (void) {


	}
	~RayTrace (void) {}
	// trace function used for raytracing , recursive reflection
	Vector trace(Vector obj_position,Vector raydirection,int depth)
	{
		if(depth>5)
		{
			return Vector(0,0,0);
		}
	
		else
		{
		int flag=1;
		Vector pointray;

		Vector normal;
		float t=m_Camera.farClip;
		// getting number of objects
		for(int i=0;i<m_Scene.GetNumObjects();i++)
		{  
			
		    SceneObject *sceneObj =m_Scene.GetObjectA(i);
		    //check if there is an intersection
		   if(sceneObj->IsSphere()){
				SceneSphere* abc=(SceneSphere*) sceneObj;
                float t1=sphereintersection(abc,obj_position,raydirection);
			    if(t>t1 && t1>0)
                {
				  t=t1;
				
			      pointray=obj_position+raydirection*t;
			      normal=(pointray-(abc->center)).Normalize();
                  m_material=m_Scene.GetMaterial(abc->material);	
				}
			}
			//check if there is an intersection
		    if(sceneObj->IsTriangle())
		    {
			       SceneTriangle* abc=(SceneTriangle*) sceneObj;
			       Vector v1=Vector(abc->vertex[0].x*abc->scale.x,abc->vertex[0].y*abc->scale.y,abc->vertex[0].z*abc->scale.z);
			       Vector v2=Vector(abc->vertex[1].x*abc->scale.x,abc->vertex[1].y*abc->scale.y,abc->vertex[1].z*abc->scale.z);
			       Vector v3=Vector(abc->vertex[2].x*abc->scale.x,abc->vertex[2].y*abc->scale.y,abc->vertex[2].z*abc->scale.z);
                   float t1=triangleintersection(v1,v2,v3,obj_position,raydirection);
				
                   if(t>t1 && t1>0)
			       {      
				     t=t1;
					
			 
			    pointray=obj_position+raydirection*t;
					 normal = ((v1-v2).Cross(v3-v2)).Normalize();
					 m_material=m_Scene.GetMaterial("Brass");
				   }
		   }
			//check if there is an intersection
		if(sceneObj->IsModel())
		{
			SceneModel* abc=(SceneModel*) sceneObj;
		

			int number=abc->GetNumTriangles();
			for(int i=0;i<number;i++)
			{
				SceneTriangle* triangle=abc->GetTriangle(i);
			glTexCoord2f(0,0);
				 Vector v1=Vector(triangle->vertex[0].x*abc->scale.x,triangle->vertex[0].y*abc->scale.y,triangle->vertex[0].z*abc->scale.z);
				 glTexCoord2f(1,0);
			       Vector v2=Vector(triangle->vertex[1].x*abc->scale.x,triangle->vertex[1].y*abc->scale.y,triangle->vertex[1].z*abc->scale.z);
				   glTexCoord2f(0,1);
			       Vector v3=Vector(triangle->vertex[2].x*abc->scale.x,triangle->vertex[2].y*abc->scale.y,triangle->vertex[2].z*abc->scale.z);
				
				  
				float t1=triangleintersection(v1,v2,v3,obj_position,raydirection);
				if(t>t1 && t1>0)
				{
					
					t=t1;
			   
					pointray=obj_position+raydirection*t;
				
				if(  pointray.y ==-10)
				{
					if(((int)(abs)(pointray.x) %2) < 1)
					{
						if(((int)(abs)(pointray.z) %2) < 1)

						return Vector(1,1,1);
						else

					
							return Vector(0,0,0);
					}
					else
                   {   if(((int)(abs)(pointray.z) %2) < 1)
						  return Vector(0,0,0);
					  else
						  return Vector(1,1,1);
					}
				}
				if(pointray.z==10)
				{
				if(((int)(abs)(pointray.x) %2) < 1)

						return Vector(0,0,1);
						else
		                return Vector(1,1,1);
				}
					normal = ((v1-v2).Cross(v3-v2)).Normalize();
					m_material=m_Scene.GetMaterial(triangle->material[0]);
					
				}
			}
			

		}
		}



		float epsilon=0.05;




		if(t>0 && t<m_Camera.farClip)

		{
			Vector color(0,0,0);		
			for(int i=0;i<m_Scene.GetNumLights();i++)// getting number of lights
			{  int flag=1;
	  	if(light2==1 && i==0)
			{
				i=1;
				
			}
			
			m_light=m_Scene.GetLight(i);

			Vector eye=(obj_position-pointray).Normalize();



			Vector lightdirection=(m_light.position-pointray).Normalize();
			float nl=normal.Dot(lightdirection);
			Vector r=((normal*(2*nl))-lightdirection).Normalize();

			for(int j=0;j<m_Scene.GetNumObjects();j++)
			{
				SceneObject *sceneObj =m_Scene.GetObjectA(j);
				//check for shadow
				if(sceneObj->IsSphere()){

					SceneSphere* abc=(SceneSphere*) sceneObj;


					float t2=sphereintersection(abc,pointray+lightdirection*epsilon,lightdirection);

					if(t2>0 )
					{
						
						flag=0;
						break;
					}


				}
				//check for shadow
				if(sceneObj->IsTriangle()){

					SceneTriangle* abc=(SceneTriangle*) sceneObj;
					Vector v1=Vector(abc->vertex[0].x*abc->scale.x,abc->vertex[0].y*abc->scale.y,abc->vertex[0].z*abc->scale.z);
					Vector v2=Vector(abc->vertex[1].x*abc->scale.x,abc->vertex[1].y*abc->scale.y,abc->vertex[1].z*abc->scale.z);
					Vector v3=Vector(abc->vertex[2].x*abc->scale.x,abc->vertex[2].y*abc->scale.y,abc->vertex[2].z*abc->scale.z);

					float t3=triangleintersection(v1,v2,v3,pointray+lightdirection*epsilon,lightdirection);

					if(t3>0 )
					{
						
						flag=0;
						break;
					}



				}
				    
			}
		       
			if(light1==1 && i==0) // if scene 1 is used 1 light at top of spheres

		{	
			
			    Vector color2=m_light.color*(m_background.ambientLight) +
				(m_light.color*m_material.diffuse)*(max(nl,0.0))*(flag)+
				((m_light.color*m_material.specular)*pow(max(r.Dot(eye),0.0),0.3*m_material.shininess))*(flag);
				if(m_material.reflective.Magnitude() > 0 )
				{
				color2 = color2 + trace(pointray+r*epsilon,r,depth+1)*m_material.reflective;
				}
	
		        color=color2;
				

			}
		
				if(light2==1 && (i==1 || i==2))// if 2 lights are used at front corner

		{	
			
			    Vector color2=m_light.color*(m_background.ambientLight) +
				(m_light.color*m_material.diffuse)*(max(nl,0.0))*(flag)+
				((m_light.color*m_material.specular)*pow(max(r.Dot(eye),0.0),0.3*m_material.shininess))*(flag);
				if(m_material.reflective.Magnitude() > 0)
				{
				color2 = color2 + trace(pointray+r*epsilon,r,depth+1)*m_material.reflective;// recursive reflection 
				}
		        color= color + color2;
			

			}
			

			
			
		
			



			}
	
			return color;
		}
		
		}
	}

	// -- Main Functions --
	// - CalculatePixel - Returns the Computed Pixel for that screen coordinate
	Vector CalculatePixel (int screenX, int screenY)
	{
		/*

		-- How to Implement a Ray Tracer --

		This computed pixel will take into account the camera and the scene
		and return a Vector of <Red, Green, Blue>, each component ranging from 0.0 to 1.0

		In order to start working on computing the color of this pixel,
		you will need to cast a ray from your current camera position
		to the image-plane at the given screenX and screenY
		coordinates and figure out how/where this ray intersects with 
		the objects in the scene descriptor.
		The Scene Class exposes all of the scene's variables for you 
		through its functions such as m_Scene.GetBackground (), m_Scene.GetNumLights (), 
		etc. so you will need to use those to learn about the World.

		To determine if your ray intersects with an object in the scene, 
		you must calculate where your objects are in 3D-space [using 
		the object's scale, rotation, and position is extra credit]
		and mathematically solving for an intersection point corresponding to that object.

		For example, for each of the spheres in the scene, you can use 
		the equation of a sphere/ellipsoid to determine whether or not 
		your ray from the camera's position to the screen-pixel intersects 
		with the object, then from the incident angle to the normal at 
		the contact, you can determine the reflected ray, and recursively 
		repeat this process capped by a number of iterations (e.g. 10).

		Using the lighting equation to calculate the color at every 
		intersection point and adding its fractional amount (determined by the material)
		will get you a final color that returns to the eye at this point.
		*/

		if ((screenX < 0 || screenX > WINDOW_WIDTH - 1) ||
			(screenY < 0 || screenY > WINDOW_HEIGHT - 1))
		{
			// Off the screen, return black
			return Vector (0.0f, 0.0f, 0.0f);
		}

	



		//Construct the Ray
		//1st is given our pixel coordinate(x,y)we need to get the model coordinate so we need to convert from screen space to camera space
		// Calculate H from the camera parameters(you can get those from m_scene creating your own camera variable) and calculate W
		//Now given H and W you need to calculate point on the screen in camera space and this gives us our ray direction
		//You will fill in math here that i wrote on the board(ray_origin,ray_direction)

		float h;
		Vector screen_pos;
		m_background=m_Scene.GetBackground();
		m_Camera=m_Scene.GetCamera();







		// detemining ray direction
		Vector Lookat=Vector(x2,0,z2);
		m_Camera.position=Vector(x,m_Camera.position.y,z);
		h=2*tan(m_Camera.fieldOfView/2)*m_Camera.nearClip;
		float w=h*((float)WINDOW_WIDTH /WINDOW_HEIGHT);
		screen_pos=m_Camera.position+ Lookat.Normalize()*(m_Camera.nearClip) + m_Camera.up*(h*(-0.5+((float)screenY/240)))
			+ Lookat.Cross(m_Camera.up).Normalize()*w*(((float)screenX/320)-0.5);
		Vector raydirection=(screen_pos-m_Camera.position).Normalize();
		// glulookat for navigation in starter.cpp
		gluLookAt (x, m_Camera.position.y, z,
			x+x2, m_Camera.target.y, z+z2,
			m_Camera.up.x, m_Camera.up.y, m_Camera.up.z);

		

		return trace(m_Camera.position,raydirection,1);// calling the trace function with initial depth 1
		
		//Until the function implemented is white
		return Vector (1.0f, 1.0f, 1.0f);
	}
};

#endif // RAYTRACE_H
