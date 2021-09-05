
#pragma once
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define MENU 0
#include "MapGen.h"
#include "Tile.h"
#include "Bullet.h"
#include  "Enemy.h"



// to do:
// Enemies
// shooting
// health
// Hud:
// HP
// Resourses
// ammo ?
// tile selected to build
static int TileSize =16;
class GameJam : public olc::PixelGameEngine
{

static const int MapSize = 1024;
static const int NodeMapSize =128;
friend Enemy;

bool isEnd = false;
bool isStatsDis = false;
bool isFightMode = false;
bool isNightStartSequence = false;
float NightStartSequenceTimer=0;;
float NightStartSequenceTime = 3.0f;

float fPlayerX =512.5f;
float fPlayerY =512.5f;
float fPlayerA =0.0f;
float fDestruction =1.0f;
float fConstruction = 0.0f;
float fMouseMapX =0.0f;
float fMouseMapY = 0.0f;
float fReachDistance =2;

double fSeconds;
int PreviousSecond=0;
double fSecondsInDay=20.;


float fModeTextFading = 1.0f; // used in left top  mode displaying text fading effect
int ModeTextLap = 50; // used in left top  mode displaying text fading effect


double Health =1 ;
int SelectedBuildTile =2; // what tile is builded, number is tile ID

float fCameraX;
float fCameraY;
float PI = 3.14159;


int lGround;
int lPlayer;
int lNight;

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
olc::Decal *dMoonAndSun = nullptr;
olc::Decal *dNight = nullptr;
olc::Decal *dMC=nullptr;


std::array<std::array<char,1024>,1024> vTileMap ;
// when replacing vTiles array size replace in Enemy.h too.
std::array<Tile*,6> vTiles ; // 0= Grass, 1 = Wood
std::array<int,2> aResourses= {0};
std::vector<Bullet*> vBullets;
std::vector<Enemy*> vEnemies;
 // i put it here so Bullet.h have acess to vTiles and vTile map;

sNode *sNodeMap;
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
public:
	bool OnUserCreate() override
	{


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
        sGrass = new olc::Sprite("./assets/tiles/Grass.png");
        sTest = new olc::Sprite ("./assets/tiles/TestTile.png");
        sMC = new olc::Sprite ("./assets/characters/mc.png");
        sWood = new olc::Sprite ("./assets/tiles/WoodAlpha.png");
        sWoodWall = new olc::Sprite ("./assets/tiles/WoodWall.png");
        sWoodFloor = new olc::Sprite ("./assets/tiles/WoodFloor.png");
        sEnemy = new olc::Sprite ("./assets/characters/Enemy.png");
        sNight = new olc::Sprite ("./assets/tiles/black.png");
        sMoonAndSun = new olc::Sprite("./assets/tiles/MoonandSun.png");
        dMoonAndSun = new olc::Decal(sMoonAndSun);
        dNight = new olc::Decal (sNight);
        dMC = new olc::Decal(sMC);
        vTiles[0] = new Tile(0,sGrass); // grass
        vTiles[1] = new Tile(0, new olc::Sprite ("./assets/tiles/Wood.png"),true,0,1,5,0,false); // Wood
        std::cout<< vTiles[1]->GetRQuantity()<<"\n";
        std::cout<< vTiles[1]->GetResource();
        vTiles[2] = new Tile(2,sWoodWall,true,0,1,2,10,false); // Wood wall
        vTiles[3] = new Tile(3,sWoodFloor,false,0,1,2,10,true); // WoodFloor


        //generating map
        srand (time(NULL));
		GenerateMap(vTileMap);
        vTileMap[512][512] = 3;
        vTileMap[513][513] = 2;
		return true;
	}



	bool OnUserUpdate(float fElapsedTime) override
	{


        if (fSeconds>fSecondsInDay && vEnemies.empty())
        {
            fSeconds=0.0;
            isFightMode = !isFightMode;
            fModeTextFading =1.0f;
            ModeTextLap = 50;
            if (isFightMode)
            {
                fPlayerX = 512.5f;
                fPlayerY = 512.5f;
            }
        }

        fSeconds +=fElapsedTime;

        if (isFightMode && PreviousSecond!=floor(fSeconds)) //
        {
            float enmx = 501;
            float enmy = 501;
            if(rand()%2==1)
            {
                if(rand()%2==1)
                {
                    enmx = 501;
                    enmy = rand()%23+500;
                }
                else
                {
                    enmx = 522;
                    enmy = rand()%23+500;
                }

            }
            else
            {
                if(rand()%2==1)
                {
                    enmy = 501;
                    enmx = rand()%23+500;
                }
                else
                {
                    enmy = 522;
                    enmx = rand()%23+500;
                }
            }


            std::cout<<"x:"<<enmx<<" y:"<<enmy<<"dis: "<< '\n';
           // vEnemies.push_back(new Enemy(515.5F,515.5F,sEnemy));
           vEnemies.push_back(new Enemy(enmx,enmy,sEnemy));
        }
        PreviousSecond = floor(fSeconds);
        float fMousePlayerDistance = sqrt( pow(fMouseMapY-fPlayerY,2)+pow(fMouseMapX-fPlayerX,2)  );
        Clear(olc::BLANK);
        // it copy all the code in Controls.h and paste it here (in Controls.h i store input handeling code)
        #include "Controls.h"


        fCameraX = fPlayerX-(ScreenWidth()/2)/TileSize;
        fCameraY = fPlayerY-(ScreenHeight()/2)/TileSize;
        SetDrawTarget(lGround);
        Clear(olc::CYAN);



		//y and x are cordinates of decals of tiles (-player cor offset) on screen, xx and yy are coordinates of position on tile map.
		for (int y = 0,yy= 0; y < ScreenHeight()+TileSize*2; y+=TileSize)
		{
			for (int x = 0,xx= 0; x < ScreenWidth()+TileSize*2; x+=TileSize)
              {

                DrawDecal(olc::vf2d (x-fmod(fPlayerX,1)*TileSize, y-fmod(fPlayerY,1)*TileSize),  vTiles[vTileMap[ xx+(int)fCameraX ][ yy+(int)fCameraY ] ]->GetDecal());

                ++xx;
              }
        ++yy;
        }

        //draws player
        SetDrawTarget(lPlayer);
        Clear(olc::BLANK);
        fMouseMapX =(float)GetMouseX()/TileSize+fCameraX;
        fMouseMapY=(float)GetMouseY()/TileSize+fCameraY;
        int BulletLoop =0;
        // draws the bullets
        for(auto &i:vBullets)
        {
            olc::vf2d BulletPrevPos = i->GetPos();
            i->Move(fElapsedTime);

//            if(!vTiles[vTileMap[i->GetX()-1][i->GetY()-1]]->isColisive())
//            {
//
//                DrawLine(  (i->GetX()-fCameraX)*TileSize,   (i->GetY()-fCameraY)*TileSize,
//                (BulletPrevPos.x-fCameraX)*TileSize,  (BulletPrevPos.y-fCameraY)*TileSize,
//                olc::YELLOW);
//            }
//            else
            if(Distance(fPlayerX,fPlayerY,i->GetX(),i->GetY())<40)
            {
                DrawLine(  (i->GetX()-fCameraX)*TileSize,   (i->GetY()-fCameraY)*TileSize,
                (BulletPrevPos.x-fCameraX)*TileSize,  (BulletPrevPos.y-fCameraY)*TileSize,
                olc::YELLOW);
            }
            else                                             /// !!! potencial memory leak !!!
            {
                delete i;
                vBullets.erase(vBullets.begin()+BulletLoop);
            }
            BulletLoop++;
        }

        fPlayerA = atan2((fMouseMapY-fPlayerY),(fMouseMapX-fPlayerX));

        DrawRotatedDecal(olc::vf2d((fPlayerX-fCameraX)*TileSize,(fPlayerY-fCameraY)*TileSize),dMC, fPlayerA+PI/2, {float(sMC->width)/2.0f,float(sMC->height)/2.0f});
        {
        int ii=0;
        ///Draws Enemy
        for(auto &i: vEnemies)
        {
            if(!vTiles[vTileMap[i->GetPosition().x][i->GetPosition().y]]->isColisive())
                i->Move(fPlayerX,fPlayerY,fElapsedTime);

            DrawDecal(olc::vf2d((i->x-fCameraX)*TileSize-TileSize/2,(i->y-fCameraY)*TileSize-TileSize/2),i->Decal);

            if(Distance(fPlayerX,fPlayerY,i->x,i->y)<1.5f)
            {
                Health-=fElapsedTime/10.0f;
            }

            int jj =0;
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
        float ClockScale = 4.0f;

        DrawRotatedDecal(olc::vf2d(ScreenWidth()-sMoonAndSun->width/2+5,sMoonAndSun->height*ClockScale),
        dMoonAndSun,isFightMode ? fSeconds/fSecondsInDay*PI:fSeconds/fSecondsInDay*PI+PI ,
        olc::vf2d(sMoonAndSun->width/2.0f,sMoonAndSun->height/2.0f),olc::vf2d(ClockScale,ClockScale));

        DrawString(10,ScreenHeight()-20-sWood->height,std::to_string(aResourses[1]),olc::BLACK);
        DrawSprite(10,ScreenHeight()-10-sWood->height,sWood);



        if(fModeTextFading>0.0f)
        {
            if (ModeTextLap >0) --ModeTextLap;
            else if (ModeTextLap <0)
            {
                ;
            }
            else fModeTextFading-= fElapsedTime;

        }
        std::string HomeCenter = "Home center";
        //std::string HomeCenter2
        DrawString((510-fCameraX)*TileSize ,(512-fCameraY)*TileSize, HomeCenter);

        std::string strMode;
        if (isFightMode) strMode = "Fight Mode";
        if (!isFightMode) strMode = "Build/Gathering Mode";

        DrawStringDecal({(float)ScreenWidth()-strMode.size()*9,10},strMode,olc::PixelF (1.0f,1.0f,1.0f,fModeTextFading));
        SetDrawTarget(lNight);
        Clear(olc::BLANK);
        if(isFightMode)
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
        DrawString(0,80,"R1: "+ std::to_string(aResourses[0]));
        DrawString(0,90,"R2d: "+ std::to_string(aResourses[1]));
        DrawString(0,100,"Selected Building Tile: "+ std::to_string(SelectedBuildTile));
        DrawString(0,110,"Distance: "+ std::to_string(Distance(fPlayerX,fPlayerY,GetMouseX()/TileSize+fCameraX,GetMouseY()/TileSize+fCameraY)));
        DrawString(0,120,"Time: "+ std::to_string(floor(fSeconds)));
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

