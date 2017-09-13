#lengthChromtFasta v0.1 (20170913) Jordi Leno-Colorado
#
#Usage: ./lengthChromtFa -i file.tfa(.gz) -o output.txt
#
#Flags:
#      -i [Compressed or uncompressed tFasta file to analyze]
#      -o [Output file to write the length of chromosomes]
#   OPTIONAL PARAMETERS:
#      -h [help and exit]

# To compile:
make -f nbproject/Makefile-Release.mk build/Release/GNU-Linux/main.o
mkdir -p build/Release/GNU-Linux
rm -f "build/Release/GNU-Linux/main.o.d"
g++ -std=c++0x -lz   -c -O2 -MMD -MP -MF "build/Release/GNU-Linux/main.o.d" -o build/Release/GNU-Linux/main.o main.cpp
/usr/bin/make -f Makefile CONF=Release

# Run examples

cd Examples

echo -------------------------------------------------------------------------------------------
echo Example. Obtain the last position of each chromosome from a tFasta file with 3 chromosomes
echo -------------------------------------------------------------------------------------------
echo
echo ../bin/lengthChromtFa -i example_chr123.tfa.gz -o example_chr123_length.txt
../bin/lengthChromtFa -i example_chr123.tfa.gz -o example_chr123_length.txt
echo

