#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QColor* curColor;
    bool isChanging;

    void rgb(QColor);
    void xyz(QColor);
    void hsv(QColor);
    void updateAllWithoutRGB();
    void updateAllWithoutHSV();
    void updateAllWithoutXYZ();
    void updateAll();
    double F1(double);
    double F2(double);


public slots:
    void changeRGB();
    void changeHSV();
    void changeXYZ();
    void useDialog();
};
#endif // MAINWINDOW_H
