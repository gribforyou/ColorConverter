#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("RGB<->HSV<->XYZ");
    this->setFixedSize(size());

    curColor = new QColor(Qt::black);
    isChanging = false;

    ui->showColor->setAutoFillBackground(true);

    ui->red->setRange(0, 255);
    ui->green->setRange(0, 255);
    ui->blue->setRange(0, 255);

    ui->hue->setRange(0, 359);
    ui->saturation->setRange(0, 255);
    ui->value->setRange(0, 255);

    ui->x->setRange(0, 100);
    ui->y->setRange(0, 100);
    ui->z->setRange(0, 100);

    ui->errorLabel->setText("");
    ui->errorLabel->update();

    connect(ui->showDialog, SIGNAL(clicked()), this, SLOT(useDialog()));

    connect(ui->red, SIGNAL(valueChanged(int)), this, SLOT(changeRGB()));
    connect(ui->green, SIGNAL(valueChanged(int)), this, SLOT(changeRGB()));
    connect(ui->blue, SIGNAL(valueChanged(int)), this, SLOT(changeRGB()));

    connect(ui->hue, SIGNAL(valueChanged(int)), this, SLOT(changeHSV()));
    connect(ui->saturation, SIGNAL(valueChanged(int)), this, SLOT(changeHSV()));
    connect(ui->value, SIGNAL(valueChanged(int)), this, SLOT(changeHSV()));

    connect(ui->x, SIGNAL(valueChanged(int)), this, SLOT(changeXYZ()));
    connect(ui->y, SIGNAL(valueChanged(int)), this, SLOT(changeXYZ()));
    connect(ui->z, SIGNAL(valueChanged(int)), this, SLOT(changeXYZ()));

    updateAll();
}

void MainWindow::rgb(QColor color){
    ui->red->setValue(color.red());
    ui->green->setValue(color.green());
    ui->blue->setValue(color.blue());
}

void MainWindow::xyz(QColor color){
    double red = (double)color.red();
    double green = (double)color.green();
    double blue = (double)color.blue();

    red = F1(red/(double)255)*100;
    green = F1(green/(double)255)*100;
    blue = F1(blue/(double)255)*100;

    double x = red*0.412453 + green*0.357580 + blue*0.180423;
    double y = red*0.212671 + green*0.715160 + blue*0.072169;
    double z = red*0.019334 + green*0.119193 + blue*0.950227;

    if(x>100){
        x = 100;
        ui->errorLabel->setText("Conversation with errors!");
        ui->errorLabel->update();
    }

    if(y>100){
        y = 100;
        ui->errorLabel->setText("Conversation with errors!");
        ui->errorLabel->update();
    }

    if(z>100){
        z = 100;
        ui->errorLabel->setText("Conversation with errors!");
        ui->errorLabel->update();
    }

    ui->x->setValue(x);
    ui->y->setValue(y);
    ui->z->setValue(z);
}

double MainWindow::F1(double c){
    if(c>=0.04045){
        return pow(((c+0.055)/1.055), 2.4);
    }
    else{
        return c/12.92;
    }
}

void MainWindow::hsv(QColor color){
    ui->hue->setValue(color.hue());
    ui->saturation->setValue(color.saturation());
    ui->value->setValue(color.value());
}



void MainWindow::changeRGB(){
    if(!isChanging){
        ui->errorLabel->setText("");
        isChanging = true;
        curColor->setRgb(ui->red->value(), ui->green->value(), ui->blue->value());
        updateAllWithoutRGB();
        isChanging = false;
    }

}

void MainWindow::changeHSV()
{
    if(!isChanging){
        ui->errorLabel->setText("");
        isChanging = true;
        curColor->setHsv(ui->hue->value(), ui->saturation->value(), ui->value->value());
        updateAllWithoutHSV();
        isChanging = false;
    }
}

void MainWindow::changeXYZ()
{
    if(!isChanging){
        ui->errorLabel->setText("");
        isChanging = true;

        double x = (double)(ui->x->value())/(double)100;
        double y = (double)(ui->y->value())/(double)100;
        double z = (double)(ui->z->value())/(double)100;

        double Rn = x*3.2406 + y*(-1.5372) + z*(-0.4986);
        double Gn = x*(-0.9689) + y*1.8758 + z*0.0415;
        double Bn = x*0.0557 + y*(-0.2040) + z*1.0570;

        Rn = F2(Rn)*(double)255;
        Gn = F2(Gn)*(double)255;
        Bn = F2(Bn)*(double)255;

        if(Rn<0 || Rn>255 || Gn<0 || Gn>255 ||Bn<0 || Bn>255 ){
            ui->errorLabel->setText("Conversation with errors!");
            ui->errorLabel->update();
        }

        if((int)Rn>255) Rn = 255;
        if((int)Rn<0) Rn = 0;

        if((int)Gn>255) Gn = 255;
        if((int)Gn<0) Gn = 0;

        if((int)Bn>255) Bn = 255;
        if((int)Bn<0) Bn = 0;

        curColor->setRed(Rn);
        curColor->setGreen(Gn);
        curColor->setBlue(Bn);

        updateAllWithoutXYZ();
        isChanging = false;
    }
}

 double MainWindow::F2(double c){
    if(c>=0.0031308){
        return 1.055*pow(c, (1/2.4)) - 0.055;
    }
    else{
        return 12.92*c;
    }
}



void MainWindow::useDialog()
{
    isChanging = true;
    QColorDialog* clrDlg = new QColorDialog();
    clrDlg->setCurrentColor(*curColor);
    QColor color = clrDlg->getColor();
    while(!color.isValid()){
        color = clrDlg->getColor();
        clrDlg->setCurrentColor(*curColor);
    }
    curColor->setRgb(color.rgb());
    delete clrDlg;
    updateAll();
    ui->showColor->show();
    isChanging = false;
}

void MainWindow::updateAllWithoutRGB()
{
    ui->errorLabel->setText("");
    ui->errorLabel->update();

    hsv(*curColor);
    xyz(*curColor);

    QPalette pal = ui->showColor->palette();
    pal.setColor(QPalette::Window, *curColor);
    ui->showColor->setPalette(pal);
    ui->showColor->update();
}

void MainWindow::updateAllWithoutHSV()
{
    ui->errorLabel->update();

    rgb(*curColor);
    xyz(*curColor);

    QPalette pal = ui->showColor->palette();
    pal.setColor(QPalette::Window, *curColor);
    ui->showColor->setPalette(pal);
    ui->showColor->update();
}

void MainWindow::updateAllWithoutXYZ()
{
    ui->errorLabel->update();

    hsv(*curColor);
    rgb(*curColor);

    QPalette pal = ui->showColor->palette();
    pal.setColor(QPalette::Window, *curColor);
    ui->showColor->setPalette(pal);
    ui->showColor->update();
}

void MainWindow::updateAll()
{
    ui->errorLabel->update();

    rgb(*curColor);
    hsv(*curColor);
    xyz(*curColor);

    QPalette pal = ui->showColor->palette();
    pal.setColor(QPalette::Window, *curColor);
    ui->showColor->setPalette(pal);
    ui->showColor->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

