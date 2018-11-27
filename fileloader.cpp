#include "fileloader.h"

FileLoader::FileLoader()
{
    QFile data_file{":/resource/data.json"};
    if (!data_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msg{nullptr};
        msg.setIcon(QMessageBox::Icon::Critical);
        msg.setText("Cannot open data file!");
        msg.exec();
        throw "Cannot open data file";
    }
    QString val = data_file.readAll();
    data_file.close();
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        QMessageBox msg{nullptr};
        msg.setIcon(QMessageBox::Icon::Critical);
        msg.setText("Cannot parse data file!");
        msg.exec();
        throw "Cannot parse data file";
    }
    QJsonObject object = document.object();
    QJsonArray enemyArray = object["enemy"].toArray();
    for (auto item : enemyArray) {
        QJsonObject thisEnemy = item.toObject();
        monsters.insert(std::pair<int, QVariantMap>{thisEnemy["id"].toInt(), thisEnemy.toVariantMap()});
    }
    QJsonArray petArray = object["pet"].toArray();
    for (auto item : petArray) {
        QJsonObject thisPet = item.toObject();
        monsters.insert(std::pair<int, QVariantMap>{thisPet["id"].toInt(), thisPet.toVariantMap()});
    }
    QJsonArray levelArr = object["level"].toArray();
    for (int i = 0; i < LEVEL_COUNT; i++) {
        for (int j = 0; j < MAXIMAL_ENEMY_TEAM_SIZE; j++) {
            levels[i][j] = levelArr[i].toArray()[j].toInt();
        }
    }
}

Type FileLoader::getType(int id) const {
//    return monsters[id]["type"].toInt();
    return static_cast<Type>(monsters.at(id)["type"].toInt());
}

int FileLoader::getAttack(int id) const {
    return monsters.at(id)["attack"].toInt();
}

int FileLoader::getDefense(int id) const {
    return monsters.at(id)["defense"].toInt();
}

int FileLoader::getHealth(int id) const {
    return monsters.at(id)["health"].toInt();
}

int FileLoader::getCooldown(int id) const {
    return monsters.at(id)["cooldown"].toInt();
}

std::string FileLoader::getName(int id) const {
    return monsters.at(id)["name"].toString().toStdString();
}

std::vector<int> FileLoader::getLevel(int level_number) const {
    assert(level_number < LEVEL_COUNT);
    return {levels[level_number], levels[level_number] + MAXIMAL_ENEMY_TEAM_SIZE};
}

FileLoader& fileLoader() {
    static FileLoader loader;
    return loader;
}
