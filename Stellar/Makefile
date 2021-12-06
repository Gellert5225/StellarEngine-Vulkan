LIB_NAME = Stellar

CXX      = g++
CPPFLAGS =
CXXFLAGS = -std=c++17 -g -O3 -DSTLR_BUILD_DLL
LDFLAGS  = 
LDLIBS   =
RM       = rm -f

# Additional flags that are necessary to compile.
# Even if not specified on the command line, these should be present.

override CPPFLAGS += -Iinclude
override CXXFLAGS += -fPIC
override LDFLAGS  += -Llib -Wl,-rpath,\$$ORIGIN/../lib
override LDLIBS   += -l$(LIB_NAME)

# EVERYTHING PAST HERE SHOULD WORK AUTOMATICALLY

.SECONDARY:

include $(wildcard ../PrettyPrint.inc)

# Find the source files that will be used.
SRC_DIR = src
EXE_SRC_FILES = $(wildcard *.cpp)
EXECUTABLES = $(patsubst %.cpp,bin/%,$(EXE_SRC_FILES))
SRC_FILES := $(sort $(shell find $(SRC_DIR) -name '*.cpp'))
O_FILES = $(patsubst %.cpp,build/%.o,$(SRC_FILES))

all: $(EXECUTABLES) lib/lib$(LIB_NAME).so

# Update dependencies with each compilation
override CPPFLAGS += -MMD
-include $(shell find build -name "*.d" 2> /dev/null)

bin/%: build/%.o | lib/lib$(LIB_NAME).so
	@mkdir -p $(@D)
	@$(call run_and_test,$(CXX) $(LDFLAGS) $< $(LDLIBS) -o $@)

lib/lib$(LIB_NAME).so: $(O_FILES)
	@mkdir -p $(@D)
	@$(call run_and_test,$(CXX) $^ -shared -o $@)

build/%.o: %.cpp
	@mkdir -p $(@D)
	@$(call run_and_test,$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@)

clean:
	@echo "Cleaning"
	@$(RM) -r bin build lib