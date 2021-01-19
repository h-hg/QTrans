#ifndef ONLINETRANSLATOR_H
#define ONLINETRANSLATOR_H

#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include "translator.h"

class OnlineTranslator : public Translator {
  Q_OBJECT

 public:
  enum TranslationError {
    NoError,
    ParametersError,
    NetworkError,
    ServiceError,
    ParsingError
  };

  OnlineTranslator(QObject *parent = nullptr)
      : Translator(parent), networkAccessManger(new QNetworkAccessManager()){};
  virtual ~OnlineTranslator(){};

  // interface inherited from Translator
  virtual bool isSupportedLanguage(Language lang) = 0;
  virtual QString getLanguageCode(Language lang) = 0;
  virtual void translate(QString const &content, Language from, Language to);

 protected:
  QNetworkAccessManager *networkAccessManger;

  // utils
  static QString encodeURL(QString const &content);
  static QString encodeParams(QMap<QString, QString> const &params);

  // interface
  virtual void request(QString const &q, QString const &from,
                       QString const &to) = 0;
  virtual void parse(QNetworkReply *reply) = 0;
};

#endif  // ONLINETRANSLATOR_H
