
SRCS = $(wildcard *.cpp)

HDRS = $(wildcard *.h)

MOCS = $(addprefix moc_,$(HDRS:%.h=%.cpp))


moc_%.cpp: %.h
	/usr/lib/qt6/libexec/moc $< -o $@

app: $(MOCS)
	g++ $(SRCS) -o app $(shell pkg-config --cflags --libs Qt6Widgets)

clean:
	rm $(MOCS) app

