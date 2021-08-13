# Hole punching coordinator for UltraGrid

This utility serves as a meeting point for UltraGrid clients, that need to connect to each other,
but don't have publicly routable IP addresses.

Building
---------
    mkdir build && cd build
    cmake ..
    make
    
Usage
---------
    ./hole_punch_coordinator [-h/--help] [-p/--port <port>]
    
If no port is specified, 12558 is used.
