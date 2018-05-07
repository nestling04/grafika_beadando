#include "init.h"
#include "scene.h"
#include "callbacks.h"

#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
	
    glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);//maybe wrong!

    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);/*
    glEnable(GL_TEXTURE_2D);//maybe wrong!
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);*/
	initialize_texture();
}

void init_scene(Scene* scene)
{	
	fullscreen = 0;

	xtranslate = 80.0;
	ytranslate = -50.0;
	ztranslate = 2000.0;
	
	xrotate = 0.0;
	yrotate = 0.0;
	
	xtps = 0.0;
	ytps = 0.0;
	ztps = 0.0;
	
    load_model(&(scene->cube[0]), "models/millenium-falcon.obj");
    print_bounding_box(&(scene->cube[0]));
	
	load_model(&(scene->cube[1]), "models/x-wing.obj");
    print_bounding_box(&(scene->cube[1]));
	
    glClearColor(0.1, 0.1, 0.1, 1.0);
    initialize_texture();
	
    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 0.0;
    scene->material.diffuse.green = 0.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 0.5;
}

void PopMenuCreate(Scene* scene)
{
	int sub1 = glutCreateMenu(switchMenu);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);	
	
	int sub2 = glutCreateMenu(switchMenu);
	glutAddMenuEntry("Horizontal movement: W,A,S,D", 3);
	glutAddMenuEntry("Vertical movement: Q,E", 4);
	glutAddMenuEntry("Camera rotation left-right: U,O", 5);
	glutAddMenuEntry("Camera rotation up-down: J,L", 6);
	glutAddMenuEntry("Exit application: ESC", 7);
	
	glutCreateMenu(switchMenu);
	glutAddSubMenu("Fullscreen mode on/off", sub1);
	glutAddSubMenu("Help", sub2);
	glutAddMenuEntry("Exit", 8);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void switchMenu(int value)
{
	switch(value)
	{
		case 1:
		{
			if(fullscreen == 0)
			{
				set_change(1);
				set_fullscreen_mode(1);
			}
			break;
		}
		case 2:
		{
			if(fullscreen == 1)
			{
				set_change(1);
				set_fullscreen_mode(0);
			}
			break;
		}
		case 8:
		{
			exit(0);
			break;
		}
	}
	glutPostRedisplay();
}

void initialize_texture()
{
    unsigned int i;
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    char texture_filenames[][32] = {"textures/space.jpg",
									"textures/falcon2.jpg",
									"textures/xwing.png"};
	for (i = 0; i < 3; ++i) {
        texture_names[i] = load_texture(texture_filenames[i], images[i]);
    }
/*
    int width;
    int height;
	
    unsigned char* image = SOIL_load_image(texture_filename, &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
            (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
*/
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	glEnable(GL_TEXTURE_2D);
}

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename, Pixel* image)
{
    GLuint texture_name;
    glGenTextures(1, &texture_name);

    int width;
    int height;

    image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return texture_name;
}