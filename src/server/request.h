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
#include "param.h"

namespace http {
namespace server {

/// A request received from a client.
struct request
{
  std::string method;
  std::string uri;
  int http_version_major;
  int http_version_minor;
  std::vector<Param> params;
  std::vector<header> headers;
  std::string body;
};

} // namespace server
} // namespace http

#endif /* SRC_SERVER_REQUEST_H_ */
