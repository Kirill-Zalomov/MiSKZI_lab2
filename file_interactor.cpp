#include "file_interactor.h"


FileInteractor::FileInteractor(QObject *parent) : QObject{parent} {}


QString FileInteractor::readContentFromFile(const QString& filepath) const {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось произвести чтение исходного файла.\n\nВозможно, файл не существует или у программы нет прав на чтение файла.");
        return QString();
    }

    QTextStream inputTextStream(&file);
    QString content = inputTextStream.readAll();
    file.close();

    return content;
}


bool FileInteractor::writeContentInFile(const QString& filepath, const QString& content, const bool &rewrite) const {
    QFile file(filepath);
    if (rewrite) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Ошибка", "Не удалось произвести запись в файл результата.\nВозможно, файл не существует или у программы нет прав на запись файла.");
            return false;
        }
    } else {
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Ошибка", "Не удалось произвести запись в файл результата.\nВозможно, файл не существует или у программы нет прав на запись файла.");
            return false;
        }
    }

    QTextStream outputTextStream(&file);
    outputTextStream << content;
    file.close();

    return true;
}


void FileInteractor::deleteFile(const QString &filepath) {
    QFile fileToDelete(filepath);
    if(fileToDelete.exists()) fileToDelete.remove();
}
