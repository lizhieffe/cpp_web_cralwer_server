/*
 * request.h
 *
 *  Created on: Oct 17, 2015
 *      Author: zhili
 */

#ifndef SRC_SERVER_REQUEST_H_
#define SRC_SERVER_REQUEST_H_

#include <string>
#include <vector>

#include "header.h"

namespace http {
namespace server3 {

/// A request received from a client.
struct request
{
  std::string method;
  std::string uri;
  int http_version_major;
  int http_version_minor;
  std::vector<header> headers;
};

} // namespace server3
} // namespace http

#endif /* SRC_SERVER_REQUEST_H_ */
