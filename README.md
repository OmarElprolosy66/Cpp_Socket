# TCP Server

This project implements a simple TCP server using C++ and Winsock. The server listens for incoming TCP connections, receives messages from clients, and echoes those messages back.

## Features

- Listens for incoming TCP connections on a specified IP address and port.
- Receives messages from clients and echoes them back.
- Handles multiple clients sequentially.

## Requirements

- Windows operating system.
- C++ compiler (e.g., MSVC).
- Winsock library.

## Building the Project

1. Ensure you have a C++ compiler installed (e.g., MSVC).
2. Ensure you have the Winsock library available.
3. Compile the project using your preferred build system. For example, you might use the following command with MSVC:

   ```sh
   cl /EHsc /I"path\to\winsock2\include" main.cpp TCPlistener.cpp /link /LIBPATH:"path\to\winsock2\lib" ws2_32.lib
   ```

## Running the Server

1. Open a command prompt and navigate to the directory containing the compiled executable.
2. Run the server executable:

   ```sh
   server.exe
   ```

   The server will start and listen for incoming connections on IP address `127.0.0.1` and port `54010` by default.

## Testing the Server

You can test the server using various CLI tools such as `netcat`.

### Using Netcat

1. Install Netcat or `ncat` (part of the Nmap suite).
2. Open a terminal or command prompt.
3. Connect to the server using:

   ```sh
   nc 127.0.0.1 54010
   ```

4. Type a message and press Enter. You should see the message echoed back by the server.

### Using Telnet

1. Open a command prompt.
2. Connect to the server using:

   ```sh
   telnet 127.0.0.1 54010
   ```

3. Type a message and press Enter. You should see the message echoed back by the server.

## Code Overview

- `TCPlistener.hpp`: Header file defining the `TCPlistener` class.
- `TCPlistener.cpp`: Implementation file for the `TCPlistener` class.
- `main.cpp`: Entry point of the application. Initializes and runs the server.

## Troubleshooting

- **Socket Creation Failed**: Ensure the specified IP address and port are available and not in use by another application.
- **WSAStartup Failed**: Verify that Winsock is properly installed and initialized.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For questions or feedback, please contact [omarelsayed6600@gmail.com](mailto:your.email@example.com).
