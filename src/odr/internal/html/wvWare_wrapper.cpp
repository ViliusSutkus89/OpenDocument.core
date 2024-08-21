#include <odr/exceptions.hpp>
#include <odr/file.hpp>
#include <odr/html.hpp>
#include <odr/internal/common/file.hpp>
#include <odr/internal/html/wvWare_wrapper.hpp>
#include <wv/wv.h>
#include <unistd.h>

extern "C" {
int convert(char *inputFile, char *outputDir, const char *password);
int no_graphics;
}

namespace odr::internal {

Html wvWare_wrapper(const File &file, const std::string &output_path,
                    const HtmlConfig &config) {
  auto disk_path = file.disk_path();
  if (!disk_path.has_value()) {
    throw FileNotFound();
  }

  auto output_file_path = output_path + "/document.html";

  char *input_file_path = strdup(disk_path->c_str());
  char *output_dir = strdup(output_path.c_str());

  no_graphics = 1;

  g_htmlOutputFileHandle = fopen(output_file_path.c_str(), "w");

  std::string password;
  int retVal = convert(input_file_path, output_dir, password.c_str());
  free(output_dir);
  free(input_file_path);
  fclose(g_htmlOutputFileHandle);
  g_htmlOutputFileHandle = nullptr;

  if (0 != retVal) {
    unlink(output_file_path.c_str());

    switch (retVal) {
    case 100: // PasswordRequired
    case 101: // Wrong Password
      throw WrongPassword();
    default:
      throw std::runtime_error("Conversion error");
    }
  }

  return {
      FileType::legacy_word_document, config, {{"document", output_file_path}}};
}

} // namespace odr::internal
