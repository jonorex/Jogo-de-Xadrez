#include "tabuleiro.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <QPen>
#include <QBrush>
#include <QVector>
#include "tropa.h"

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

Tabuleiro::Tabuleiro(QWidget *parent) : QWidget(parent)
{

    setAttribute(Qt::WA_StaticContents);

    for(int i = 0; i < 8; i++){     //cria tabuleiro
            for(int j = 0; j < 8; j++){
                QRect r(i*50,j*50,50,50); //com tamanho 50x50 de cada casa
                casas[i][j] = new Casa(r, i, j);
                }
    }

          update();
}



void Tabuleiro::abrirArquivo(QVector<QString> v){
    int x, y;
    for(int i = 0; i < v.size(); i=i+3){
        x = v[i+1].toInt();
        y = v[i+2].toInt();

        adicionarTropa(QPoint(x,y), v[i]);
    }
    update();
}

QString Tabuleiro::getSave(){ //metódo que cria a string salva no arquivo
    QString save;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(tropas[i][j]!= NULL){
                save += tropas[i][j]->getType() + "\n"+QString::number(i)+"\n"+QString::number(j)+"\n";

            }
        }
    }
    return save;
}

void Tabuleiro::desmarcarCasas(){ // utilizado para desmarcar todas as casa selecinadas após jogodas
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            casas[i][j]->unSelect();

        }
    }
}

int Tabuleiro::getClick(){ //utilizado para definir o primeiro e o segundo clique de uma jofas
    return click;
}

void Tabuleiro::setClick(){
    if(click == 0){
        click = 1;
    }else if(click == 1){
        click = 2;
    }else{
        click = 0;
    }
}

void Tabuleiro::adicionarTropa(QPoint p, QString tipo){//adicona uma tropa no tabuleirp
    Tropa *t;
    QString str;
    if(p.x()>7 or p.y()>7 or p.x()<0 or p.y()<0){//caso o usuário escolha um local fora do tabuleiro
        throw 3;
    }
    if(tipo == "torre"){ //verifica o tipo da peça

         t = new Torre();
         str = Torre::getStr();
    }else if(tipo == "bispo"){
         t = new Bispo();
         str = Bispo::getStr();

    }
    else if(tipo == "rainha"){
        t = new Rainha();
        str = "C:/Users/joaov/Documents/xadreizinho/xadrezinho_imagens/dama.png";
    }
    else{
        return;
    }

    t->setCasa(casas[p.x()][p.y()]);//marca a casa onde está a peca
    casas[p.x()][p.y()]->setOcupado(true);


    QImage loadedImage;//roda a imagem

    if (!loadedImage.load(str)){
        qDebug() << "Imagem não Abriu";
        throw 4;
    }
    else{
        qDebug() << "Abriu";
    }
    QSize newSize = loadedImage.size();
    resizeImage(&loadedImage, newSize, p);
    t->setImage(loadedImage);
    tropas[p.x()][p.y()] = t;
}

void Tabuleiro::resizeImage(QImage *image, const QSize &newSize, QPoint p)
//! [19] //! [20]
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(p, *image);
    *image = newImage;
}



void Tabuleiro::swap(int x, int y){
    tropas[lastTropa->getCasa()->X()][lastTropa->getCasa()->Y()] = NULL;
    lastTropa->getCasa()->setOcupado(false);
    lastTropa->setCasa(casas[x][y]);
    tropas[x][y] = lastTropa;
    this->desmarcarCasas();
    update();
}

void Tabuleiro::excluir(QPoint p){
    if(tropas[p.x()][p.y()] == NULL){
        throw(2);
    }
      tropas[p.x()][p.y()]->getCasa()->setOcupado(false);
      tropas[p.x()][p.y()] = NULL;
}

void Tabuleiro::mousePressEvent(QMouseEvent *event)
//! [11] //! [12]
{
    if (event->button() == Qt::LeftButton) {
        //this->desmarcarCasas();
        //this->setClick();

        lastPoint = event->pos();
        int x = lastPoint.x()/50;
        int y = lastPoint.y()/50;
        if(casas[x][y]->getSelect() and casas[x][y]!=lastTropa->getCasa()){
            swap(x,y);
            return;
        }
        if(lastCasa != casas[x][y]){
            this->desmarcarCasas();
        }
        lastCasa = casas[x][y];

        if(tropas[x][y]!=NULL){
            lastTropa = tropas[x][y];
            //tropas[x][y]->setClick();
            QString s = tropas[x][y]->selectCasas(QPoint(x,y), casas);
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){

                    if(s[j*8+i] == '1'){
                            casas[i][j]->setSelect();
                            if(!casas[i][j]->getSelect() and this->getClick() == 2)
                                casas[i][j]->setSelect();
                    }else {
                         casas[i][j]->unSelect();
                    }
                 }
            }
            }

        }
        //qDebug() << "Teste" << this->id << x << y;
        update();
    }




void Tabuleiro::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for(int i = 0; i < 8;i++){
        for(int j = 0; j<8;j++){
            if(casas[i][j]->getSelect()){//verica se a casa está selecionada
                QBrush cor(Qt::blue);
                painter.setBrush(cor);
            }else{// se não tiver coloca a sua cor original
                QBrush cor;
                painter.setBrush(casas[i][j]->getColor());
            }
            painter.drawRect(casas[i][j]->getR());
            if(tropas[i][j]!=NULL){ //veridica se há uma peça na coordenada
                if(tropas[i][j]->getClick()){
                    QBrush cor(Qt::yellow);//não tá usando
                    painter.setBrush(cor);
                    painter.drawRect(casas[i][j]->getR());
                }
                painter.drawImage(tropas[i][j]->getCasa()->X()*50,tropas[i][j]->getCasa()->Y()*50,tropas[i][j]->getImage());//desenha a imagem da peca na posição onde ela está marcada
            }
        }
    }
    //painter.drawImage(50,50,img);
}


