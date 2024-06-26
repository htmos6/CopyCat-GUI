#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QQueue>
#include <QPair>
#include <QTimer>
#include <QColor>
#include <QtMath>
#include <QRgb>
#include <QPen>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QMessageBox>

#include "picoconnection.h"

class QPaintEvent;
class QMouseEvent;
class DrawWidget : public QWidget
{
    Q_OBJECT
    public:
        explicit DrawWidget(QWidget *parent = 0);
        ~DrawWidget();

        void drawPixel(QPoint pt, bool is_echoed = false);
        void printPoints();
        //unsigned int pixels[1920][1080];

    public slots:
        QColor drawColor();
        void clear();
        void setDrawColor(QColor color);
        void connectToPico();
        void drawPath(int pathID);

    signals:
    protected:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
        void mouseMoveEvent(QMouseEvent *);
        void resizeEvent(QResizeEvent *);

        void resetPen();
        void customizePen(QPen& currentPen, QRgb value, int width, QString colorName);
        void calculateAngleDistance(QPoint prePt10, QPoint curPt10);
        bool distCalculator(QPoint prePt10, QPoint curPt10);
        // void drawTriangle(QPoint previousTrianglePt, QPoint currentTrianglePt, int angle, int length);
        void autoPath(int width, int height, int automationCode);

        void enableClick();

    private:
        QPixmap m_pixmap;
        QImage m_canvas;
        QColor m_drawColor;
        QPen pen;

        QPoint previousPt;
        QPoint prePt10;
        QPoint curPt10;

        qreal bisectorVectorAngle = 0;
        qreal bisectorVectorLength;

        QQueue<QPair<int, int>> angleDistanceQueue;
        //QQueue<QPair<int, int>> angleDistanceQueueAuto;
        QPair<int, int> angleDistancePair;
        QPair<int, int> angleDistancePairAuto;

        QTimer clickTimer;
        int points = 0;
        PicoConnection* pico = nullptr;
        QQueue<QPair<int, int>> autoPathQ;
};

#endif // DRAWWIDGET_H
