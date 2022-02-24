QT -= gui

TEMPLATE = lib
DEFINES += DLLTEST1_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dlltest1.cpp \
    singletontest1.cpp

HEADERS += \
    dllTest1_global.h \
    dlltest1.h \
    singletontest1.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-SingletonPattern-Desktop_Qt_5_14_2_MinGW_64_bit-Debug/dllTest0/release/ -ldllTest0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-SingletonPattern-Desktop_Qt_5_14_2_MinGW_64_bit-Debug/dllTest0/debug/ -ldllTest0
else:unix: LIBS += -L$$PWD/../../build-SingletonPattern-Desktop_Qt_5_14_2_MinGW_64_bit-Debug/dllTest0/ -ldllTest0


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build-SingletonPattern-Desktop_Qt_5_14_2_MinGW_64_bit-Debug/dllDatabase/release/ -ldllDatabase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build-SingletonPattern-Desktop_Qt_5_14_2_MinGW_64_bit-Debug/dllDatabase/debug/ -ldllDatabase
else:unix: LIBS += -L$$PWD/../../build-SingletonPattern-Desktop_Qt_5_14_2_MinGW_64_bit-Debug/dllTest0/ -ldllDatabase

