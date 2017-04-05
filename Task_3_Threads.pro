TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#boost include
INCLUDEPATH += "$$(Boost_DIR)"
LIBS += "-L$$(Boost_DIR)\stage\lib"

SOURCES += main.cpp \
    scaner.cpp \
    parser.cpp \
    projectAnalyzer.cpp

HEADERS += parser.h \
    scaner.h \
    stringMutexQueue.h \
    projectAnalyzer.h
