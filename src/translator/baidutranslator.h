#ifndef BAIDUTRANSLATOR_H
#define BAIDUTRANSLATOR_H

#include <QNetworkAccessManager>
#include <QUrl>

#include "translator.h"
class BaiduTranslator : public Translator {
 public:
  BaiduTranslator();

 protected:
  static QMap<Language, QString> const lang2Code;
  static QUrl url;
  QNetworkAccessManager *networkAccessManger;
};

#endif  // BAIDUTRANSLATOR_H
