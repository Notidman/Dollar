#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonObject>
#include <QMap>
#include <QString>

class JsonParser
{
public:
  JsonParser();
  QJsonObject create_json(QMap<QString, QString> project_struct);
};

#endif // JSONPARSER_H
