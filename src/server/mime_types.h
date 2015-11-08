/*
 * mimetype.h
 *
 *  Created on: Oct 17, 2015
 *      Author: zhili
 */

#ifndef SRC_SERVER_MIME_TYPES_H_
#define SRC_SERVER_MIME_TYPES_H_

#include <string>

namespace http {
namespace server3 {
namespace mime_types {

/// Convert a file extension into a MIME type.
std::string extension_to_type(const std::string& extension);

} // namespace mime_types
} // namespace server3
} // namespace http

#endif /* SRC_SERVER_MIME_TYPES_H_ */
