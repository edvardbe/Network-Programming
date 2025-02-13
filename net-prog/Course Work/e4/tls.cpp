#include <asio.hpp>
#include <asio/ssl.hpp>
#include <iostream>
#include <thread>

using namespace std;

class EchoServer {
  asio::awaitable<void> handle_request(asio::ssl::stream<asio::ip::tcp::socket> socket) {
    co_await socket.async_handshake(asio::ssl::stream_base::server, asio::use_awaitable);
    cout << "Server: handshake successful" << endl;

    for (;;) {
      std::string buffer;
      auto bytes_transferred = co_await asio::async_read_until(socket, asio::dynamic_buffer(buffer), "\r\n", asio::use_awaitable);
      auto message = buffer.substr(0, bytes_transferred - 2); // Strip \r\n at end of buffer
      cout << "Server: received: " << message << endl;
      // Close socket when "exit" is retrieved from client
      if (message == "exit") {
        cout << "Server: closing connection" << endl;
        // Connection is closed when socket is destroyed
        co_return;
      }
      bytes_transferred = co_await asio::async_write(socket, asio::buffer(buffer), asio::use_awaitable);
      cout << "Server: sent: " << message << endl;
    }
  }

public:
  asio::awaitable<void> start() {
    auto executor = co_await asio::this_coro::executor;
    asio::ip::tcp::acceptor acceptor(executor, {asio::ip::tcp::v6(), 3000});

    cout << "Server: waiting for connection" << endl;
    asio::ssl::context ssl_context(asio::ssl::context::tlsv13_server);
    ssl_context.use_certificate_chain_file("server.crt");
    ssl_context.use_private_key_file("server.key", asio::ssl::context::pem);
    for (;;) {
      asio::ssl::stream<asio::ip::tcp::socket> socket(co_await acceptor.async_accept(asio::use_awaitable), ssl_context);
      cout << "Server: connection from " << socket.lowest_layer().remote_endpoint().address() << ':' << socket.lowest_layer().remote_endpoint().port() << endl;

      co_spawn(executor, handle_request(std::move(socket)), asio::detached);
    }
  }
};

class EchoClient {
public:
  asio::awaitable<void> start() {
    auto executor = co_await asio::this_coro::executor;
    asio::ip::tcp::resolver resolver(executor);

    // Resolve host (DNS-lookup if needed)
    auto resolver_results = co_await resolver.async_resolve("localhost", to_string(3000), asio::use_awaitable);

    asio::ssl::context ssl_context(asio::ssl::context::tlsv13_client);
    ssl_context.set_verify_mode(asio::ssl::verify_none);
    asio::ssl::stream<asio::ip::tcp::socket> socket(executor, ssl_context);
    co_await asio::async_connect(socket.lowest_layer(), resolver_results, asio::use_awaitable);
    cout << "Client: connected" << endl;

    co_await socket.async_handshake(asio::ssl::stream_base::client, asio::use_awaitable);
    cout << "Client: handshake successful" << endl;

    std::string message("hello");
    auto bytes_transferred = co_await asio::async_write(socket, asio::buffer(message + "\r\n"), asio::use_awaitable);
    cout << "Client: sent: " << message << endl;

    std::string buffer;
    bytes_transferred = co_await asio::async_read_until(socket, asio::dynamic_buffer(buffer), "\r\n", asio::use_awaitable);
    message = buffer.substr(0, bytes_transferred - 2); // Strip \r\n at end of buffer
    cout << "Client: received: " << message << endl;

    message = "exit";
    bytes_transferred = co_await asio::async_write(socket, asio::buffer(message + "\r\n"), asio::use_awaitable);
    cout << "Client: sent: " << message << endl;
  }
};

int main() {
  // Provides asynchronous I/O functionality
  asio::io_context event_loop(1);

  EchoServer echo_server;
  co_spawn(event_loop, echo_server.start(), asio::detached);

  EchoClient echo_client;
  co_spawn(event_loop, echo_client.start(), asio::detached);

  event_loop.run();
}
