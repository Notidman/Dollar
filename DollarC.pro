QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutmenu.cpp \
    dialogdir.cpp \
    dialogfile.cpp \
    dialogselecttemplate.cpp \
    dollarwriter.cpp \
    formcpplanguage.cpp \
    formphplanguage.cpp \
    formtemplate.cpp \
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
    dialogdir.h \
    dialogfile.h \
    dialogselecttemplate.h \
    dollarwriter.h \
    formcpplanguage.h \
    formphplanguage.h \
    formtemplate.h \
    gitmenu.h \
    mainwindow.h \
    projectsmenu.h \
    projectstructfilewriter.h \
    settingsmenu.h \
    templatesmenu.h \
    welcomemenu.h

FORMS += \
    aboutmenu.ui \
    dialogdir.ui \
    dialogfile.ui \
    dialogselecttemplate.ui \
    formcpplanguage.ui \
    formphplanguage.ui \
    formtemplate.ui \
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
