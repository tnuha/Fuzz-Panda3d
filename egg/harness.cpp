#include "eggData.h"

static bool initialized = false;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t len) {
    if (!initialized) {
        initialized = true;
        Notify::ptr()->set_ostream_ptr(new std::ofstream("/dev/null"), false);
    }

    if (len < 8)
        return 0;

    const uint8_t* payload = data;
    size_t payload_len = len - 8;
    const uint8_t* ctrl = data + payload_len;

    if (payload_len > (1 << 16))
        return 0;

    std::string input(reinterpret_cast<const char*>(payload), payload_len);
    std::istringstream stream(input);

    EggData egg;

    if (!egg.read(stream)) {
        return 0;
    }

    uint8_t b0 = ctrl[0];
    uint8_t b1 = ctrl[1];
    uint8_t b2 = ctrl[2];
    uint8_t b3 = ctrl[3];
    uint8_t b4 = ctrl[4];
    uint8_t b5 = ctrl[5];
    uint8_t b6 = ctrl[6];
    uint8_t b7 = ctrl[7];

    int iters = 1 + (b4 % 3);

    for (int i = 0; i < iters; ++i) {
        int mode = b0 % 3;

        if (mode == 0)
            egg.triangulate_polygons(EggData::T_polygon);
        else if (mode == 1)
            egg.triangulate_polygons(EggData::T_convex);
        else
            egg.triangulate_polygons(EggData::T_polygon | EggData::T_convex);

        double threshold = b1 / 255.0;
        if (threshold < 0.01)
            threshold = 0.01;

        egg.recompute_vertex_normals(threshold);

        if (b2 & 1)
            egg.remove_unused_vertices(true);
    }

    if (b3 & 1)
        egg.flatten_transforms();
    if (b3 & 2)
        egg.apply_texmats();

    if (b2 & 2)
        egg.strip_normals();

    if ((b2 & 4) && (b6 & 1))
        egg.unify_attributes(true, true, true);

    if (b5 & 1)
        egg.recompute_polygon_normals();

    if ((b6 & 1) && (b3 & 1))
        egg.reverse_vertex_ordering();

    // Core sanity cleanup (always run)
    egg.remove_invalid_primitives(true);
    egg.remove_unused_vertices(true);

    if ((b7 & 1) && payload_len < (1 << 15)) {
        std::ostringstream out;
        egg.write_egg(out);

        std::istringstream in2(out.str());
        EggData egg2;
        if (!egg2.read(in2))
            return 0;
    }

    return 0;
}