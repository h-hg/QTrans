#ifndef GOOGLETRANSLATOR_H
#define GOOGLETRANSLATOR_H

#include "onlinetranslator.h"

class GoogleTranslator : public OnlineTranslator {
  Q_OBJECT
 public:
  GoogleTranslator(QObject *parent = nullptr);
  virtual ~GoogleTranslator(){};

  // interface inherited from Translator
  virtual bool isSupportedLanguage(Language lang);
  virtual QString getLanguageCode(Language lang);
  // virtual void translate(QString const &content, Language from, Language to);

 protected:
  static QUrl url;
  static QMap<Language, QString> googleLang2Code;

  // interface inherited from OnlineTranslator
  virtual void request(QString const &q, QString const &from,
                       QString const &to);
  virtual void parse(QNetworkReply *reply);
};

#endif  // GOOGLETRANSLATOR_H
