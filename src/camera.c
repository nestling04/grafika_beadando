#include "camera.h"
#include "scene.h"

#include <GL/glut.h>

#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 0.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
}

void update_camera(Camera* camera, double time)
{
    double y_angle;
    double y_side_angle;
	//double linear_angle;
	
    y_angle = degree_to_radian(camera->rotation.y);
    y_side_angle = degree_to_radian(camera->rotation.y + 90.0);
	//linear_angle = degree_to_radian(camera->rotation.x);
	
    camera->position.z += cos(y_angle) * camera->speed.x * time;
	//ztranslate += cos(y_angle) * camera->speed.x * time;
    camera->position.x += sin(y_angle) * camera->speed.x * time;
	//xtranslate += sin(y_angle) * camera->speed.x * time;
    camera->position.z += cos(y_side_angle) * camera->speed.z * time;
	//ztranslate += cos(y_side_angle) * camera->speed.z * time;
    camera->position.x += sin(y_side_angle) * camera->speed.z * time;
	//xtranslate += sin(y_side_angle) * camera->speed.z * time;
	
	camera->position.y += camera->speed.y * time;
	//ytranslate += camera->speed.y * time;
	
	//Collison avoidance
	if((camera->position.x)<-999)
	{
		camera->position.x=-999;
	}
	else if((camera->position.x)>999)
	{
		camera->position.x=999;
	}
	
	if((camera->position.y)<-499)
	{
		camera->position.y=-499;
	}
	else if((camera->position.y)>499)
	{
		camera->position.y=499;
	}
	
	if((camera->position.z)<-999)
	{
		camera->position.z=-999;
	}
	else if((camera->position.z)>999)
	{
		camera->position.z=999;
	}
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x), 1.0, 0, 0);
    glRotatef(-(camera->rotation.y), 0, 1.0, 0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
	
	xtps = camera->position.x;
	ytps = camera->position.y;
	ztps = camera->position.z;
	
	xrotate = camera->rotation.x;
	yrotate = camera->rotation.y;
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.y += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.y < 0) {
        camera->rotation.y += 360.0;
    }

    if (camera->rotation.y > 360.0) {
        camera->rotation.y -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}

void set_camera_vertical_speed(Camera* camera, double speed)
{
	camera->speed.y = speed;
}