#ifndef STRUCTSPROJECTSENUMS_H
#define STRUCTSPROJECTSENUMS_H
#include <QMap>
#include <string_view>

enum class TypeFile
{
  Dir = 0,
  File,
  Content,
  ExternalFile,
};

const QMap<TypeFile, QString> map_type_file{{
    {TypeFile::Dir, "Dir"},
    {TypeFile::File, "File"},
    {TypeFile::Content, "Content"},
    {TypeFile::ExternalFile, "EFile"}
}};

enum ColumnIndex
{
  Type = 0,
  Name,
};

namespace jsonkeys {
  static const QString name = "name";
  static const QString control_version = "control_version";
  static const QString build_system = "build_system";
  static const QString language = "language";
  static const QString struct_pj = "struct";
  static const QString libraries = "libraries";
  static const QString struct_pj_name = "Name";
  static const QString struct_pj_type = "Type";
  static const QString struct_pj_childr = "Children";
}

#endif // STRUCTSPROJECTSENUMS_H
