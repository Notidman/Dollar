QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 staticlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutmenu.cpp \
    cppfilewriter.cpp \
    dialogdir.cpp \
    dialogfile.cpp \
    dialogselecttemplate.cpp \
    dollarwriter.cpp \
    formclanguage.cpp \
    formcpplanguage.cpp \
    formphplanguage.cpp \
    gitmenu.cpp \
    main.cpp \
    mainwindow.cpp \
    projectsmenu.cpp \
    projectstructfilewriter.cpp \
    settingsmenu.cpp \
    templatesmenu.cpp \
    welcomemenu.cpp

HEADERS += \
    aboutmenu.h \
    abstractlanguagefilewriter.h \
    cppfilewriter.h \
    dialogdir.h \
    dialogfile.h \
    dialogselecttemplate.h \
    dollarwriter.h \
    formclanguage.h \
    formcpplanguage.h \
    formphplanguage.h \
    gitmenu.h \
    mainwindow.h \
    projectsmenu.h \
    projectstructfilewriter.h \
    settingsmenu.h \
    structsprojectsenums.h \
    templatesmenu.h \
    welcomemenu.h

FORMS += \
    aboutmenu.ui \
    dialogdir.ui \
    dialogfile.ui \
    dialogselecttemplate.ui \
    formclanguage.ui \
    formcpplanguage.ui \
    formphplanguage.ui \
    gitmenu.ui \
    mainwindow.ui \
    projectsmenu.ui \
    settingsmenu.ui \
    templatesmenu.ui \
    welcomemenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    DollarC_en_150.ts

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib64/release/ -lgit2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib64/debug/ -lgit2
else:unix: LIBS += -L$$PWD/../../../../../../usr/lib64/ -lgit2

INCLUDEPATH += $$PWD/../../../../../../usr/lib64
DEPENDPATH += $$PWD/../../../../../../usr/lib64

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib64/release/ -lquazip1-qt5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib64/debug/ -lquazip1-qt5
else:unix: LIBS += -L$$PWD/../../../../../../usr/lib64/ -lquazip1-qt5

INCLUDEPATH += $$PWD/../../../../../../usr/include/QuaZip-Qt5-1.2/quazip
DEPENDPATH += $$PWD/../../../../../../usr/include/QuaZip-Qt5-1.2/quazip
