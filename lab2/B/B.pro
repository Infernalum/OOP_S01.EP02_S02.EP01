QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        lab2_b.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
	lab2_b.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CardDeckLib_a_b/release/ -lCardDeckLib_a_b
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CardDeckLib_a_b/debug/ -lCardDeckLib_a_b

INCLUDEPATH += $$PWD/../CardDeckLib_a_b
DEPENDPATH += $$PWD/../CardDeckLib_a_b

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CardDeckLib_a_b/release/libCardDeckLib_a_b.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CardDeckLib_a_b/debug/libCardDeckLib_a_b.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CardDeckLib_a_b/release/CardDeckLib_a_b.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CardDeckLib_a_b/debug/CardDeckLib_a_b.lib
