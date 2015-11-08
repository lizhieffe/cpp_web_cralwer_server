/*
 * mimetype.cpp
 *
 *  Created on: Oct 17, 2015
 *      Author: zhili
 */

#include "mime_types.h"

#include <map>
#include <string>

namespace http {
namespace server3 {
namespace mime_types {

const std::map<std::string, std::string> extesionio_to_type_mapping = {
		{ "gif", "image/gif" },
		{ "htm", "text/html" },
		{ "html", "text/html" },
		{ "jpg", "image/jpeg" },
		{ "png", "image/png" },
};

std::string extension_to_type(const std::string& extension) {
  const auto match = extesionio_to_type_mapping.find(extension);
  if (match == extesionio_to_type_mapping.end()) {
  	return "text/plain";
  } else {
  	return match->second;
  }
}

} // namespace mime_types
} // namespace server3
} // namespace http
