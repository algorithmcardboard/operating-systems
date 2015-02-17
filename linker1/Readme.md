#Linker - Lab1

**Author** Anirudhan Jegannathan Rajagopalan

**N-Number** N18824115

**Email** ajr619@nyu.edu

##How to compile?
    g++ linker.cpp -o linker

**DataStructurees**
####Symbol Table
A vector of the symbols that are defined in the code.  It also has an auxillary map of symbol to position in the vector to enable fast lookups.

##Files
**Main File**
  linker.cpp

**./ds folder**
  Contains the various objects used by the linker.
  * Token - Contains ```int lineNUmber```, ```int columnNumber``` and ```char* token```.  Every token is delimited by ```\n```, ```\t``` or a ``` ```.
  * Symbol - Contains all fields in a token.  Only tokens that are alphanumeric are pushed into a symbol.  It has additional fields such as ```moduleBaseAddress```, ```isUsed``` and ```hasMultipleDefinitions```.

**./readers folder**
  Contains readers for every type of list
  * *DefinitionListReader* Reads a definition list (num of definitions followed by num pairs of symbols & relative address)
  * *UseListReader* Reads a use list (num of definitions followed by num symbols)
  * *ProgramTextReader* Reads the code instructions.  (num instructions followed by num pairs of addressing & opcode.  Addressing should be one of ```[I, R, A, E]``` and opcode should be less than ```10000```.  The last three positions of opcode is the address.
