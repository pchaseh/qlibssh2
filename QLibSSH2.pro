QT -= gui
QT += core network

TEMPLATE = lib
DEFINES += QLIBSSH2_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include/

SOURCES += \
    src/Ssh2Debug.cpp \
    src/Ssh2LocalPortForwarding.cpp \
    src/Ssh2Process.cpp \
    src/Ssh2Scp.cpp \
    src/Ssh2Types.cpp \
    src/Ssh2Channel.cpp \
    src/Ssh2Client.cpp

HEADERS += \
    include/QLibSSH2_global.h \
    include\Ssh2Channel.h \
    include\Ssh2Debug.h \
    include\Ssh2Scp.h \
    include\Ssh2Types.h \
    include\Ssh2Client.h \
    include\Ssh2LocalPortForwarding.h \
    include\Ssh2Process.h

win32: LIBS += -L$$PWD/libssh2/libssh2.dll $$PWD/libssh2/libssh2.lib

INCLUDEPATH += $$PWD/libssh2/build/include
DEPENDPATH += $$PWD/libssh2/build/include


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
