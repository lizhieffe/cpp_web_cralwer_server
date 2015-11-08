/*
 * header.h
 *
 *  Created on: Oct 17, 2015
 *      Author: zhili
 */

#ifndef SRC_SERVER_HEADER_H_
#define SRC_SERVER_HEADER_H_

#include <string>

namespace http {
namespace server {

struct header
{
  std::string name;
  std::string value;
};

} // namespace server
} // namespace http

#endif /* SRC_SERVER_HEADER_H_ */
