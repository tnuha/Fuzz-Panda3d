#include "bamFile.h"
#include <unistd.h>

/*
 * Useful docs:
 * https://docs.panda3d.org/1.10/cpp/reference/panda3d.core.BamFile#_CPPv47BamFile
 * Tested interfaces are obvious below
 */

static bool initialized = false;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t len) {
  // Suppress panda3d notify/assert output
  if (!initialized) {
    initialized = true;
    Notify::ptr()->set_ostream_ptr(new std::ofstream("/dev/null"), false);
  }

  // Wrap raw bytes in an istream — no disk I/O
  std::string input(reinterpret_cast<const char *>(data), len);
  std::istringstream stream(input);

  BamFile bam;
  if (!bam.open_read(stream)) {
    return 0;
  }

  bam.get_current_major_ver();
  bam.get_current_minor_ver();
  bam.get_file_endian();
  bam.get_file_major_ver();
  bam.get_file_minor_ver();
  bam.get_file_stdfloat_double();
  bam.get_reader();
  bam.is_eof();
  bam.is_valid_read();
  bam.is_valid_write();
  bam.read_node();
  bam.read_object();
  bam.resolve();

  return 0;
}
