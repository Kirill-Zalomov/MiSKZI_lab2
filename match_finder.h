#ifndef MATCHFINDER_H
#define MATCHFINDER_H


#include <QObject>
#include <QString>
#include <QStringList>

#include <QDebug>


class MatchFinder : public QObject {
    Q_OBJECT

public:
    explicit MatchFinder(QObject *parent = nullptr);
    quint32 countMatches(const QString &text, const QStringList &dictionary);

};


#endif // MATCHFINDER_H
