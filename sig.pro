TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \ 
    sgf_utils.cpp \
    sgfnode.cpp \
    sgftree.cpp \
    sgfmerge.cpp \
    main.cpp

HEADERS += \
    sgf_properties.h \
    sgftree.h

DISTFILES += \
    sgf_extras.def \
    sgf_properties.def
