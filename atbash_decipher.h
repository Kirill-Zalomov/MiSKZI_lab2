#ifndef ATBASH_DECIPHER_H
#define ATBASH_DECIPHER_H


#include <QObject>
#include <QByteArray>


const static QString russianAlphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const static QString secondAlphabet = "\t!\"#$%&'()*+,-/:;<=>?@[\\]^_`{|}~№";
const static qsizetype alphabetSize = 35;



class ModifiedAtbashDecipher : public QObject {
    Q_OBJECT

public:
    explicit ModifiedAtbashDecipher(QObject *parent = nullptr);
    QString decipher(const QString& input, const quint8& key) const;
};


#endif /* ATBASH_DECIPHER_H */
