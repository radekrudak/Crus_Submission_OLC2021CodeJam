#pragma once
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define MENU 0
//#define DIRT 0
//#define FLOOR 1
//#define WALL 2
//#define ROOF 3


#include "MapGen.h"
#include "Tile.h"
#include "Bullet.h"
#include  "Enemy.h"
#include "Item.h"
#include "FindPath.h"


// to do:
// Enemies
// shooting
// health
// Hud:
// HP
// Resourses
// ammo ?
// tile selected to build

using TZpos = PositionOnTileStack;

constexpr int TileSize =16;
constexpr float PI = 3.14159;
class GameJam : public olc::PixelGameEngine
{


     int MapSize = 1024;


    double fTileScale =1.0f;
    float fTest;
    friend Enemy;
/// BOOLS
    bool isEnd = false;
    bool isStatsDis = false;
    bool isFightMode = false;
    bool isNight = false;
    bool isNightStartSequence = false;
/// players Stuff
    float fCameraX;
    float fCameraY;
    float fPlayerX =123.5f;
    float fPlayerY =128.5f;
    float fPlayerA =0.0f;
    float fDestruction =1.0f;
    float fConstruction = 0.0f;
    float fMouseMapX =0.0f;
    float fMouseMapY = 0.0f;
    float fReachDistance =2;
    double Health =1 ;
    std::string MouseText;
// Game Clocks stuff;
    double fSeconds;
    int PreviousSecond=0;
    double fSecondsInDay=20.;

///////////////////////////////////////////// /VIASUAL EVECTS
    float fModeTextFading = 1.0f; // used in left top  mode displaying text fading effect
    int ModeTextLap = 50; // used in left top  mode displaying text fading effect
/////////////////////






////////////////////// layers
    int lGround;
    int lPlayer;
    int lNight;
//////////////////////////// Sprites
    olc::Sprite *sGrass =nullptr;
    olc::Sprite *sWood =nullptr;
    olc::Sprite *sMT =nullptr;
    olc::Sprite *sTest=nullptr;
    olc::Sprite *sMC=nullptr;
    olc::Sprite *sWoodWall=nullptr;
    olc::Sprite *sWoodFloor=nullptr;
    olc::Sprite *sEnemy=nullptr;
    olc::Sprite *sNight = nullptr;
    olc::Sprite *sMoonAndSun = nullptr;
    olc::Sprite *sPGELogo = nullptr;

    olc::Decal *dTest = nullptr;
    olc::Decal *dPGELogo = nullptr;
    olc::Decal  *dWood = nullptr;
    olc::Decal *dMoonAndSun = nullptr;
    olc::Decal *dNight = nullptr;
    olc::Decal *dMC=nullptr;
    Tile *Tilemapp;

/////////////////////////////////////////////////// ARRAYS
    std::vector<std::vector< std::vector<Tile *> > > vTileMap;

// body is at the ned of this file, this fun. goes trough vector and chechs if one of the tile is colisive if yes returnes true other wise false
    bool isColisivTileInIt( std::vector<Tile *> vTiless);


// when replacing vTiles array size replace in Enemy.h too.
    std::vector<Tile*> vTiles ; // 0= Grass, 1 = Wood etc.
    std::vector<Tile*> vBuildableTiles;
    int ChosenBuildTile = 2;
    std::vector<Item*> vItems;
    std::vector<ItemSlot*> vInventory;

//std::vector<int> aResourses= {0,0,0};
    std::vector<Bullet*> vBullets;
    std::vector<Enemy*> vEnemies;
// Node map for A* path finding
    std::vector<std::vector<sNode*>> vNodeMap;


    float AStarCounterMax=0.5f;
    float AStarCounter =AStarCounterMax;
public:
    GameJam()
    {
        // Name your application
        sAppName = "GameJamEntry";

    }
    float Distance(float x1, float y1,float x2,float y2)
    {
        return sqrtf((x1 -x2)*(x1 -x2)+(y1 -y2)*(y1 -y2));
    }
    void FindPath(olc::vi2d  StartPoint, olc::vi2d EndPoint)
    {
        ;//   #include"FindPath.h"
    }
    void SpawnEnemy()
    {
        ;
    }
    bool IsEnoughItems(Item* SearchedItem,int Quant)
    {

        for(auto &i: vInventory)
        {
            if(i->ItemPtr== SearchedItem&& Quant<= i->Quantity)
            {
                return true;
            }
        }
        return false;
    }
    ItemSlot* FindItemInInventory(Item* SearchedItem)
    {


        for (auto &i:vInventory)
        {
            if(i->ItemPtr==SearchedItem)
            {
                return i;
            }

        }
        return nullptr;
    }
public:
    bool OnUserCreate() override
    {
            vTileMap.reserve(MapSize);

        // Tilemapp = new Tile[1024]();
        //Enemy test(vTileMap,vTiles);
        lNight = CreateLayer();
        lPlayer = CreateLayer();
        lGround = CreateLayer();
        //sprite loading
        sMT = new olc::Sprite("./assets/tiles/TextureMissing.png");
        for(auto &i:vTiles)
        {
            i = new Tile(0xBEEF,sMT);


        }
        sPGELogo =    new olc::Sprite("./assets/PGELogo.png");
        sGrass =      new olc::Sprite("./assets/tiles/Grass.png");
        sTest =       new olc::Sprite ("./assets/tiles/TestTile.png");
        sMC =         new olc::Sprite ("./assets/characters/mc.png");
        sWood =       new olc::Sprite ("./assets/tiles/WoodAlpha.png");
        sWoodWall =   new olc::Sprite ("./assets/tiles/WoodWall.png");
        sWoodFloor =  new olc::Sprite ("./assets/tiles/WoodFloor.png");
        sEnemy =      new olc::Sprite ("./assets/characters/Enemy.png");
        sNight =      new olc::Sprite ("./assets/tiles/black.png");
        sMoonAndSun = new olc::Sprite("./assets/tiles/MoonandSun.png");

        dPGELogo =     new olc::Decal(sPGELogo);
        dWood =       new olc::Decal (sWood);
        dMoonAndSun = new olc::Decal(sMoonAndSun);
        dNight =      new olc::Decal (sNight);
        dMC =         new olc::Decal(sMC);

        vItems.push_back(new Item(sWood,dWood));
        vItems.push_back(new Item(sWood,dWood));

        vTiles.push_back( new Tile(0,sGrass,false,TZpos::floor)); // grass

        vTiles.push_back(new Tile(1, new olc::Sprite ("./assets/tiles/WoodAlpha.png"),true)); // Wood
        vTiles[1]->vItemsGathered.push_back(vItems[1]);
        std::cout<<vTiles[1]->vItemsGathered.back()<<"\n";
        std::cout<<vTiles[1]->vItemsGathered.front()<<"\n";
        vTiles[1]->vItemsGatheredQuantity.push_back(5);


        vTiles.push_back(new Tile(2,sWoodWall,true)); // Wood wall
        vTiles[2]->vItemsRequiredQuantity.push_back(10);
        vTiles[2]->vItemsRequired.push_back(vItems[1]);
        vBuildableTiles.push_back(vTiles[2]);


        vTiles.push_back(new Tile(3,sWoodFloor,false,TZpos::floor)); // WoodFloor
//        vTiles[3]->vItemsRequiredQuantity.push_back(10);
//        vTiles[3]->vItemsRequired.push_back(vItems[1]);
//        vBuildableTiles.push_back(vTiles[3]);
        vTiles.push_back(new Tile(4,sTest,false,TZpos::dirt)); // cley


        //generating map
        using namespace std::chrono;


        auto mapstart = high_resolution_clock::now();



        GenerateMap(vTileMap,vTiles);

        auto mapstop = high_resolution_clock::now();

        vNodeMap.reserve(MapSize);
        // Seting up nodemap for a*
        for(int x=0;x<MapSize;++x)
        {
            std::vector<sNode*> v1;
            v1.reserve(MapSize);
            for(int y=0;y<MapSize;++y)
            {
                std::cout<<"Allocating node "<< x<<" "<<y<<std::endl;
                v1.push_back(new sNode);
                v1[y]->x =x;
                v1[y]->y =y;
            }
         vNodeMap.push_back(v1);
        }
        auto NodeMapStop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(mapstop - mapstart);
        auto duration2 = duration_cast<milliseconds>(mapstop - mapstart);
        std::cout << "Time taken by MapGen: "
                  << duration.count() << " seconds"
                  << duration2.count() << " miliseconds" << std::endl;
        auto duration3 = duration_cast<seconds>(NodeMapStop - mapstop);
        auto duration4 = duration_cast<milliseconds>(NodeMapStop - mapstop);
        std::cout << "Time taken by NodeGen: "
                  << duration3.count() << " seconds"
                  << duration4.count() << " miliseconds" << std::endl;
        return true;
    }




    bool OnUserUpdate(float fElapsedTime) override
    {


        if (fSeconds>fSecondsInDay )
        {
            fSeconds=0.0;
            isNight = !isNight;
        }

        fSeconds +=fElapsedTime;


        PreviousSecond = floor(fSeconds);
        float fMousePlayerDistance = sqrt( pow(fMouseMapY-fPlayerY,2)+pow(fMouseMapX-fPlayerX,2)  );
        Clear(olc::BLANK);
        // it copy all the code in Controls.h and paste it here (in Controls.h i store input handeling code)
        #include "Controls.h"


        fCameraX = fPlayerX-(ScreenWidth()/2)/TileSize;
        fCameraY = fPlayerY-(ScreenHeight()/2)/TileSize;
        SetDrawTarget(lGround);
        Clear(olc::CYAN);


        ///Tile Drawing
        //y and x are cordinates of decals of tiles (-player cor offset) on screen, xx and yy are coordinates of position on tile map.
        for (int y = 0,yy= 0; y < ScreenHeight()+TileSize*fTileScale*2; y+=TileSize*fTileScale)
        {
            for (int x = 0,xx= 0; x < ScreenWidth()+TileSize*fTileScale*2; x+=TileSize*fTileScale)
            {

                for (auto &i:vTileMap[ xx+(int)fCameraX  ][ yy+(int)fCameraY ] )
                {
                    DrawDecal(olc::vf2d (x-fmod(fPlayerX,1)*TileSize*fTileScale, y-fmod(fPlayerY,1)*TileSize*fTileScale),
                              i->GetDecal(),olc::vf2d(fTileScale,fTileScale));
                }
                // DrawDecal(olc::vf2d (x-fmod(fPlayerX,1)*TileSize, y-fmod(fPlayerY,1)*TileSize),  vTileMap[ xx+(int)fCameraX  ][ yy+(int)fCameraY ].back()->GetDecal());


                ++xx;
            }
            ++yy;
        }

        //draws player
        SetDrawTarget(lPlayer);
        Clear(olc::BLANK);
        fMouseMapX =(float)GetMouseX()/TileSize+fCameraX;
        fMouseMapY=(float)GetMouseY()/TileSize+fCameraY;

        fPlayerA = atan2((fMouseMapY-fPlayerY),(fMouseMapX-fPlayerX));

        DrawRotatedDecal(olc::vf2d((fPlayerX-fCameraX)*TileSize*fTileScale,(fPlayerY-fCameraY)*TileSize*fTileScale),dMC, fPlayerA+PI/2, {float(sMC->width)/2.0f,float(sMC->height)/2.0f});


        int BulletLoop =0;
        // draws the bullets
        for(auto &i:vBullets)
        {
            olc::vf2d BulletPrevPos = i->GetPos();
            i->Move(fElapsedTime);

            if( Distance(fPlayerX,fPlayerY,i->GetX(),i->GetY())<40)
            {

                DrawLine(  (i->GetX()-fCameraX)*TileSize,   (i->GetY()-fCameraY)*TileSize,
                (BulletPrevPos.x-fCameraX)*TileSize,  (BulletPrevPos.y-fCameraY)*TileSize,
                olc::YELLOW);
            }


            else
            {
                delete i;
                vBullets.erase(vBullets.begin()+BulletLoop);
            }
            BulletLoop++;
        }

        {
        int ii=0;
        ///Draws Enemy
        for(auto &i: vEnemies)
        {
            //if(!vTiles[vTileMap[i->GetPosition().x][i->GetPosition().y]]->isColisive())
                i->Move(fPlayerX,fPlayerY,fElapsedTime);

            DrawDecal(olc::vf2d((i->x-fCameraX)*TileSize-TileSize/2,(i->y-fCameraY)*TileSize-TileSize/2),i->Decal);

            if(Distance(fPlayerX,fPlayerY,i->x,i->y)<1.5f)
            {
                Health-=fElapsedTime/10.0f;
            }

            int jj =0;
            /// On web this dosn't work because of frame rate thus it probably will not work on lower frame rate on PC,(value change between is so big on lower frame rates that
            /// before distance is low  enough to see it as hit bullet is already behind enemy.)

            for(auto &j: vBullets)
          {
                std::cout<<"Distance: "<<Distance(j->GetPos().x,j->GetPos().y, i->x,i->y)<<"\n";

                if(Distance(j->GetPos().x,j->GetPos().y, i->x,i->y)<0.5f)
                {
                    delete j;
                    delete i;
                    vBullets.erase(vBullets.begin()+jj);
                    vEnemies.erase(vEnemies.begin()+ii);
                }

            ++jj;

            }
        ++ii;
        }
        }
        // enabling layers
        EnableLayer(lPlayer,true);
        EnableLayer(lGround,true);

        // HUD DRAWING

        DrawString(GetMouseX()-MouseText.size()*8/2,GetMouseY()-20, MouseText);
        float ClockScale = 4.0f;

        DrawRotatedDecal(olc::vf2d(ScreenWidth()-sMoonAndSun->width/2+5,sMoonAndSun->height*ClockScale),
                         dMoonAndSun,isNight ? fSeconds/fSecondsInDay*PI:fSeconds/fSecondsInDay*PI+PI,
                         olc::vf2d(sMoonAndSun->width/2.0f,sMoonAndSun->height/2.0f),olc::vf2d(ClockScale,ClockScale));

        //DrawString(10,ScreenHeight()-20-sWood->height,std::to_string(aResourses[1]),olc::BLACK);
        //DrawSprite(10,ScreenHeight()-10-sWood->height,sWood);



        if(fModeTextFading>0.0f)
        {
            if (ModeTextLap >0) --ModeTextLap;
            else if (ModeTextLap <0)
            {
                ;
            }
            else fModeTextFading-= fElapsedTime;

        }
        //std::string HomeCenter = "Home center";
        //std::string HomeCenter2
        //DrawString((510-fCameraX)*TileSize ,(512-fCameraY)*TileSize, HomeCenter);

        std::string strMode;
        if (isFightMode) strMode = "Fight Mode";
        if (!isFightMode) strMode = "Build/Gathering Mode";

        DrawStringDecal({(float)ScreenWidth()-strMode.size()*9,10},strMode,olc::PixelF (1.0f,1.0f,1.0f,fModeTextFading));
        SetDrawTarget(lNight);
        Clear(olc::BLANK);
        if(isNight)
            DrawDecal(olc::vf2d(0,0),dNight,olc::vf2d(1.0f,1.0f),olc::PixelF(1.0f,1.0f,1.0f,0.25f));

        EnableLayer(lNight,true);
        SetDrawTarget(nullptr);
        if (Health<0.0f)
        {
            DrawString(ScreenWidth()/2-50,ScreenHeight()/2," Game over \n refresh page to start again");
        }
        if (isStatsDis)
        {
            DrawString(0,0,"PlayerX: "+ std::to_string(fPlayerX));
            DrawString(0,10,"PlayerY: "+ std::to_string(fPlayerY)+std::to_string(fPlayerA));

            DrawString(0,20,"CameraX: "+ std::to_string(fCameraX));
            DrawString(0,30,"CameraY: "+ std::to_string(fCameraY));
            DrawString(0,40,"MouseX: "+ std::to_string(fMouseMapX));
            DrawString(0,50,"MouseY: "+ std::to_string(fMouseMapY));
            DrawString(0,60,"Destruction: "+ std::to_string(fDestruction));
            DrawString(0,70,"Construction: "+ std::to_string(fConstruction));
            if(!vInventory.empty())
            {
                DrawString(0,80,"R1: "+ std::to_string(vInventory[0]->Quantity));

            }
            else
                DrawString(0,80,"R1: Empty");

            if(vInventory.size()>=2)
            {
                DrawString(0,90,"R2: "+ std::to_string(vInventory[1]->Quantity));

            }
            else
                DrawString(0,90,"R2: Empty");
            //      DrawString(0,90,"R2d: "+ std::to_string(aResourses[1]));

            DrawString(0,110,"Distance: "+ std::to_string(Distance(fPlayerX,fPlayerY,GetMouseX()/TileSize+fCameraX,GetMouseY()/TileSize+fCameraY)));
            DrawString(0,120,"Time: "+ std::to_string(floor(fSeconds)));
            DrawString(0,130,"Scale: "+ std::to_string(fTileScale));
        }
        // DrawString(0,20,"TileX: "+ std::to_string(fCameraX%1));

        return true;
    }


    bool OnUserDestroy() override
    {

        delete sGrass;
        return true;
    }
};



