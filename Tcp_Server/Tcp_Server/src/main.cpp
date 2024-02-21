#include <iostream>
#include "TCPlistener.hpp"

// Function to handle received messages
void Listener_MessageReceived(TCPlistener* listener, int client, std::string msg);

int main() {
    // Create a TCP listener instance with IP address "127.0.0.1" and port number 54010
    TCPlistener server("127.0.0.1", 54010, Listener_MessageReceived);

    // Initialize the server
    if (!server.init()) {
        std::cerr << "Server initialization failed." << std::endl;
        return 1; // Return error code 1 to indicate initialization failure
    }

    // Run the server to start listening for incoming connections and messages
    server.run();

    return 0; // Return 0 to indicate successful completion
}

// Function to handle received messages
void Listener_MessageReceived(TCPlistener* listener, int client, std::string msg) {
    // Echo the received message back to the client
    listener->Send(client, msg);
}
