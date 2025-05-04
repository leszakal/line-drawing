#include "render.h"
#include <SDL3/SDL.h>

// Handles window creation, rendering, and render/window destruction
void createWindowAndRender(std::vector<Point> &bresenham_points, std::vector<Point> &wu_points) {
	bool loopShouldStop = false;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << SDL_GetError();
		return;
	}

	// Create window and renderer
	SDL_Window* window = SDL_CreateWindow("Line Algorithms", 1200, 900, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	// Lower resolution to see pixels, but keep window size the same
	// https://wiki.libsdl.org/SDL3/SDL_SetRenderLogicalPresentation
	// Comment this out to see full resolution and size
	SDL_SetRenderLogicalPresentation(renderer, 300, 225, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	// Continue rendering until window closed
	while (!loopShouldStop)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_QUIT:
				loopShouldStop = true;
				break;
			}
		}

		// Set backgroundNum color
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// For alpha blending: https://wiki.libsdl.org/SDL3/SDL_SetRenderDrawBlendMode
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		// Plot each point
		for (Point point : bresenham_points) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderPoint(renderer, point.x, point.y);
		}

		for (Point point : wu_points) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, point.gradient * 255);
			SDL_RenderPoint(renderer, point.x, point.y);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}