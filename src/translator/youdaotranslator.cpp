/*
 * This is a web api from 有道翻译
 * From: https://ai.youdao.com/product-fanyi-text.s
 * Language support:
 * https://ai.youdao.com/DOCSIRMA/html/自然语言翻译/API文档/文本翻译服务/文本翻译服务-API文档.html
 * Another api: http://fanyi.youdao.com/translate?&doctype=json&type=AUTO&i=计算
 */

#include "youdaotranslator.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

QUrl YoudaoTranslator::url =
    QUrl(QStringLiteral("https://aidemo.youdao.com/trans"));

QMap<Translator::Language, QString> YoudaoTranslator::youdaoLang2Code = {
    {SimplifiedChinese, QStringLiteral("zh-CHS")},
    {Hmong, QStringLiteral("hmn")},
    {SerbianCyrillic, QStringLiteral("sr-Cyrl")},
    {SerbianLatin, QStringLiteral("sr-Latn")},
};

YoudaoTranslator::YoudaoTranslator(QObject *parent) : OnlineTranslator(parent) {
  connect(networkAccessManger, &QNetworkAccessManager::finished, this,
          &YoudaoTranslator::parse);
}

bool YoudaoTranslator::isSupportedLanguage(Language lang) {
  switch (lang) {
    case SimplifiedChinese:  // 中文 zh-CHS
    case English:            // 英文 en
    case Japanese:           // 日文 ja
    case Korean:             // 韩文 ko
    case French:             // 法文 fr
    case Spanish:            // 西班牙文 es
    case Portuguese:         // 葡萄牙文 pt
    case Italian:            // 意大利文 it
    case Russian:            // 俄文 ru
    case Vietnamese:         // 越南文 vi
    case German:             // 德文 de
    case Arabic:             // 阿拉伯文 ar
    case Indonesian:         // 印尼文 id
    case Afrikaans:          // 南非荷兰语 af
    case Bosnian:            //波波斯尼亚语 bs
    case Bulgarian:          // 保加利亚语 bg
    case Cantonese:          // 粤语 yue
    case Catalan:            // 加泰隆语 ca
    case Croatian:           // 克罗地亚语 hr
    case Czech:              // 捷克语 cs
    case Danish:             // 丹麦语 da
    case Dutch:              // 荷兰语 nl
    case Estonian:           // 爱沙尼亚语 et
    case Fijian:             // 斐济语 fj
    case Finnish:            // 芬兰语 fi
    case Greek:              // 希腊语 el
    case HaitianCreole:      // 海地克里奥尔语 ht
    case Hebrew:             // 希伯来语 he
    case Hindi:              // 印地语 hi
    case Hmong:              // 白苗语 mww
    case Hungarian:          // 匈牙利语 hu
    case Swahili:            // 斯瓦希里语 sw
    case Klingon:            // 克林贡语 tlh
    case Latvian:            // 拉脱维亚语 lv
    case Lithuanian:         // 立陶宛语 lt
    case Malay:              // 马来语 ms
    case Maltese:            // 马耳他语 mt
    case Norwegian:          // 挪威语 no
    case Persian:            // 波斯语 fa
    case Polish:             // 波兰语 pl
    case QueretaroOtomi:     // 克雷塔罗奥托米语 otq
    case Romanian:           // 罗马尼亚语 ro
    case SerbianCyrillic:    // 塞尔维亚语(西里尔文) sr-Cyrl
    case SerbianLatin:       // 塞尔维亚语(拉丁文) sr-Latn
    case Slovak:             // 斯洛伐克语 sk
    case Slovenian:          // 斯洛文尼亚语 sl
    case Swedish:            // 瑞典语 sv
    case Tahitian:           // 塔希提语 ty
    case Thai:               // 泰语 th
    case Tongan:             // 汤加语 to
    case Turkish:            // 土耳其语 tr
    case Ukrainian:          // 乌克兰语 uk
    case Urdu:               // 乌尔都语 ur
    case Welsh:              // 威尔士语 cy
    case YucatecMaya:        // 尤卡坦玛雅语 yua
    case Albanian:           // 阿尔巴尼亚语 sq
    case Amharic:            // 阿姆哈拉语 am
    case Armenian:           // 亚美尼亚语 hy
    case Azerbaijani:        // 阿塞拜疆语 az
    case Bengali:            // 孟加拉语 bn
    case Basque:             // 巴斯克语 eu
    case Belarusian:         // 白俄罗斯语 be
    case Cebuano:            // 宿务语 ceb
    case Corsican:           // 科西嘉语 co
    case Esperanto:          // 世界语 eo
    case Tagalog:            // 菲律宾语 tl
    case Frisian:            // 弗里西语 fy
    case Galician:           // 加利西亚语 gl
    case Georgian:           // 格鲁吉亚语 ka
    case Gujarati:           // 古吉拉特语 gu
    case Hausa:              // 豪萨语 ha
    case Hawaiian:           // 夏威夷语 haw
    case Icelandic:          // 冰岛语 is
    case Igbo:               // 伊博语 ig
    case Irish:              // 爱尔兰语 ga
    case Javanese:           // 爪哇语 jw
    case Kannada:            // 卡纳达语 kn
    case Kazakh:             // 哈萨克语 kk
    case Khmer:              // 高棉语 km
    case Kurdish:            // 库尔德语 ku
    case Kyrgyz:             // 柯尔克孜语 ky
    case Lao:                // 老挝语 lo
    case Latin:              // 拉丁语 la
    case Luxembourgish:      // 卢森堡语 lb
    case Macedonian:         // 马其顿语 mk
    case Malagasy:           // 马尔加什语 mg
    case Malayalam:          // 马拉雅拉姆语 ml
    case Maori:              // 毛利语 mi
    case Marathi:            // 马拉地语 mr
    case Mongolian:          // 蒙古语 mn
    case Myanmar:            // 缅甸语 my
    case Nepali:             // 尼泊尔语 ne
    case Chichewa:           // 齐切瓦语 ny
    case Pashto:             // 普什图语 ps
    case Punjabi:            // 旁遮普语 pa
    case Samoan:             // 萨摩亚语 sm
    case ScotsGaelic:        // 苏格兰盖尔语 gd
    case Sesotho:            // 塞索托语 st
    case Shona:              // 修纳语 sn
    case Sindhi:             // 信德语 sd
    case Sinhala:            // 僧伽罗语 si
    case Somali:             // 索马里语 so
    case Sundanese:          // 巽他语 su
    case Tajik:              // 塔吉克语 tg
    case Tamil:              // 泰米尔语 ta
    case Telugu:             // 泰卢固语 te
    case Uzbek:              // 乌兹别克语 uz
    case Xhosa:              // 南非科萨语 xh
    case Yiddish:            // 意第绪语 yi
    case Yoruba:             // 约鲁巴语 yo
    case Zulu:               // 南非祖鲁语 zu
    case Auto:               // 自动识别 auto
      return true;
    default:
      return false;
  }
}

QString YoudaoTranslator::getLanguageCode(Language lang) {
  return youdaoLang2Code.value(lang, Translator::getLanguageCode(lang));
}

void YoudaoTranslator::request(QString const &q, QString const &from,
                               QString const &to) {
  QMap<QString, QString> params = {
      {QStringLiteral("from"), from},       // source language
      {QStringLiteral("to"), to},           // destination language
      {QStringLiteral("q"), encodeURL(q)},  // queried sentence
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

void YoudaoTranslator::parse(QNetworkReply *reply) {
  QByteArray replyData = reply->readAll();
  QJsonDocument jsonDoc = QJsonDocument::fromJson(replyData);
  QJsonObject jsonObj = jsonDoc.object();
  QString cResult;
  QString errorCode = jsonObj.value("errorCode").toString();
  if (errorCode != "0") {
    cResult = errorCode;
    qDebug() << errorCode << Qt::endl;
  } else {
    QJsonArray values = jsonObj.value("translation").toArray();
    qDebug() << values.size() << Qt::endl;
    for (auto it = values.begin(); it != values.end(); ++it) {
      cResult += it->toString();
    }
  }
  reply->deleteLater();
  emit finished(cResult);
}
