#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include "core_server/internal/interface/backend.hpp"
#include "unit_tests/core_server/internal/evaluation/evaluation_algorithm/common.hpp"

namespace CORE::Internal::Evaluation::UnitTests {
TEST_CASE("Evaluation of a query with contiguous events Projection all filters") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT msft, intel, amzn FROM Stock\n"
    "WHERE SELL as msft: SELL as intel: SELL as amzn\n"
    "FILTER msft[name='MSFT'] AND msft[price > 100]\n"
    "    AND intel[name='INTL']\n"
    "    AND amzn[name='AMZN'] AND amzn[price < 2000]";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 1);
  REQUIRE(output.complex_events[0].start == 5);
  REQUIRE(output.complex_events[0].end == 7);

  REQUIRE(output.complex_events[0].events.size() == 3);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[0].events[1], 0, "INTL", 80));
  REQUIRE(is_the_same_as(output.complex_events[0].events[2], 0, "AMZN", 1900));

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(81)}};
  INFO("SELL INTL 81");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1920)}};
  INFO("SELL AMZN 1920");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);
}

TEST_CASE("Evaluation of a query with contiguous events Projection msft, intel") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT msft, intel FROM Stock\n"
    "WHERE SELL as msft: SELL as intel: SELL as amzn\n"
    "FILTER msft[name='MSFT'] AND msft[price > 100]\n"
    "    AND intel[name='INTL']\n"
    "    AND amzn[name='AMZN'] AND amzn[price < 2000]";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();
  REQUIRE(output.complex_events.size() == 1);
  REQUIRE(output.complex_events[0].start == 5);
  REQUIRE(output.complex_events[0].end == 7);

  REQUIRE(output.complex_events[0].events.size() == 2);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[0].events[1], 0, "INTL", 80));

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(81)}};
  INFO("SELL INTL 81");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1920)}};
  INFO("SELL AMZN 1920");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);
}

TEST_CASE("Evaluation of long query with projection") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT msft, amzn FROM Stock\n"
    "WHERE SELL as msft: SELL as intel: SELL as amzn: SELL as msft: SELL "
    "as intel: SELL as amzn: SELL as msft: SELL as intel: SELL as amzn\n"
    "FILTER msft[name='MSFT'] AND intel[name='INTL'] AND amzn[name='AMZN']";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");
  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 1);

  REQUIRE(output.complex_events[0].start == 5);
  REQUIRE(output.complex_events[0].end == 13);

  REQUIRE(output.complex_events[0].events.size() == 6);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[0].events[1], 0, "AMZN", 1900));
  REQUIRE(is_the_same_as(output.complex_events[0].events[2], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[0].events[3], 0, "AMZN", 1900));
  REQUIRE(is_the_same_as(output.complex_events[0].events[4], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[0].events[5], 0, "AMZN", 1900));

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(81)}};
  INFO("SELL INTL 81");
  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1920");
  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);
}

TEST_CASE("Evaluation of long query with projection swapped order") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT amzn, msft FROM Stock\n"
    "WHERE SELL as msft: SELL as intel: SELL as amzn: SELL as msft: SELL "
    "as intel: SELL as amzn: SELL as msft: SELL as intel: SELL as amzn\n"
    "FILTER msft[name='MSFT'] AND intel[name='INTL'] AND amzn[name='AMZN']";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");
  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 1);

  REQUIRE(output.complex_events[0].start == 5);
  REQUIRE(output.complex_events[0].end == 13);

  REQUIRE(output.complex_events[0].events.size() == 6);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[0].events[1], 0, "AMZN", 1900));
  REQUIRE(is_the_same_as(output.complex_events[0].events[2], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[0].events[3], 0, "AMZN", 1900));
  REQUIRE(is_the_same_as(output.complex_events[0].events[4], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[0].events[5], 0, "AMZN", 1900));

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(81)}};
  INFO("SELL INTL 81");
  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1920");
  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);
}

TEST_CASE(
  "Evaluation of a query with mix of contiguous sequencing, contiguous "
  "iteration, and "
  "OR Projection") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT amzn FROM Stock\n"
    "WHERE (SELL):+ as msft; (SELL OR BUY) as intel; SELL as amzn\n"
    "FILTER msft[name='MSFT']\n"
    "    AND intel[name='INTL']\n"
    "    AND amzn[name='AMZN']";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 2);

  REQUIRE(output.complex_events[0].start == 1);
  REQUIRE(output.complex_events[0].end == 4);
  REQUIRE(output.complex_events[1].start == 0);
  REQUIRE(output.complex_events[1].end == 4);

  REQUIRE(output.complex_events[0].events.size() == 1);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "AMZN", 1900));

  REQUIRE(output.complex_events[1].events.size() == 1);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "AMZN", 1900));

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(105)}};
  INFO("SELL MSFT 105");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(85)}};
  INFO("SELL INTL 85");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1901)}};
  INFO("SELL AMZN 1901");

  // NOTE: If fails, should check if correct. Made assuming correctness

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 3);

  REQUIRE(output.complex_events[0].start == 5);
  REQUIRE(output.complex_events[0].end == 7);
  REQUIRE(output.complex_events[1].start == 1);
  REQUIRE(output.complex_events[1].end == 7);
  REQUIRE(output.complex_events[2].start == 0);
  REQUIRE(output.complex_events[2].end == 7);

  REQUIRE(output.complex_events[0].events.size() == 1);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "AMZN", 1901));

  REQUIRE(output.complex_events[1].events.size() == 1);
  REQUIRE(is_the_same_as(output.complex_events[1].events[0], 0, "AMZN", 1901));

  REQUIRE(output.complex_events[2].events.size() == 1);
  REQUIRE(is_the_same_as(output.complex_events[2].events[0], 0, "AMZN", 1901));
}

TEST_CASE(
  "Evaluation of a query with mix of contiguous iteration, contiguous "
  "sequencing, non contiguous sequencing, and "
  "OR v2 Projection") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT msft FROM Stock\n"
    "WHERE (SELL):+ as msft: (SELL OR BUY) as intel; SELL as amzn\n"
    "FILTER msft[name='MSFT']\n"
    "    AND intel[name='INTL']\n"
    "    AND amzn[name='AMZN']";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 2);

  REQUIRE(output.complex_events[0].start == 1);
  REQUIRE(output.complex_events[0].end == 4);
  REQUIRE(output.complex_events[1].start == 0);
  REQUIRE(output.complex_events[1].end == 4);

  REQUIRE(output.complex_events[0].events.size() == 1);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "MSFT", 102));

  REQUIRE(output.complex_events[1].events.size() == 2);
  REQUIRE(is_the_same_as(output.complex_events[1].events[0], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[1].events[1], 0, "MSFT", 102));
}

TEST_CASE(
  "Evaluation of a query with mix of non contiguous iteration, contiguous "
  "sequencing, and non contiguous sequencing with Projection over events") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT SELL, BUY FROM Stock\n"
    "WHERE (SELL)+: BUY: SELL";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 1);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 2);
  REQUIRE(output.complex_events[0].start == 2);
  REQUIRE(output.complex_events[0].end == 4);
  REQUIRE(output.complex_events[1].start == 0);
  REQUIRE(output.complex_events[1].end == 4);

  REQUIRE(output.complex_events[0].events.size() == 3);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "MSFT", 102));
  REQUIRE(is_the_same_as(output.complex_events[0].events[1], 1, "INTL", 80));
  REQUIRE(is_the_same_as(output.complex_events[0].events[2], 0, "AMZN", 1900));

  REQUIRE(output.complex_events[1].events.size() == 4);
  REQUIRE(is_the_same_as(output.complex_events[1].events[0], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[1].events[1], 0, "MSFT", 102));
  REQUIRE(is_the_same_as(output.complex_events[1].events[2], 1, "INTL", 80));
  REQUIRE(is_the_same_as(output.complex_events[1].events[3], 0, "AMZN", 1900));
}

TEST_CASE(
  "Evaluation of a query with mix of non contiguous iteration, contiguous "
  "sequencing, and non contiguous sequencing with Projection over BUY "
  "event") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT BUY FROM Stock\n"
    "WHERE (SELL)+: BUY: SELL";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 1);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 2);
  REQUIRE(output.complex_events[0].start == 2);
  REQUIRE(output.complex_events[0].end == 4);
  REQUIRE(output.complex_events[1].start == 0);
  REQUIRE(output.complex_events[1].end == 4);

  REQUIRE(output.complex_events[0].events.size() == 1);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 1, "INTL", 80));

  REQUIRE(output.complex_events[1].events.size() == 1);
  REQUIRE(is_the_same_as(output.complex_events[1].events[0], 1, "INTL", 80));
}

TEST_CASE(
  "Evaluation of a query with mix of non contiguous iteration, contiguous "
  "sequencing, and non contiguous sequencing / Empty Projection") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT nt FROM Stock\n"
    "WHERE (SELL)+: BUY: SELL";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 1);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 2);
  REQUIRE(output.complex_events[0].start == 2);
  REQUIRE(output.complex_events[0].end == 4);
  REQUIRE(output.complex_events[1].start == 0);
  REQUIRE(output.complex_events[1].end == 4);

  REQUIRE(output.complex_events[0].events.size() == 0);

  REQUIRE(output.complex_events[1].events.size() == 0);
}

TEST_CASE(
  "Evaluation of a query with mix of contiguous iteration, contiguous "
  "sequencing, non contiguous sequencing, and "
  "OR v2 / Empty Projection") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT nvda FROM Stock\n"
    "WHERE (SELL):+ as msft: (SELL OR BUY) as intel; SELL as amzn\n"
    "FILTER msft[name='MSFT']\n"
    "    AND intel[name='INTL']\n"
    "    AND amzn[name='AMZN']";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 2);
  REQUIRE(output.complex_events[0].start == 1);
  REQUIRE(output.complex_events[0].end == 4);
  REQUIRE(output.complex_events[1].start == 0);
  REQUIRE(output.complex_events[1].end == 4);

  REQUIRE(output.complex_events[0].events.size() == 0);

  REQUIRE(output.complex_events[1].events.size() == 0);
}

TEST_CASE(
  "Evaluation of a query with mix of non contiguous iteration, contiguous "
  "sequencing, and non contiguous sequencing with Projection over events "
  "swapped") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT BUY, SELL FROM Stock\n"
    "WHERE (SELL)+: BUY: SELL";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 1);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 2);
  REQUIRE(output.complex_events[0].start == 2);
  REQUIRE(output.complex_events[0].end == 4);
  REQUIRE(output.complex_events[1].start == 0);
  REQUIRE(output.complex_events[1].end == 4);

  REQUIRE(output.complex_events[0].events.size() == 3);
  REQUIRE(is_the_same_as(output.complex_events[0].events[0], 0, "MSFT", 102));
  REQUIRE(is_the_same_as(output.complex_events[0].events[1], 1, "INTL", 80));
  REQUIRE(is_the_same_as(output.complex_events[0].events[2], 0, "AMZN", 1900));

  REQUIRE(output.complex_events[1].events.size() == 4);
  REQUIRE(is_the_same_as(output.complex_events[1].events[0], 0, "MSFT", 101));
  REQUIRE(is_the_same_as(output.complex_events[1].events[1], 0, "MSFT", 102));
  REQUIRE(is_the_same_as(output.complex_events[1].events[2], 1, "INTL", 80));
  REQUIRE(is_the_same_as(output.complex_events[1].events[3], 0, "AMZN", 1900));
}

TEST_CASE(
  "Evaluation of a query with mix of contiguous iteration, contiguous "
  "sequencing, non contiguous sequencing, and "
  "OR v2 / none Projection") {
  Internal::Interface::Backend<TestResultHandler> backend;
  TestResultHandler result_handler;

  auto event_type_id_1 = backend.add_event_type("SELL",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});
  auto event_type_id_2 = backend.add_event_type("BUY",
                                                {{"name", Types::ValueTypes::STRING_VIEW},
                                                 {"price", Types::ValueTypes::INT64}});

  auto stream_type = backend.add_stream_type("Stock", {event_type_id_1, event_type_id_2});

  std::string string_query =
    "SELECT NONE FROM Stock\n"
    "WHERE (SELL):+ as msft: (SELL OR BUY) as intel; SELL as amzn\n"
    "FILTER msft[name='MSFT']\n"
    "    AND intel[name='INTL']\n"
    "    AND amzn[name='AMZN']";

  backend.declare_query(string_query, result_handler);

  Types::Event event;
  Types::Enumerator output;

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(101)}};
  INFO("SELL MSFT 101");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("MSFT"),
            std::make_shared<Types::IntValue>(102)}};
  INFO("SELL MSFT 102");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {1,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("BUY INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("INTL"),
            std::make_shared<Types::IntValue>(80)}};
  INFO("SELL INTL 80");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 0);

  event = {0,
           {std::make_shared<Types::StringValue>("AMZN"),
            std::make_shared<Types::IntValue>(1900)}};
  INFO("SELL AMZN 1900");

  backend.send_event_to_queries(0, event);

  output = result_handler.get_enumerator();

  REQUIRE(output.complex_events.size() == 2);

  REQUIRE(output.complex_events.size() == 2);
  REQUIRE(output.complex_events[0].start == 1);
  REQUIRE(output.complex_events[0].end == 4);
  REQUIRE(output.complex_events[1].start == 0);
  REQUIRE(output.complex_events[1].end == 4);

  REQUIRE(output.complex_events[0].events.size() == 0);

  REQUIRE(output.complex_events[1].events.size() == 0);
}
}  // namespace CORE::Internal::Evaluation::UnitTests
