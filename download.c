#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buf[10000];
FILE *fp;

void tag(){
	char ch;
	int i = 0;
	while((ch = getc(fp)) != '>') buf[i++] = ch;
	buf[i] = '\0';
}

int main(int argc, char *argv[]){
	char word[100], wget[100];
	FILE *out = fopen(argv[1], "w");
	if(!out){
		fprintf(stderr, "cannot open output file\n");
		return -1;
	}

	for(int a = 1;; ++a){

		fgets(word, sizeof word, stdin);

		for(int i = 0;; ++i){
			if(word[i] == '\n'){
				word[i] = '\0';
				break;
			}
		}

		if(!strcmp(word, ":q")){
			printf("complete\n");
			return 0;
		}

		strcpy(wget, "wget https://en.oxforddictionaries.com/definition/");
		strcat(wget, word);
		strcat(wget, " 2>/dev/null");
		system(wget);

		fp = fopen(word, "r");

		fprintf(out, "%s\n", word);

re:
	for(char x;;){
		x = getc(fp);
		if(x == EOF) goto loopend;
		if(x == '<'){
			tag();
			if(!strcmp(buf, "section class=\"gramb\"")){
				for(;;) if(getc(fp) == '<'){
					tag();
					if(!strcmp(buf, "span class=\"ind\"")){
						char ch;
						while((ch = getc(fp)) != '<') putc(ch, out);
						putc('\n', out);
						while(getc(fp) != '>');
					}
					else if(!strcmp(buf, "/section")){
						goto re;
					}
				}
			}
		}
	}
loopend:
	fclose(fp);
	printf("%d ", a);
	fflush(stdout);
	putc('\n', out);
	strcpy(wget, "rm ");
	strcat(wget, word);
	system(wget);
	}
}
