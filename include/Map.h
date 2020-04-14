#ifndef EXAM_MAP_H
#define EXAM_MAP_H

#include <SDL2/SDL.h>
#include <vector>
#include <map>

class Map {
public:
    Map(const std::string& filePath, int mapIndex);

    int currentMap[32][29];

    void loadMapFromFile(const char *filePath);

    void loadLevelMap(int map[32][29]);

private:
    void createWallWithTexture(int map[32][29], int row, int column);

    int tileLength = 30;


    SDL_Texture *fill;
    SDL_Texture *round;
    SDL_Texture *black;
    SDL_Texture *endN;
    SDL_Texture *endW;
    SDL_Texture *endS;
    SDL_Texture *endE;
    SDL_Texture *wallDoubleEdgeWE;
    SDL_Texture *wallDoubleEdgeNS;
    SDL_Texture *cornerSW;
    SDL_Texture *cornerNW;
    SDL_Texture *cornerNE;
    SDL_Texture *cornerSE;
    SDL_Texture *insideCornerNW;
    SDL_Texture *insideCornerNE;
    SDL_Texture *insideCornerSW;
    SDL_Texture *insideCornerSE;
    SDL_Texture *edgeS;
    SDL_Texture *edgeN;
    SDL_Texture *edgeE;
    SDL_Texture *edgeW;
    SDL_Texture *pellet;
    SDL_Texture *pelletLarge;
    SDL_Texture *fruit;

};


#endif
