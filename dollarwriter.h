#ifndef DOLLARWRITER_H
#define DOLLARWRITER_H
#include <QJsonObject>
#include <QString>
#include <QJsonDocument>
#include <string_view>

class DollarWriter
{
public:
  DollarWriter();
  void create_template_storage();
  QJsonDocument load_template(QString path_file);
  bool save_template(QJsonDocument document, QString file_name);
  QString way_to_storage_templates();

private:
  QString name_templates_storage = "templates";
};

#endif // DOLLARWRITER_H
