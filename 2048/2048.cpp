#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define  MapSize 4
using namespace std;
int map[MapSize][MapSize];
int   useCnt = MapSize*MapSize;
int  values[15] = {2,4,8,16,32,64,128,256,512,1024,2048};


void initMap()
{
    int len = MapSize*MapSize;
    for(int i = 0; i < len; i++){
        map[i/MapSize][i%MapSize] = 0;
    }

    int  t1 = rand()%useCnt--;
    map[t1/MapSize][t1%MapSize] = values[(rand()%64 < 50) ? 0:1];

    int t2 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i < t2; i++){
        index++;
        if(map[index/MapSize][index%MapSize]) i--;
        
    }
    map[index/MapSize][index%MapSize] = values[(rand()%64 < 50) ? 0:1];
}
void printMap()
{
    for(int i = 0; i < MapSize; i++){
        for(int j = 0;  j < MapSize; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void  up()
{
    for(int i = 0; i < MapSize; i++){
        int t = 0;
        for(int j = 0; j < MapSize; j++){
            if(map[j][i]){
                map[t++][i] = map[j][i];
            }
        }
        for(int j = t; j < MapSize; j++)
            map[j][i] = 0;
 
        for(int j = 0; j < t-1; j++){
            if(map[j][i] == map[j+1][i]){
                map[j][i] *= 2;
                for(int z = j+1; z-1 < MapSize ; z++)
                    map[z][i] = map[z+1][i];
                map[MapSize-1][i] = 0;
                useCnt++;
                t--;
            }
        }
    }
    int t1 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i <= t1; i++){
        index++;
        if(map[index/MapSize][index%MapSize])
            i--;
    }
    map[index/MapSize][index%MapSize] = values[(rand()%64 < 50) ? 0:1];
}

void  down()
{
    for(int i = 0; i < MapSize; i++){
        int t = MapSize-1;
        for(int j = MapSize-1; j >= 0; j--){
            if(map[j][i]){
                map[t--][i] = map[j][i];
            }
        }
        for(int j = t; j >= 0; j--)
            map[j][i] = 0;
 
        for(int j = MapSize-1; j > t+1; j--){
            if(map[j][i] == map[j-1][i]){
                map[j][i] *= 2;
                for(int z = j-1; z+1 > 0 ; z--)
                    map[z][i] = map[z-1][i];
                map[0][i] = 0;
                useCnt++;
                t++;
            }
        }
    }
    int t1 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i <= t1; i++){
        index++;
        if(map[index/MapSize][index%MapSize])
            i--;
    }
    map[index/MapSize][index%MapSize] = values[(rand()%64 < 50) ? 0:1];
}

void  left()
{
    for(int i = 0; i < MapSize; i++){
        int t = 0;
        for(int j = 0; j < MapSize; j++){
            if(map[i][j]){
                map[i][t++] = map[i][j];
            }
        }
        for(int j = t; j < MapSize; j++)
            map[i][j] = 0;
 
        for(int j = 0; j < t-1; j++){
            if(map[i][j] == map[i][j+1]){
                map[i][j] *= 2;
                for(int z = j+1; z-1 < MapSize ; z++)
                    map[i][z] = map[i][z+1];
                map[i][MapSize-1] = 0;
                useCnt++;
                t--;
            }
        }
    }
    int t1 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i <= t1; i++){
        index++;
        if(map[index/MapSize][index%MapSize])
            i--;
    }
    map[index/MapSize][index%MapSize] = values[(rand()%64 < 50) ? 0:1];
}
void  right()
{
    for(int i = 0; i < MapSize; i++){
        int t = MapSize-1;
        for(int j = MapSize-1; j >= 0; j--){
            if(map[i][j]){
                map[i][t--] = map[i][j];
            }
        }
        for(int j = t; j >= 0; j--)
            map[i][j] = 0;
 
        for(int j = MapSize-1; j > t+1; j--){
            if(map[i][j] == map[i][j-1]){
                map[i][j] *= 2;
                for(int z = j-1; z+1 > 0 ; z--)
                    map[i][z] = map[i][z-1];
                map[i][0] = 0;
                useCnt++;
                t++;
            }
        }
    }
    int t1 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i <= t1; i++){
        index++;
        if(map[index/MapSize][index%MapSize])
            i--;
    }
    map[index/MapSize][index%MapSize] = values[(rand()%64 < 50) ? 0:1];
}
char direction()//读取键盘的方向键
{
	int c1 = _getch(), c2 = _getch();
	if (c2 == 72)return 'u';
	if (c2 == 80)return 'd';
	if (c2 == 75)return 'l';
	if (c2 == 77)return 'r';
	return ' ';
}

int main()
{
    srand(time(0));
    initMap();
    while(1){
        printMap();
        switch (direction())
        {
        case 'u':
            up();
            break;
        
        case 'l':
            left();
            break;
        case 'r':
            right();
            break;
        
        case 'd':
            down();
            break;
    
        default:
            break;
        }

        system("cls");
        
    }
    return 0;
}
