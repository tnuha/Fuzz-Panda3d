# Panda3D Fuzzer

We are FUZZING this [pander](<https://github.com/panda3d/panda3d>).

### Build on MacOS

1. get a better OS
2. in case of failing step 1 use the `./macos_build.sh` script

### Build on GNU+Linux

1. good
2. use the `./gnulinux_build.sh` script

Note we currently focus on debian.
You can use this command to install most dependencies:
```sh
sudo apt-get install build-essential pkg-config fakeroot python3-dev libpng-dev libjpeg-dev libtiff-dev zlib1g-dev libssl-dev libx11-dev libgl1-mesa-dev libxrandr-dev libxxf86dga-dev libxcursor-dev bison flex libfreetype6-dev libvorbis-dev libeigen3-dev libopenal-dev libode-dev libbullet-dev nvidia-cg-toolkit libgtk-3-dev libassimp-dev libopenexr-dev
```

### Build on Windows

1. no

### Build on FreeBSD

1. this would be cool but I'm not doing this

## After building panda3d...

You now should have an AFL++ compatible set of Panda3D libraries.
Change your current directory to the interface of interest,
and once there, either
- Fuzz with `make fuzz`
- triage with `make triager`

During triage we also have a helper script for large crash directories,
`triager.py` in the root of this project.

# Results

Currently we have posted the following issues to the main panda3d repository
on GitHub:

- [SEGV in pallocator](<https://github.com/panda3d/panda3d/issues/1818>)
- [SEGV in stl_tree](<https://github.com/panda3d/panda3d/issues/1819>)
- [SEGV in GeomVertexArrayFormat::is_registered](<https://github.com/panda3d/panda3d/issues/1820>)
- [SEGV in Geom::reset_geom_rendering](<https://github.com/panda3d/panda3d/issues/1821>)

