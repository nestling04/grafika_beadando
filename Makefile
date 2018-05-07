all:
	gcc -Iinclude/ src/callbacks.c src/camera.c src/init.c src/main.c src/scene.c src/utils.c -lSOIL -lobj -lopengl32 -lglu32 -lglut32 -lm -o SW_models.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/callbacks.c src/camera.c src/init.c src/main.c src/scene.c src/utils.c -lobj -lGL -lSOIL -lGLU -lglut -lm -o SW_models.exe -Wall -Wextra -Wpedantic
	
