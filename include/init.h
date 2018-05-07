#ifndef INIT_H
#define INIT_H

#include "scene.h"

/**
 * Initialize the OpenGL context.
 */
void init_opengl();

void init_scene(Scene* scene);

void initialize_texture();

/**
 * Switch function for menu.
 */
void switchMenu(int value);

/**
 * Initialize the pop-up menu.
 */
void PopMenuCreate();

GLuint initialize_texture2(char* filename);

GLuint load_texture(char* filename, Pixel* image);

#endif /* INIT_H */

