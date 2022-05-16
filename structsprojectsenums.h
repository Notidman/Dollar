#ifndef STRUCTSPROJECTSENUMS_H
#define STRUCTSPROJECTSENUMS_H
#include <QMap>

enum class TypeFile
{
  Dir = 0,
  File,
  Content,
};

const QMap<TypeFile, QString> map_type_file{{
    {TypeFile::Dir, "Dir"},
    {TypeFile::File, "File"},
    {TypeFile::Content, "Content"}
}};

enum ColumnIndex
{
  Type = 0,
  Name,
};

#endif // STRUCTSPROJECTSENUMS_H
