#include <asio.hpp>
#include <iostream>
#include <thread>

using namespace std;

class EchoServer {
  asio::io_context &io_context;
  asio::ip::tcp::endpoint endpoint;
  asio::ip::tcp::acceptor acceptor;

  void handle_request(const shared_ptr<asio::ip::tcp::socket> &socket) {
    // Read buffer with automatic memory management through reference counting
    auto read_buffer = make_shared<std::string>();
    // Read from client until newline ("\r\n")
    async_read_until(*socket, asio::dynamic_buffer(*read_buffer), "\r\n", [this, socket, read_buffer](const error_code &ec, size_t bytes_transferred) {
      // If not error:
      if (!ec) {
        // Retrieve message from client as string, without the last two characters (\r\n)
        auto message = read_buffer->substr(0, bytes_transferred - 2);

        cout << "Server: received: " << message << endl;

        // Close socket when "exit" is retrieved from client
        if (message == "exit") {
          cout << "Server: closing connection" << endl;
          // Connection is closed when socket is destroyed
          return;
        }

        if (message.substr(0, 4) == "GET ") {
          string request_path = message.substr(4, message.find(" ", 4) - 4);
          cout << "Request path: " << request_path << endl;

          // Handle the different GET requests
          if (request_path == "/") {
            send_response(socket, "<h1>Welcome to the Echo Server!</h1>");
          } else if (request_path == "/page1") {
            send_response(socket, "<html><body><h1>Page 1</h1><p>This is page 1</p></body></html>");
          } else if (request_path == "/page2") {
            send_response(socket, "<html><body><h1>Page 2</h1><p>This is page 2</p></body></html>");
          } else {
            send_response(socket, "404 Not Found: Page not found");
          }
        }  
      }
    });
  }

  void send_response(const shared_ptr<asio::ip::tcp::socket> &socket, const string &message) {
    // Construct HTTP response
    string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Length: " + to_string(message.length()) + "\r\n";
    response += "Content-Type: text/html; charset=UTF-8\r\n";
    response += "\r\n";
    response += message + "\r\n";

    // Write response to client
    auto write_buffer = make_shared<std::string>(response);
    async_write(*socket, asio::buffer(*write_buffer), [this, socket, write_buffer](const error_code &ec, size_t bytes_transferred) {
      if (!ec) {
        cout << "Server: sent: " << write_buffer->substr(0, bytes_transferred - 2) << endl;
        // Handle new request
        handle_request(socket);
      }
    });
  }

public:
  // Initializing the fields of the EchoServer object, io_context, endpoint and acceptor, using their constructors
  EchoServer(asio::io_context &io_context_) : io_context(io_context_), endpoint(asio::ip::tcp::v6(), 3000), acceptor(io_context, endpoint) {}

  void start() {
    // The (client) socket (connection) is added to the lambda and handle_request
    // in order to keep the object alive for as long as it is needed.
    // make_shared creates an object with automatic memory management through reference counting
    auto socket = make_shared<asio::ip::tcp::socket>(io_context);

    // Accepts a new connection.
    acceptor.async_accept(*socket, [this, socket](const error_code &ec) {
      // Immediately start accepting a new connection
      start();
      // If not error:
      if (!ec) {
        cout << "Server: connection from " << socket->remote_endpoint().address() << ':' << socket->remote_endpoint().port() << endl;
        handle_request(socket);
      }
    });
  }
};

class EchoClient {
  asio::io_context &io_context;

  asio::ip::tcp::resolver resolver;

public:
  EchoClient(asio::io_context &io_context_) : io_context(io_context_), resolver(io_context) {}

  void start(const string &host, unsigned short port) {
    // Resolve host (DNS-lookup if needed)
    resolver.async_resolve(host, to_string(port), [this](const error_code &ec, asio::ip::tcp::resolver::results_type resolver_results) {
      // If not error:
      if (!ec) {
        // The socket (connection) is added to the lambda in order to keep the object alive for as long as it is needed.
        // make_shared creates an object with automatic memory management through reference counting
        auto socket = make_shared<asio::ip::tcp::socket>(this->io_context);
        asio::async_connect(*socket, resolver_results, [socket](const error_code &ec, asio::ip::tcp::endpoint /*endpoint*/) {
          // If not error:
          if (!ec) {
            cout << "Client: connected" << endl;
            // Write buffer with automatic memory management through reference counting
            auto write_buffer = make_shared<std::string>();

            // Add message to be written to client
            *write_buffer = "hello\r\n";

            // Write to client
            async_write(*socket, asio::buffer(*write_buffer), [socket, write_buffer](const error_code &ec, size_t bytes_transferred) {
              // If not error:
              if (!ec) {
                cout << "Client: sent: " << write_buffer->substr(0, bytes_transferred - 2) << endl;
                // read buffer with automatic memory management through reference counting
                auto read_buffer = make_shared<std::string>();
                // Read from client until newline ("\r\n")
                async_read_until(*socket, asio::dynamic_buffer(*read_buffer), "\r\n", [socket, read_buffer](const error_code &ec, size_t bytes_transferred) {
                  // If not error:
                  if (!ec) {
                    // Retrieve message from server as string, without the last two characters (\r\n)
                    auto message = read_buffer->substr(0, bytes_transferred - 2);

                    cout << "Client: received: " << message << endl;

                    auto write_buffer = make_shared<std::string>();
                    *write_buffer = "exit\r\n";
                    async_write(*socket, asio::buffer(*write_buffer), [socket, write_buffer](const error_code &ec, size_t bytes_transferred) {
                      if (!ec)
                        cout << "Client: sent: " << write_buffer->substr(0, bytes_transferred - 2) << endl;
                    });
                  }
                });
              }
            });
          }
        });
      }
    });
  }
};

int main() {
  // Provides asynchronous I/O functionality
  asio::io_context io_context;

  EchoServer echo_server(io_context);
  cout << "Server: waiting for connection" << endl;
  echo_server.start();

  EchoClient echo_client(io_context);
  echo_client.start("localhost", 3000);

  io_context.run();
}
