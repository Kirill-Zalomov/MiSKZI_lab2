#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QString>
#include <QScreen>
#include <QRect>
#include <QFile>

#include "file_interactor.h"
#include "atbash_decipher.h"
#include "match_finder.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Controller; }
QT_END_NAMESPACE


class Controller : public QMainWindow {
    Q_OBJECT

private:
    QStringList dictionary;

    void moveWindowToCenterOfDisplay();
    void setStatusBarText(const QString &text);
    bool validateFileToDecipher();
    void fillDictionaryWithContentFromFile(QFile fileWithDictionary);

public:
    Controller(QWidget *parent = nullptr);
    ~Controller();

    QStringList getDictionary() const;
    void setDictionary(const QStringList &newDictionary);

private slots:
    void on_buttonDecypher_clicked();
    void on_buttonOpenFile_clicked();

private:
    Ui::Controller *ui;

};


#endif // CONTROLLER_H
