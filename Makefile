all: test

us-west.csv.xz:
	wget http://zverik.osm.rambler.ru/gps/files/extracts/usa/us-west.csv.xz

us-west.csv: us-west.csv.xz
	xz -k -d us-west.csv.xz

stdin-render: stdin-render.cpp
	clang++ -o stdin-render stdin-render.cpp `mapnik-config --cflags --libs --ldflags` -lboost_system

test: stdin-render us-west.csv
	time cat us-west.csv | ./stdin-render; open test.png

clean:
	rm -rf ./stdin-render

.PHONY: test
