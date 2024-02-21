#ifndef TCP_LISTENER_H
#define TCP_LISTENER_H

#include <string>
#include <WinSock2.h> // or WS2tcpip.h if needed
#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE (49152)

/**
 * @brief Represents a TCP listener that listens for incoming connections and messages.
 */
class TCPlistener {
public:
    /**
     * @brief Defines a function pointer type for the message receive handler.
     *
     * @param listener The TCP listener instance.
     * @param client The socket of the client.
     * @param msg The received message.
     */
    typedef void (*MessageReceiveHandler)(TCPlistener* listener, int client, std::string msg);

    /**
     * @brief Constructs a new TCPlistener object.
     *
     * @param ipAddress The IP address on which to listen for incoming connections.
     * @param port The port number on which to listen for incoming connections.
     * @param handler The message receive handler function to be called when a message is received.
     */
    TCPlistener(std::string ipAddress, int port, MessageReceiveHandler handler);

    /**
     * @brief Destroys the TCPlistener object and cleans up any resources.
     */
    ~TCPlistener();

    /**
     * @brief Sends a message to the specified client.
     *
     * @param clientSocket The socket of the client to send the message to.
     * @param msg The message to send.
     */
    void Send(int clientSocket, const std::string& msg) const;

    /**
     * @brief Initializes Winsock.
     *
     * @return true if initialization succeeds, false otherwise.
     */
    bool init() const;

    /**
     * @brief Runs the main process loop, listening for incoming connections and messages.
     */
    void run() const;

    /**
     * @brief Cleans up resources and shuts down Winsock.
     */
    void cleanup() const;

private:
    /**
     * @brief Creates a socket for listening to incoming connections.
     *
     * @return The created socket.
     */
    SOCKET CreateSocket() const;

    /**
     * @brief Waits for a connection from a client.
     *
     * @param listening The listening socket.
     * @return The socket of the connected client.
     */
    SOCKET WaitForConnection(SOCKET& listening) const;

    int m_port; ///< The port number on which to listen for incoming connections.
    std::string m_ipAddress; ///< The IP address on which to listen for incoming connections.
    MessageReceiveHandler m_messageReceived; ///< The message receive handler function.
};

#endif // TCP_LISTENER_H
