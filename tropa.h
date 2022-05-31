#ifndef TROPA_H
#define TROPA_H

#include <QVector>
#include <QPoint>
#include <QImage>
#include "casa.h"

class Casa;

class Tropa{
    QVector<QVector<bool>> move;
    QPoint position;
    QImage image;
    Casa *c;
    bool click;

 public:
    Tropa();
    QImage getImage();
    void setImage(QImage img);
    QVector<QVector<bool>> getMove();
    void setMove(QVector<QVector<bool>> m);
    void setPosition(QPoint p);
    void setClick(){
        if(click) click = false;
        else{click = true;}
    }

    bool getClick(){return click;}
    void setCasa(Casa *casa);
    Casa *getCasa(){
        return c;
    }
    void mover(Casa casa);
    virtual QString selectCasas(QPoint p, Casa *casa[8][8])=0;
    virtual QString getType()=0;
};

class Torre : public Tropa{
    static QString str;
    QVector<QVector<bool>> move;
public:
    Torre():Tropa(){
    };
    QString selectCasas(QPoint p, Casa *casas[8][8]);

    static QString getStr();
    QString getType(){
        return "torre";
    }
};

class Bispo : public Tropa{
    static QString str;

public:
    Bispo():Tropa(){}
    QString selectCasas(QPoint p, Casa *casas[8][8]);
    static QString getStr();
    QString getType(){
        return "bispo";
    }

};

class Rainha : public Tropa{
    static QString str;
public:
    Rainha():Tropa(){}
    QString selectCasas(QPoint p, Casa *casas[8][8]);
    QString getStr();
    QString getType(){
        return "rainha";
    }

};



#endif // TROPA_H
