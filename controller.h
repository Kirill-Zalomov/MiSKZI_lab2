#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QString>
#include <QScreen>
#include <QRect>
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class Controller; }
QT_END_NAMESPACE


class Controller : public QMainWindow {
    Q_OBJECT

private:
    void moveWindowToCenterOfDisplay();
    void setStatusBarText(const QString &text);
    bool validateFileToDecipher();

public:
    Controller(QWidget *parent = nullptr);
    ~Controller();

private slots:
    void on_buttonDecypher_clicked();
    void on_buttonOpenFile_clicked();

private:
    Ui::Controller *ui;

};


#endif // CONTROLLER_H
