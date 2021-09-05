
float MovingSpeed = 4.0f;
if (GetKey(olc::Key::F1).bPressed)
{
    isStatsDis = !isStatsDis;

}

//if (GetKey(olc::Key::CTRL).bPressed)
//{
//    isFightMode = !isFightMode;
//    fModeTextFading =1.0f;
//    ModeTextLap = 50;
//}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if (!isFightMode)
{
  // Build  /resoursce mode
    if (GetKey(olc::Key::D).bHeld)
{
    fPlayerX+= MovingSpeed*fElapsedTime;
    if (vTiles[vTileMap[fPlayerX][fPlayerY]]->isColisive())
    {
        fPlayerX-= MovingSpeed*fElapsedTime;
    }
}
if (GetKey(olc::Key::A).bHeld)
{
    fPlayerX-= MovingSpeed*fElapsedTime;
        if (vTiles[vTileMap[fPlayerX][fPlayerY]]->isColisive())
    {
        fPlayerX+= MovingSpeed*fElapsedTime;
    }
}
if (GetKey(olc::Key::S).bHeld)
{
    fPlayerY+= MovingSpeed*fElapsedTime;
        if (vTiles[vTileMap[fPlayerX][fPlayerY]]->isColisive())
    {
         fPlayerY-= MovingSpeed*fElapsedTime;
    }
}
if (GetKey(olc::Key::W).bHeld)
{
    fPlayerY-= MovingSpeed*fElapsedTime;
            if (vTiles[vTileMap[fPlayerX][fPlayerY]]->isColisive())
    {
         fPlayerY+= MovingSpeed*fElapsedTime;
    }
}



    if (GetKey(olc::Key::K1).bHeld)
    {
        SelectedBuildTile = 2;
    }
        if (GetKey(olc::Key::K2).bHeld)
    {
        SelectedBuildTile = 3;
    }
    // GATHERING RESOURSERS
    if ((int)((float)GetMouseX()/TileSize+fCameraX) ==(int)fMouseMapX &&

            (int)((float)GetMouseY()/TileSize+fCameraY)==(int)fMouseMapY &&

            GetMouse(0).bHeld && vTiles[vTileMap[fMouseMapX][fMouseMapY]]->GetResource()  &&
            fMousePlayerDistance < fReachDistance

            )
    {
        std::string GatheringResourses = "Gathering Resourses";
        DrawString(GetMouseX()-GatheringResourses.size()*8/2,GetMouseY()-20, GatheringResourses);
        // width
        FillRect(GetMouseX()-GatheringResourses.size()*8/2, GetMouseY()-10, GatheringResourses.size()*8*fDestruction,10,olc::RED );
        DrawRect(GetMouseX()-GatheringResourses.size()*8/2, GetMouseY()-10, GatheringResourses.size()*8,10, olc::WHITE );

        fDestruction += 0.6f*fElapsedTime;
        if (fDestruction >1)
        {
            fDestruction =0.0f;
            aResourses[vTiles[vTileMap[fMouseMapX][fMouseMapY]]->GetResource()] += vTiles[vTileMap[fMouseMapX][fMouseMapY]]->GetRQuantity();
            vTileMap[fMouseMapX][fMouseMapY] = vTiles[vTileMap[fMouseMapX][fMouseMapY]]->GetBase();

        }

    }
    else
    {
        fDestruction =0.0f;
    }
        // BUILDING
    if ((int)((float)GetMouseX()/TileSize+fCameraX) ==(int)fMouseMapX &&

            (int)((float)GetMouseY()/TileSize+fCameraY)==(int)fMouseMapY &&

            GetMouse(1).bHeld && vTiles[vTileMap[fMouseMapX][fMouseMapY]]->GetIsFloor() &&

            (aResourses[vTiles[SelectedBuildTile]->GetResource()] -vTiles[SelectedBuildTile]->GetResourceRequirement())>=0 &&

            vTileMap[fMouseMapX][fMouseMapY] == vTiles[SelectedBuildTile]->GetBase() &&

            fMousePlayerDistance < fReachDistance

       )
    {
        std::string Building = "Constructing";
        DrawString(GetMouseX()-Building.size()*8/2,GetMouseY()-20, Building);
        // width
        FillRect(GetMouseX()-Building.size()*8/2, GetMouseY()-10, Building.size()*8*fConstruction,10,olc::RED );
        DrawRect(GetMouseX()-Building.size()*8/2, GetMouseY()-10, Building.size()*8,10, olc::WHITE );


        fConstruction += 0.6f*fElapsedTime;
        if (fConstruction >1)
        {
            fConstruction =0.0f;
            //aResourses[vTiles[vTileMap[fMouseMapX-1][fMouseMapY-1]]->GetResource()] += vTiles[vTileMap[fMouseMapX-1][fMouseMapY-1]]->GetRQuantity();

            aResourses[vTiles[SelectedBuildTile]->GetResource()] -=vTiles[SelectedBuildTile]->GetResourceRequirement();
            vTileMap[fMouseMapX][fMouseMapY] = SelectedBuildTile;


        }

    }
    else
    {
        fConstruction =0.0f;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
else if(Health>0)
{
    //std::string strAmmo = "Ammo: "
    std::string strHealth= "Health";
    DrawString(ScreenWidth()/2-strHealth.size()*8/2,ScreenHeight()-20,strHealth);
    FillRect(ScreenWidth()/2-strHealth.size()*8/2,ScreenHeight()-10,strHealth.size()*8*Health,5, olc::RED);
     DrawRect(ScreenWidth()/2-strHealth.size()*8/2,ScreenHeight()-10,strHealth.size()*8,5, olc::WHITE);
    if (GetMouse(0).bPressed)
    {
        vBullets.push_back(new Bullet(fPlayerX,fPlayerY,fPlayerA));
    }



}
