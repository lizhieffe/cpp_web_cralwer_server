/*
 * request_parser.h
 *
 *  Created on: Oct 17, 2015
 *      Author: zhili
 */

#ifndef SRC_SERVER_REQUEST_PARSER_H_
#define SRC_SERVER_REQUEST_PARSER_H_

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

namespace http {
namespace server {

struct request;

/// Parser for incoming requests.
class RequestParser {
public:
  /// Construct ready to parse the request method.
  RequestParser();

  /// Reset to initial parser state.
  void reset();

  /// Parse some data. The tribool return value is true when a complete request
  /// has been parsed, false if the data is invalid, indeterminate when more
  /// data is required. The InputIterator return value indicates how much of the
  /// input has been consumed.
  template <typename InputIterator>
  boost::tuple<boost::tribool, InputIterator> parse(request& req,
      InputIterator begin, InputIterator end) {
    while (begin != end) {
      boost::tribool result = consume(req, *begin++);
      if (result || !result)
        return boost::make_tuple(result, begin);
    }
    boost::tribool result = boost::indeterminate;
    return boost::make_tuple(result, begin);
  }

private:
  /// Handle the next character of input.
  boost::tribool consume(request& req, char input);

  /// Check if a byte is an HTTP character.
  static bool is_char(int c);

  /// Check if a byte is an HTTP control character.
  static bool is_ctl(int c);

  /// Check if a byte is defined as an HTTP tspecial character.
  static bool is_tspecial(int c);

  /// Check if a byte is a digit.
  static bool is_digit(int c);

  // Get the body length from the header of name Content-Length.
  static int FindBodyLength(const request& req);

  /// The current state of the parser.
  enum state
  {
    method_start,
    method,
    uri_start,
    uri,
		// The start of a param name and value pair.
		param_start,
		param_name,
		param_value,
    http_version_h,
    http_version_t_1,
    http_version_t_2,
    http_version_p,
    http_version_slash,
    http_version_major_start,
    http_version_major,
    http_version_minor_start,
    http_version_minor,
    expecting_newline_1,
    header_line_start,
    header_lws,
    header_name,
    space_before_header_value,
    header_value,
    expecting_newline_2,
    expecting_newline_3,
		possible_body_start,
		body_start
  } state_;

  // Number of chars in the body to be read.
  size_t body_chars_left_ = 0;
};

} // namespace server
} // namespace http

#endif /* SRC_SERVER_REQUEST_PARSER_H_ */
