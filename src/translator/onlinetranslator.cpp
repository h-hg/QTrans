#include "onlinetranslator.h"

#include <QList>
#include <QStringList>

QString OnlineTranslator::encodeURL(QString const &content) {
  return QString::fromStdString(QUrl::toPercentEncoding(content).toStdString());
}

QString OnlineTranslator::encodeParams(QMap<QString, QString> const &params) {
  auto list = QList<QString>();
  for (auto iter = params.begin(); iter != params.end(); ++iter)
    list.push_back(iter.key() + QStringLiteral("=") + iter.value());
  return QStringList(list).join(QStringLiteral("&"));
}

void OnlineTranslator::translate(QString const &content, Language from,
                                 Language to) {
  if (!isSupportedLanguage(from) || !isSupportedLanguage(to)) return;
  QString fromCode = getLanguageCode(from), toCode = getLanguageCode(to);
  request(content, fromCode, toCode);
}
