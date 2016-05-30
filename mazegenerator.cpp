#include "mazegenerator.h"

MazeGenerator::MazeGenerator()
{
     N = 30;
     M = 22;
     maxX = 100;
     maxY = 50;
     maxHeight = 9;
     numMountains = 7;



}

void MazeGenerator::drawRectMap(std::vector< std::vector < int> >& map, Block &block){
    std::cout << map[0].size() << " " << map.size() << std::endl;
    for(int i = 0 ; i < map.size(); ++i){
        for(int j = 0 ; j < map[0].size(); ++j){
            if(map[i][j] == 0)
            {
                block.addBlock(25,25,25*i+25,25*j+25);
            }
        }
    }
}
bool MazeGenerator::valid(std::vector< std::vector < int> > & map, int posx, int posy, int dir){
    std::cerr << "lets validate... " << std::endl;

    if     ((!(posx < 0 ))
        && (!(posy < 0 ))
        && (!(posx >= map[0].size()))
        && (!(posy >= map.size()))
        && ( (map[posy][posx] == 0)) ){

            for(int i = 0; i < 4 ; ++i){

                if(i != inverseDir[dir]){
                    int posx2 = posx + dirx[i];
                    int posy2 = posy + diry[i];

                    if ((posx2 >= 0 )
                    && (posy2 >= 0 )
                    && (posy2 < map.size())
                    && (posx2 < map[0].size())) {
                        if ((map[posy2][posx2] == 1)) return false;
                    }
                }

            }

            return true;
        }
        return false;
}
void MazeGenerator::generateMaze(std::vector< std::vector < int> > & map, int iniX, int iniY){
    std::cerr << "generating Maze" << std::endl;
    Pos pos(iniX, iniY);

    Randoms randoms(4);

    while(randoms.haveNumbers()){
        int dir = randoms.getNum();
        if(dir != dir_none) {
            std::cerr << pos.x + dirx[dir] << " , " << pos.y + diry[dir] << std::endl;
                        std::cerr <<"           "<< pos.x + 2*dirx[dir] << " , " << pos.y + 2*diry[dir] << std::endl;
                        std::cerr << "dir " << dir << dirx[dir] << diry[dir] << std::endl;
            if(valid(map,pos.x + dirx[dir], pos.y + diry[dir], dir)){
                std::cerr << "validated" << std::endl;
                map[pos.y + diry[dir]][pos.x + dirx[dir]] = 1;
                generateMaze(map, pos.x + dirx[dir], pos.y + diry[dir]);
            }
        }
    }

}

void MazeGenerator::createMaze()
{
    std::vector< std::vector < int> > map( N, std::vector<int>(M, 0));
    generateMaze(map, 0,0);
    drawRectMap(map, block);
    Maze = block.blockContainer;
}

void MazeGenerator::draw(RenderTarget &target, RenderStates states) const
{
    //states.transform *= getTransform();
    for(unsigned int i=0;i<Maze.size();i++)
        target.draw(Maze[i]);
}

