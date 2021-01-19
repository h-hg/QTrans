#ifndef BAIDUTRANSLATOR2_H
#define BAIDUTRANSLATOR2_H

#include "onlinetranslator.h"

class BaiduTranslator2 : public OnlineTranslator {
  Q_OBJECT
 public:
  BaiduTranslator2(QObject *parent = nullptr);
  virtual ~BaiduTranslator2(){};

  // interface inherited from Translator
  virtual bool isSupportedLanguage(Language lang);
  virtual QString getLanguageCode(Language lang);
  // virtual void translate(QString const &content, Language from, Language to);

 protected:
  static QUrl url;
  static QMap<Language, QString> baiduLang2Code;

  QString appid, sk;

  // interface inherited from OnlineTranslator
  virtual void request(QString const &q, QString const &from,
                       QString const &to);
  virtual void parse(QNetworkReply *reply);
};

#endif  // BAIDUTRANSLATOR2_H
