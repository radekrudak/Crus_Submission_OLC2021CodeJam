

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define MENU 0
#include "MapGen.h"
#include "Tile.h"
#include "Bullet.h"
#include <math.h>

// to do:
// Enemies
// shooting
// health
// Hud:
// HP
// Resourses
// ammo ?
// tile selected to build
bool isStatsDis = false;
bool isFightMode = false;

float fPlayerX =512;
float fPlayerY =512;
float fPlayerA =0.0f;
float fDestruction =1.0f;
float fConstruction = 0.0f;
float fMouseMapX =0.0f;
float fMouseMapY = 0.0f;
float fReachDistance =2;

float fModeTextFading = 1.0f;
int ModeTextLap = 50;


int Health;
int SelectedBuildTile =2; // what tile is builded, number is tile ID

float fCameraX;
float fCameraY;
float PI = 3.14159;
static int TileSize =16;

int lGround;
int lPlayer;

//std::unique_ptr<olc::Sprite> sprTile;
olc::Sprite *sGrass ;
olc::Sprite *sWood;
olc::Sprite *sMT;
olc::Sprite *sTest;
olc::Sprite *sMC;
olc::Sprite *sWoodWall;
olc::Sprite *sWoodFloor;
olc::Decal *dMC;
std::array<std::array<char,1024>,1024> vTileMap ;
std::array<Tile*,6> vTiles ; // 0= Grass, 1 = Wood
std::array<int,2> aResourses= {0};
std::vector<Bullet*> vBullets;
 // i put it here so Bullet.h have acess to vTiles and vTile map;
class GameJam : public olc::PixelGameEngine
{
public:
	GameJam()
	{
		// Name your application
		sAppName = "GameJamEntry";

	}

public:
	bool OnUserCreate() override
	{

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

		return true;
	}



	bool OnUserUpdate(float fElapsedTime) override
	{
        float fMousePlayerDistance = sqrt( pow(fMouseMapY-fPlayerY,2)+pow(fMouseMapX-fPlayerX,2)  );
        Clear(olc::BLANK);
        // it copy all the code in Controls.h and paste it here (in Controls.h i store input handeling code)
        #include "Controls.h"


        fCameraX = fPlayerX-(ScreenWidth()/2)/TileSize;
        fCameraY = fPlayerY-(ScreenHeight()/2)/TileSize;
        SetDrawTarget(lGround);
        Clear(olc::CYAN);


		// Called once per frame, draws random coloured pixels
		//y and x are cordinates of decals of tiles (-player cor offset) on screen, xx and yy are coordinates of position on tile map.
		for (int y = 0,yy= -1; y < ScreenHeight()+TileSize*2; y+=TileSize)
		{
			for (int x = 0,xx= -1; x < ScreenWidth()+TileSize*2; x+=TileSize)
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
        for(auto &i:vBullets)
        {
            olc::vf2d BulletPrevPos = i->GetPos();
            i->Move(fElapsedTime);
            if(!vTiles[vTileMap[i->GetX()-1][i->GetY()-1]]->isColisive())
            {

            DrawLine(  (i->GetX()-fCameraX)*TileSize,   (i->GetY()-fCameraY)*TileSize,
                (BulletPrevPos.x-fCameraX)*TileSize,  (BulletPrevPos.y-fCameraY)*TileSize,
                olc::YELLOW);
            }
            else                                                /// !!! potencial memory leak !!!
            {
                delete i;
                vBullets.erase(vBullets.begin()+BulletLoop);
            }
            BulletLoop++;
        }

        fPlayerA = atan2((fMouseMapY-fPlayerY),(fMouseMapX-fPlayerX));

        DrawRotatedDecal(olc::vf2d((fPlayerX-fCameraX)*TileSize,(fPlayerY-fCameraY)*TileSize),dMC, fPlayerA+PI/2, {float(sMC->width)/2.0f,float(sMC->height)/2.0f});

        // enabling layers
        EnableLayer(lPlayer,true);
        EnableLayer(lGround,true);

      //  DrawRect(5,ScreenHeight()-15-sWood->height,sWood->width,sWood->height);
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

        std::string strMode;
        if (isFightMode) strMode = "Fight Mode";
        if (!isFightMode) strMode = "Build/Gathering Mode";

        DrawStringDecal({ScreenWidth()-strMode.size()*9,10},strMode,olc::PixelF (1.0f,1.0f,1.0f,fModeTextFading));
        SetDrawTarget(nullptr);
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
        DrawString(0,110,"Distance: "+ std::to_string(fMousePlayerDistance));
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

