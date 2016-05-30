#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H
#include <time.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "block.h"
#include "randoms.h"
#include <SFML/Graphics.hpp>

class MazeGenerator: public Drawable
{
public:
    MazeGenerator();

    void createMaze();

    enum directions {
        dir_up, dir_down, dir_right, dir_left, dir_none
    };
    struct Pos {
      int x;
      int y;
      Pos() {} //creadora per defecte
      Pos(int ii, int jj) : x(ii), y(jj) { }    //creadora which set i = ii and j = jj (ii and jj are the parameters)
    };
      std::vector <RectangleShape> Maze;
private:
    int N, M, maxX,maxY,maxHeight, numMountains;
    //          N   S   E   W  NONE
    int dirx[5] = { 0,  0,  1, -1, 0};
    int diry[5] = { 1, -1,  0,  0, 0};
    int inverseDir[5] = {1, 0, 3, 2, 5};
    Block block;

    void drawRectMap(std::vector< std::vector < int> >& map, Block &block);
    bool valid(std::vector< std::vector < int> > & map, int posx, int posy, int dir);
    void generateMaze(std::vector< std::vector < int> > & map, int iniX, int iniY);
    virtual void draw(RenderTarget &target, RenderStates states) const;

};

#endif // MAZEGENERATOR_H
