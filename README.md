# qlibssh2

Qt wrapper for libssh2

## Usage
### Compilation
Build and install libssh2:
```bash
git clone https://github.com/libssh2/libssh2.git
cd libssh2
mkdir build
cmake -DCRYPTO_BACKEND=WinCNG -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=./build .
cmake --build . --target install
```

Create the path `3rdparty/libssh2` in the project's directory and add the following:
- `lib/libssh2.lib`
- `include/libssh2.h`

Build qlibssh2:
```bash
qmake
make
```

To use it in one of your projects, link it as follows:
```qmake
LIBS += -L$$PWD/3rdparty/qlibssh2/lib -lqlibssh2

INCLUDEPATH += $$PWD/3rdparty/qlibssh2/include
```


### API

```cpp
#include "Ssh2Client.h"

#include <QtCore/QCoreApplication>

using namespace qlibssh2;

int main(int argc, char *argv[])
{
    QCoreApplication app{argc, argv};

    Ssh2Settings settings;
    Ssh2Client client{settings};

    QObject::connect(&client, &Ssh2Client::sessionStateChanged, [](Ssh2Client::SessionStates state) {
        qDebug() << "state" << state;
    });
    client.connectToHost("foo@192.168.0.1");

    return app.exec();
}
```
