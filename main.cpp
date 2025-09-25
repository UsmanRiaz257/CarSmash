#include"graphics.h"
int main(int argc,char* argv[]){
    QApplication a(argc,argv);
    Cars c;
    c.show();
    return a.exec();
}





// #include <QApplication>
// #include <QLabel>
// #include<QWidget>
// #include<QHBoxLayout>
// #include<QPushButton>
// #include<QPainter>
// #include<QPen>
// #include<QBrush>
// class Mywidget:public QWidget{
//     protected:
//         void paintEvent(QPaintEvent *)override{
//             QPainter paint(this);
//             QPen pen(Qt::red,2);
//             int width=this->width();
//             int height=this->height();
//             //ROAD
//             paint.setPen(pen);
//             QBrush brush(Qt::gray,Qt::SolidPattern);
//             paint.setBrush(brush);
//             paint.drawRect(int(width*0.25),0,int(width*0.5),height);
//             // DOTTED LINES
//             QPen pen2(Qt::white,5);
//             pen2.setStyle(Qt::DotLine);
//             paint.setPen(pen2);
//             paint.drawLine(int(width*0.41),0,int(width*0.41),height);
//             paint.drawLine(int(width*0.57),0,int(width*0.57),height);
//             // CARS
//             QPen pen3(Qt::black,1);
//             paint.setPen(pen3);
//             QBrush Brush2(Qt::red);
//             paint.setBrush(Brush2);
//             paint.drawRect(int(width*0.45),int(height*0.8),35,70);
//         }
// };
// int main(int argc, char *argv[]){
//     QApplication app(argc, argv);
//     Mywidget w;
//     w.show();
//     return app.exec();
// }