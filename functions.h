#include <iostream>
#include <graphics.h>
#include <mattcore.h>
#include <mattmark.h>
const int sizes=80; /// 50 be best
const int probabilityToBeWhite=30; ///30 works best
class point
{
public:
    int x,y;
    bool wasAlive;
    point(int x1,int y1,bool wasAlive1)
    {
        x=x1;
        y=y1;
        wasAlive=wasAlive1;
    }

};
vector<point> haveChanged;
void drawPixel(const int &x,const int &y,const bool &isAlive=0)
{
    if(isAlive==0)
        setcolor(0);
    else
        setcolor(15);
    for(int i=0; i<10; i++)
        line(x*10,y*10+i,x*10+10,y*10+i);
}
class cell
{
public:
    bool alive;
    cell()
    {
        alive=0;
    }
};

cell lastFrame[101][101];

class board
{
public:
    cell theCells[101][101];
    int getNeighbours(int x, int y)
    {
        int howmany = 0;
        if (theCells[(x - 1)][y].alive == 1 && x != 0)
            howmany++;
        if (theCells[(x-1)][(y-1)].alive==1&&x!=0&&y!=0)
            howmany++;
        if (theCells[(x-1)][(y+1)].alive==1&&x!=0&&y!=sizes)
            howmany++;
        if (theCells[(x)][(y - 1)].alive == 1 && y != 0)
            howmany++;
        if (theCells[(x)][(y + 1)].alive == 1 && y != sizes)
            howmany++;
        if (theCells[(x + 1)][y].alive == 1 && x != sizes)
            howmany++;
        if (theCells[(x + 1)][(y + 1)].alive == 1 && x != sizes && y != sizes)
            howmany++;
        if (theCells[(x + 1)][(y - 1)].alive == 1 && x != sizes && y != 0)
            howmany++;
        return howmany;
    }
    void randomConstructs()
    {
        for(int i=0; i<sizes; i++)
            for(int j=0; j<sizes; j++)
                theCells[i][j].alive=(matt::core::random(1,100)>100-probabilityToBeWhite)?1:0;
    }
    void nextStep()
    {
        int s[101][101];
        for (int y = 0; y < sizes; y++)
            for (int x = 0; x < sizes; x++)
                s[x][y] = getNeighbours(x, y);
        for (int y = 0; y < sizes; y++)
            for (int x = 0; x < sizes; x++)
            {
                if (theCells[x][y].alive==1)
                {
                    if (s[x][y] > 3)
                    {
                        theCells[x][y].alive=0;
                        haveChanged.push_back(point(x,y,0));
                    }
                    if (s[x][y] < 2)
                    {
                        theCells[x][y].alive=0;
                        haveChanged.push_back(point(x,y,0));
                    }
                }
                else
                {
                    if (s[x][y] == 3){
                        theCells[x][y].alive=1;
                        haveChanged.push_back(point(x,y,1));

                    }
                }
            }

    }
    void prettyPrint()
    {
        for(int i=0; i<sizes; i++)
        {
            for(int j=0; j<sizes; j++)
            {
                if(theCells[i][j].alive)
                    std::cout<<"X";
                else
                    std::cout<<" ";
            }
            std::cout<<"\n";
        }
    }
    void initDraw(){
         for(int i=0; i<sizes; i++)
            for(int j=0; j<sizes; j++)
                drawPixel(j,i,theCells[i][j].alive);

    }
    void draw()
    {
        for(auto&zz:haveChanged)
            drawPixel(zz.x,zz.y,zz.wasAlive);
        haveChanged = vector<point>();

    }
};
