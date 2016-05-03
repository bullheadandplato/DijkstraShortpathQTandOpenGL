#pragma once
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include "ui_glwidget.h"
#include "OsamaDistance.h"
size_t static xp;
size_t static  yp;
class GLWidget : public QGLWidget
{
public:
    void setPoints(size_t x, size_t y);

    void paintGL();
    void initializeGL();
    GLWidget(QWidget *parent = 0);

    ~GLWidget();

    static const size_t MATRIX_SIZE = OsamaDistance::MATRIX_SIZE;

    Q_OBJECT

	void resizeGL(int w, int h);

	void PaintQuad(size_t x, size_t y) const;
	void PaintCube(size_t x, size_t y) const;
    void ShowPath(size_t x, size_t y);
	void ShowWalls() const;
    void fix();




private:
	Ui::GLWidget ui;
	size_t mWallsNumber;
    OsamaDistance mCalcDistance;


public slots:
	void SetWallsNumber(int number);
	void GenerateWalls();
	void FindPath();
    void setPos();
};

#endif // GLWIDGET_H
