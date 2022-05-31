#ifndef CASA_H
#define CASA_H



#include "tropa.h"
#include <QRect>
#include <QPoint>
#include <QColor>


class Casa{
    static bool lastColor;
    QRect r;
    QColor color;
    bool select;
    bool ocupado;
    int x;
    int y;

public:
    Casa(QRect r, int X, int Y);

    QRect getR(){
        return r;
    }

    bool getSelect(){return select;}
    void setOcupado(bool b){ocupado=b;}
    bool getOcupado(){return ocupado;}
    void setSelect(){
        if(select)
            select=false;
        else
            select=true;
    }
    void unSelect(){
        select = false;
    }

    void seleciona(){
        select = true;
    }

    int X(){
        return x;
    }
    int Y(){
        return y;
    }
    QColor getColor(){return color;}

    //static bool getStr();

};

#endif // CASA_H
