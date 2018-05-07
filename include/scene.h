#ifndef SCENE_H
#define SCENE_H

#include <GL/glut.h>
#include <SOIL/SOIL.h>
#include "camera.h"

#include <SOIL/SOIL.h>
#include <obj/model.h>

typedef GLubyte Pixel[3];

Pixel* images[3];
GLuint texture_names[3];

typedef struct Scene
{
    Camera camera;
    Model cube[3];
    Material material;
} Scene;

float xtranslate, ytranslate, ztranslate, xtps, ytps, ztps, xrotate, yrotate;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene, const Camera* camera);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Load texture from file and returns with the texture name..
 */
GLuint load_texture(char* filename, Pixel* image);

void set_obj_speed(float speed);

#endif /* SCENE_H */
