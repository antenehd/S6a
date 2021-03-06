
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*finds a substring in a given string('parent_str') that immediatly follows another reference substring('ref_str') untill space charater or new line character or null character. if return is not NULL it should be freed after use*/
char * test_parse_string(char * parent_str, char * ref_str){

	char * found = NULL;
	char * ps = NULL;
	char * pd = NULL;
	size_t len_found = 0;

	if((!parent_str) || (!ref_str))
		return NULL;

	/*Search for the reference substring*/
	if((ps = strstr(parent_str, ref_str)) == NULL)
		return NULL;

	/*jump pointer to the end of the reference substring*/
	ps = ps + strlen(ref_str);

	/*find the first space or null or newline character after the end of the reference substring*/
	if(((pd = strchr(ps, ' ')) != NULL) || ((pd = strchr(ps, '\n')) != NULL) || ((pd = strchr(ps, '\0')) != NULL))
		len_found = pd - ps;

	/*copy the substring after the reference substring untill space charater or new line character or null character*/
	if(len_found){

		if((found = malloc(len_found + 1)) != NULL){
	
			memset(found, '\0', len_found + 1);
			strncpy(found, ps, len_found);
		}
	}		

	return found;
}

/*reads a file content into a buffer and returns a pointer to a buffer. file contetn size should be less 1000.  if return is not NULL it should be freed after use*/
char * test_parse_conf(char * filename){

	FILE * f = NULL;
	char * buf = NULL;
	long size = 0;


	if(!filename)
		return NULL;
		
	/*open file for reading*/
	if((f = fopen(filename, "r")) == NULL){	
		perror("Error : ");
		return NULL;
	}

	/*copute size of file*/
	fseek(f, 0, SEEK_END);
	size = ftell(f);

	/*read whole file content to buffer*/
	if(size <= 1000 && size > 0){
		
		fseek(f, 0, SEEK_SET);
				
		if((buf = malloc(size + 1)) != NULL){

			memset(buf, '\0',size + 1);
			fread( buf, size + 1, 1, f);
		}		
	}

	return buf;
}
