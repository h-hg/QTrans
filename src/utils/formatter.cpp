#include "formatter.h"

#include <QRegularExpression>
#include <QVector>

Formatter::Formatter(QObject *parent) : QObject(parent) {}

QString Formatter::removeLineBreaks(const QString &content) {
  QString ret = content;
  QVector<QPair<QRegularExpression, QString>> rules = {
      {QRegularExpression(QStringLiteral("([a-z])-\n([a-z])")),
       QStringLiteral("\\1\\2")},  // splited word
      {QRegularExpression(QStringLiteral("([^.])(\n)")),
       QStringLiteral("\\1 ")}  // unfinished sentence
  };
  for (auto &rule : rules) ret.replace(rule.first, rule.second);
  return ret;
}

QString Formatter::removeRedundantSpace(const QString &content) {
  return content.simplified();
}
