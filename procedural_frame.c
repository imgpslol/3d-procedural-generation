#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define LINES_PER_FRAME 20  // Number of random lines per frame
#define DURATION_SECONDS 30  // Run for 30 seconds

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create window and renderer
    SDL_Window *window = SDL_CreateWindow("Procedural Frame (30s)", 
                                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                         WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Seed random number generator
    srand(time(NULL));

    // Start timing
    clock_t start_time = clock();
    int running = 1;

    // Main loop
    while (running) {
        // Check if 30 seconds have elapsed
        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
        if (elapsed_time >= DURATION_SECONDS) {
            running = 0;
            break;
        }

        // Handle events (e.g., close window)
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                break;
            }
        }

        // Clear screen (black background)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw random white lines
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White lines
        for (int i = 0; i < LINES_PER_FRAME; i++) {
            int x1 = rand() % WINDOW_WIDTH;
            int y1 = rand() % WINDOW_HEIGHT;
            int x2 = rand() % WINDOW_WIDTH;
            int y2 = rand() % WINDOW_HEIGHT;
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }

        // Update screen
        SDL_RenderPresent(renderer);

        // Control frame rate (e.g., 60 FPS)
        SDL_Delay(16);  // ~60 FPS (1000ms / 60 ≈ 16ms per frame)
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}