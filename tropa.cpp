#include "tropa.h"
#include <QDebug>
#include <casa.h>


class Casa;

QString Torre::str = "C:/Users/joaov/Documents/xadreizinho/xadrezinho_imagens/torre.png";//localização das imagens
QString Bispo::str = "C:/Users/joaov/Documents/xadreizinho/xadrezinho_imagens/bispo.png";

Tropa::Tropa(){
    click = false;  // verica se a tropa tá clicada
}

QVector<QVector<bool>> Tropa::getMove(){
    return move;
}
void Tropa::setMove(QVector<QVector<bool>> m){//não utilizado
    move = m;
}
void Tropa::setPosition(QPoint p){
    position = p;
}

QImage Tropa::getImage(){
    return image;
}
void Tropa::setImage(QImage img){
    image = img;
}

void Tropa::setCasa(Casa *casa){
     // c->setOcupado(false);
    c = casa;
    c->setOcupado(true);
}



//QPoint Torre::*selectCasas(int x, int y){

//}
QString Torre::getStr(){
    return str;
}
//movimentos genéricos
void andaParaEsquerda(QString &s, int x, int y, Casa *(*casas)[8]){
    int i = 0;
    //marcar para esquerda
    //confere se tem alguem do lado
    while(i!=x+1){
        s[y*8+x-i]='1';
       if(casas[x-i][y]->getOcupado() && i!=0){ //quando encontrado uma casa onde contém outra peca o metodo é pausado
           break;
       }
       //qDebug() << "Movimento: "<< y*8+x-i;
       i++;
    }
}

void andaParaDireita(QString &s, int x, int y, Casa *(*casas)[8]){
    int i = x;
    int b =0;
    while(i<8){
       s[y*8+i] = '1';
       if(casas[x+b][y]->getOcupado() && b!=0){
           break;
       }
       i++;
       b++;
    }
}

void andaParaCima(QString &s, int x, int y, Casa *(*casas)[8]){
    int i = y;
    int b = 0;
    //marcar para esquerda
    //confere se tem alguem do lado
    while(i>-1){
        s[i*8+x]='1';
        //qDebug() << "Movimento para cima: "<< i*8+x;
       if(casas[x][y-b]->getOcupado() && b!=0)
           break;
     i--;
     b++;
    }
}
void andaParaBaixo(QString &s, int x, int y, Casa *(*casas)[8]){
    int i = y;
    int b = 0;
    while(i<8){
        s[i*8+x]='1';
       // qDebug() << "Movimento para cima: "<< i*8+x;
       if(casas[x][y+b]->getOcupado() && b!=0)
           break;
     i++;
     b++;
    }
}

void sobeEsquerda(QString &s, int x, int y, Casa *(*casas)[8]){
    int i = y;
    int b = 0;
    while(i>-1){
        if(x-b > -1){
        s[i*8-b+x]='1';
        //qDebug() << "Movimento para cima: "<< i*8+x;
       if(casas[x-b][y-b]->getOcupado() && b!=0)
           break;

    }
        i--;
        b++;
   }
}
void desceDireita(QString &s, int x, int y, Casa *(*casas)[8]){
    int i = y;
    int b = 0;

    while(i<8){
        if(x+b < 8){
        s[i*8+b+x]='1';
        //c=(i*8)+b;
      //  qDebug() << "Movimeto bispo "<< i*8+b+x;

       if(casas[x+b][y+b]->getOcupado() && b!=0)
           break;

     }
        i++;
        b++;
    }
}
void desceEsquerda(QString &s, int x, int y, Casa *(*casas)[8]){
    int i = y;
    int b = 0;
    int n = y*8+x;
    while(i < 8){
        if(x-b > 0){
        n+=7;
        s[n]='1';
        //c=(i*8)+b;
        qDebug() << "Movimeto bispo "<< i*8+b+x;

       if(casas[x-b][y-b]->getOcupado() && b!=0)
           break;

     }
        i++;
        b++;
    }
}
void sobeDireita(QString &s, int x, int y, Casa *(*casas)[8]){
    //  qDebug() << "ENTROU";
      int i = x;
      int b = 0;
      int n = y*8+x;
    //  qDebug() << x;

      while(x+b<7 and y-b>0){
          if(y-b > 0 and x+b <7){
              if(casas[x+b][y-b]->getOcupado() && b!=0)
                  break;
              n-=7;
          s[n]='1';
          //qDebug() << "Movimento para cima: "<< i*8+x;


      }
          i--;
          b++;
          }
}



QString Torre::selectCasas(QPoint p, Casa *(*casas)[8]){//movimento da torre é usado uma string em que na casa que contém 1 a peça pode se mover e aque contém zero não pode
    QString s = "000000000000000000000000000000000000000000000000000000000000000";
    int x = p.x();
    int y = p.y();
    //anda para esquerda
    if(x>0){
        andaParaEsquerda(s,x,y,casas);

        }
    //anda para direita
     if(x<8){
        andaParaDireita(s,x,y,casas);
     }
    //anda para cima
    if(y>0){
        andaParaCima(s,x,y,casas);
     }
    //anda para baixo
    if(y<7){
        andaParaBaixo(s,x,y,casas);
      }

    return s;
}



QString Bispo::getStr(){ //retorna endereço da imagem
    return str;
}



QString Bispo::selectCasas(QPoint p, Casa *(*casas)[8]){//movimento da bispo é usado uma string em que na casa que contém 1 a peça pode se mover e aque contém zero não pode
    QString s = "000000000000000000000000000000000000000000000000000000000000000";
    int x = p.x();
    int y = p.y();

    //subir
    if(y>0 and x>0){
        sobeEsquerda(s,x,y,casas);
     }
    //desce direita
    if(y<8 and x<7){
        desceDireita(s,x,y,casas);
    }
    //desceEsquerda
    if(y>0 and x>0){
        desceEsquerda(s,x,y,casas);
    }
    //sobe direita
    if(y>0 and x < 7){
        sobeDireita(s,x,y,casas);
     }


    return s;
}




QString Rainha::selectCasas(QPoint p, Casa *(*casas)[8]){
    QString s = "000000000000000000000000000000000000000000000000000000000000000";
    int x = p.x();
    int y = p.y();

    //anda para esquerda
    if(x>0){
        andaParaEsquerda(s,x,y,casas);

        }
    //anda para direita
     if(x<8){
        andaParaDireita(s,x,y,casas);
     }
    //anda para cima
    if(y>0){
        andaParaCima(s,x,y,casas);
     }
    //anda para baixo
    if(y<7){
        andaParaBaixo(s,x,y,casas);
      }

    //subir
    if(y>0 and x>0){
        sobeEsquerda(s,x,y,casas);
     }
    //desce direita
    if(y<8 and x<7){
        desceDireita(s,x,y,casas);
    }
    //desceEsquerda
    if(y>0 and x>0){
        desceEsquerda(s,x,y,casas);
    }
    //sobe direita
    if(y>0 and x < 7){
        sobeDireita(s,x,y,casas);
     }

    return s;
}

