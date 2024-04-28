// DO NOT MODIFY THIS FILE
// This constants can be replaced with alternates during grading

#ifndef CONSTANTS_2_H
#define CONSTANTS_2_H

#define USAGE_MSG "53HistStats [-h] [-o OUTFILE] [-i IGNOREFILE] [-p LEVEL] [-s] -A | -F | -U NUM\n"\
                  "\n  -F          Print executable programs from most to least frequently found"\
                  "\n  -U NUM      Prints the NUM most recently used executable programs"\
                  "\n  -A          Print all the executable programs in alphabetical order"\
                  "\n  -h          Prints the usage statement to STDOUT. All other arguments are ignored"\
                  "\n  -o          Output is written to OUTFILE if specified. If unspecified, output is written to STDOUT"\
                  "\n  -i          List of executable files to ignore"\
                  "\n  -p          Print level (0,1,2) for output format"\
                  "\n  -s          Print additional statistics about excecutable identified\n"\

#define TOTALCNT "Total number of commands: "           // Print value as integer
#define EXTCNT "Number of unique executables: "         // Print value as integer
#define BG "Percentage of background commands (&): "    // Print value as double using %.2f 
#define PIPE "Percentage of piped commands (|): "       // Print value as double using %.2f 
#define R_IN  "Percentage of commands with input redirection (<): "       // Print value as double using %.2f, eg. 50.00%
#define R_OUT "Percentage of commands with output redirection (>): "       // Print value as double using %.2f, eg. 25.20%
#define R_ERR "Percentage of commands with error redirection (2>): "      // Print value as double using %.2f, eg. 0.00%

#endif
