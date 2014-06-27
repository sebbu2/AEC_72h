#include <iostream>
#include <cstring>
#include <string>

int main(int argc, char* argv[]) {
	if(argc==2) {
		if( strcmp(argv[1],"-v")==0 || strcmp(argv[1],"--version")==0 ) {
			printf("%s version 0.0.1\n", argv[0]);
		}
		return 1;
	}
	return 0;
}
//
