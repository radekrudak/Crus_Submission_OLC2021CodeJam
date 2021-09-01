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
}

