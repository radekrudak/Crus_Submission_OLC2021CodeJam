// Used Javid9 A Star algorythm inplementation as reference.
//std::cout<<"Finding a path";
sNodeMap = new sNode[MapSize*MapSize];
for (int x= (int)fPlayerX-NodeMapSize/2; x<(int)fPlayerX+NodeMapSize/2; x++)
    for (int y =(int)fPlayerY-NodeMapSize/2; y< (int)fPlayerY+NodeMapSize/2; y++)
    {
        std::cout<<"Loop x: "<<x<<"y: "<<y <<"start \n";
        sNodeMap[y * MapSize +x].x =x;
        sNodeMap[y * MapSize +x].y =y;
        sNodeMap[y * MapSize +x].parent = nullptr;
        sNodeMap[y * MapSize +x].bVisited = false;
        std::cout<<"Loop end \n";
    }
std::cout<<"Loop one ended \n";

for (int x= (int)fPlayerX-NodeMapSize/2; x<(int)fPlayerX+NodeMapSize/2; x++)
    for (int y =(int)fPlayerY-NodeMapSize/2; y< (int)fPlayerY+NodeMapSize/2; y++)
    {

        if (y>0)
            sNodeMap[y*MapSize + x].vNeighbours.push_back(&sNodeMap[(y-1)*MapSize + (x+0)]);
        if (y< MapSize-1)
            sNodeMap[y*MapSize + x].vNeighbours.push_back(&sNodeMap[(y+1)*MapSize+ (x+0)]);
        if (x>0)
            sNodeMap[y*MapSize + x].vNeighbours.push_back(&sNodeMap[(y+0)*MapSize + (x-1)]);
        if (x<MapSize-1)
            sNodeMap[y*MapSize + x].vNeighbours.push_back(&sNodeMap[(y+0)*MapSize + (x+1)]);

    }
std::cout<<"Loop two ended \n";
sNode *sNodeStart = &sNodeMap[StartPoint.y*NodeMapSize+StartPoint.y];
sNode *sNodeEnd = &sNodeMap[EndPoint.y*NodeMapSize+EndPoint.y];

// sets all nodes's dynamic properties to default value
for (int x= 0; x<NodeMapSize; x++)
    for (int y =0; y< NodeMapSize; y++)
    {

        sNodeMap[y * NodeMapSize + x].bVisited = false;
        sNodeMap[y * NodeMapSize + x].fGlobalGoal = INFINITY;
        sNodeMap[y * NodeMapSize + x].fLocalGoal = INFINITY;
        sNodeMap[y * NodeMapSize + x].parent = nullptr;

    }

sNodeStart->fLocalGoal = 0.0f ;//seting local goal "distance to start" to zero;
sNodeStart->fGlobalGoal = Distance(sNodeStart,sNodeEnd);
sNode *CurrentNode = sNodeStart;

 delete[] sNodeMap;
