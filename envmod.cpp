#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <sys/time.h>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const string VARS="CDPATH:CPATH:C_INCLUDE_PATH:CPLUS_INCLUDE_PATH:OBJC_INCLUDE_PATH:LD_LIBRARY_PATH:LD_RUN_PATH:LIBRARY_PATH:MANPATH:PATH:PERL5LIB:PERLLIB:PKG_CONFIG_PATH";

const string VARS2="INCLUDES:CPPFLAGS:CFLAGS:CXXFLAGS:LDFLAGS:LOADLIBES:LDLIBS";

void print_vars(const string list) {
	int i=1;
	int a=0;
	int b=0;
	string var;
	do {
		b=list.find(':', a);
		var=list.substr(a, b-a);
		printf("\t%02d\t%s=%s\n", i, var.c_str(), getenv(var.c_str()));
		a=b+1;
		++i;
	}
	while(b!=string::npos);
}

int main(int argc, char* argv[]) {
	if(argc==2) {
		if( strcmp(argv[1],"-v")==0 || strcmp(argv[1],"--version")==0 ) {
			printf("%s version 0.0.1\n", argv[0]);
			return 0;
		}
	}
	for(int i=1; i<argc; ++i) {
		if(strcmp(argv[i],"vars")==0) {
			printf("VARS = %s\n", VARS.c_str());
		}
		if(strcmp(argv[i],"vars2")==0) {
			printf("VARS2 = %s\n", VARS2.c_str());
		}
		if(strcmp(argv[i],"show")==0) {
			print_vars(VARS);
		}
		if(strcmp(argv[i],"show2")==0) {
			print_vars(VARS2);
		}
		if(strcmp(argv[i],"print")==0) {
			if(i+1>=argc) {
				fprintf(stderr, "ERROR : missing argument for print.\n");
				return 1;
			}
			printf("\t%s=%s\n", argv[i+1], getenv(argv[i+1]));
			++i;
		}
	}
	return 0;
}
//
