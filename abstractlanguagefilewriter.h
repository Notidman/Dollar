#ifndef ABSTRACTLANGUAGEFILEWRITER_H
#define ABSTRACTLANGUAGEFILEWRITER_H
#include <QJsonArray>
#include <QString>

class AbstractLanguageFileWriter
{
public:
  AbstractLanguageFileWriter() {}
  virtual void write(const QJsonArray& json, const QString& path) = 0;
  virtual ~AbstractLanguageFileWriter() {}
};

#endif // ABSTRACTLANGUAGEFILEWRITER_H
