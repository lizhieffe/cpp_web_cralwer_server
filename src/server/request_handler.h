/*
 * requesthandler.h
 *
 *  Created on: Oct 17, 2015
 *      Author: zhili
 */

#ifndef SRC_SERVER_REQUEST_HANDLER_H_
#define SRC_SERVER_REQUEST_HANDLER_H_

#include <string>
#include <boost/noncopyable.hpp>

namespace http {
namespace server {

struct reply;
struct request;

/// The common handler for all incoming requests.
class request_handler
  : private boost::noncopyable
{
public:
  /// Construct with a directory containing files to be served.
  explicit request_handler(const std::string& doc_root);

  /// Handle a request and produce a reply.
  void handle_request(const request& req, reply& rep);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;

  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
};

} // namespace server
} // namespace http

#endif /* SRC_SERVER_REQUEST_HANDLER_H_ */
