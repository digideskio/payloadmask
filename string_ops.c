#include "string_ops.h"
#include "mem_ops.h"

void *entropy_clock(void)
{
	double cpu_time;
	struct timeval tv;

	cpu_time = ((double) clock()) / CLOCKS_PER_SEC;
	gettimeofday(&tv, NULL);
	srandom((getpid() << 16) ^ tv.tv_sec ^ tv.tv_usec ^ (int)cpu_time);
  	return NULL;	
}


char *rand_str(char *dst, int size)
{
	static const char text[] =	"abcdefghijklmnopqrstuvwxyz"                     
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	entropy_clock();

	int i, len = random() % (size - 1);
  
	if( !len ) 
		len=8;
 
	for ( i=0; i<len; ++i )
		dst[i] = text[random() % (sizeof text - 1)];

   	dst[i] = '\0';

	return dst;
}

int char_type_counter(char *string,char type)
{
	int counter=0;
 
	while(*string != '\0')
	{
		if(*string==type) 
			counter++;
		string++;
	}
  
	return counter;
}


void chomp(char * str)
{
 
	while (*str) 
	{
		if ( *str == '\n' || *str == '\r' ) 
		{
			*str = 0;
			return;
		}
		str++;
	}
  
}




char *replace(char *instring,char *old,char *new)
{ 
	int instring_size=strlen(instring),new_size=strlen(new),old_size=strlen(old),out_size=instring_size+1,count=0;
	char *out=NULL,*tmp=NULL;
 	
	tmp = xmalloc(old_size+1);
	out = xmalloc(out_size);

	if(!out || !tmp)
 		return NULL;
    
 	if(instring_size<old_size || !old_size)
	{       
		strcpy(out, instring);
 		free(tmp);
		return out;
	}   

	out[0]='\0';
    
 	while(count <= instring_size)
	{       
		strncpy(tmp,(instring+count),old_size);
		tmp[old_size]='\0';
		if(!strcmp(tmp,old))
		{
			if(new_size!=old_size)
			{
				out_size=out_size+new_size-old_size;
				out=xrealloc(out,out_size);

				if(!out)
				{
					free(tmp);
					return NULL;
				}
			}
			strcat(out,new);
			count=count+old_size-1;
		}else{
			tmp[1]='\0';
			strcat(out,tmp);
		}

		count++;
	}

	free(tmp);

	return out;
}





