LIB_NAME = Stellar

CXX      = g++
CPPFLAGS =
CXXFLAGS = -std=c++17 -g -O3 -DSTLR_BUILD_DLL -fPIC
LDFLAGS  = 
LDLIBS   =
RM       = rm -f

# Target OS detection
ifeq ($(OS),Windows_NT) # OS is a preexisting environment variable on Windows
	OS = windows
	LIB_EXT = .dll
	GLFW_LIB = glfw3.dll
else
	UNAME := $(shell uname -s)
	ifeq ($(UNAME),Darwin)
		OS = macos
	else 
		ifeq ($(UNAME),Linux)
			OS = linux
			LIB_EXT = .so
			GLFW_LIB = libglfw.so.3.3
		else
			$(error OS not supported by this Makefile)
		endif
	endif
endif
# OS-specific settings
ifeq ($(OS),windows)
	LDFLAGS += -L./vendor/glfw/libs -L"C:\Windows\System32"
	CPPFLAGS += -I ./vendor/glfw/include -I "C:\VulkanSDK\1.2.198.1\Include"
	LDLIBS += -lglfw3 -lopengl32 -lgdi32 -lvulkan-1

	ifeq ($(win32),1)
	$(error Stellar Engine does not support 32 bit os)
	endif

	else ifeq ($(OS),macos)
		INCLUDES +=
		LDFLAGS +=
		LDLIBS +=
	else ifeq ($(OS),linux)
		CPPFLAGS += -I ./vendor/glfw/include 
		LDFLAGS += L./vendor/glfw/libs
		LDLIBS += -lglfw -lvulkan
endif

# EVERYTHING PAST HERE SHOULD WORK AUTOMATICALLY

.SECONDARY:

include $(wildcard ../PrettyPrint.inc)

# Find the source files that will be used.
SRC_DIR = src
EXE_SRC_FILES = $(wildcard *.cpp)
EXECUTABLES = $(patsubst %.cpp,bin/%,$(EXE_SRC_FILES))
SRC_FILES := $(sort $(shell find $(SRC_DIR) -name '*.cpp'))
O_FILES = $(patsubst %.cpp,build/%.o,$(SRC_FILES))

all: $(EXECUTABLES) lib/lib$(LIB_NAME)$(LIB_EXT)
	@mkdir -p ../Sandbox/bin
	@cp ./lib/libStellar$(LIB_EXT) ../Sandbox/bin/
	@cp ./vendor/glfw/libs/$(GLFW_LIB) ../Sandbox/bin/

# Update dependencies with each compilation
override CPPFLAGS += -MMD
-include $(shell find build -name "*.d" 2> /dev/null)

bin/%: build/%.o | lib/lib$(LIB_NAME)$(LIB_EXT)
	@mkdir -p $(@D)
	@$(call run_and_test,$(CXX) $(LDFLAGS) $< $(LDLIBS) -o $@)

lib/lib$(LIB_NAME)$(LIB_EXT): $(O_FILES)
	@mkdir -p $(@D)
	@$(call run_and_test,$(CXX) $(LDFLAGS) $(LDLIBS) $^ -shared -o $@)

build/%.o: %.cpp
	@mkdir -p $(@D)
	@$(call run_and_test,$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@)

clean:
	@echo "Cleaning"
	@$(RM) -r bin build lib