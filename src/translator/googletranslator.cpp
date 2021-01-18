/*
 * This is a web api from google translation
 * From: https://ai.youdao.com/product-fanyi-text.s
 * Language support: https://cloud.google.com/translate/docs/languages
 * Another api: https://translate.googleap.cn/translate_a/single
 */

#include "googletranslator.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

QUrl GoogleTranslator::url =
    QUrl(QStringLiteral("https://translate.googleapis.com/translate_a/single"));

QMap<Translator::Language, QString> GoogleTranslator::googleLang2Code = {
    {Javanese, QStringLiteral("jv")}};

GoogleTranslator::GoogleTranslator(QObject *parent) : OnlineTranslator(parent) {
  connect(networkAccessManger, &QNetworkAccessManager::finished, this,
          &GoogleTranslator::parse);
}

bool GoogleTranslator::isSupportedLanguage(Language lang) {
  switch (lang) {
    case Afrikaans:           // af
    case Albanian:            // sq
    case Amharic:             // am
    case Arabic:              // ar
    case Armenian:            // hy
    case Azerbaijani:         // az
    case Basque:              // eu
    case Belarusian:          // be
    case Bengali:             // bn
    case Bosnian:             // bs
    case Bulgarian:           // bg
    case Catalan:             // ca
    case Cebuano:             // ceb (ISO-639-2)
    case SimplifiedChinese:   // zh-CN or zh (BCP-47)
    case TraditionalChinese:  // zh-TW (BCP-47)
    case Corsican:            // co
    case Croatian:            // hr
    case Czech:               // cs
    case Danish:              // da
    case Dutch:               // nl
    case English:             // en
    case Esperanto:           // eo
    case Estonian:            // et
    case Finnish:             // fi
    case French:              // fr
    case Frisian:             // fy
    case Galician:            // gl
    case Georgian:            // ka
    case German:              // de
    case Greek:               // el
    case Gujarati:            // gu
    case HaitianCreole:       // ht
    case Hausa:               // ha
    case Hawaiian:            // haw (ISO-639-2)
    case Hebrew:              // he or iw
    case Hindi:               // hi
    case Hmong:               // hmn (ISO-639-2)
    case Hungarian:           // hu
    case Icelandic:           // is
    case Igbo:                // ig
    case Indonesian:          // id
    case Irish:               // ga
    case Italian:             // it
    case Japanese:            // ja
    case Javanese:            // jv
    case Kannada:             // kn
    case Kazakh:              // kk
    case Khmer:               // km
    case Kinyarwanda:         // rw
    case Korean:              // ko
    case Kurdish:             // ku
    case Kyrgyz:              // ky
    case Lao:                 // lo
    case Latin:               // la
    case Latvian:             // lv
    case Lithuanian:          // lt
    case Luxembourgish:       // lb
    case Macedonian:          // mk
    case Malagasy:            // mg
    case Malay:               // ms
    case Malayalam:           // ml
    case Maltese:             // mt
    case Maori:               // mi
    case Marathi:             // mr
    case Mongolian:           // mn
    case Myanmar:             // my, (Burmese)
    case Nepali:              // ne
    case Norwegian:           // no
    case Chichewa:            // ny, (Nyanja)
    case Oriya:               // or, (Odia)
    case Pashto:              // ps
    case Persian:             // fa
    case Polish:              // pl
    case Portuguese:          // pt, (Portugal, Brazil)
    case Punjabi:             // pa
    case Romanian:            // ro
    case Russian:             // ru
    case Samoan:              // sm
    case ScotsGaelic:         // gd
    case SerbianCyrillic:     // sr, (Serbian)
    case Sesotho:             // st
    case Shona:               // sn
    case Sindhi:              // sd
    case Sinhala:             // si, (Sinhalese)
    case Slovak:              // sk
    case Slovenian:           // sl
    case Somali:              // so
    case Spanish:             // es
    case Sundanese:           // su
    case Swahili:             // sw
    case Swedish:             // sv
    case Tagalog:             // tl, (Filipino)
    case Tajik:               // tg
    case Tamil:               // ta
    case Tatar:               // tt
    case Telugu:              // te
    case Thai:                // th
    case Turkish:             // tr
    case Turkmen:             // tk
    case Ukrainian:           // uk
    case Urdu:                // ur
    case Uighur:              // ug, (Uyghur)
    case Uzbek:               // uz
    case Vietnamese:          // vi
    case Welsh:               // cy
    case Xhosa:               // xh
    case Yiddish:             // yi
    case Yoruba:              // yo
    case Zulu:                // zu
    case Auto:
      return true;
    default:
      return false;
  }
}

QString GoogleTranslator::getLanguageCode(Language lang) {
  return googleLang2Code.value(lang, Translator::getLanguageCode(lang));
}

void GoogleTranslator::request(QString const &q, QString const &from,
                               QString const &to) {
  QMap<QString, QString> params = {
      {QStringLiteral("client"), QStringLiteral("gtx")},  // client type
      {QStringLiteral("ie"), QStringLiteral("UFT-8")},    // input code
      {QStringLiteral("oe"), QStringLiteral("UFT-8")},    // output code
      {QStringLiteral("dt"),
       QStringLiteral("t")},  // return type of server, t means only translation
      {QStringLiteral("dj"), QStringLiteral("1")},  // unknown
      {QStringLiteral("sl"), from},                 // source language
      {QStringLiteral("tl"), to},                   // target language
      // {QStringLiteral("hl"), QStringLiteral("en")},  // GUI language
      {QStringLiteral("q"), encodeURL(q)}  // queried sentence
  };
  auto data = encodeParams(params).toUtf8();
  qDebug() << data << Qt::endl;
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
  request.setHeader(
      QNetworkRequest::ContentTypeHeader,
      QStringLiteral("application/x-www-form-urlencoded; charset=UTF-8"));
  networkAccessManger->post(request, data);
}

void GoogleTranslator::parse(QNetworkReply *reply) {
  QByteArray replyData = reply->readAll();
  QJsonDocument jsonDoc = QJsonDocument::fromJson(replyData);
  QJsonObject jsonObj = jsonDoc.object();
  qDebug() << jsonObj << Qt::endl;
  QString cResult;
  QJsonArray data = jsonObj.value("sentences").toArray();
  for (auto iter = data.begin(); iter != data.end(); ++iter) {
    cResult += (iter->toObject()).value("trans").toString();
  }
  reply->deleteLater();
  emit finished(cResult);
}
