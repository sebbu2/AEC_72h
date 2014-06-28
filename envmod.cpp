#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <ctime>
//#include <iostream>
#include <cstring>
//#include <string>

extern char ** environ;

const int LOOP=100000;

int main(int argc, char* argv[], char* envp[]) {
	if(argc==2) {
		if( strcmp(argv[1],"-v")==0 || strcmp(argv[1],"--version")==0 ) {
			printf("%s version 0.0.1\n", argv[0]);
		}
		return 1;
	}
	char *buf=NULL;
	clock_t t=0;
	/*1*/
	t=clock();
	for(int a=0;a<LOOP;++a) {
		for(int i=0;envp[i]!=NULL;++i) {
			if(strncmp(envp[i],"PATH=",5)==0) buf=envp[i]+5;
		}
	}
	t=clock()-t;
	printf("%s\n", buf);
	printf ("%d clicks (%f seconds)\n", (int)t, ((float)t)/CLOCKS_PER_SEC);
	//*/
	/*2
	t=clock();
	for(int a=0;a<LOOP;++a) {
		for(int i=0;environ[i]!=NULL;++i) {
			if(strncmp(environ[i],"PATH=",5)==0) buf=environ[i]+5;
		}
	}
	t=clock()-t;
	printf("%s\n", buf);
	printf ("%d clicks (%f seconds)\n", (int)t, ((float)t)/CLOCKS_PER_SEC);
	//*/
	/*3
	t=clock();
	for(int a=0;a<LOOP;++a) {
		buf=getenv("PATH");
	}
	t=clock()-t;
	printf("%s\n", buf);
	printf ("%d clicks (%f seconds)\n", (int)t, ((float)t)/CLOCKS_PER_SEC);
	*/
	//*/
	return 0;
}
//
