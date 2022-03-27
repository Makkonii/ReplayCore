#ifndef _AUTH_SERVER_H
#define _AUTH_SERVER_H

#include "../Defines/Common.h"
#include "../Crypto/BigNumber.h"

#ifdef _WIN32
#include "winsock2.h"
#else
#include <sys/socket.h>
#include <pcap/pcap.h>
#include <unistd.h>
#endif

#include <string>
#include <map>
#include <thread>

class AuthServer;
class ByteBuffer;

typedef void(AuthServer::*AuthOpcodeHandler) (ByteBuffer& buffer);

struct ClientData
{
    uint16 build = 0;
    std::string sessionKey;
    std::string name;
    BigNumber N, s, g, v;
    BigNumber b, B;
    BigNumber K;
    BigNumber _reconnectProof;
};

class AuthServer
{
public:
    static AuthServer& Instance();
    void StartNetwork();
    void StopNetwork();
    bool IsEnabled() const { return m_enabled; }
    uint16 GetClientBuild() const { return m_clientData.build; }
    std::string GetSessionKey() const { return m_clientData.sessionKey; }
    std::thread m_networkThread;
private:
    bool m_enabled = false;
    ClientData m_clientData;
    SOCKET m_authSocket;
    SOCKET m_socketPrototype;
    #ifdef _WIN32
    SOCKADDR_IN m_address;
    #else
    sockaddr_in m_address;
    #endif
    std::map<uint8, AuthOpcodeHandler> m_opcodeHandlers;

    void ResetClientData();
    void SetupOpcodeHandlers();
    void NetworkLoop();
    void HandlePacket(ByteBuffer& buffer);
    void HandleLogonChallenge(ByteBuffer& buffer);
    void HandleLogonProof(ByteBuffer& buffer);
    void HandleRealmlist(ByteBuffer& buffer);
};

#define sAuth AuthServer::Instance()

#endif