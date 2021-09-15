// I was using jJavid9 A Star algorythm inplementation as reference.
#pragma once
struct sNode
{

bool bVisited = false;
float fGlobalGoal = INFINITY ;
float fLocalGoal=INFINITY;
bool Wall =false ;
int x;
int y;

std::vector<sNode*> vNeighbours;
sNode *parent = nullptr;

};

void FindPath(olc::vf2d Start, olc::vf2d End, std::vector<std::vector<sNode*>> &mapa)
{
    int Width = mapa.size();

    int Height = 0;
    for (auto &i: mapa)
    {
        if(i.size()<Height)
        {
            Height=i.size();
        }
    }



    sNode* StartNode =mapa[(int)Start.x][(int)Start.y];
    sNode* EndNode = mapa[(int)End.x][(int)End.y];
    while(mapa[(int)End.x][(int)End.y]->parent == nullptr)
    {



    }




}
