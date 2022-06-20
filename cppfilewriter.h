#ifndef CPPFILEWRITER_H
#define CPPFILEWRITER_H
#include "abstractlanguagefilewriter.h"

class CppFileWriter : public AbstractLanguageFileWriter
{
public:
  virtual void write(const QJsonArray &json, const QString &path) override;
  CppFileWriter();
};

#endif // CPPFILEWRITER_H
