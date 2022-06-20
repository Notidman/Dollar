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
  QJsonDocument load_metafile(QString path_file);
  bool save_drc(QJsonDocument document, QString file_name);
  QString way_to_storage_templates();
  QString way_tmp_dir();
  QString get_name_metafile();
  QStringList find_all_efiles(const QJsonArray &meta_json);
  QStringList find_efiles(const QJsonObject json);
  bool compress_dir(QString drc_file, QString dir);
  QString get_way_metafile();
  void remove_tmp_dir();
  void create_tmp_dir(QString drc_file);

private:
  const QString name_templates_storage = "templates";
  const QString name_tmp_storage = ".tmp_dollar";
  const QString name_metafile = "METAINFO";
};

#endif // DOLLARWRITER_H
