QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cliLogic.cpp \
    creategroupwindow.cpp \
    createpostwindow.cpp \
    group.cpp \
    home.cpp \
    main.cpp \
    mainwindow.cpp \
    post.cpp \
    register.cpp \
    searchwindow.cpp \
    sendmessagewindow.cpp \
    showfriendswindow.cpp \
    showmygroups.cpp \
    showprofilewindow.cpp \
    updateuserinfo.cpp \
    user.cpp

HEADERS += \
    cliLogic.h \
    creategroupwindow.h \
    createpostwindow.h \
    group.h \
    home.h \
    mainwindow.h \
    post.h \
    register.h \
    searchwindow.h \
    sendmessagewindow.h \
    showfriendswindow.h \
    showmygroups.h \
    showprofilewindow.h \
    updateuserinfo.h \
    updateuserui.h \
    user.h

FORMS += \
    creategroupwindow.ui \
    createpostwindow.ui \
    home.ui \
    mainwindow.ui \
    register.ui \
    searchwindow.ui \
    sendmessagewindow.ui \
    showfriendswindow.ui \
    showmygroups.ui \
    showprofilewindow.ui \
    updateuserinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
