#-------------------------------------------------
# 音乐播放器
#-------------------------------------------------

INCLUDEPATH     += $$PWD/src

HEADERS += \
    $$PWD/src/musicplayer.h \
    $$PWD/src/lyricwidget.h \
    $$PWD/src/lyricfactory.h \
    $$PWD/src/musictoolbar.h \
    $$PWD/src/musicrecord.h \
    $$PWD/src/musicplaylistwidget.h

SOURCES += \
    $$PWD/src/musicplayer.cpp \
    $$PWD/src/lyricwidget.cpp \
    $$PWD/src/lyricfactory.cpp \
    $$PWD/src/musictoolbar.cpp \
    $$PWD/src/musicrecord.cpp \
    $$PWD/src/musicplaylistwidget.cpp

include($$PWD/Ui/ui.pri)
include($$PWD/Skin/skin.pri)


