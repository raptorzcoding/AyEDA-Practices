CXX = g++
CXXFLAGS = -Wall

SRCS = Main.cc
OBJS = $(SRCS:.cc=.o)
EXEC = BigNumbers

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean