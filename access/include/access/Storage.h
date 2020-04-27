#ifndef ODR_ACCESS_STORAGE_H
#define ODR_ACCESS_STORAGE_H

#include <access/Path.h>
#include <access/Stream.h>
#include <exception>
#include <functional>
#include <memory>

namespace odr {
namespace access {

class FileNotFoundException final : public std::exception {
public:
  explicit FileNotFoundException(std::string path) : path(std::move(path)) {}
  const std::string &getPath() const { return path; }
  const char *what() const noexcept final { return "file not found"; }

private:
  std::string path;
};

class FileNotCreatedException final : public std::exception {
public:
  explicit FileNotCreatedException(std::string path) : path(std::move(path)) {}
  const std::string &getPath() const { return path; }
  const char *what() const noexcept final { return "file not created"; }

private:
  std::string path;
};

class ReadStorage {
public:
  typedef std::function<void(const Path &)> Visitor;

  virtual ~ReadStorage() = default;

  virtual bool isSomething(const Path &) const = 0;
  virtual bool isFile(const Path &) const = 0;
  virtual bool isDirectory(const Path &) const = 0;
  virtual bool isReadable(const Path &) const = 0;

  virtual std::uint64_t size(const Path &) const = 0;

  // TODO only list for subdir? harder in case of zip
  virtual void visit(Visitor) const = 0;

  virtual std::unique_ptr<Source> read(const Path &) const = 0;
};

class WriteStorage {
public:
  virtual ~WriteStorage() = default;

  virtual bool isWriteable(const Path &) const = 0;

  virtual bool remove(const Path &) const = 0;
  virtual bool copy(const Path &from, const Path &to) const = 0;
  virtual bool move(const Path &from, const Path &to) const = 0;

  virtual bool createDirectory(const Path &) const = 0;

  virtual std::unique_ptr<Sink> write(const Path &) const = 0;
};

class Storage : public ReadStorage, public WriteStorage {
public:
  ~Storage() override = default;

  bool isSomething(const Path &) const override = 0;
  bool isFile(const Path &) const override = 0;
  bool isDirectory(const Path &) const override = 0;
  bool isReadable(const Path &) const override = 0;
  bool isWriteable(const Path &) const override = 0;

  std::uint64_t size(const Path &) const override = 0;

  bool remove(const Path &) const override = 0;
  bool copy(const Path &from, const Path &to) const override = 0;
  bool move(const Path &from, const Path &to) const override = 0;

  bool createDirectory(const Path &) const override = 0;

  void visit(Visitor) const override = 0;

  std::unique_ptr<Source> read(const Path &) const override = 0;
  std::unique_ptr<Sink> write(const Path &) const override = 0;
};

} // namespace access
} // namespace odr

#endif // ODR_ACCESS_STORAGE_H
