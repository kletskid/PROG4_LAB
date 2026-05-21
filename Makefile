
app:
	g++ main.cpp -o app $(shell pkg-config --cflags --libs Qt6Widgets)

clean:
	rm app

