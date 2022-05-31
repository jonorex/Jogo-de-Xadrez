#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QWidget>
#include "cooordenada.h"
#include "tropa.h"
#include "casa.h"
#include <QVector>

class Tabuleiro : public QWidget
{
    Q_OBJECT
public:
     Tabuleiro(QWidget *parent = nullptr);
     Tabuleiro(QVector<QString> v);
     void abrirArquivo(QVector<QString> v);
     QString getSave();//metodo que cria o arquivo
     void adicionarTropa(QPoint p, QString tipo);
     void excluir(QPoint p);

protected:


    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
signals:

private:
    QPoint lastPoint;
    int id;
    Casa *casas[8][8];
    Tropa *tropas[8][8];
    QImage img;
    bool play;//não utilizado
    int click;
    Tropa *lastTropa;//utilizado para marcar a ultima peca selecionada

    Casa *lastCasa;


    void resizeImage(QImage *image, const QSize &newSize, QPoint p);



    int getClick();

    void setClick();

    void desmarcarCasas();

    void swap(int x, int y);


};

#endif // TABULEIRO_H
