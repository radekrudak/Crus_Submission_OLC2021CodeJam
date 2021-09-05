#pragma once
#include "Tile.h"
void GenerateMap(std::array<std::array<char,1024>,1024> &mapa)
{
    for (auto &i:mapa)
    {
        for (auto &b:i)
        {
            if (rand()%10 > 3)
                b=0;
            else
                b=1;

        }

    }
    for (int y=500;y<524;y++)
        for(int x=500;x<524;x++)
        {
         mapa[x][y] = 0;
        }
}

