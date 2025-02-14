#include <asio.hpp>
#include <iostream>
#include <thread>

using namespace std;

const size_t max_udp_message_size = 0xffff - 20 - 8; // 16 bit UDP length field - 20 byte IP header - 8 byte UDP header

class EchoServer {
  asio::ip::udp::socket socket;

public:
  EchoServer(asio::io_context &io_context) : socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v6(), 3000)) {}

  asio::awaitable<void> handle_request(asio::ip::udp::endpoint endpoint, string message) {
    co_await socket.async_send_to(asio::buffer(message, message.length()), endpoint, asio::use_awaitable);
    cout << "Server: sent: " << message
         << ", to " << endpoint.address() << ":" << endpoint.port() << endl;
  }

  asio::awaitable<void> start() {
    for (;;) {
      char buffer[max_udp_message_size];
      asio::ip::udp::endpoint endpoint;
      auto bytes_transferred = co_await socket.async_receive_from(asio::buffer(buffer, max_udp_message_size), endpoint, asio::use_awaitable);

      auto message = string(buffer, bytes_transferred);
      cout << "Server: received: " << message << ", from " << endpoint.address() << ":" << endpoint.port() << endl;

			pair<vector<double>, vector<double>> v_pair = parse_message(message);
			string dot = to_string(dot_product(v_pair.first, v_pair.second));

			cout << "Dot product of the received vectors: " << dot << endl;
      co_spawn(socket.get_executor(), handle_request(std::move(endpoint), dot), asio::detached);
    }
  }
  std::pair<std::vector<double>, std::vector<double>> parse_message(const std::string &input) {
    std::vector<double> vec1, vec2;
    std::stringstream ss(input);
    std::string segment;
    bool firstVector = true;

    while (std::getline(ss, segment, ']')) {
      std::stringstream temp(segment);
      std::string num;
      std::vector<double> *targetVector = firstVector ? &vec1 : &vec2;
      firstVector = false;

      while (std::getline(temp, num, ',')) {
        std::string cleanNum;
        for (char c : num) {
          if (std::isdigit(c) || c == '.' || c == '-') {
            cleanNum += c;
          }
        }
        if (!cleanNum.empty()) {
          targetVector->push_back(std::stod(cleanNum));
        }
      }
    }
    return {vec1, vec2};
  }

  double dot_product(vector<double> v1, vector<double> v2) {
    int v1_len = v1.size();
    int v2_len = v2.size();
    if (v1_len != v2_len) {
      vector<int> sizes = {v1_len, v2_len};
      throw sizes;
    }

    double result = 0;

    for (int i = 0; i < v1_len; i++) {
      double temp = v1[i] * v2[i];
      result += temp;
    }
    return result;
  }
};

class EchoClient {
public:
  asio::awaitable<void> start() {
    auto executor = co_await asio::this_coro::executor;
    asio::ip::udp::socket socket(executor, asio::ip::udp::endpoint(asio::ip::udp::v6(), 0));

    // Resolve host (DNS-lookup if needed)
    auto endpoint = (co_await asio::ip::udp::resolver(executor)
                         .async_resolve(asio::ip::udp::v6(), "localhost", to_string(3000), asio::use_awaitable))
                        .begin()
                        ->endpoint();

    std::string message("[7, 8, 9, 10, 11, 12], [1, 2, 3, 4, 5, 6]");
    auto bytes_transferred = co_await socket.async_send_to(asio::buffer(message, message.length()), endpoint, asio::use_awaitable);
    cout << "Client: sent: " << message
         << ", to " << endpoint.address() << ":" << endpoint.port() << endl;

    char buffer[max_udp_message_size];
    bytes_transferred = co_await socket.async_receive_from(asio::buffer(buffer, max_udp_message_size), endpoint, asio::use_awaitable);
    cout << "Client: received: " << string(buffer, bytes_transferred)
         << ", from " << endpoint.address() << ":" << endpoint.port() << endl;
  }
};

int main() {
  // Provides asynchronous I/O functionality
  asio::io_context event_loop(1);

  EchoServer echo_server(event_loop);
  co_spawn(event_loop, echo_server.start(), asio::detached);

  EchoClient echo_client;
  co_spawn(event_loop, echo_client.start(), asio::detached);

  event_loop.run();
}
