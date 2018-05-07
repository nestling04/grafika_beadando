#include "callbacks.h"
#include "scene.h"

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 70.0

int change = 0;

struct {
    int x;
    int y;
} mouse_position;

void display()
{
	if(change == 1)
	{
		glutDestroyWindow(window);
		if(fullscreen == 0)
		{
			window = glutCreateWindow("Meszaros Gergo DML5Q5");
		}
		else if(fullscreen == 1)
		{	
			window = glutEnterGameMode();
		}
		glutSetWindow(window);
		change = 0;
	}
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    set_view(&camera);
    draw_scene(&scene, &camera);

    glPopMatrix();
    glutSwapBuffers();
	glutPostRedisplay();
}

void set_fullscreen_mode(int decision)
{
	fullscreen = decision;
}

void set_change(int sense)
{
	change = sense;
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / (double)height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{	
	rotate_camera(&camera, (mouse_position.x - x) / 3, (mouse_position.y - y) / 3);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    float position;
	float camera_speed = 50;
	
    switch (key) {
	case 'w':
        set_camera_speed(&camera, -camera_speed);
		//set_obj_speed(-camera_speed);
        break;
    case 's':
        set_camera_speed(&camera, camera_speed);
		//set_obj_speed(camera_speed);
        break;
    case 'a':
        set_camera_side_speed(&camera, -camera_speed);
		//set_obj_side_speed(&camera, -camera_speed);
        break;
	case 'd':
        set_camera_side_speed(&camera, camera_speed);
		//set_obj_side_speed(&camera, camera_speed);
        break;
	case 'q':
		set_camera_vertical_speed(&camera, camera_speed);
		//set_obj_vertical_speed(&camera, camera_speed);
		break;
	case 'e':
		set_camera_vertical_speed(&camera, -camera_speed);
		//set_obj_vertical_speed(&camera, -camera_speed);
		break;
    
	case 'j':
		rotate_camera(&camera, 0.0, -1.0);
		break;
	case 'l':
		rotate_camera(&camera, 0.0, 1.0);
		break;
	case 'u':
		rotate_camera(&camera, 1.0, 0.0);
		break;
	case 'o':
		rotate_camera(&camera, -1.0, 0.0);
		break;
	case 27: // Escape key
      glutDestroyWindow(window);
      exit (0);
      break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    float position;

    switch (key) {
	case 'w':
		set_camera_speed(&camera, 0.0);
		//set_obj_speed(0.0);
		break;
    case 's':
        set_camera_speed(&camera, 0.0);
		//set_obj_speed(0.0);
        break;
    case 'a':
        set_camera_side_speed(&camera, 0.0);
        break;
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
	case 'q':
		set_camera_vertical_speed(&camera, 0.0);
		break;
	case 'e':
		set_camera_vertical_speed(&camera, 0.0);
		break;
	case 27: // Escape key
      glutDestroyWindow(window);
      exit (0);
      break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);

    glutPostRedisplay();
}