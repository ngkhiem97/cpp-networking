# Network Programming

The following is the repository for network programming, which is taught in the course Advanced Programming Techniques (CSE411) at Lehigh University.

## Abstract

Steps to communicate through the network:
- Create an IO context object (abstraction of the OS data transfer interface)
- Resolve the hostname you want to connect to
- Create a socket
- Connect using the socket
- Transfer data (requesting or serving)
- Close the connection

The following repository holds the programs following the steps above.

## Repository structure

- bin: binary/executed files.
- src: source files of the binary/executed files

## Requirements

**Download Boost Asio libraries for network and low-level I/O programming**

```bash
wget https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.bz2
gzip boost_1_80_0.tar.bz2 boost-1.80.0
```

## Compiling source files

```bash
g++ -std=c++20 -pthread -I./boost-1.80.0 -I./boost-1.80.0/include -L./boost-1.80.0/lib -o ./bin/<target_file> ./src/<source_file> -lboost_thread
```

## Executing target file
```bash
./bin/<target_file>
```

## Detail: Steps to communicate through the network
### 1. Create an IO context object (abstraction of the OS data transfer interface)

As an example with Boost Asio, an io context object can be created as:

```c++
#include <boost/asio.hpp>
// Creating a default io context object
boost::asio::io_context io_context;
// Creating an io context object with
// concurrency hint = 8
boost::asio::io_context io_context{8};
// The io context object will block until
// all IO operations associated with the
// object complete
io_context.run();
```

The detail implementation is at the file **./src/io_context.cpp**, which output the following when the file is compiled and executed:

```
Entering steady_timer::wait
Exited steady_timer::wait
Entering steady_timer::async_wait
Exited steady_timer::async_wait
Entering io_context::run
<<callback function>>
Exited io_context
```

### 2. Resolve the hostname you want to connect to

To resolve the hostname of a server with Boost Asio:
```cpp
#include <boost/asio.hpp>
// Creating a default io context object
boost::asio::io_context io_context;
// Creating a hostname resolver object
boost::asio::ip::tcp::resolver
resolver{io_context};
// Invoking the resolve function on the resolver
resolver.resolve("www.google.com", "http", ec);
```

The detail implementation is at the file **./src/hostname_resol.cpp**, which output the following when the file is compiled and executed:

```
http www.google.com 142.250.80.100:80
http www.google.com [2607:f8b0:4006:80d::2004]:80
```

It can also be implemented to run asynchronously. The asynchronous implemetation is at the file **./src/hostname_resol_async.cpp**.

### 3. Create a socket

Once we have the IP address of the service we want to connect to, we create a connection
- Create a socket
- Connect using the socket

To connect to an IP address using the socket with Boost Asio:
```cpp
#include <boost/asio.hpp>
// Creating a default io context object
boost::asio::io_context io_context;
// Creating a socket object
boost::asio::ip::tcp::socket
socket{io_context};
// Invoking the connect function on the socket
boost::asio::connect(socket, endpoint);
```

The detail implementation is at the file **./src/ip_connect.cpp**, which output the following when the file is compiled and executed:

```
Connected to : 142.251.40.196:80
```