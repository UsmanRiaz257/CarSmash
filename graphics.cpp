#include<graphics.h>

QPointF Cars::metertopixel(double x, double y){
    transformation();
    return QPointF (offsetx+(x*scale),offsety+(y*scale));
}
void Cars::transformation(){
    double XRatio = w/Worldx ;
    double YRatio  =  h/Worldy;
    if (XRatio>YRatio){
        offsetx = (XRatio-YRatio)*(Worldx)/2;
        scale =YRatio; 
        offsety=0.0;
    }
    else{
        offsety = (YRatio-XRatio)*(Worldy)/2;
        scale = XRatio;
        offsetx = 0.0 ;
    }
}
void Cars::paintEvent(QPaintEvent *) {
    w=width();
    h=height();
    QPainter painter(this);
    collisions();
    drawRoad(& painter);
    drawCars(& painter);
    drawTank(& painter);
    drawBullet(& painter);
}
void Cars::drawRoad(QPainter *painter){
    QPen pen(Qt::red,2);
    painter->setPen(pen);
    QBrush brush(Qt::gray,Qt::SolidPattern);
    painter->setBrush(brush);
    QPointF pos1 = metertopixel( Worldx*0.3,0.0);
    QPointF pos2 = metertopixel( Worldx*0.7, Worldy);
    painter->drawRect(QRectF(pos1, pos2));
    QPen pen2(Qt::white,5);
    pen2.setStyle(Qt::DotLine);
    painter->setPen(pen2);
    QPointF pos3 = metertopixel(Worldx*0.43,0);
    QPointF pos4 = metertopixel( Worldx*0.43,Worldy);
    painter->drawLine(QLineF(pos3,pos4));
    QPointF pos5 = metertopixel(Worldx*0.57,0);
    QPointF pos6 = metertopixel( Worldx*0.57,Worldy);
    painter->drawLine(QLineF(pos5,pos6));
}
void Cars::drawCars(QPainter *painter){
    QPen pen3(Qt::black,1);
    painter->setPen(pen3);
    QBrush Brush2(Qt::red);
    painter->setBrush(Brush2);
    QPointF pos1 = metertopixel(Worldx*CarsPos[0][0],Worldy*(CarsPos[0][1]));
    QPointF pos2 = metertopixel(Worldx*(CarsPos[0][0]+carWidth),Worldy*(CarsPos[0][1]+carHeight));
    painter->drawRect(QRectF(pos1, pos2));
    QPointF pos3 = metertopixel(Worldx*CarsPos[1][0],Worldy*(CarsPos[1][1]));
    QPointF pos4 = metertopixel(Worldx*(CarsPos[1][0]+carWidth),Worldy*(CarsPos[1][1]+carHeight));
    painter->drawRect(QRectF(pos3, pos4));
    QPointF pos5 = metertopixel(Worldx*CarsPos[2][0],Worldy*(CarsPos[2][1]));
    QPointF pos6 = metertopixel(Worldx*(CarsPos[2][0]+carWidth),Worldy*(CarsPos[2][1]+carHeight));
    painter->drawRect(QRectF(pos5, pos6));
}
Cars::Cars(QWidget *parent):QWidget(parent){
    QTimer *timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this ,[&](){
        if (isGameOver==true){
            timer->stop();
        }
        CarsPos[0][1]+=speed;
        CarsPos[1][1]+=speed;
        CarsPos[2][1]+=speed;
        speed+=0.00001;
        update();
        for (int i=0;i<BulletsPos.size();i++){
          BulletsPos[i][1]-=0.03;
        }
        if (CarsPos[0][1]+0.05>=1){
            newCarPos(0);
        }
        if (CarsPos[1][1]+0.05>=1){
            newCarPos(1);
        }
        if (CarsPos[2][1]+0.05>=1){
            newCarPos(2);
        }        

    });
    timer->start(30);
}

double Cars::randomNumber(double x,double y){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.3, 0.66);
    return dist(gen);   
}


void Cars::drawTank(QPainter *painter){
    QBrush Brush2(Qt::blue);
    painter->setBrush(Brush2);
    QPointF pos1 = metertopixel(Worldx*TankXPosition,Worldy*(TankYPosition));
    QPointF pos2 = metertopixel(Worldx*(TankXPosition+0.04),Worldy*(TankYPosition+carHeight));
    painter->drawRect(QRectF(pos1, pos2));
}

void Cars::drawBullet(QPainter *painter){
    painter->drawText(w-100,10,QString("Bullet:%1").arg(ammo));
    painter->drawText(w-100,30,QString("Score:%1").arg(Score));
    QPen pen(Qt::black);  
    painter->setPen(pen);
    QBrush Brush(Qt::yellow);
    painter->setBrush(Brush);
    for (int i=0;i<BulletsPos.size();i++){
        QPointF pos1 = metertopixel(Worldx*(BulletsPos[i][0]),Worldy*(BulletsPos[i][1]));
        QPointF pos2 = metertopixel(Worldx*(BulletsPos[i][0]+0.01),Worldy *(BulletsPos[i][1]+0.01));
        painter->drawRect(QRectF(pos1,pos2));
    }
}
void Cars::collisions() {
    // Car with tank
    for (int i = 0; i < CarsPos.size(); i++) {
        bool xOverlap = std::abs(TankXPosition - CarsPos[i][0]) <= carWidth;
        bool yOverlap = std::abs(TankYPosition - CarsPos[i][1]) <= carHeight;

        if (xOverlap && yOverlap) {
            isGameOver = true;
            return;
        }
    }

    // Car with bullets
    for (int b = 0; b < BulletsPos.size(); b++) {
        double bx = BulletsPos[b][0];
        double by = BulletsPos[b][1];

        for (int i = 0; i < CarsPos.size(); i++) {
            bool hit = (bx >= CarsPos[i][0] and bx <= CarsPos[i][0] + carWidth and  by >= CarsPos[i][1] and by <= CarsPos[i][1] + 0.105);

            if (hit) {
                Score+=1;
                newCarPos(i);
                BulletsPos.erase(BulletsPos.begin() + b);
                b-=1;
                break; 
            }
        }
    }
}

void Cars::keyPressEvent(QKeyEvent *event){
    if (event->key()==Qt::Key_Left){
        TankXPosition=std::max(0.3,TankXPosition-0.01);
    }
    if (event->key()==Qt::Key_Right){
        TankXPosition=std::min(0.66,TankXPosition+0.01);
    }
    if (event->key()==Qt::Key_Space){
        if (ammo>0){
            ammo--;
        BulletsPos.push_back({TankXPosition+0.0175,TankYPosition});}
   }
    if (event->key()==Qt::Key_R){
        QTimer::singleShot(2000, this, [this]() { 
        ammo=max_ammo;
        });
    }

    update();
}

void Cars::newCarPos(int index){
    bool flag =false;
    while (flag==false){
        int count=0;
        CarsPos[index][0]=randomNumber(0.3,0.66);
        CarsPos[index][1]=0.0;
        for (int i=0;i<CarsPos.size();i++){
            if (i==index){
                continue;
            }
            if (abs(CarsPos[index][0]-CarsPos[i][0])<=carWidth and std::abs(CarsPos[index][1]-CarsPos[i][1])<=carHeight){
                count+=1;
            }

        }
        if (count==0){
            flag=true;
        }
}
}