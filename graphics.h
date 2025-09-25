#ifndef GRAPHICS_H
#define GRAPHICS_H
#include<QWidget>
#include<iostream>
#include<QPainter>
#include<QPaintEvent>
#include<QPen>
#include<QBrush>
#include<vector>
#include<QTimer>
#include<QApplication>
#include<QKeyEvent>
#include<QRandomGenerator>
class Cars : public QWidget {
    Q_OBJECT  
private:
    static constexpr double Worldx = 13.0;
    static constexpr double Worldy = 9.0;
    int w = width();
    int h = height();
    double  carWidth=0.04;
    double carHeight=0.1;
    std::vector<std::vector<double>> CarsPos={{0.53,0.0},{0.66,0.5},{0.35,0.25}};
    double TankXPosition=0.48;
    double TankYPosition=0.8;
    bool isGameOver=false;
    double offsetx, offsety, scale;
    double speed=0.01;
    int max_ammo=10;
    int Score=0;
    int ammo=10;
    QTimer *timer;   
    std::vector<std::vector<double>>BulletsPos;
       
public:
    Cars(QWidget *parent = nullptr);   
    
    QPointF metertopixel(double x,double y);
    void transformation();
    void drawRoad(QPainter *painter);
    void drawCars(QPainter *painter);
    void drawTank(QPainter *painter);
    void collisions();
    void newCarPos(int index);

    void drawBullet(QPainter *painter);
    double randomNumber(double x ,double y);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *) override;
};
#endif