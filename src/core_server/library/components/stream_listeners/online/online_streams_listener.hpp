#pragma once

#include <thread>
#include <vector>

#include "core_server/internal/interface/backend.hpp"
#include "shared/datatypes/aliases/port_number.hpp"
#include "shared/networking/message_receiver/zmq_message_receiver.hpp"

namespace CORE::Library::Components {

template <typename ResultHandlerT>
class OnlineStreamsListener {
  using Backend = CORE::Internal::Interface::Backend<ResultHandlerT>;

 private:
  Backend& backend;
  Types::PortNumber receiver_port;
  Internal::ZMQMessageReceiver receiver;
  std::thread worker_thread;
  std::atomic<bool> stop_condition;

 public:
  OnlineStreamsListener(Backend& backend, Types::PortNumber port_number)
      : backend(backend),
        receiver_port(port_number),
        receiver("tcp://*:" + std::to_string(port_number)) {
    start();
  }

  ~OnlineStreamsListener() { stop(); }

  // Delete Copy constructor and assigment as that should not be done with the stream listener
  OnlineStreamsListener(const OnlineStreamsListener&) = delete;
  OnlineStreamsListener& operator=(const OnlineStreamsListener&) = delete;

 private:
  void start() {
    stop_condition = false;
    worker_thread = std::thread([&]() {
      while (!stop_condition) {
        std::string s_message = receiver.receive();
        Types::Stream
          stream = Internal::CerealSerializer<Types::Stream>::deserialize(
            s_message);
        for (auto& event : stream.events) {
          backend.send_event_to_queries(stream.id, event);
        }
      }
    });
  }

  void stop() {
    Internal::ZMQMessageSender sender("tcp://localhost:"
                                      + std::to_string(receiver_port));
    stop_condition = true;
    sender.send(Internal::CerealSerializer<Types::Stream>::serialize(
      Types::Stream(0, {})));
    worker_thread.join();
  }
};

}  // namespace CORE::Library::Components
