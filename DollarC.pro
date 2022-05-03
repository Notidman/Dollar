QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientmenu.cpp \
    dialognamedir.cpp \
    dialognamefile.cpp \
    dialognamenew.cpp \
    dialogselecttemplate.cpp \
    filegenerator.cpp \
    main.cpp \
    mainwindow.cpp \
    projectsmenu.cpp \
    settingsmenu.cpp \
    templatesmenu.cpp \
    welcomemenu.cpp

HEADERS += \
    clientmenu.h \
    dialognamedir.h \
    dialognamefile.h \
    dialognamenew.h \
    dialogselecttemplate.h \
    filegenerator.h \
    mainwindow.h \
    projectsmenu.h \
    settingsmenu.h \
    templatesmenu.h \
    welcomemenu.h

FORMS += \
    clientmenu.ui \
    dialognamedir.ui \
    dialognamefile.ui \
    dialognamenew.ui \
    dialogselecttemplate.ui \
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
