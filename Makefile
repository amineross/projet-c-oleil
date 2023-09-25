build:
	gcc ./source_code/vue_controller/test.c -Wall -std=c99 -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -lSDL2_gfx -o game

run:
	./game 

clean:
	rm game 
