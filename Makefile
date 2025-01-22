CC = gcc
WINCC = x86_64-w64-mingw32-gcc
WEBCC = -emcc
LDFLAGS = -Llibraries -lraylib -lm
PROFFLAGS = -g -pg
WINFLAGS = -Llibraries/windows -lgdi32 -luser32 -lwinmm -lkernel32 -lopengl32
LINFLAGS = -Llibraries/linux
WEBFLAGS = -Llibraries/web -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 -Wno-unused-command-line-argument --preload-file resources
LDFLAGS = -lraylib -lm
SRC = src/*.c
OUTPUT = build/game
WEBOUTPUT = build/index.html
OUTDIR = build/

program:
	$(CC) $(SRC) -o $(OUTPUT) $(LDFLAGS) $(LINFLAGS)

windows:
	$(WINCC) $(SRC) -o $(OUTPUT) $(LDFLAGS) $(WINFLAGS)

web:
	$(WEBCC) $(SRC) -o $(WEBOUTPUT) $(LDFLAGS) $(WEBFLAGS)

profile:
	$(CC) $(SRC) -o $(OUTPUT) $(LDFLAGS) $(PROFFLAGS)

clean:
	rm -f $(OUTDIR)* $(WEB-OUT)
