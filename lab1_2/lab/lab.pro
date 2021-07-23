QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	lab1_2.cpp \
	main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
	lab1_2.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CetaneryLib/release/ -lCetaneryLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CetaneryLib/debug/ -lCetaneryLib
else:unix: LIBS += -L$$OUT_PWD/../CetaneryLib/ -lCetaneryLib

INCLUDEPATH += $$PWD/../CetaneryLib
DEPENDPATH += $$PWD/../CetaneryLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CetaneryLib/release/libCetaneryLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CetaneryLib/debug/libCetaneryLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CetaneryLib/release/CetaneryLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CetaneryLib/debug/CetaneryLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CetaneryLib/libCetaneryLib.a
