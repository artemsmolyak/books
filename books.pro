#-------------------------------------------------
#
# Project created by QtCreator 2017-01-06T21:16:33
#
#-------------------------------------------------

QT       += core gui xml sql   network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TARGET = bookshelf
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    assesment.cpp \
    editdialog.cpp \
    addquotesdialog.cpp \
    quote.cpp \
    settingswindow.cpp \
    database.cpp


HEADERS  += mainwindow.h \
    data.h \
    assesment.h \
    initdb.h \
    editdialog.h \
    addquotesdialog.h \
    quote.h \
    settingswindow.h \
    database.h


FORMS    += \
    mainwindow.ui \
    assesment.ui



RESOURCES += resource/rsc.qrc


CONFIG += c++11

QMAKE_CXXFLAGS += -g


DISTFILES += \
    resource/books.sqlite \
    resource/books.xml \
    resource/bookPic.jpg \
    resource/netu.jpg \
    resource/picButtons/textbold.png \
    resource/picButtons/textcenter.png \
    resource/picButtons/textitalic.png \
    resource/picButtons/textjustify.png \
    resource/picButtons/textleft.png \
    resource/picButtons/textright.png \
    resource/picButtons/textunder.png \
    resource/empty.png \
    resource/star_fill.png \
    resource/star_no_fill.png \
    resource/bookcase.ico \
    resource/bookPic.ico \
    resource/styles/black.css \
    resource/styles/QTDark.css \
    resource/qml/main (copy).qml \
    resource/qml/main.qml \
    resource/icons/bookcase.ico \
    resource/icons/bookPic.ico

 win32:RC_FILE = myapp.rc
