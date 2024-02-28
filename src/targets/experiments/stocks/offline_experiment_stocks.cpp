#include <thread>

#include "core_server/internal/parsing/ceql_query/parser.hpp"
#include "core_server/internal/parsing/stream_declaration/parser.hpp"
#include "core_server/library/server.hpp"
#include "targets/experiments/data_handler.hpp"

using namespace CORE;

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cout << "There must be 2 arguments: The query path and the data path."
              << std::endl;
    return 1;
  }

  std::string query_path = argv[1];
  std::string data_path = argv[2];
  std::string declaration_path = argv[3];

  FrameMark;
  try {
    Types::PortNumber starting_port{5000};
    Library::OfflineServer server{starting_port};
    Client client{"tcp://localhost", 5000};

    DataHandler::DataReader reader(query_path);
    reader.read_query();

    Internal::Parsing::Declaration::Parser parser;
    Types::StreamInfo stream_info = parser.parse_stream(
      reader.read_declaration_file(declaration_path));
    std::vector<Types::Event> events = stream_info.get_events_from_csv(data_path);

    DataHandler::do_declaration(client,
                               stream_info);

    std::string query_string = reader.query;

    std::cout << "Query: " << query_string << std::endl;

    client.add_query(std::move(query_string));

    std::cout << "Read events " << events.size() << std::endl;
    FrameMark;

    // for (Types::Event event_to_send : reader.events) {
    //   ZoneScopedN("main::send_event");
    //   server.receive_stream({0, {event_to_send}});
    // }
    server.receive_stream({0, std::move(events)});

    return 0;
  } catch (std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
    return 1;
  }
}
