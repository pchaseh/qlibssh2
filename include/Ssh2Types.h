/*
MIT License

Copyright (c) 2020 Mikhail Milovidov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once

#include <QMetaType>
#include <QString>

#include <system_error>

#include "QLibSSH2_global.h"


struct _LIBSSH2_SESSION;
typedef struct _LIBSSH2_SESSION LIBSSH2_SESSION;

struct _LIBSSH2_CHANNEL;
typedef struct _LIBSSH2_CHANNEL LIBSSH2_CHANNEL;

struct _LIBSSH2_KNOWNHOSTS;
typedef struct _LIBSSH2_KNOWNHOSTS LIBSSH2_KNOWNHOSTS;

namespace qlibssh2
{

extern const std::error_code ssh2_success;

QLIBSSH2_EXPORT QString defaultUser();
QLIBSSH2_EXPORT QString defaultKey();
QLIBSSH2_EXPORT QString defaultKnownHosts();

struct QLIBSSH2_EXPORT Ssh2Settings {
    QString user = defaultUser();
    quint16 port = 22;
    QString passphrase;
    QString key = defaultKey();
    QString keyphrase;
    QString known_hosts = defaultKnownHosts();
    unsigned int timeout = 1000;
    bool autoAppendToKnownHosts = false;
    QLatin1String autoAppendKnownHostComment;
    bool isPasswordAuth() const;
    bool isKeyAuth() const;
};

enum Ssh2Error {
    ErrorReadKnownHosts = 1,
    ErrorWriteKnownHosts,
    SessionStartupError,
    UnexpectedError,
    HostKeyInvalidError,
    HostKeyMismatchError,
    HostKeyUnknownError,
    HostKeyAppendError,
    AuthenticationError,
    FailedToOpenChannel,
    FailedToCloseChannel,
    ProcessFailedToStart,
    ChannelReadError,
    ChannelWriteError,
    TryAgain,
    ConnectionTimeoutError,
    TcpConnectionError,
    TcpConnectionRefused,
    ScpReadFileError,
    ScpWriteFileError
};

QLIBSSH2_EXPORT std::error_code make_error_code(Ssh2Error ssh2_error);
} // namespace qlibssh2

Q_DECLARE_METATYPE(qlibssh2::Ssh2Settings)

namespace std
{
template <>
struct QLIBSSH2_EXPORT is_error_code_enum<qlibssh2::Ssh2Error> : true_type {
};
} // namespace std
