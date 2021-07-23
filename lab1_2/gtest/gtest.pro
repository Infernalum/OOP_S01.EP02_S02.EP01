QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	gtest.cc \
	gtest_main.cc

HEADERS += \
	gtest/gtest-death-test.h \
	gtest/gtest-message.h \
	gtest/gtest-param-test.h \
	gtest/gtest-printers.h \
	gtest/gtest-spi.h \
	gtest/gtest-test-part.h \
	gtest/gtest-typed-test.h \
	gtest/gtest.h \
	gtest/gtest_pred_impl.h \
	gtest/gtest_prod.h \
	gtest/internal/gtest-death-test-internal.h \
	gtest/internal/gtest-filepath.h \
	gtest/internal/gtest-internal.h \
	gtest/internal/gtest-linked_ptr.h \
	gtest/internal/gtest-param-util-generated.h \
	gtest/internal/gtest-param-util.h \
	gtest/internal/gtest-port.h \
	gtest/internal/gtest-string.h \
	gtest/internal/gtest-tuple.h \
	gtest/internal/gtest-type-util.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
