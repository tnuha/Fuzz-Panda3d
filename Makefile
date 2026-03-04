.PHONY: all clean run

CXX = afl-clang-fast++
CXXFLAGS = -g -O1 -fno-omit-frame-pointer

INCDIR = panda3d/include
LIBDIR = panda3d/lib

UNAME_S := $(shell uname -s)

# Libraries used by both platforms
COMMON_LIBS := -lp3framework -lpanda -lpandaexpress -lp3dtool -lp3dtoolconfig -lp3direct -lpandagl -lpandaegg \
							-lssl -lcrypto -lpng -ljpeg -lz -ltiff -lIex -lIlmThread -lsquish -lopusfile -lopus -lvorbisfile -lvorbis -logg -lobjc  \

LDLIBS :=
ifeq ($(UNAME_S),Darwin)
# macOS: link frameworks
	LDLIBS += $(COMMON_LIBS) -lIlmImf -lHalf

# Framework flags must come after -l flags
	FRAMEWORKS := \
		-framework CoreVideo \
		-framework Carbon \
		-framework IOKit \
		-framework AppKit \
		-framework OpenGL \

	LDLIBS += $(FRAMEWORKS)
else
# GNU/Linux
	LDLIBS += $(COMMON_LIBS) -lX11 -lGL -lOpenEXR -lImath
endif

harness: harness.cpp
	$(CXX) $(CXXFLAGS) harness.cpp -o harness -I$(INCDIR) -L$(LIBDIR) $(LDLIBS)

fuzz: harness
	afl-fuzz -i in -o out -- ./harness @@

clean:
	rm -f harness