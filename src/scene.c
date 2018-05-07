#include "scene.h"
#include "init.h"
#include "camera.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include <obj/load.h>
#include <obj/draw.h>

void draw_scene(const Scene* scene, const Camera* camera)
{	
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
	draw_skybox();
	draw_objects(scene, camera);
}

void draw_origin()
{	
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100000, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100000, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100000);

    glEnd();
	glDisable(GL_COLOR_MATERIAL);
}

void draw_skybox()
{
	int x=1000;
	int y=500;
	
	glEnable(GL_TEXTURE_2D);
	
    glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(-x, -y, -x);
	glColor3f(1, 0, 0);
	glTexCoord2f(0.0,1.0);
    glVertex3f(-x, y, -x);
	glColor3f(1, 1, 1);
	glTexCoord2f(1.0,1.0);
	glVertex3f(x, y, -x);
	glColor3f(1, 1, 1);
	glTexCoord2f(1.0,0.0);
	glVertex3f(x, -y, -x);
    glEnd();
	
    glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(-x, -y, -x);
	glColor3f(1, 0, 0);
	glTexCoord2f(0.0,1.0);
    glVertex3f(-x, y, -x);
	glColor3f(0, 1, 0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-x, y, x);
	glColor3f(0, 1, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-x, -y, x);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
    glTexCoord2f(0.0,0.0);
	glVertex3f(-x, y, x);
	glColor3f(0, 1, 0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-x, -y, x);
	glColor3f(0, 0, 1);
	glTexCoord2f(1.0,1.0);
	glVertex3f(x, -y, x);
	glColor3f(0, 0, 1);
	glTexCoord2f(1.0,0.0);
	glVertex3f(x, y, x);
    glEnd();
	
    glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
    glTexCoord2f(0.0,0.0);
	glVertex3f(x, -y, x);
	glColor3f(0, 0, 1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(x, y, x);
	glColor3f(1, 1, 1);
	glTexCoord2f(1.0,1.0);
	glVertex3f(x, y, -x);
	glColor3f(1, 1, 1);
	glTexCoord2f(1.0,0.0);
	glVertex3f(x, -y, -x);
    glEnd();
	
    glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	glBegin(GL_QUADS);
	//bottom
	glColor3f(1, 1, 1);
    glTexCoord2f(0.0,0.0);
	glVertex3f(x, -y, -x);
	glColor3f(0, 0, 1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(x, -y, x);
	glColor3f(0, 1, 0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-x, -y, x);
	glColor3f(1, 0, 0);
	glTexCoord2f(1.0,0.0);
    glVertex3f(-x, -y, -x);
    glEnd();
	
    glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	glBegin(GL_QUADS);
	//top
	glColor3f(1, 1, 1);
    glTexCoord2f(0.0,0.0);
	glVertex3f(x, y, -x);
	glColor3f(0, 0, 1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(x, y, x);
	glColor3f(0, 1, 0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-x, y, x);
	glColor3f(1, 0, 0);
	glTexCoord2f(1.0,0.0);
    glVertex3f(-x, y, -x);
	
    glEnd();
}

void draw_objects(const Scene* scene, const Camera* camera)
{	
	//Millenium falcon
	glScalef(0.2,0.2,0.2);
	glTranslatef(xtps*5 + xtranslate, ytps*5 + ytranslate, ztps*5 + ztranslate);
	
	glTranslatef(-(xtps*5 + xtranslate), -(ytps*5 + ytranslate), -(ztps*5 + ztranslate));
	glRotatef(xrotate, 1.0, 0.0, 0.0);
	glRotatef(yrotate, 0.0, 1.0, 0.0);
	glTranslatef(xtps*5 + xtranslate, ytps*5 + ytranslate, ztps*5 + ztranslate);
	
    glBindTexture(GL_TEXTURE_2D, texture_names[1]);
	draw_model(&(scene->cube[0]));
	
	//X-wing
    glBindTexture(GL_TEXTURE_2D, texture_names[2]);
	draw_model(&(scene->cube[1]));
	
	//printf("x=%lf\n",camera->position.x);
	//printf("y=%lf\n",camera->position.y);
	//printf("z=%lf\n",camera->position.z);
}

void set_lighting()
{
    float ambient_light[] = { 0.1f, 0.1f, 0.1f, 0.0f };
    float diffuse_light[] = { 0.5f, 0.5f, 0.5f, 0.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    float position[] = { -1000.0f, -500.0f, -1000.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void set_obj_speed(float speed)
{
	//ztranslate += speed;
}