#include "eggData.h"

static bool initialized = false;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t len) {
    // Suppress panda3d notify/assert output
    if (!initialized) {
        initialized = true;
        Notify::ptr()->set_ostream_ptr(new std::ofstream("/dev/null"), false);
    }

    // Wrap raw bytes in an istream — no disk I/O
    std::string input(reinterpret_cast<const char*>(data), len);
    std::istringstream stream(input);

    EggData egg;

    if (!egg.read(stream)) {
        return 0; // Invalid input.
    }

    // Perform some operations on the data to test various code paths.
    egg.triangulate_polygons(EggData::T_polygon | EggData::T_convex);
    egg.remove_invalid_primitives(true);
    egg.remove_unused_vertices(true);
    egg.recompute_vertex_normals(0.5);
    egg.recompute_polygon_normals();

    return 0;
}