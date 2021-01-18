#ifndef FORMATTER_H
#define FORMATTER_H

#include <QObject>

class Formatter : public QObject {
  Q_OBJECT
 public:
  explicit Formatter(QObject *parent = nullptr);
  static QString removeLineBreaks(QString const &content);
  static QString removeRedundantSpace(QString const &content);
 signals:
};

#endif  // FORMATTER_H
