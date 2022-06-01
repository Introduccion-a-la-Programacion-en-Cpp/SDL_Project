// SDL_Project.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"

using namespace std;

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    string filePath = "assets/img/logo.png";
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());

    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = WIDTH;
    dest.h = HEIGHT;
   
    SDL_bool done = SDL_FALSE;
    string fontfilePath = "assets/fonts/arial.ttf";
    TTF_Init();
    TTF_Font* Sans = TTF_OpenFont(fontfilePath.c_str(), 24); //this opens a font style and sets a size
   
    SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Project ready...", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.w = WIDTH * 0.85; // controls the width of the rect
    Message_rect.h = HEIGHT * 0.20; // controls the height of the rect
    Message_rect.x = (WIDTH >> 1) - (Message_rect.w >> 1);  //controls the rect's x coordinate 
    Message_rect.y = HEIGHT >> 1; // controls the rect's y coordinte
   

    while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &dest);

        //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

        //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

        SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
        }
    }

    //Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return 0;
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
