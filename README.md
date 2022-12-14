# Network Programming with Boost Asio

The following is the repository for network programming with [Boost Asio <boost/asio.hpp>](https://www.boost.org/). The content from this repository if from the course Advanced Programming Techniques (CSE411) provided by Lehigh University.

## Abstract

Steps to communicate through the network:
- Create an IO context object (abstraction of the OS data transfer interface)
- Resolve the hostname you want to connect to
- Create a socket and connect using the socket
- Transfer data (requesting or serving)

The following repository holds the programs following the steps above. The detailed implementations are discussed.

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
g++ -std=c++20 -pthread -I./boost-1.80.0 -I./boost-1.80.0/include -o ./bin/<target_file> ./src/<source_file>
```

## Executing target file
```bash
./bin/<target_file>
```

## Detail: Steps to communicate through the network with Boost Asio
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

The detail implementation is at the file [**./src/io_context.cpp**](./src/io_context.cpp), which output the following when the file is compiled and executed:

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

The detail implementation is at the file [**./src/hostname_resol.cpp**](./src/hostname_resol.cpp), which output the following when the file is compiled and executed:

```
http www.google.com 142.250.80.100:80
http www.google.com [2607:f8b0:4006:80d::2004]:80
```

It can also be implemented to run asynchronously. The asynchronous implemetation is at the file [**./src/hostname_resol_async.cpp**](./src/hostname_resol_async.cpp).

### 3. Create a socket and connect using the socket

Once we have the IP address of the service we want to connect to, we create a connection by:
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

The detail implementation is at the file [**./src/ip_connect.cpp**](./src/ip_connect.cpp), which output the following when the file is compiled and executed:

```
Connected to : 142.251.40.196:80
```

### 4. Transfer data (requesting or serving)

Any data transfer with Boost Asio is done using buffers. Types of buffer in Boost Asio (all support two methods data() and size()).
- Constant Buffer (boost::asio::const_buffer) cannot be modified once constructed
- Mutable Buffer (boost::asio::mutable_buffer) can be modified after construction
- Resizable Buffer (boost::asio:streambuf) resizable automatically (based on std::streambuf)

Implementations of different buffer types is at the file [**./src/asio_buffers.cpp**](./src/asio_buffers.cpp), which output the following when the file is compiled and executed:
```
Mutable buffer: 20
Constant buffer: 20
Stream buffer size: 16
String from Stream buffer: Hello
Stream buffer size: 11
```

Data can be read from active sockets into buffers or written to active sockets from buffers. Three functions for reads and two for writing:

**Reading Data from sockets**

| Function                             | Description   |
| ------------------------------------ | ------------- |
| read(s, b, [cmp], [ec])              | Read from socket s into a mutate buffer b according to completion condition cmp. Sets the error_code ec if an error condition is encountered, otherwise, throws a system_error |
| read_at(s, off, b, [cmp], [ec])      | Reads from socket s, starting from size_t offset off, into a mutable buffer b according to completion condition cmp. Sets the error_code ec if an error condition is encountered; otherwise, throws a system_error |
| read_until(s, b, x, [ec])            | Reads from socket s into a mutable buffer b until it meets a condition represented by x, which can be one of the following: a char, a string_view, a boost::regex, or a match condition. Sets the error_code ec if an error is encountered; otherwise, throws a system error |

**Writing Data to sockets**

| Function                             | Description   |
| ------------------------------------ | ------------- |
| write(s, b, [cmp], [ec])             | Writes into socket s from a const buffer b according to completion condition cmp. Sets the error_code ec if an error condition is encountered, otherwise, throws a system_error |
| write_at(s, off, b, [cmp], [ec])     | Writes into socket s, from a mutable buffer b starting from size_t offset off, according to completion condition cmp. Sets the error_code ec if an error condition is encountered; otherwise, throws a system_error |

The file [**./src/simple_http_client.cpp**](./src/simple_http_client.cpp) implements a simple HTTP client example that connects to a server and requests a response, which outputs the HTTP response of www.google.com.

The file [**./src/simple_echo_server.cpp**](./src/simple_echo_server.cpp) implements a simple echo server example that listens on a port and responds to requests with capitalized version of the request. the outputs should be as following following when the file is compiled and executed:

```bash
% ./bin/simple_echo_server &
% ncat localhost 1895
hello
HELLO
^C
read_until: End of file [asio.misc:2]
```

Additionally, the file [**./src/simple_echo_server_threads.cpp**](./src/simple_echo_server_threads.cpp) implements the same echo server example but with multiple threads (work-in-progress).
