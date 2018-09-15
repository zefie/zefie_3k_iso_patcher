// Dump ISO in multiMAN in "Direct Disc Access" mode
// Use with https://github.com/zefie/getkey_gameos_zefie (to get disc.key)
// Need "3Dump.bin" for disc.key generation. TODO: help user make 3Dump.bin

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>

#ifdef __linux__
#include <sys/io.h>
#else
#include <io.h>
#endif

//#define DEBUG 1

typedef enum { false, true } bool;

void print_debug(char *fmt, ...) {
#ifdef DEBUG
	va_list arg;
	va_start(arg, fmt);
	vprintf(fmt, arg);
	va_end(arg);
#endif
	return;
}

bool file_exists(char *filename) {
	print_debug("checking if %s exists\n",filename);
	if (access(filename, 0) != -1) {
		print_debug("%s exists\n",filename);
		return true;
	}
	print_debug("%s does NOT exist\n",filename);
	return false;
}

// --- 

void getFileDir(char *filename, char *ret) {
	print_debug("attempting to find directory for %s\n",filename);
	char tmp[PATH_MAX];
	realpath(filename, tmp);
	if (!tmp) {
		printf("Error finding directory for %s (Err %i).\n", filename, errno);
		return;
	}
	print_debug("realpath for %s returned %s\n",filename,tmp);
	char *pos = strrchr(tmp, 47);
	int strpos = (pos - tmp);
	strncpy(ret, tmp, strpos);
	print_debug("found directory %s\n",ret);
}

void getFileNoExt(char *filename, char *ret) {
	print_debug("attempting to remove extention from %s\n",filename);
	char filenoext[PATH_MAX];
	char *pos = strrchr(filename, 46);
	int strpos = (pos - filename);
	strncpy(ret, filename, strpos);
	ret[strpos] = 0;
	print_debug("result: %s\n",ret);
}

void findKeyfile(char *filename, char *ret) {	
	char filepath[PATH_MAX];
	getFileDir(filename, filepath);
	strcpy(ret, filepath);
	strcat(ret, "/disc.key");
	print_debug("attempting to find keyfile %s\n",ret);
	if (!file_exists(ret)) {
		print_debug("%s does NOT exist\n",ret);
		strcpy(ret, filepath);
		char filenoext[PATH_MAX];
		getFileNoExt(filename, filenoext);
		strcat(ret,"/");
		strcat(ret,filenoext);
		print_debug("attempting to find keyfile %s\n",ret);
		strncat(ret, ".key", -1);
		if (!file_exists(ret)) {
			print_debug("%s does NOT exist\n",ret);
			ret[5] = 0;
		}
	}
}

int main(int argc, char *argv[], char *envp[])
{
	char *filename;	
#ifdef DEBUG
	filename = "Minecraft Story Mode.ISO";
#else
	if (argc > 1) {
		filename = argv[1];
	}
	else {
		printf("You did not specify an iso file.\n");
		return 1;
	}
#endif
	
	if (file_exists(filename)) {
		printf("Found %s, searching for 3K Key File...\n", filename);
		
		char keyfilename[PATH_MAX];
		findKeyfile(filename, keyfilename);
		
		if (keyfilename[5] == 0) {
			printf("Could not find zefie 3K key dump (disc.key)\n");
			return 1;
		}
		printf("Found %s, patching...\n", keyfilename);
		
		FILE *file = fopen(filename, "rb+");
		if (!file) {
			printf("Error opening ISO %s for patching (Err %i).\n", filename, errno);
			return 1;
		}
		
		char test[14];
		fseek(file, 2048, SEEK_SET);
		fgets(test, 13, file);
		if (!strcmp(test, "PlayStation3")) {
			FILE *keyfile = fopen(keyfilename, "rb");
			if (!keyfile) {
				printf("Error opening key file %s for reading (Err %i).\n", keyfilename, errno);
				return 1;
			}
			fseek(keyfile, 0, SEEK_END);
			long keylen = ftell(keyfile);
			fseek(keyfile, 0, SEEK_SET);
			char *keybin = malloc(keylen + 1);
			fread(keybin, 1, keylen, keyfile);
			fclose(keyfile);
			free(keyfile);
			
			
			int header_threekey = 3952;

			fseek(file, header_threekey, SEEK_SET);
			fwrite(keybin, keylen, 1, file);
			printf("Patched %i bytes of %s successfully.\n", keylen, filename);
			fclose(file);
			free(file);
		}
		else {
			printf("%s\n", test);
			fclose(file);
			free(file);
			printf("Not a PS3 ISO");
			return 1;
		}
	}
	return 0;
}

