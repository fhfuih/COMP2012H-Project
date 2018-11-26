#ifndef FILELOADER_H
#define FILELOADER_H

#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <map>
#include <string>
#include <vector>

#include "Utils.h"

namespace DoNotTouchThisDamnNamespace {
    class FileLoader;
}

class DoNotTouchThisDamnNamespace::FileLoader
{
private:
    typedef std::map<int, QJsonObject> MonsterMap;

    MonsterMap monsters;
    QJsonArray levels;

public:
    FileLoader();
    int getType(int id) const;
    int getAttack(int id) const;
    int getDefense(int id) const;
    int getHealth(int id) const;
    int getCooldown(int id) const;
    std::string getName(int id) const;
    std::vector<int> getLevel(int level_number) const;
};

const DoNotTouchThisDamnNamespace::FileLoader fileLoader;

#endif // FILELOADER_H