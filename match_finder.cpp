#include "match_finder.h"


MatchFinder::MatchFinder(QObject *parent) : QObject{parent} {}


quint32 MatchFinder::countMatches(const QString &text, const QStringList &dictionary) {
    qsizetype dictionarySize = dictionary.size();
    if(dictionarySize == 0) return 0;

    quint32 result = 0;
    qsizetype index = 0;
    while(index < dictionarySize) {
        if(text.contains(dictionary.at(index))) result++;
        index++;
    }

    return result;
}
