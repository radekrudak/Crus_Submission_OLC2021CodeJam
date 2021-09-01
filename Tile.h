#pragma once
class Tile
{
    int ID;
    int Base =0;
    int Resource  =0; // type of resource it is required to build/ is gathered after gathering
    int RQuantity =0; // quantity of resources gathered after gathering
    int ResourceRequirement =0; // required number of resources of type Resource (look second varable up) to build this tile
    bool isColide =false;
    bool isFloor = true;
    olc::Sprite *Sprite = nullptr;
    olc::Decal *Decal = nullptr;

    public:
    Tile(int id =0, olc::Sprite *spr = nullptr, bool c=false,int base = 0,int r=0, int rq=0,int rreq=0, bool floor = true)
    {
        ID = id;
        isColide =c;
        Base = base;
        Resource = r;
        RQuantity = rq;
        ResourceRequirement =rreq;
        isFloor = floor;
        if (spr)
        {
            Sprite = spr;
            Decal = new olc::Decal(Sprite);
        }

    }

    olc::Decal *GetDecal()
    {
     return Decal;
    }
    bool isColisive()
    {
        return isColide;
    }
    void LoadDecal()
    {
      if (Sprite)
            Decal = new olc::Decal(Sprite);
    }
    int GetBase()
    {
        return Base;
    }
    int GetResource()
    {
        return Resource;
    }
    int GetRQuantity()
    {
        return RQuantity;
    }
    bool GetIsFloor()
    {
        return isFloor;
    }
    int GetResourceRequirement()
    {
        return ResourceRequirement;
    }
};

