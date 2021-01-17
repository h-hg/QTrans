#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QLocale>
#include <QMap>
#include <QObject>
#include <QString>

class Translator : public QObject {
  Q_OBJECT
 public:
  enum Language {
    NoLanguage = -1,
    Auto,
    Afrikaans,
    Albanian,
    Amharic,
    Arabic,
    Armenian,
    Azerbaijani,
    Bashkir,
    Basque,
    Belarusian,
    Bengali,
    Bosnian,
    Bulgarian,
    Cantonese,
    Catalan,
    Cebuano,
    Chichewa,
    Corsican,
    Croatian,
    Czech,
    Danish,
    Dutch,
    English,
    Esperanto,
    Estonian,
    Fijian,
    Filipino,
    Finnish,
    French,
    Frisian,
    Galician,
    Georgian,
    German,
    Greek,
    Gujarati,
    HaitianCreole,
    Hausa,
    Hawaiian,
    Hebrew,
    HillMari,
    Hindi,
    Hmong,
    Hungarian,
    Icelandic,
    Igbo,
    Indonesian,
    Irish,
    Italian,
    Japanese,
    Javanese,
    Kannada,
    Kazakh,
    Khmer,
    Kinyarwanda,
    Klingon,
    KlingonPlqaD,
    Korean,
    Kurdish,
    Kyrgyz,
    Lao,
    Latin,
    Latvian,
    LevantineArabic,
    Lithuanian,
    Luxembourgish,
    Macedonian,
    Malagasy,
    Malay,
    Malayalam,
    Maltese,
    Maori,
    Marathi,
    Mari,
    Mongolian,
    Myanmar,
    Nepali,
    Norwegian,
    Oriya,
    Papiamento,
    Pashto,
    Persian,
    Polish,
    Portuguese,
    Punjabi,
    QueretaroOtomi,
    Romanian,
    Russian,
    Samoan,
    ScotsGaelic,
    SerbianCyrillic,
    SerbianLatin,
    Sesotho,
    Shona,
    SimplifiedChinese,
    Sindhi,
    Sinhala,
    Slovak,
    Slovenian,
    Somali,
    Spanish,
    Sundanese,
    Swahili,
    Swedish,
    Tagalog,
    Tahitian,
    Tajik,
    Tamil,
    Tatar,
    Telugu,
    Thai,
    Tongan,
    TraditionalChinese,
    Turkish,
    Turkmen,
    Udmurt,
    Uighur,
    Ukrainian,
    Urdu,
    Uzbek,
    Vietnamese,
    Welsh,
    Xhosa,
    Yiddish,
    Yoruba,
    YucatecMaya,
    Zulu
  };
  Q_ENUM(Language)
  explicit Translator(QObject *parent = nullptr) : QObject(parent){};
  virtual ~Translator() {}
  static QString getLanguageName(Language lang);
  static Language getLanguage(QLocale const &locale);
  virtual bool isSupportedLanguage(Language lang) = 0;
  virtual bool isRunning() = 0;
  virtual QString getLanguageCode(Language lang) = 0;
  virtual void translate(QString const &content, Language from,
                         Language to) = 0;

 protected:
  static QMap<Language, QString> const genericLang2Code;
 signals:
  void finished(QString);
};

#endif  // TRANSLATOR_H
