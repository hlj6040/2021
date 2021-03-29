#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

#include <stdlib.h>
#include <time.h>

#define  MAPSize 4
using namespace std;
int MAP[MAPSize][MAPSize];
int   useCnt = MAPSize*MAPSize;
int  values[15] = {2,4,8,16,32,64,128,256,512,1024,2048};

bool gailv(){
    return  rand()%100 < 90;
}
void initMAP()
{
    int len = MAPSize*MAPSize;
    for(int i = 0; i < len; i++){
        MAP[i/MAPSize][i%MAPSize] = 0;
    }

    int  t1 = rand()%useCnt--;
    MAP[t1/MAPSize][t1%MAPSize] = values[gailv() ? 0:1];

    int t2 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i < t2; i++){
        index++;
        if(MAP[index/MAPSize][index%MAPSize]) i--;

    }
    MAP[index/MAPSize][index%MAPSize] = values[gailv() ? 0:1];
}

void  up()
{
    for(int i = 0; i < MAPSize; i++){
        int t = 0;
        for(int j = 0; j < MAPSize; j++){
            if(MAP[j][i]){
                MAP[t++][i] = MAP[j][i];
            }
        }
        for(int j = t; j < MAPSize; j++)
            MAP[j][i] = 0;

        for(int j = 0; j < t-1; j++){
            if(MAP[j][i] == MAP[j+1][i]){
                MAP[j][i] *= 2;
                for(int z = j+1; z < MAPSize-1 ; z++)
                    MAP[z][i] = MAP[z+1][i];
                MAP[MAPSize-1][i] = 0;
                useCnt++;
                t--;
            }
        }
    }
    int t1 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i <= t1; i++){
        index++;
        if(MAP[index/MAPSize][index%MAPSize])
            i--;
    }
    MAP[index/MAPSize][index%MAPSize] = values[gailv() ? 0:1];
}

void  down()
{
    for(int i = 0; i < MAPSize; i++){
        int t = MAPSize-1;
        for(int j = MAPSize-1; j >= 0; j--){
            if(MAP[j][i]){
                MAP[t--][i] = MAP[j][i];
            }
        }
        for(int j = t; j >= 0; j--)
            MAP[j][i] = 0;

        for(int j = MAPSize-1; j > t+1; j--){
            if(MAP[j][i] == MAP[j-1][i]){
                MAP[j][i] *= 2;
                for(int z = j-1; z > 1 ; z--)
                    MAP[z][i] = MAP[z-1][i];
                MAP[0][i] = 0;
                useCnt++;
                t++;
            }
        }
    }
    int t1 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i <= t1; i++){
        index++;
        if(MAP[index/MAPSize][index%MAPSize])
            i--;
    }
    MAP[index/MAPSize][index%MAPSize] = values[gailv() ? 0:1];
}

void  left()
{
    for(int i = 0; i < MAPSize; i++){
        int t = 0;
        for(int j = 0; j < MAPSize; j++){
            if(MAP[i][j]){
                MAP[i][t++] = MAP[i][j];
            }
        }
        for(int j = t; j < MAPSize; j++)
            MAP[i][j] = 0;

        for(int j = 0; j < t-1; j++){
            if(MAP[i][j] == MAP[i][j+1]){
                MAP[i][j] *= 2;
                for(int z = j+1; z < MAPSize-1 ; z++)
                    MAP[i][z] = MAP[i][z+1];
                MAP[i][MAPSize-1] = 0;
                useCnt++;
                t--;
            }
        }
    }
    int t1 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i <= t1; i++){
        index++;
        if(MAP[index/MAPSize][index%MAPSize])
            i--;
    }
    MAP[index/MAPSize][index%MAPSize] = values[gailv() ? 0:1];
}
void  right()
{
    for(int i = 0; i < MAPSize; i++){
        int t = MAPSize-1;
        for(int j = MAPSize-1; j >= 0; j--){
            if(MAP[i][j]){
                MAP[i][t--] = MAP[i][j];
            }
        }
        for(int j = t; j >= 0; j--)
            MAP[i][j] = 0;

        for(int j = MAPSize-1; j > t+1; j--){
            if(MAP[i][j] == MAP[i][j-1]){
                MAP[i][j] *= 2;
                for(int z = j-1; z > 1 ; z--)
                    MAP[i][z] = MAP[i][z-1];
                MAP[i][0] = 0;
                useCnt++;
                t++;
            }
        }
    }
    int t1 = rand()%useCnt--;
    int index = -1;
    for(int i = 0; i <= t1; i++){
        index++;
        if(MAP[index/MAPSize][index%MAPSize])
            i--;
    }
    MAP[index/MAPSize][index%MAPSize] = values[gailv() ? 0:1];
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int lenx = this->width()/4,
        leny = this->height()/4;
    image = QImage(800,800,QImage::Format_RGB32);
    QRgb backColor = qRgb(255,255,255);
    image.fill(backColor);
    initMAP();
    move();

}
void  MainWindow:: move()
{
    QImage image = QImage(200,200,QImage::Format_RGB32);
    QRgb backColor = qRgb(255,255,255);
    image.fill(backColor);
    image = initMap();
    QPainter painter(&image);
    QFont font("宋体", 10, QFont::Bold, true);
    painter.setPen(Qt::black);

    int k = 150;
    for(int i = 0; i < MAPSize; i++)
        for(int j = 0; j < MAPSize; j++){
            const QRect rectangle = QRect(i*k, j*k, i*k+k, j*k+k);
            QString str;
            painter.drawText(rectangle,Qt::AlignCenter,str.setNum(MAP[i][j]));
        }
    paint(image);
}
QImage MainWindow::initMap()
{
    int x = this->width(),
        y = this->height();

    QImage image = QImage(800,800,QImage::Format_RGB32);
    QRgb backColor = qRgb(255,255,255);
    image.fill(backColor);

    QPainter painter(&image);
    painter.setPen(Qt::black);
    int lenx = x/4, leny = y/4;
    for(int i = 1; i <= 3; i++){
        painter.drawLine(lenx*i,0,lenx*i,y);
        painter.drawLine(0,leny*i,y,leny*i);
    }
    return image;
}
void  MainWindow::paint(QImage image)
{
    this->image = image;
    update();
}
MainWindow::~MainWindow()
{
    delete ui;
}


void  MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,image);
}
