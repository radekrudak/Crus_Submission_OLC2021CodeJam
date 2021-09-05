#pragma once
static const int MapSize = 1024;


struct sNode
{
bool bVisited = false;
float fGlobalGoal  ;
float fLocalGoal ;
int x;
int y;

std::vector<sNode*> vNeighbours;
sNode *parent;

};

class Enemy
{   public:
    sNode *sNodeMap = nullptr;
    float x;
    float y;
    olc::Sprite *Sprite=nullptr;
    olc::Decal *Decal=nullptr;
    public:
     Enemy(float xx,float yy,olc::Sprite *sp)
    {
            x=xx;
            y=yy;
            Sprite=sp;
            Decal = new olc::Decal(sp);
    }

    olc::vf2d Move(float fPX,float fPY,float fElapsedTime)
    {
        x+= (fPX-x) *fElapsedTime;
        y+= (fPY-y)*fElapsedTime;
        return olc::vf2d(x,y);
    }
    olc::vf2d GetPosition()
    {
        return olc::vf2d (x,y);

    }
};
