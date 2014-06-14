#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void padFunc(FILE *in, FILE *pad, FILE *out) {
	unsigned char x, i, p;

	// TODO: Customisable offsets
	fseek(in, 0L, SEEK_SET);
	fseek(pad, 0L, SEEK_SET);
	
	i = fgetc(in);
	p = fgetc(pad);
	while(!feof(in)) {
		x = i ^ p;
		i = fgetc(in);
		p = fgetc(pad);
		fputc(x, out);
	}
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("You should be passing input file and pad file\n");
		return 1;
	}
	FILE *in = NULL, *pad = NULL, *out = NULL;
	
	printf("Opening input file: %s\n", argv[1]);
	in = fopen(argv[1], "r");
	
	printf("Opening pad file: %s\n", argv[2]);
	pad = fopen(argv[2], "r");
	
	printf("Opening out file: %s\n", argv[3]);
	out = fopen(argv[3], "w");

	// xor all of 'in' with 'pad' from offset 0 into 'out'
	padFunc(in, pad, out);

	fsync(fileno(out));
	fclose(out); fclose(in); fclose(pad);	
	return 0;
}
