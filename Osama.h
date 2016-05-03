#pragma once
#ifndef Osama_H
#define Osama_H

#include "ui_osama.h"

class Osama : public QMainWindow
{
	Q_OBJECT

public:
    Osama(QWidget *parent = 0, Qt::WindowFlags flags = 0);

    ~Osama();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_pressed();

    void on_lineEdit_editingFinished();

    void on_abc_clicked();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_returnPressed();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_returnPressed();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

private:
    Ui::OsamaClass ui;
};

#endif // Osama_H
