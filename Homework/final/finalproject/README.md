# Final Project - Zombie Roads Part 1 and Part 2
# Ayush Khanal
# Professor Christopher Godley Data Structures Section 310

Description:
    This project was meant to simulate a road network

#Part 1 Build and Run Instructions and details
    list of files:
        Graph.h
        GraphPart1.cpp
        mainPart1.cpp
        zombieCities.txt
    compile:
        g++ -std=c++11 mainPart1.cpp GraphPart1.cpp -o finalpart1.o
    run:
        ./finalpart1.o zombieCities.txt
#Part 2 Build and Run Instructions and details
    list of files:
        Graph.hpp
        GraphPart2.cpp
        mainPart2.cpp
        zombieCities.txt
    compile:
        g++ -std=c++11 mainPart2.cpp GraphPart2.cpp -o finalpart2.o
    run:
        ./finalpart2.o zombieCities.txt

#zombie text file should have this format

cities,Atlanta,Boston,Boulder,Cheyenne,Chicago,Cleveland,Disneyland,Key West,Miami,New Orleans,New York,Portland,San Francisco,Seattle,Yakima
Atlanta,0,-1,-1,-1,-1,-1,-1,-1,663,487,-1,-1,-1,-1,-1
Boston,-1,0,-1,-1,982,640,-1,-1,-1,-1,215,-1,-1,-1,-1
Boulder,-1,-1,0,-1,1130,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1


#line one should be the city list delimited by commas, the cities list should only be on the first line ignore text wrapping
