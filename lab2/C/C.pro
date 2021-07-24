QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        lab2_c.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
	lab2_c.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CardDeckLib_c/release/ -lCardDeckLib_c
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CardDeckLib_c/debug/ -lCardDeckLib_c

INCLUDEPATH += $$PWD/../CardDeckLib_c
DEPENDPATH += $$PWD/../CardDeckLib_c

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CardDeckLib_c/release/libCardDeckLib_c.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CardDeckLib_c/debug/libCardDeckLib_c.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CardDeckLib_c/release/CardDeckLib_c.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CardDeckLib_c/debug/CardDeckLib_c.lib
