#include "temp_function.h"

int main(int argc, char **argv){
	int rez = 0;
	opterr=0;

	while ((rez = getopt(argc,argv,"hf:m:y")) != -1)
	{
		switch (rez)
		{
		case 'h': help(); break;
		case 'f': fileReader(optarg); break;
		case 'm': printMonthStat(optarg); break;
		case 'y': printYearStat(); break;  
		case '?': help(); break;
		default: help(); break;
		}
	}
	
	return 0;
}
