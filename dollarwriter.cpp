#include "dollarwriter.h"
#include "structsprojectsenums.h"
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>
#include <QStringList>
#include <QJsonArray>
#include <fstream>
#include <filesystem>
#include <JlCompress.h>

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

QJsonDocument DollarWriter::load_metafile(QString path_file)
{
  QFile jsonFile(path_file);
  jsonFile.open(QFile::ReadOnly);
  return QJsonDocument().fromJson(jsonFile.readAll());
}

bool DollarWriter::save_drc(QJsonDocument document, QString file_name)
{
  QDir temp_dir(".");
  temp_dir.mkdir(name_tmp_storage);

  const QString json_path = name_tmp_storage + '/' + name_metafile + ".json";

  QFile jsonFile(json_path);
  jsonFile.open(QFile::WriteOnly);

  if(!jsonFile.write(document.toJson()))
    return false;

  jsonFile.close();

  QJsonObject template_file = document.object();

  QStringList files_to_copy(find_all_efiles(template_file.value(jsonkeys::struct_pj).toArray()));
//  QFile::copy("/path/file", "/path/copy-of-file");
  for( const auto& file:files_to_copy)
  {
    QFile::copy(file, name_tmp_storage + "/" + QFileInfo(file).fileName());
  }

  const QString& path_to_drc_file =
      QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) +
      '/' + name_templates_storage + '/' + file_name + ".drc";

  if ( !compress_dir(path_to_drc_file, name_tmp_storage) )
  {
    return false;
  }

//  int errorp = 0;
//  zip_t *arch = zip_open(path_to_file.toStdString().c_str(), ZIP_CREATE, &errorp);
//  if ( errorp)
//    return false;

//  for( const auto& file: std::filesystem::directory_iterator(name_tmp_storage.toStdString()))
//  {
////    add_file(ar, file.path().c_str(), QFileInfo(file.path().c_str()).fileName().toStdString());
//    add_file_in_drc(arch, file.path().c_str(), QFileInfo(file.path().c_str()).fileName().toStdString());
//  }

//  zip_close(arch);

  // remove tmp dir
  remove_tmp_dir();

  return true;
}

QString DollarWriter::way_to_storage_templates()
{
  return QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) +
      '/' + name_templates_storage + '/';
}

QString DollarWriter::way_tmp_dir()
{
  return name_tmp_storage;
}

QString DollarWriter::get_name_metafile()
{
  return name_metafile;
}

QStringList DollarWriter::find_all_efiles(const QJsonArray& meta_json)
{
  QStringList efiles;
  for(int i = 0; i < meta_json.count(); ++i)
  {
    efiles += find_efiles(meta_json.at(i).toObject());
  }
  return efiles;
}

QStringList DollarWriter::find_efiles(const QJsonObject json)
{
  QStringList efiles;

  auto type = json.value(jsonkeys::struct_pj_type).toString();
  auto name = json.value(jsonkeys::struct_pj_name).toString();

  if( type == map_type_file[TypeFile::Dir])
  {
    efiles += find_all_efiles(json.value(jsonkeys::struct_pj_childr).toArray());
  }
  else if ( type == map_type_file[TypeFile::ExternalFile])
  {
    efiles += json.value(jsonkeys::struct_pj_childr).toArray().at(0)
        .toObject().value(jsonkeys::struct_pj_name).toString();
  }

  return efiles;
}

bool DollarWriter::compress_dir(QString drc_file, QString dir)
{
  if( JlCompress::compressDir(drc_file, dir))
  {
    return true;
  }
  else
    return false;
}

QString DollarWriter::get_way_metafile()
{
  return name_tmp_storage + '/' + name_metafile + ".json";
}

void DollarWriter::remove_tmp_dir()
{
  QDir remove_tmp(name_tmp_storage);
  remove_tmp.removeRecursively();
}

void DollarWriter::create_tmp_dir(QString drc_file)
{
  QStringList list = JlCompress::extractDir(drc_file, name_tmp_storage);

  for( auto& file:list)
  {
    qDebug() << "Extract: " << file;
  }
}

//void DollarWriter::add_file_in_drc(DollarWriter::archive, std::string file_path, std::string new_file_name)
//{
//  std::ifstream fs(file_path, std::ios_base::binary);
//  std::string content((std::istreambuf_iterator<char>(fs)),
//                      (std::istreambuf_iterator<char>()));
//  fs.close();

//  zip_source_t *source = zip_source_buffer(archive, content.c_str(), content.length(), 0);
//  zip_file_add(archive, new_file_name.c_str(), source, ZIP_FL_ENC_UTF_8);
//}
