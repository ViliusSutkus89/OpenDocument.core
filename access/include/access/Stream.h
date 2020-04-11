#ifndef ODR_ACCESS_STREAM_H
#define ODR_ACCESS_STREAM_H

#include <cstdint>

namespace odr {
namespace access {

class Source {
public:
  virtual ~Source() = default;
  virtual std::uint32_t read(char *data, std::uint32_t amount) = 0;
  virtual std::uint32_t available() const { return 0; }
};

class Sink {
public:
  virtual ~Sink() = default;
  virtual void write(const char *data, std::uint32_t amount) = 0;
};

} // namespace access
} // namespace odr

#endif // ODR_ACCESS_STREAM_H