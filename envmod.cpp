#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <sys/time.h>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define SEPC ';'
#define SEPS ";"

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

int find_nth(const string &str, int n, char c, int pos=0) {
	int a=pos;
	int b=pos;
	for(int i=0;i<n;++i) {
		b=str.find(c, a);
		a=b+1;
		if(b==string::npos) return b;
	}
	return b;
}

#define NEED_ARG(func, nb) if(i+nb>=argc) {\
				fprintf(stderr, "ERROR : missing %d argument for %s.\n", nb, func);\
				return 1;\
			}

int main(int argc, char* argv[]) {
	if(argc==2) {
		if( strcmp(argv[1],"-v")==0 || strcmp(argv[1],"--version")==0 ) {
			printf("%s version 0.0.1\n", argv[0]);
			return 0;
		}
	}
	string file;
	string ext;
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
			NEED_ARG("print", 1);
			printf("\t%s=%s\n", argv[i+1], getenv(argv[i+1]));
			++i;
		}
		if(strcmp(argv[i],"help")==0) {
			printf("\tvars\nprint VARS variables\n");
			printf("\tvars2\nprint VARS2 variables\n");
			printf("\tshow\nprint VARS value\n");
			printf("\tshow2\nprint VARS2 value\n");
			printf("\tsave 'file'\nsave variables to 'file'\n");
			printf("\taddb 'VAR' 'pos' 'dir'\nadd 'dir' before the 'pos'th entry in 'VAR'\n");
			printf("\taddp 'VAR' 'pos' 'dir'\nadd 'dir' after the 'pos'th entry in 'VAR'\n");
		}
		if(strcmp(argv[i],"addp")==0) {
			NEED_ARG("addp", 3);
			const char* arg1=argv[i+1];
			const char* arg2=argv[i+2];
			const char* arg3=argv[i+3];
			if(strstr(VARS.c_str(), (string(":")+arg1+':').c_str())==NULL) {
				fprintf(stderr, "ERROR: variable %s not supported.\n", argv[i+1]);
				return 2;
			}
			const char* val=getenv(arg1);
			string val2=string(val);
			int nb=atoi(arg2);
			if(count(val2.begin(),val2.end(),SEPC)+1 < nb) {
				fprintf(stderr, "ERROR: there is less entries than %d.\n", nb);
				return 2;
			}
			if(nb<1) {
				fprintf(stderr, "ERROR: the first entry is 1.\n");
				return 2;
			}
			int pos1=find_nth(val2, nb, SEPC);
			printf("%d\n", pos1);
			if(pos1==string::npos) {
				val2=val2+';'+string(arg3);
			}
			else {
				val2=val2.substr(0, pos1)+';'+string(arg3)+val2.substr(pos1);
			}
#if 0
			setenv(arg1, val2.c_str(), 1);//overwrite
#else
			putenv((string(arg1)+'='+val2).c_str());
#endif
		}
		if(strcmp(argv[i],"addb")==0) {
			NEED_ARG("addb", 3);
			const char* arg1=argv[i+1];
			const char* arg2=argv[i+2];
			const char* arg3=argv[i+3];
			if(strstr(VARS.c_str(), (string(":")+arg1+':').c_str())==NULL) {
				fprintf(stderr, "ERROR: variable %s not supported.\n", argv[i+1]);
				return 2;
			}
			const char* val=getenv(arg1);
			string val2=string(val);
			int nb=atoi(arg2);
			if(count(val2.begin(),val2.end(),SEPC)+1 < nb) {
				fprintf(stderr, "ERROR: there is less entries than %d.\n", nb);
				return 2;
			}
			if(nb<1) {
				fprintf(stderr, "ERROR: the first entry is 1.\n");
				return 2;
			}
			int pos1=find_nth(val2, nb-1, SEPC);
			printf("%d\n", pos1);
			if(pos1==string::npos || pos1==0) {
				val2=string(arg3)+';'+val2;
			}
			else {
				val2=val2.substr(0, pos1)+';'+string(arg3)+val2.substr(pos1);
			}
#if 0
			setenv(arg1, val2.c_str(), 1);//overwrite
#else
			putenv((string(arg1)+'='+val2).c_str());
#endif
		}
		if(strcmp(argv[i],"save")==0) {
			NEED_ARG("save", 1);
			file=argv[i+1];
			int extp=file.rfind('.');
			if(extp==string::npos) {
				fprintf(stderr, "ERROR: no extension given for save.\n");
				return 2;
			}
			ext=file.substr(extp+1);
			if(strstr(":sh:bat:", (':'+ext+':').c_str())==NULL) {
				fprintf(stderr, "ERROR: unknown extension for save : '%s'.\n", ext.c_str());
			}
			FILE* fp=fopen(file.c_str(), "w");
			if(ext=="sh") {
				fprintf(fp, "#!/bin/sh\n");
				int a=0;
				int b=0;
				string var;
				do {
					b=VARS.find(':', a);
					var=VARS.substr(a, b-a);
					const char *val=getenv(var.c_str());
					if(val==NULL) val="";
					fprintf(fp, "export %s='%s'\n", var.c_str(), val);
					a=b+1;
					++i;
				}
				while(b!=string::npos);
			}
			else if(ext=="bat") {
				fprintf(fp, "@echo off\r\n");
				int a=0;
				int b=0;
				string var;
				do {
					b=VARS.find(':', a);
					var=VARS.substr(a, b-a);
					const char *val=getenv(var.c_str());
					if(val==NULL) val="";
					fprintf(fp, "set %s=%s\n", var.c_str(), val);
					a=b+1;
					++i;
				}
				while(b!=string::npos);
			}
			fclose(fp);
		}
	}
	return 0;
}
//
