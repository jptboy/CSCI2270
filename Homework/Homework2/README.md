# Homework 2 - Word Analysis
# Ayush Khanal
# Professor Christopher Godley Data Structures Section 310

Description:
    This assignment is meant to write a program that analyzes lexical information from a large text file that is the hunger games book without punctuation.

List of Files:
    main.cpp-has all the code

How to build and run:
  
  Go to the directory called Homework2
  
  Compile:

  g++ -std=c++11 main.cpp -o homework2.o
  
Run:
  
./homework2.o #(numberOfOutputsWanted) bookFile(filename.txt) ignoreWords(filename.txt)

./homework2.o 30 HungerGames_edit.txt ignoreWords.txt

# The book text file should have this format:
hunger 
games 
parti 
the tributes 
 
when i wake up the other side of the bed is cold my 
fingers stretch out seeking prims warmth but finding 
only the rough canvas cover of the mattress she 
must have had bad dreams and climbed in with our 
mother of course she did this is the day of the 

#ignorewords textfile should have this format
word
also
hello