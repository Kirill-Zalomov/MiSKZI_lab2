#include "controller.h"
#include "ui_main_window.h"


Controller::Controller(QWidget *parent) : QMainWindow(parent) {
    this->ui = new Ui::Controller();
    this->ui->setupUi(this);
}


Controller::~Controller() {
    delete this->ui;
}


void Controller::on_buttonOpenFile_clicked() {

}

