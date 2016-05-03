#include "StdAfx.h"
#include "Osama.h"
#include "glwidget.h"
#include<iostream>

Osama::Osama(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.horizontalScrollBar->setRange(0, GLWidget::MATRIX_SIZE * GLWidget::MATRIX_SIZE);
}

Osama::~Osama()
{

}

void Osama::on_pushButton_3_clicked()
{

}



void Osama::on_pushButton_pressed()
{

}

void Osama::on_lineEdit_editingFinished()
{
    QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);
}


void Osama::on_abc_clicked()
{

}


void Osama::on_lineEdit_2_editingFinished()
{
    QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);

}

void Osama::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);
}

void Osama::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{
    QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);
}

void Osama::on_lineEdit_textChanged(const QString &arg1)
{
    QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);
}

void Osama::on_lineEdit_returnPressed()
{
    QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);
}

void Osama::on_lineEdit_textEdited(const QString &arg1)
{ QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);

}

void Osama::on_lineEdit_2_returnPressed()
{
    QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);
}

void Osama::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);
}

void Osama::on_lineEdit_2_textEdited(const QString &arg1)
{ QString l=ui.lineEdit->text();
    size_t x=l.toInt();
    xp=x;
    QString i=ui.lineEdit_2->text();
    size_t y=i.toInt();
    yp=y;
    GLWidget a;
    a.setPoints(xp,yp);

}
