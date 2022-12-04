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

As an example, an io context object can be created as:

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