## Simple socket.io-cpp-chatbot-sample
Sample of Socket.IO C++ Simple Chatbot

This program provide result of command on native client's shell to web browser.

### Compile native client.

```
$ git clone https://github.com/kukuhpro/
$ cd socket.io-cpp-client-sample
$ cd src
$ mkdir build
$ cd build
$ cmake -D SIO_DIR=<Socket.IO C++ Client dir> -D BOOST_ROOT=<Boost dir> ..
$ make
```

### Run server.

```
$ cd socket.io-cpp-client-sample
$ cd src
$ npm install
$ node index.jx
```

### Run client

```
$ cd socket.io-cpp-client-sample
$ cd src/build
$ ./client http://localhost:8000/ <Your pc's ID.>
```

### Access by web browser.

Access to [http://localhost:8000/](http://localhost:8000/) and input browser's ID.
Input command (like 'ls') and push button.
The results on C++ client are displayed.
