# cpp-networking

The following is the repository for network programming, which is taught in the course Advanced Programming Techniques (CSE411) at Lehigh University.

## Abstract

Steps to communicate through the network
- Create an IO context object (abstraction of the OS data transfer interface)
- Resolve the hostname you want to connect to
- Create a socket
- Connect using the socket
- Transfer data (requesting or serving)
- Close the connection

## Repository structure

- bin: binary/executed files.
- boost-1.80.0: Boost Asio libraries for network and low-level I/O programming.
- src: source files of the binary/executed files