# Example UDP and TCP over TLS server and client

## Prerequisites

- Linux or MacOS
- The C++ IDE [juCi++](https://gitlab.com/cppit/jucipp) is recommended

## Installing dependencies

The examples use the following libraries:

- C++ library for network and low-level I/O programming:
  [Asio C++ Library](https://think-async.com/Asio/)
- C cryptographic library: [OpenSSL](https://www.openssl.org/)

### Manjaro

Run the following command to install this package in Manjaro:

```sh
sudo pacman -S asio openssl
```

### MacOS

Run the following command to install this package in MacOS:

```sh
brew install asio openssl
```

## Running

To run tls.cpp you need to create a self-signed SSL certificate, and store the certificate and private key in server.crt and server.key, respectively.
