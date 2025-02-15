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
#include <QList>
#include <QPointer>
#include <QtNetwork/QTcpSocket>

#include "Ssh2Types.h"

#include "QLibSSH2_global.h"


namespace qlibssh2
{
class QLIBSSH2_EXPORT Ssh2Process;
class QLIBSSH2_EXPORT Ssh2Channel;
class QLIBSSH2_EXPORT Ssh2Scp;
class QLIBSSH2_EXPORT Ssh2LocalPortForwarding;

class QLIBSSH2_EXPORT Ssh2Client final : public QTcpSocket
{
    Q_OBJECT
    Q_ENUMS(SessionStates Ssh2AuthMethods)
    Q_PROPERTY(SessionStates sessionState READ sessionState NOTIFY sessionStateChanged)
    Q_PROPERTY(int channelsCount READ channelsCount NOTIFY channelsCountChanged)
    Q_PROPERTY(int openChannelsCount READ openChannelsCount NOTIFY openChannelsCountChanged)
public:
    enum Ssh2AuthMethods {
        NoAuth,
        PublicKeyAuthentication,
        PasswordAuthentication
    };

    enum SessionStates {
        NotEstableshed,
        StartingSession,
        GetAuthMethods,
        Authentication,
        Established,
        FailedToEstablish,
        Closing,
        Closed,
        Aborted
    };
    Q_ENUM(SessionStates)

    Ssh2Client(Ssh2Settings ssh2_settings_,
               QObject* parent = nullptr);

    ~Ssh2Client();

    using QTcpSocket::connectToHost;
    void connectToHost(const QString& hostName, qint16 port = 22);
    void connectToHost(const QString& userName, const QString& hostName, quint16 port = 22);

    SessionStates sessionState() const;

    void disconnectFromHost() override;

    LIBSSH2_SESSION* ssh2Session() const;

    QPointer<Ssh2Process> createProcess(const QString& command);
    QPointer<Ssh2Scp> scpSend(const QString& localFilePath, const QString &destinationPath);
    QPointer<Ssh2Scp> scpReceive(const QString& remoteFilePath, const QString &destinationPath);
    QPointer<Ssh2LocalPortForwarding>
    localPortForwarding(quint16 localListenPort, const QHostAddress &remoteHost, quint16 remoteListenPort);
    QPointer<Ssh2LocalPortForwarding>
    localPortForwarding(const QHostAddress& localHost, quint16 localListenPort,
                        const QHostAddress &remoteHost, quint16 remoteListenPort);

    int channelsCount() const;
    int openChannelsCount() const;

    std::error_code appendToKnownHosts(const QLatin1String& comment) const;

signals:
    void sessionStateChanged(SessionStates ssh2_state);
    void ssh2Error(std::error_code ssh2_error);

    void openChannelsCountChanged(int openChannelsCount);
    void channelsCountChanged(int openChannelsCount);

private slots:
    void onTcpConnected();
    void onTcpDisconnected();
    void onReadyRead();

    void onChannelStateChanged(int state);

    void onSocketStateChanged(const QAbstractSocket::SocketState& state);

private:
    void addChannel(Ssh2Channel* channel);
    QList<Ssh2Channel*> getChannels() const;

    void setSsh2SessionState(const SessionStates& new_state);
    const std::error_code& setSsh2SessionState(const SessionStates& new_state,
                                               const std::error_code& error_code);

    void destroySsh2Objects();
    std::error_code createSsh2Objects();

    std::error_code checkKnownHosts() const;
    std::error_code getAvailableAuthMethods();
    Ssh2AuthMethods getAuthenticationMethod(const QList<Ssh2AuthMethods>& available_auth_methods) const;
    std::error_code authenticate();
    std::error_code startSshSession();
    void closeChannels();
    void closeSession();
    void checkConnection();

    std::error_code setLastError(const std::error_code& error_code);

    Ssh2Settings ssh2_settings_;
    SessionStates ssh2_state_;

    QList<Ssh2AuthMethods> ssh2_available_auth_methods_;
    Ssh2AuthMethods ssh2_auth_method_;

    std::error_code last_error_;

    LIBSSH2_SESSION* ssh2_session_;
    LIBSSH2_KNOWNHOSTS* known_hosts_;
};
} // namespace qlibssh2
