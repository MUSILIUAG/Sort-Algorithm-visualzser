#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <random>
#include <ranges>
#include <algorithm>
#include <vector>
#include <assert.h>
#undef main



void draw_state(std::vector<int>& v, SDL_Renderer* renderer, unsigned int red, unsigned int blue)
{
    unsigned int index = 0;
    for (int i : v)
    {
        if (index == red)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (index == blue)
            SDL_SetRenderDrawColor(renderer, 0,0,255,255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderDrawLine(renderer,index,99,index,i);
        ++index;
    }
}

void render_lines(std::vector<int>& v, SDL_Renderer* renderer, int i, int j,int n)
{
    //clear screen
    //
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 0);
    SDL_RenderClear(renderer);

    //Draw state of the sort 
    //
    draw_state(v, renderer, i, j);
    //show to the window
    //
    SDL_RenderPresent(renderer);
    SDL_Delay(n);
}


int main()
{
   
    int decision;
    std::cout << "What sorting algoithhm would you like?" << "\n" << "Type 1 for bubble sort or 2 for selection sort: ";
    std::cin >> decision;

    std::random_device rd;
    std::uniform_int_distribution<int> d(1, 99);
    std::vector<int> v;

    // Populate the vector with random numbers
    //
    for (int i = 0; i < 100; i++)
    {
        v.push_back(d(rd));
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(100 * 5, 100 * 5, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 5, 5);





    // Bubble Sort algorithm
    //
    if (decision == 1)
    {
        for (unsigned int i = 0; i < v.size(); i++)
        {
            for (unsigned int j = i; j < v.size(); j++)
            {
                if (v[j] < v[i])
                {
                    std::swap(v[j], v[i]);
                }
                render_lines(v,renderer,i, j, 1);
            }
        }
    }
    // Selection Sort algorithm
    //
    if (decision == 2) {
        for (unsigned int i = 0; i < v.size() - 1; i++) {
            int minIndex = i;

            for (unsigned int j = i + 1; j < v.size(); j++) {
                if (v[j] < v[minIndex]) {
                    minIndex = j;
                    render_lines(v, renderer, i, minIndex, 100);
                }
            }
            std::swap(v[i], v[minIndex]);
            
        }
    }
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }
        }
    }

    // Clean up resources before exiting
    //
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;

};
