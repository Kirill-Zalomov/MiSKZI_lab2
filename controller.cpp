#include "controller.h"
#include "ui_main_window.h"


Controller::Controller(QWidget *parent) : QMainWindow(parent) {
    this->ui = new Ui::Controller();
    this->ui->setupUi(this);
    this->moveWindowToCenterOfDisplay();
}


Controller::~Controller() {
    delete this->ui;
}


void Controller::moveWindowToCenterOfDisplay() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rect = screen->geometry();
    QPoint centerPoint = rect.center();
    centerPoint.setX(centerPoint.x() - (this->width() / 2));
    centerPoint.setY(centerPoint.y() - this->height() / 2);
    this->move(centerPoint);
}


inline void Controller::setStatusBarText(const QString &text) {
    this->ui->labelStatusBar->setText("  Строка состояния: " + text);
}


bool Controller::validateFileToDecipher() {
    QString inputFileAbsolutePath = this->ui->lineEditInputFile->text();
    if(inputFileAbsolutePath.isEmpty()) {
        this->setStatusBarText(R"(Входной файл не выбран.)");
        return false;
    }

    QFile inputFile = QFile(this->ui->lineEditInputFile->text());
    if(!inputFile.exists()) {
        this->setStatusBarText(R"(Входной файл не существует.)");
        return false;
    }

    return true;
}


void Controller::on_buttonOpenFile_clicked() {
    QString inputFilePath;
    inputFilePath = QFileDialog::getOpenFileName(this, "Выбор файл", QStandardPaths::writableLocation(QStandardPaths::HomeLocation), "Текстовые файлы (*.txt)");
    if(inputFilePath.isEmpty()) return;

    this->ui->lineEditInputFile->setText(inputFilePath);
    this->ui->lineEditInputFile->setCursorPosition(0);
    this->setStatusBarText("Выбран входной файл.");
}


void Controller::on_buttonDecypher_clicked() {
    if(!(this->validateFileToDecipher())) return;
}



