#ifndef FILEINTERACTOR_H
#define FILEINTERACTOR_H


#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


class FileInteractor : public QObject {
    Q_OBJECT

public:
    explicit FileInteractor(QObject *parent = nullptr);
    QString readContentFromFile(const QString& filepath) const;
    bool writeContentInFile(const QString &filepath, const QString &content, const bool &rewrite) const;
    void deleteFile(const QString &filepath);
};


#endif // FILEINTERACTOR_H
