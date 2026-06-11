QTFLAGS := $(shell pkg-config --cflags Qt6Widgets)
QTLIBS  := $(shell pkg-config --libs Qt6Widgets)

CFLAGS := -g

CXX_SRCS := $(filter-out $(wildcard moc_*.cpp),$(wildcard *.cpp))
C_SRCS   := $(wildcard *.c) $(wildcard fsm_functions/*.c)
HDRS     := $(wildcard *.hpp)

MOCS := $(addprefix moc_,$(HDRS:.hpp=.cpp))

OBJS := $(C_SRCS:.c=.o) \
        $(CXX_SRCS:.cpp=.o) \
        $(MOCS:.cpp=.o)

moc_%.cpp: %.hpp
	/usr/lib/qt6/libexec/moc $< -o $@

%.o: %.cpp
	g++ $(CFLAGS) $(QTFLAGS) -c $< -o $@

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

app: $(OBJS)
	g++ $(CFLAGS) $(OBJS) -o $@ $(QTLIBS)

clean:
	rm -f $(OBJS) $(MOCS) app
