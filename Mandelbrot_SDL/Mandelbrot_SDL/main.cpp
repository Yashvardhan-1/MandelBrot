#include <SDL.h>
#include <Windows.h>
// #include <iostream>
// using namespace std;


int	WIDTH = 800;
int HEIGHT = 800;

long double min = -2.84;
long double max = 1.0;
long double factor = 1;
int MAX_ITERATIONS = 200;

long double map(long double value, long double in_min, long double in_max, long double out_min, long double out_max) {
	return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(1440, 900, 0, &window, &renderer);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

	int count = 0;

	while (true) {

		max -= 0.1 * factor;
		min += 0.15 * factor;
		factor *= 0.9349;
		MAX_ITERATIONS += 5;

		if (count > 30) {
			MAX_ITERATIONS *= 1.02;
		}

		SDL_RenderPresent(renderer);
		 
		long double a, b,ai, bi;
		int iterations;

		for (int x = 0; x < WIDTH; x++) {

			//if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
				//return 0;
			//}

			if ((GetKeyState('Q') <0 )) {
				return 0; 
			}

			for (int y = 0; y < HEIGHT; y++) {

				a = map(x, 0, WIDTH, min, max);
				b = map(y, 0, HEIGHT, min, max);

				ai = a;
				bi = b;

				iterations = 0;

				for (int i = 0; i < MAX_ITERATIONS; i++) {
					
					long double a1 = a * a - b * b;
					long double b1 = 2 * a * b;

					a = a1 + ai;
					b = b1 + bi;

					if ((a + b) > 2) {
						break;
					}

					iterations++;
				}
				
				int bright = map(iterations, 0, MAX_ITERATIONS, 0, 255);

				if ((iterations == MAX_ITERATIONS) || bright < 20) {
					bright = 0;
				}

				int red = map(bright*bright, 0, 255 * 255, 0, 255);
				int green = bright;
				int blue = map((sqrt(bright)), 0 , sqrt(255), 0, 255);

				SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
				SDL_RenderDrawPoint(renderer, x, y);

			}
		}
		count++;
	}

	return 0;
}