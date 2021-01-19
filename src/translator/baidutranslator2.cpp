/*
 * This is a web api from 百度 translation
 * From: http://api.fanyi.baidu.com/product/113
 * Language support: https://cloud.google.com/translate/docs/languages
 * Another api: https://translate.googleap.cn/translate_a/single
 */

#include "baidutranslator2.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QUrlQuery>

QUrl BaiduTranslator2::url =
    QUrl(QStringLiteral("http://api.fanyi.baidu.com/api/trans/vip/translate"));

QMap<Translator::Language, QString> BaiduTranslator2::baiduLang2Code = {
    {Javanese, QStringLiteral("jv")}};

BaiduTranslator2::BaiduTranslator2(QObject *parent) : OnlineTranslator(parent) {
  connect(networkAccessManger, &QNetworkAccessManager::finished, this,
          &BaiduTranslator2::parse);
}

bool BaiduTranslator2::isSupportedLanguage(Language lang) {
  // switch (lang) {
  //    case Arabic:                         // 阿拉伯语, ara,
  //    case Irish:                          // 爱尔兰语, gle,
  //    case Occitan:                        // 奥克语, oci, Occitan
  //    case Albanian:                       // 阿尔巴尼亚语, alb,
  //    case Algerian Arabic:                // 阿尔及利亚阿拉伯语, arq,
  //    case Akan:                           // 阿肯语, aka,
  //    case Aragonese:                      // 阿拉贡语, arg,
  //    case Amharic:                        // 阿姆哈拉语, amh,
  //    case Assamese:                       // 阿萨姆语, asm,
  //    case Aymara:                         // 艾马拉语, aym,
  //    case Azerbaijani:                    // 阿塞拜疆语, aze,
  //    case Asturian:                       // 阿斯图里亚斯语, ast,
  //    case Ossetian:                       // 奥塞梯语, oss,
  //    case Estonian:                       // 爱沙尼亚语, est,
  //    case Ojebwa:                         // 奥杰布瓦语, oji,
  //    case Oriya:                          // 奥里亚语, ori,
  //    case Oromo:                          // 奥罗莫语, orm,
  //    case Polish:                         // 波兰语, pl,
  //    case Persian:                        // 波斯语, per,
  //    case Breton:                         // 布列塔尼语, bre,
  //    case Bashkir:                        // 巴什基尔语, bak,
  //    case Basque:                         // 巴斯克语, baq,
  //    case Brazilian Portuguese:           // 巴西葡萄牙语, pot,
  //    case Belarusian:                     // 白俄罗斯语, bel,
  //    case Berber:                         // 柏柏尔语, ber,
  //    case Pampanga:                       // 邦板牙语, pam,
  //    case Bulgarian:                      // 保加利亚语, bul,
  //    case Northern Sami:                  // 北方萨米语, sme,
  //    case Northern Sotho:                 // 北索托语, ped,
  //    case Bumba:                          // 本巴语, bem,
  //    case Biling:                         // 比林语, bli,
  //    case Bislama:                        // 比斯拉马语, bis,
  //    case Baluchi:                        // 俾路支语, bal,
  //    case Icelandic:                      // 冰岛语, ice,
  //    case Bosnian:                        // 波斯尼亚语, bos,
  //    case Bhojpur:                        // 博杰普尔语, bho,
  //    case Brazilian:                      // 巴西语, pt_BR,
  //    case Chuvash:                        // 楚瓦什语, chv,
  //    case Tsunga:                         // 聪加语, tso,
  //    case Danish:                         // 丹麦语, dan,
  //    case German:                         // 德语, de,
  //    case Tatar:                          // 鞑靼语, tat,
  //    case Shan:                           // 掸语, sha,
  //    case Teton:                          // 德顿语, tet,
  //    case Dhivehi:                        // 迪维希语, div,
  //    case Low German:                     // 低地德语, log,
  //    case Russian:                        // 俄语, ru,
  //    case French:                         // 法语, fra,
  //    case Filipino:                       // 菲律宾语, fil,
  //    case Finnish:                        // 芬兰语, fin,
  //    case Sanskrit:                       // 梵语, san,
  //    case Friuli:                         // 弗留利语, fri,
  //    case Fulani:                         // 富拉尼语, ful,
  //    case Faroese:                        // 法罗语, fao,
  //    case Gaelic:                         // 盖尔语, gla,
  //    case Congo:                          // 刚果语, kon,
  //    case Highland Sorbian:               // 高地索布语, ups,
  //    case Cambodian:                      // 高棉语, hkm,
  //    case Greenlandic:                    // 格陵兰语, kal,
  //    case Georgian:                       // 格鲁吉亚语, geo,
  //    case Gujarati:                       // 古吉拉特语, guj,
  //    case Ancient Greek:                  // 古希腊语, gra,
  //    case Old English:                    // 古英语, eno,
  //    case Guarani:                        // 瓜拉尼语, grn,
  //    case Korean:                         // 韩语, kor,
  //    case Dutch:                          // 荷兰语, nl,
  //    case Hupa:                           // 胡帕语, hup,
  //    case Hakachin:                       // 哈卡钦语, hak,
  //    case Kazakh:                         // 哈萨克语, kaz,
  //    case Haitian:                        // 海地语, ht,
  //    case Hausa:                          // 豪萨语, hau,
  //    case Montenegrin:                    // 黑山语, mot,
  //    case Haitian Creole:                 // 海地克里奥尔语, ht,
  //    case Kyrgyz:                         // 吉尔吉斯语, kir,
  //    case Galician:                       // 加利西亚语, glg,
  //    case Canadian French:                // 加拿大法语, frn,
  //    case Catalan:                        // 加泰罗尼亚语, cat,
  //    case Czech:                          // 捷克语, cs,
  //    case Kabyle:                         // 卡拜尔语, kab,
  //    case Kannada:                        // 卡纳达语, kan,
  //    case Kanuri:                         // 卡努里语, kau,
  //    case Kashubian:                      // 卡舒比语, kah,
  //    case Cornish:                        // 康瓦尔语, cor,
  //    case Xhosa:                          // 科萨语, xho,
  //    case Corsican:                       // 科西嘉语, cos,
  //    case Creek:                          // 克里克语, cre,
  //    case Crimean Tatar:                  // 克里米亚鞑靼语, cri,
  //    case Klingon:                        // 克林贡语, kli,
  //    case Croatian:                       // 克罗地亚语, hrv,
  //    case Quechua:                        // 克丘亚语, que,
  //    case Kashmiri:                       // 克什米尔语, kas,
  //    case Konkani:                        // 孔卡尼语, kok,
  //    case Kurdish:                        // 库尔德语, kur,
  //    case Latin:                          // 拉丁语, lat,
  //    case Lao:                            // 老挝语, lao,
  //    case Romanian:                       // 罗马尼亚语, rom,
  //    case Latjalai:                       // 拉特加莱语, lag,
  //    case Latvian:                        // 拉脱维亚语, lav,
  //    case Limburgish:                     // 林堡语, lim,
  //    case Lingala:                        // 林加拉语, lin,
  //    case Luganda:                        // 卢干达语, lug,
  //    case Luxembourgish:                  // 卢森堡语, ltz,
  //    case Rusynian:                       // 卢森尼亚语, ruy,
  //    case Kinyarwanda:                    // 卢旺达语, kin,
  //    case Lithuanian:                     // 立陶宛语, lit,
  //    case Romansh:                        // 罗曼什语, roh,
  //    case Romani:                         // 罗姆语, ro,
  //    case Logical:                        // 逻辑语, loj,
  //    case Malay:                          // 马来语, may,
  //    case Burmese:                        // 缅甸语, bur,
  //    case Marathi:                        // 马拉地语, mar,
  //    case Malagasy:                       // 马拉加斯语, mg,
  //    case Malayalam:                      // 马拉雅拉姆语, mal,
  //    case Macedonian:                     // 马其顿语, mac,
  //    case Marshallese:                    // 马绍尔语, mah,
  //    case Maitili:                        // 迈蒂利语, mai,
  //    case Manks:                          // 曼克斯语, glv,
  //    case Mauritian Creole:               // 毛里求斯克里奥尔语, mau,
  //    case Maori:                          // 毛利语, mao,
  //    case Bengali:                        // 孟加拉语, ben,
  //    case Maltese:                        // 马耳他语, mlt,
  //    case Mongolian:                      // 蒙语, mon,
  //    case Marathi:                        // 马拉提语, mr,
  //    case Mongolian(Cyrillic):            // 蒙古语（西里尔）, moc,
  //    case Hmong:                          // 苗语, hmn,
  //    case Norwegian:                      // 挪威语, nor,
  //    case Neapolitan:                     // 那不勒斯语, nea,
  //    case South Ndebele:                  // 南恩德贝莱语, nbl,
  //    case Afrikaans:                      // 南非荷兰语, afr,
  //    case South Sotho:                    // 南索托语, sot,
  //    case Nepali:                         // 尼泊尔语, nep,
  //    case Portuguese:                     // 葡萄牙语, pt,
  //    case Punjabi:                        // 旁遮普语, pan,
  //    case Papiamento:                     // 帕皮阿门托语, pap,
  //    case Pashto:                         // 普什图语, pus,
  //    case Nyanja:                         // 齐切瓦语, nya,
  //    case Twi:                            // 契维语, twi,
  //    case Cherokee:                       // 切罗基语, chr,
  //    case Japanese:                       // 日语, jp,
  //    case Swedish:                        // 瑞典语, swe,
  //    case Sardinian:                      // 萨丁尼亚语, srd,
  //    case Samoan:                         // 萨摩亚语, sm,
  //    case Serbia:                         // 塞尔维亚-克罗地亚语, sec,
  //    case Serbian:                        // 塞尔维亚语, srp,
  //    case Songhai:                        // 桑海语, sol,
  //    case Sinhala:                        // 僧伽罗语, sin,
  //    case Esperanto:                      // 世界语, epo,
  //    case Written Norwegian:              // 书面挪威语, nob,
  //    case Slovak:                         // 斯洛伐克语, sk,
  //    case Slovenian:                      // 斯洛文尼亚语, slo,
  //    case Swahili:                        // 斯瓦希里语, swa,
  //    case Scots:                          // 苏格兰语, sco,
  //    case Somali:                         // 索马里语, som,
  //    case Setswana:                       // 塞茨瓦纳语, tn,
  //    case Serbian(Cyrillic):              // 塞尔维亚语（西里尔）, src,
  //    case Thai:                           // 泰语, th,
  //    case Turkish:                        // 土耳其语, tr,
  //    case Tajik:                          // 塔吉克语, tgk,
  //    case Tamil:                          // 泰米尔语, tam,
  //    case Filipino:                       // 他加禄语, tgl,
  //    case Tigrinya:                       // 提格利尼亚语, tir,
  //    case Telugu:                         // 泰卢固语, tel,
  //    case Tunisian Arabic:                // 突尼斯阿拉伯语, tua,
  //    case Turkmen:                        // 土库曼语, tuk,
  //    case Tatar:                          // 塔塔尔语, tt,
  //    case Ukrainian:                      // 乌克兰语, ukr,
  //    case Walloon:                        // 瓦隆语, wln,
  //    case Welsh:                          // 威尔士语, wel,
  //    case Venda:                          // 文达语, ven,
  //    case Wolof:                          // 沃洛夫语, wol,
  //    case Urdu:                           // 乌尔都语, urd,
  //    case Uzbek:                          // 乌兹别克语, uzb,
  //    case Uyghur:                         // 维吾尔语, uig,
  //    case Spanish:                        // 西班牙语, spa,
  //    case Hebrew:                         // 希伯来语, heb,
  //    case Greek:                          // 希腊语, el,
  //    case Hungarian:                      // 匈牙利语, hu,
  //    case West Frisian:                   // 西弗里斯语, fry,
  //    case Silesian:                       // 西里西亚语, sil,
  //    case Hiliganun:                      // 希利盖农语, hil,
  //    case Lower Sorbian:                  // 下索布语, los,
  //    case Hawaiian:                       // 夏威夷语, haw,
  //    case New Norwegian:                  // 新挪威语, nno,
  //    case West African written language:  // 西非书面语, nqo,
  //    case Sindhi:                         // 信德语, snd,
  //    case Shona:                          // 修纳语, sna,
  //    case Cebuano:                        // 宿务语, ceb,
  //    case Syriac:                         // 叙利亚语, syr,
  //    case Cantonese added:                // 新增粤语, yus,
  //    case Add Mandarin:                   // 新增普通话, zhs,
  //    case Sundanese:                      // 巽他语, sun,
  //    case English:                        // 英语, en,
  //    case Hindi:                          // 印地语, hi,
  //    case Indonesian:                     // 印尼语, id,
  //    case Italian:                        // 意大利语, it,
  //    case Vietnamese:                     // 越南语, vie,
  //    case Yiddish:                        // 意第绪语, yid,
  //    case Inter:                          // 因特语, ina,
  //    case Aceh:                           // 亚齐语, ach,
  //    case Ingush:                         // 印古什语, ing,
  //    case Igbo:                           // 伊博语, ibo,
  //    case Ido:                            // 伊多语, ido,
  //    case Yoruba:                         // 约鲁巴语, yor,
  //    case Armenian:                       // 亚美尼亚语, arm,
  //    case Inuktitut:                      // 伊努克提图特语, iku,
  //    case Inuit:                          // 因纽特语, iu,
  //    case Iranian:                        // 伊朗语, ir,
  //    case SimplifiedChinese:              // 中文(简体), zh,
  //    case TraditionalChinese:             // 中文(繁体), cht,
  //    case LiteraryChinese:                // 中文(文言文), wyw,
  //    case Cantonese:                      // 中文(粤语), yue,
  //    case Zazaqi:                         // 扎扎其语, zaz,
  //    case Middle French:                  // 中古法语, frm,
  //    case Zulu:                           // 祖鲁语, zul,
  //    case Javanese:                       // 爪哇语, jav,
  //    case Tibetan:                        // 藏语, tib,
  //    case Tsongkha:                       // 宗喀语/不丹语, dzo
  //      return true;
  //    default:
  //      return false;
  //}
  return true;
}

QString BaiduTranslator2::getLanguageCode(Language lang) {
  return baiduLang2Code.value(lang, Translator::getLanguageCode(lang));
}

void BaiduTranslator2::request(QString const &q, QString const &from,
                               QString const &to) {
  auto salt = QString::number(QRandomGenerator::global()->generate());
  QString sign = QCryptographicHash::hash((appid + q + salt + sk).toUtf8(),
                                          QCryptographicHash::Md5)
                     .toHex();
  QMap<QString, QString> params = {
      {QStringLiteral("from"), from},       // source language
      {QStringLiteral("to"), to},           // target language
      {QStringLiteral("q"), encodeURL(q)},  // queried sentence
      {QStringLiteral("appid"), appid},    {QStringLiteral("salt"), salt},
      {QStringLiteral("sign"), sign}};
  auto data = encodeParams(params).toUtf8();
  qDebug() << data << Qt::endl;
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader,
                    "application/x-www-form-urlencoded");
  networkAccessManger->post(request, data);
}

void BaiduTranslator2::parse(QNetworkReply *reply) {
  QByteArray replyData = reply->readAll();
  qDebug() << replyData << Qt::endl;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(replyData);
  QJsonObject jsonObj = jsonDoc.object();
  qDebug() << jsonObj << Qt::endl;
  QString cResult;
  if (jsonObj.contains("error_code")) {
    cResult = "error";  // getErrorMsg(jsonObj.value("error_code").toString());
  } else {
    QJsonArray value = jsonObj.value("trans_result").toArray();
    QJsonObject object1 = value.at(0).toObject();
    cResult = object1.value("dst").toString();
  }
  reply->deleteLater();
  emit finished(cResult);
}
