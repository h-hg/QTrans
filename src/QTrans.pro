QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    translator/baidutranslator2.cpp \
    translator/googletranslator.cpp \
    translator/onlinetranslator.cpp \
    translator/translator.cpp \
    translator/youdaotranslator.cpp \
    utils/formatter.cpp

HEADERS += \
    mainwindow.h \
    translator/baidutranslator2.h \
    translator/googletranslator.h \
    translator/onlinetranslator.h \
    translator/translator.h \
    translator/youdaotranslator.h \
    utils/formatter.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    language/en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
