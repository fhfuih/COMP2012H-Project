#ifndef FILELOADER_H
#define FILELOADER_H

#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QVariantMap>
#include <map>
#include <string>
#include <vector>

#include "Utils.h"

class FileLoader
{
private:
    typedef std::map<int, QVariantMap> MonsterMap;

    MonsterMap monsters;
    int levels[LEVEL_COUNT][MAXIMAL_ENEMY_TEAM_SIZE];

public:
    Type getType(int id) const;
    int getAttack(int id) const;
    int getDefense(int id) const;
    int getHealth(int id) const;
    int getCooldown(int id) const;
    QString getName(int id) const;
    std::vector<int> getLevel(int level_number) const;

    /* Lazy Singletion implementation */
private:
    FileLoader();

public:
    FileLoader(const FileLoader&) = delete;
    void operator=(const FileLoader&) = delete;
    // deleted functions are better set public, as is pointed out in Effective Modern C++

    friend FileLoader& fileLoader();
};

/* The only interface to get the singleton object, similar to qDebug() syntax */
FileLoader& fileLoader();

#endif // FILELOADER_H
