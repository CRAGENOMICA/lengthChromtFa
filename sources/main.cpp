/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on September 13, 2017, 12:40 PM
 */

#include <stdio.h>
#include <cstdlib>
#include <iostream>
//#include <sstream>
#include <string>
#include <vector>
#include "zutil.h"
#include "zindex.h"
#include "CStringTools.h"
#include "File.h"

void help(std::string name) {
    std::cerr << "lengthChromtFa\n"
            << "Usage: ./lengthChromtFa -i file.tfa(.gz) -o output.txt\n"
            << "Options:\n"
            << "\t-h\t\tHelp and exit\n"
            << "\t-i\t\tCompressed or uncompressed tFasta file to analyze\n"
            << "\t-o\t\tOutput file to write the length of chromosomes\n"
            << std::endl;
}

int main(int argc, char** argv) {

    /////////////////////////////
    // Argumentos del programa //
    /////////////////////////////

    std::string tfastafile;
    std::string outlist;

    char tmp;
    if (argc == 1) {
        help(argv[0]);
        exit(1);
    }

    while ((tmp = getopt(argc, argv, "hi:o:")) != -1) {
        switch (tmp) {
            case 'h':
                help(argv[0]);
                break;
            case 'i':
                tfastafile = std::string(optarg);
                break;
            case 'o':
                outlist = std::string(optarg);
                break;
        }
    }

    if (tfastafile == "") {
        // Si no se da ningún tFasta en el comando
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\tInput tFasta not defined" << std::endl;
        std::cout << std::endl;
        return 1;
    }
    if (outlist == "") {
        // Si no se da ningun nombre para el output en el comando
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\tOutput file not defined" << std::endl;
        std::cout << std::endl;
        return 1;
    }

    std::cout << std::endl;
    std::cout << "Input tFasta: " << tfastafile << std::endl;
    std::cout << "Output file: " << outlist << std::endl;
    std::cout << std::endl;

    File tfasta(tfastafile);
    File output(outlist);

    std::string line;
    std::string chrom = "";
    std::string pos = "";
    std::string firstline = "yes";
    std::string current_chrom;
    std::string current_pos;

    // Abrir el tFasta output para escribir en él
    if (output.openWriteFile()) {
        // Abrir el tFasta
        if (tfasta.openReadFile()) {
            // Siempre que no lleguemos al final del archivo:
            while (!tfasta.endFile()) {
                line = tfasta.readLine();
                if (line[0] != '#') {
                    // Si la linea no corresponde al header
                    if (chrom == "" && pos == "") {
                        firstline = "yes";
                        std::vector<std::string> linetfa_vector = CStringTools::split(line, '\t');
                        std::vector<std::string> chrompos = CStringTools::split(linetfa_vector[0], ':');
                        chrom = chrompos[0];
                        pos = chrompos[1];
                    } else {
                        std::vector<std::string> linetfa_vector = CStringTools::split(line, '\t');
                        std::vector<std::string> chrompos = CStringTools::split(linetfa_vector[0], ':');
                        chrom = chrompos[0];
                        pos = chrompos[1];
                        if (chrom != current_chrom) {
                            output.writeFile(current_chrom + "\t" + current_pos + "\n");
                        }
                    }
                    current_chrom = chrom;
                    current_pos = pos;
                }
            }
            if (tfasta.endFile()) {
                output.writeFile(current_chrom + "\t" + current_pos + "\n");
            }
            tfasta.closeFile();
        }
        output.closeFile();
    }

    return 0;
}
