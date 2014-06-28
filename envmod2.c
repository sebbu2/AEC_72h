#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

void print_dir2(const char* dir, int size) {
	if(strlen(dir)!=0) {
		printf("%.*s\n", size, dir);
	}
	else {
		printf("<empty>\n");
	}
}

void print_dir1(const char* dir) {
	print_dir2(dir, -1);
}

void print_dir_list(const char* var) {
	const char* pos=NULL;
	const char* pos2=var;
	int i=0;
	do {
		//printf("%p %p\n", pos2, pos);
		pos=strchr(pos2, ';');
		printf("\t%02d\t", i+1);
		if(pos!=0) {
			print_dir2(pos2, pos-pos2);
		}
		else {
			print_dir1(pos2);
		}
		pos2=pos+1;
		//printf("%p %p\n", pos2, pos);
		++i;
		//if(i>=10) break;
	}
	while(pos!=NULL);
}

int main(int argc, char* argv[]) {
	if(argc==2) {
		if( strcmp(argv[1],"-v")==0 || strcmp(argv[1],"--version")==0 ) {
			printf("%s version 0.0.1\n", argv[0]);
			return 0;
		}
		//return 1;
	}
	char *buf=NULL;
	buf=getenv("PATH");
	print_dir_list(buf);
	//printf("%s\n", buf);
	return 0;
}
//
