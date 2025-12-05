CC := clang
CFLAGS := -Wall
CFLAGS_DEBUG := -g -O0 -Wextra
CXX := clang++
CXXFLAGS := -Wall
CXXFLAGS_DEBUG := -g -O0 -Wextra

ifeq ($(DEBUG),1)
CFLAGS += $(CFLAGS_DEBUG)
CXXFLAGS += $(CXXFLAGS_DEBUG)
endif

# TestKit linkage support
# Set LINK_TESTKIT=1 when calling make to compile and link testkit/testkit.c
# Example: make FILE=main LINK_TESTKIT=1
TESTKIT_DIR := ~/projects/jyyos/testkit
TESTKIT_SRC := $(TESTKIT_DIR)/testkit.c
TESTKIT_OBJ := $(TESTKIT_DIR)/testkit.o
TESTKIT_INC := -I$(TESTKIT_DIR)



SRCS := $(wildcard *.c) $(wildcard *.cpp)

PROGS := $(SRCS:.c=)
PROGS := $(PROGS:.cpp=)

.PHONY: all clean
all: $(PROGS)


# Build testkit object when requested
$(TESTKIT_OBJ): $(TESTKIT_SRC)
	$(CC) $(CFLAGS) $(TESTKIT_INC) -c $< -o $@

ifeq ($(LINK_TESTKIT),1)
# If LINK_TESTKIT is set, link the testkit object into executables.
%: %.c $(TESTKIT_OBJ)
	$(CC) $(CFLAGS) $(TESTKIT_INC) $< $(TESTKIT_OBJ) -o $@

%: %.cpp $(TESTKIT_OBJ)
	$(CXX) $(CXXFLAGS) $(TESTKIT_INC) $< $(TESTKIT_OBJ) -o $@
else
%: %.c
	$(CC) $(CFLAGS) $< -o $@

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
endif


clean:
	rm -f $(PROGS)
	rm -rf *.dSYM