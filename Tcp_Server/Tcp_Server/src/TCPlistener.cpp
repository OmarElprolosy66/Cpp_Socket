#include <iostream>
#include <WS2tcpip.h>
#include "TCPlistener.hpp"

/**
 * @brief Constructs a TCP listener object.
 *
 * @param ipAddress The IP address on which to listen for incoming connections.
 * @param port The port number on which to listen for incoming connections.
 * @param handler The message receive handler function to be called when a message is received.
 */
TCPlistener::TCPlistener(std::string ipAddress, int port, MessageReceiveHandler handler)
    : m_ipAddress(ipAddress), m_port(port), m_messageReceived(handler) { }

/**
 * @brief Destroys the TCP listener object and cleans up any resources.
 */
TCPlistener::~TCPlistener() {
    cleanup();
}

/**
 * @brief Sends a message to the specified client.
 *
 * @param clientSocket The socket of the client to send the message to.
 * @param msg The message to send.
 */
void TCPlistener::Send(int clientSocket, const std::string& msg) const {
    send(clientSocket, msg.c_str(), msg.size(), 0); // Avoid sending the null terminator
}

/**
 * @brief Initializes Winsock.
 *
 * @return true if initialization succeeds, false otherwise.
 */
bool TCPlistener::init() const {
    WSADATA data;
    WORD version = MAKEWORD(2, 2);
    int winit = WSAStartup(version, &data);
    if (winit != 0) {
        std::cerr << "WSAStartup failed: " << winit << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Runs the main process loop, listening for incoming connections and messages.
 */
void TCPlistener::run() const {
    char buf[MAX_BUFFER_SIZE];

    while (true) {
        SOCKET listening = CreateSocket();
        if (listening == INVALID_SOCKET) {
            std::cerr << "Failed to create socket." << std::endl;
            break;
        }

        SOCKET client = WaitForConnection(listening);
        if (client != INVALID_SOCKET) {
            closesocket(listening);

            int byteReceived = 0;
            do {
                ZeroMemory(buf, MAX_BUFFER_SIZE);
                byteReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
                if (byteReceived > 0) {
                    if (m_messageReceived != nullptr)
                        m_messageReceived((TCPlistener*)this, client, std::string(buf, byteReceived));
                }
            } while (byteReceived > 0);
            closesocket(client);
        }
    }
    cleanup();
}

/**
 * @brief Cleans up resources and shuts down Winsock.
 */
void TCPlistener::cleanup() const {
    WSACleanup();
}

/**
 * @brief Creates a socket for listening to incoming connections.
 *
 * @return The created socket.
 */
SOCKET TCPlistener::CreateSocket() const {
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        std::cerr << "socket creation failed: " << WSAGetLastError() << std::endl;
        return INVALID_SOCKET;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ipAddress.c_str(), &hint.sin_addr);

    int bindResult = bind(listening, (sockaddr*)&hint, sizeof(hint));
    if (bindResult == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
        closesocket(listening);
        return INVALID_SOCKET;
    }

    int listenResult = listen(listening, SOMAXCONN); // SOMAXCONN is a reasonable backlog size
    if (listenResult == SOCKET_ERROR) {
        std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
        closesocket(listening);
        return INVALID_SOCKET;
    }

    return listening;
}

/**
 * @brief Waits for a connection from a client.
 *
 * @param listening The listening socket.
 * @return The socket of the connected client.
 */
SOCKET TCPlistener::WaitForConnection(SOCKET& listening) const {
    SOCKET client = accept(listening, nullptr, nullptr);
    if (client == INVALID_SOCKET) {
        std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
    }
    return client;
}
