TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#boost
#INCLUDEPATH += "D:\boost_1_63_0"
#LIBS += "-LD:\boost_1_63_0\stage\lib"

#filesystem
INCLUDEPATH += "$$PWD\boost"
LIBS += "-L$$PWD\3rd_party\libs\boost"

SOURCES += main.cpp \
    scaner.cpp \
    parser.cpp

HEADERS += parser.h \
    scaner.h \
    stringMutexQueue.h \
