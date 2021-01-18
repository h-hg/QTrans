#ifndef YOUDAOTRANSLATOR_H
#define YOUDAOTRANSLATOR_H

#include "onlinetranslator.h"

class YoudaoTranslator : public OnlineTranslator {
  Q_OBJECT
 public:
  YoudaoTranslator(QObject *parent);
  virtual ~YoudaoTranslator(){};

  // interface inherited from Translator
  virtual bool isSupportedLanguage(Language lang);
  virtual QString getLanguageCode(Language lang);
  // virtual void translate(QString const &content, Language from, Language to);

 protected:
  static QUrl url;
  static QMap<Language, QString> youdaoLang2Code;

  // interface inherited from OnlineTranslator
  virtual void request(QString const &q, QString const &from,
                       QString const &to);
  virtual void parse(QNetworkReply *reply);
};

#endif  // YOUDAOTRANSLATOR_H
