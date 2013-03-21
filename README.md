## dot rendering experiments

## Depends

 - Mapnik master

Install Mapnik master on ubuntu:

    sudo add-apt-repository ppa:mapnik/nightly-trunk
    sudo apt-get update
    sudo apt-get install libmapnik libmapnik-dev

Install Mapnik master on os x:

    brew update
    brew install mapnik --HEAD

## Usage

To setup the test data, compile, and run the code do:

    make

## Background
    
Currently the first test script uses an osm gps trace dump
from the western us from, simply because it is of moderate
size and a simple test case.

http://zverik.osm.rambler.ru/gps/files/extracts/usa/index.html

Learn more about the sample data from:

http://blog.osmfoundation.org/2012/04/01/bulk-gps-point-data/
