TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#boost
INCLUDEPATH += "D:\boost_1_63_0"
LIBS += "-LD:\boost_1_63_0\stage\lib"

SOURCES += main.cpp \
    scaner.cpp \
    parser.cpp

HEADERS += parser.h \
    scaner.h \
    stringMutexQueue.h
