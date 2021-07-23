TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CetaneryLib/release/ -lCetaneryLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CetaneryLib/debug/ -lCetaneryLib

INCLUDEPATH += $$PWD/../CetaneryLib
DEPENDPATH += $$PWD/../CetaneryLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CetaneryLib/release/libCetaneryLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CetaneryLib/debug/libCetaneryLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CetaneryLib/release/CetaneryLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CetaneryLib/debug/CetaneryLib.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gtest/release/ -lgtest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gtest/debug/ -lgtest

INCLUDEPATH += $$PWD/../gtest
DEPENDPATH += $$PWD/../gtest

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gtest/release/libgtest.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gtest/debug/libgtest.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gtest/release/gtest.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../gtest/debug/gtest.lib
