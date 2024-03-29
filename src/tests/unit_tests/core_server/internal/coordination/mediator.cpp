// #include <catch2/catch_message.hpp>
// #include <catch2/catch_test_macros.hpp>
// #include <catch2/matchers/catch_matchers_vector.hpp>
// #include <chrono>
// #include <cstddef>
// #include <memory>
// #include <stdexcept>
// #include <string>
// #include <thread>
// #include <utility>
// #include <vector>
//
// #include "core_client/client.hpp"
// #include "core_client/message_handler.hpp"
// #include "core_server/library/server.hpp"
// #include "core_streamer/streamer.hpp"
// #include "shared/datatypes/aliases/event_type_id.hpp"
// #include "shared/datatypes/aliases/port_number.hpp"
// #include "shared/datatypes/catalog/attribute_info.hpp"
// #include "shared/datatypes/catalog/datatypes.hpp"
// #include "shared/datatypes/catalog/event_info.hpp"
// #include "shared/datatypes/catalog/stream_info.hpp"
// #include "shared/datatypes/client_request.hpp"
// #include "shared/datatypes/client_request_type.hpp"
// #include "shared/datatypes/complex_event.hpp"
// #include "shared/datatypes/enumerator.hpp"
// #include "shared/datatypes/event.hpp"
// #include "shared/datatypes/server_response.hpp"
// #include "shared/datatypes/server_response_type.hpp"
// #include "shared/datatypes/stream.hpp"
// #include "shared/datatypes/value.hpp"
// #include "shared/networking/message_dealer/zmq_message_dealer.hpp"
// #include "shared/networking/message_sender/zmq_message_sender.hpp"
// #include "shared/networking/message_subscriber/zmq_message_subscriber.hpp"
// #include "shared/serializer/cereal_serializer.hpp"
//
// namespace CORE::Internal::UnitTests::COREBackendCoordinationTests {
//
// Types::ServerResponse
// send_request(ZMQMessageDealer& dealer, Types::ClientRequest& request) {
//   std::string serialized_request = CerealSerializer<Types::ClientRequest>::serialize(
//     request);
//   auto serialized_response = dealer.send_and_receive(serialized_request);
//   return CerealSerializer<Types::ServerResponse>::deserialize(serialized_response);
// }
//
// Types::EventTypeId
// declare_and_check_for_event(Client& client,
//                             std::string name,
//                             std::vector<Types::AttributeInfo> attribute_info) {
//   try {
//     auto id = client.declare_event_type(name, std::move(attribute_info));
//     Types::EventInfo event_info_from_id = client.get_event_info(id);
//     Types::EventInfo event_info_from_name = client.get_event_info(id);
//     REQUIRE(event_info_from_id == event_info_from_name);
//     REQUIRE(event_info_from_id.id == id);
//     REQUIRE(event_info_from_id.name == name);
//     return id;
//   } catch (std::runtime_error) {
//     REQUIRE((false && "A response gave an error"));
//     return -1;
//   }
// }
//
// Types::EventTypeId declare_and_check_for_stream(Client& client,
//                                                 std::string name,
//                                                 std::vector<Types::EventTypeId> ids) {
//   try {
//     auto id = client.declare_stream_type(name, std::move(ids));
//     Types::StreamInfo stream_info_from_id = client.get_stream_info(id);
//     Types::StreamInfo stream_info_from_name = client.get_stream_info(id);
//     REQUIRE(stream_info_from_id == stream_info_from_name);
//     REQUIRE(stream_info_from_id.id == id);
//     REQUIRE(stream_info_from_id.name == name);
//     return id;
//   } catch (std::runtime_error) {
//     REQUIRE((false && "A response gave an error"));
//     return -1;
//   }
// }
//
// std::string create_query(std::string filter_clause) {
//   // clang-format off
//   return "SELECT ALL * \n"
//          "FROM S1, S2\n"
//          "WHERE (Ints AS X) OR (Mixed AS X)\n"
//          "FILTER\n"
//          + filter_clause + "\n"
//          "WITHIN 4 EVENTS\n";
//   // clang-format on
// }
//
// std::vector<Types::ComplexEvent>
// complex_events_from_enumerator(Types::Enumerator enumerator) {
//   std::vector<Types::ComplexEvent> out{};
//   for (auto val : enumerator) {
//     out.push_back(val);
//   }
//   return out;
// }
//
// std::vector<Types::ComplexEvent>
// complex_events_from_serialized_enumerator(std::string ser_enumerator) {
//   return complex_events_from_enumerator(
//     CerealSerializer<Types::Enumerator>::deserialize(ser_enumerator));
// }
//
// TEST_CASE(
//   "INTEGRATION TEST:"
//   "Query sent to the Router creates a query evaluator, a listener receives"
//   "a message, stores it in the ring tuple queue and sends it to the"
//   "dummy query evaluator, the dummy query evaluator then evaluates it"
//   "and responds back a string representing the bits that are satisfied",
//   "[server coordination]") {
//   // TODO: Change this to actual complex event, not queryEvaluator.
//   Types::PortNumber starting_port{5000};
//   Library::OnlineServer server{starting_port};
//   INFO("Started mediator.");
//
//   Client client{"tcp://localhost", starting_port};
//
//   auto event_type_id_1 = declare_and_check_for_event(
//     client,
//     "Ints",
//     {Types::AttributeInfo("Int1", Types::ValueTypes::INT64),
//      Types::AttributeInfo("Int2", Types::ValueTypes::INT64)});
//   auto stream_type_id_1 = declare_and_check_for_stream(client, "S1", {event_type_id_1});
//   auto event_type_id_2 = declare_and_check_for_event(
//     client,
//     "Mixed",
//     {Types::AttributeInfo("Int1", Types::ValueTypes::INT64),
//      Types::AttributeInfo("Int2", Types::ValueTypes::INT64),
//      Types::AttributeInfo("Double1", Types::ValueTypes::DOUBLE)});
//   auto stream_type_id_2 = declare_and_check_for_stream(client,
//                                                        "S2",
//                                                        {event_type_id_1, event_type_id_2});
//
//   std::string query = create_query(
//     "Ints[Int1 >= 20 AND Int2 >= 1] AND "
//     "Mixed[Int1 <= 30 OR Double1 >= 3.0]");
//   Types::ClientRequest create_query_evaluator{std::move(query),
//                                               Types::ClientRequestType::AddQuery};
//
//   ZMQMessageDealer dealer("tcp://localhost:5000");
//   INFO("Before creating the query evaluator");
//   Types::ServerResponse response = send_request(dealer, create_query_evaluator);
//   REQUIRE(response.response_type == Types::ServerResponseType::PortNumber);
//   auto port_number = CerealSerializer<Types::PortNumber>::deserialize(
//     response.serialized_response_data);
//   REQUIRE(port_number == 5002);
//
//   ZMQMessageSubscriber subscriber("tcp://localhost:" + std::to_string(port_number));
//   std::string message;
//   std::thread subscriber_thread = std::thread([&]() { message = subscriber.receive(); });
//   std::this_thread::sleep_for(std::chrono::milliseconds(10));
//   ZMQMessageSender sender("tcp://localhost:" + std::to_string(5001));
//   Types::Event event_to_send{event_type_id_1,
//                              {std::make_shared<Types::IntValue>(20),
//                               std::make_shared<Types::IntValue>(2)}};
//   INFO("BEFORE sending the event");
//   sender.send(CerealSerializer<Types::Stream>::serialize(
//     Types::Stream(stream_type_id_1, {event_to_send})));
//   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//   INFO("Event sent");
//   subscriber_thread.join();
//   INFO("Subscriber thread joined. (message was received.)");
//   Types::Enumerator enumerator = CerealSerializer<Types::Enumerator>::deserialize(message);
//   INFO("BEFORE echecking complex_events");
//   REQUIRE(complex_events_from_enumerator(enumerator).size() == 1);
//   INFO("Finished");
// }
//
// TEST_CASE(
//   "INTEGRATION TEST:"
//   "3 queries, 1 tuple. One weakly typed query."
//   "[server coordination]") {
//   // TODO: Change this to complex events.
//   Types::PortNumber starting_port{5000};
//   Library::OnlineServer server{starting_port};
//
//   Client client{"tcp://localhost", starting_port};
//
//   auto event_type_id_1 = declare_and_check_for_event(
//     client,
//     "Ints",
//     {Types::AttributeInfo("Int1", Types::ValueTypes::INT64),
//      Types::AttributeInfo("Int2", Types::ValueTypes::INT64)});
//   auto stream_type_id_1 = declare_and_check_for_stream(client, "S1", {event_type_id_1});
//   auto event_type_id_2 = declare_and_check_for_event(
//     client,
//     "Mixed",
//     {Types::AttributeInfo("Int1", Types::ValueTypes::INT64),
//      Types::AttributeInfo("Int2", Types::ValueTypes::INT64),
//      Types::AttributeInfo("Double1", Types::ValueTypes::DOUBLE)});
//   auto stream_type_id_2 = declare_and_check_for_stream(client,
//                                                        "S2",
//                                                        {event_type_id_1, event_type_id_2});
//
//   // TODO: Maybe add the variables in the other parts of the query.
//   std::vector<std::string> queries;
//   queries.push_back(
//     create_query("Ints[Int1 >= 20 AND Int2 >= 1] AND "
//                  "X[Int1 <= 30 OR Double1 >= 3.0]"));
//   queries.push_back(
//     create_query("Mixed[Int1 >= 3 AND Int2 <= 20] AND "
//                  "X[Int1 == 30 OR Double1 >= 3.0]"));
//   queries.push_back(
//     create_query("Ints[Int2 <= 4 AND Int2 >= 1] AND "
//                  "X[Double1 == 30 OR Int2 >= 1.0]"));
//
//   Types::PortNumber expected_port_number = 5002;
//   for (auto& query : queries) {
//     auto port_number = client.add_query(query);
//     REQUIRE(port_number == expected_port_number++);
//   }
//
//   std::vector<std::unique_ptr<LimitedMessageStorer>> handlers{};
//
//   for (size_t port = 5002; port < expected_port_number; port++) {
//     handlers.emplace_back(
//       std::make_unique<LimitedMessageStorer>(1));  // Store one enumerator.
//     client.subscribe_to_complex_event<LimitedMessageStorer>(handlers.back().get(), port);
//   }
//
//   INFO("Created handlers");
//
//   Streamer streamer("tcp://localhost", 5001);
//   Types::Event event_to_send{event_type_id_1,
//                              {std::make_shared<Types::IntValue>(20),
//                               std::make_shared<Types::IntValue>(2)}};
//
//   // Mitigate slow joiner syndrome where events gets processed and sent before
//   // clients are fully connected. Done for test due to low impact on real usage
//   // due to the fact that we are not guaranteed a client will be connected.
//   std::this_thread::sleep_for(std::chrono::milliseconds(500));
//   streamer.send_stream(stream_type_id_1, event_to_send);
//
//   client.join_all_threads();
//
//   INFO("Stopped mediators and joined clients");
//
//   REQUIRE(handlers[0]->storage.size() == 1);
//   REQUIRE(complex_events_from_enumerator(handlers[0]->storage[0]).size() == 1);
//   REQUIRE(handlers[1]->storage.size() == 1);
//   REQUIRE(complex_events_from_enumerator(handlers[1]->storage[0]).size() == 0);
//   REQUIRE(handlers[2]->storage.size() == 1);
//   REQUIRE(complex_events_from_enumerator(handlers[2]->storage[0]).size() == 1);
// }
// }  // namespace CORE::Internal::UnitTests::COREBackendCoordinationTests
