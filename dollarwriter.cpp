#include "dollarwriter.h"
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>

DollarWriter::DollarWriter()
{

}

void DollarWriter::create_template_storage()
{
  const QString& json_storage_path = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
  QDir dir(json_storage_path);
  if( dir.mkdir(name_templates_storage) )
  {
    qDebug() << "Created templates storage!";
  }
}

QJsonDocument DollarWriter::load_template(QString file_name)
{
  const QString& path_to_file =
      QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) +
      '/' + name_templates_storage + '/' + file_name;

  QFile jsonFile(path_to_file);
  jsonFile.open(QFile::ReadOnly);
  return QJsonDocument().fromJson(jsonFile.readAll());
}

bool DollarWriter::save_template(QJsonDocument document, QString file_name)
{
  const QString& path_to_file =
      QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) +
      '/' + name_templates_storage + '/' + file_name + ".json";

  QFile jsonFile(path_to_file);
  jsonFile.open(QFile::WriteOnly);

  if(jsonFile.write(document.toJson()))
    return true;
  else
    return false;

}

QString DollarWriter::way_to_storage_templates()
{
  return QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) +
      '/' + name_templates_storage + '/';
}
