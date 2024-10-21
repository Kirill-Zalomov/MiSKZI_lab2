#include "atbash_decipher.h"


ModifiedAtbashDecipher::ModifiedAtbashDecipher(QObject *parent) : QObject(parent) {}


QString ModifiedAtbashDecipher::decipher(const QString& input, const quint8& key) const {
    QString output;

    for (qint32 i = 0; i < input.length(); i++) {
        QChar currentSymbol = input[i].toLower();
        if (secondAlphabet.contains(currentSymbol)) {
            int index = secondAlphabet.indexOf(currentSymbol);
            int encryptedIndex = secondAlphabet.length() - index - 1;
            int shiftedIndex = (encryptedIndex + key) % secondAlphabet.length();
            output += russianAlphabet[shiftedIndex];
        }
        else {
            output += currentSymbol;
        }
    }

    return output;
}
