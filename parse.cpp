#include "parse.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void showHelp() {
  cout << "-help: print out the help message. "                         <<endl; 
  cout << "-end : specify the number of the Ends   "                    <<endl; 
  cout << "-rand: specify the number of random backoff index"           <<endl; 
  cout << "-type: specify the traffic type, uniform or Beta distribtion"<<endl; 
}
void lineParsing (int argc, char** argv) {
  if (argc == 1) {
    showHelp();
    exit(0);
  }
  else {

    for (int i = 1; i < argc; i++) {
      if (!strcmp(argv[i], "-help")) {
        showHelp();
        exit(0);
      }
      else if (!strcmp(argv[i], "-end")) {
        lte::EndNum = atoi(argv[++i]);
	cerr << "EndNum = \t" << lte::EndNum << endl;
      }
      else if (!strcmp(argv[i], "-rand")) {
        lte::RandomBackoffIndex = atoi(argv[++i]);
	cerr << "Random Backoff Index = \t" << lte::RandomBackoffIndex << endl;
      }
      else if (!strcmp(argv[i], "-type")) {
        if (!strcmp(argv[++i], "uniform")) {
          lte::traffic_type = uniform_start;
	  cerr << "traffic type = \t" << "uniform\n";
	}
        else if (!strcmp(argv[i], "beta")) {
          lte::traffic_type = beta_start;
	  cerr << "traffic type = \t" << "beta\n";
	}
        else {
          cerr << "false traffic type " << argv[i] << endl;
          exit(1);
        }
      } 
      else if (!strcmp(argv[i], "-max")) {
	lte::MAX = atoi(argv[++i]);
	cerr << "limit of retransmition = \t" << lte::MAX << endl;
      }
      else if (!strcmp(argv[i], "-pre")) {
	double part = atoi(argv[++i]);
	if ((part >= 1) && (part <= 54)) {
	    lte::preambleNum = part;
	    cerr << "Num. of preamble for machine = \t" 
              << lte::preambleNum <<endl;
	}
      }
      else {
        cerr << "false argument " << argv[i] << endl;
        exit(1);
      }
    }

  }
}
