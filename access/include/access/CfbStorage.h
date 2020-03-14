#ifndef ODR_CFBSTORAGE_H
#define ODR_CFBSTORAGE_H

#include <access/Storage.h>

namespace odr {
namespace access {

struct CfbException : public std::runtime_error {
  explicit CfbException(const char *desc) : std::runtime_error(desc) {}
};
struct NoCfbFileException : public CfbException {
  NoCfbFileException() : CfbException("no cfb file") {}
};
struct CfbFileCorruptedException : public CfbException {
  CfbFileCorruptedException() : CfbException("cfb file corrupted") {}
};

class CfbReader final : public ReadStorage {
public:
  explicit CfbReader(const Path &);
  ~CfbReader() final;

  bool isSomething(const Path &) const final;
  bool isFile(const Path &) const final;
  bool isFolder(const Path &) const final;
  bool isReadable(const Path &) const final;

  std::uint64_t size(const Path &) const final;

  void visit(Visitor) const final;

  std::unique_ptr<Source> read(const Path &) const final;

private:
  class Impl;
  const std::unique_ptr<Impl> impl;
};

} // namespace access
} // namespace odr

#endif // ODR_CFBSTORAGE_H
