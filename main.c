# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct line {
	char *col1;
	char *col2;
	char *col3;
};

int main(int argc, char *argv[]) {
	// check if second argument is inputted on command line
	if (argv[1] == NULL) {
		printf("Error");
		return 0;
	}
	// open given file to read
	// input = file stream
	FILE *input = fopen(argv[1], "r");
	// check if the given file exists
	if (input == NULL) {
		printf("Error");
		return 0;
	}
	// allocate initial memory to entries
	struct line *entries = malloc(sizeof(struct line));
	// entries_size = i + 1, used as size of new allocated memory
	int entries_size = 0;
	// i = index/number of lines in file
	int i = 0;
	// initialize size and buf for getline()
	size_t size = 0;
	// buf is where getline() stores the line
	char *buf = NULL;
	// initialize variables for longest line in each column
	int max_col1 = 0;
	int max_col2 = 0;
	int max_col3 = 0;
	// length = length of line
	ssize_t length;
	// loop until reach the end of the file
	while ((length = getline(&buf, &size, input)) != -1) {
		// increment entries_size at the beginning so it starts at 1
		entries_size++;
		// reallocate memory that is the size of line * entries_size to entries
		entries = realloc(entries, sizeof(struct line) * entries_size);
		// store characters in buf to array
		char *array = strdup(buf);
		// make a copy of array to make changes to
		char *stringp = array;
		// separate the strings using delimiters and store in struct members
		entries[i].col1 = strsep(&stringp, " ");
		entries[i].col2 = strsep(&stringp, " ");
		// skip search for single quotes in header
		if (i != 0) {
			strsep(&stringp, "'");
			entries[i].col3 = strsep(&stringp, "'");
		}
		else {
			entries[i].col3 = strsep(&stringp, "\n");
		}
		// determine lengths of each string
		int col1_len = strlen(entries[i].col1);
		int col2_len = strlen(entries[i].col2);
		int col3_len = strlen(entries[i].col3);
		// determine if those lengths are greater than the previous maximum lengths
		// if so, assign the max length to that length
		if (col1_len > max_col1) {
			max_col1 = col1_len;
		}
		if (col2_len > max_col2) {
			max_col2 = col2_len;
		}
		if (col3_len > max_col3) {
			max_col3 = col3_len;
		}
		i++;
		
	}
	// check if the end of the file was reached
	if (!feof(input)) {
		printf("Error");
		return 0;
	}
	// j = index
	int j = 0;
	// print dashed line with a width of the sum of all the max columns and 10 for spacing
	while (j < (max_col1 + max_col2 + max_col3 + 10)) {
		printf("-");
		j++;
	}
	// print header line with correct formating
	printf("\n| %-*s | ", max_col1, entries[0].col1);
	printf("%*s | ", max_col2, entries[0].col2);
	printf("%-*s |\n", max_col3, entries[0].col3);
	j = 0;
	// print another dashed line
	while (j < (max_col1 + max_col2 + max_col3 + 10)) {
		printf("-");
		j++;
	}
	printf("\n");
	// start at 1 to skip header line
	j = 1;
	// print each line with correct formatting
	while (j < i) {
		printf("| %-*s | ", max_col1, entries[j].col1);
		printf("%*s | ", max_col2, entries[j].col2);
		printf("%-*s |\n", max_col3, entries[j].col3);
		
		j++;
	}
	j = 0;
	// print another dashed line
	while (j < (max_col1 + max_col2 + max_col3 + 10)) {
		printf("-");
		j++;
	}
	printf("\n");
	j = 0;
	// free each array's memory allocated using strdup()
	while (j < entries_size) {
		free(entries[j].col1);
		j++;
	}
	// free buf memory allocated using getline()
	free(buf);
	// free entries memory allocated using malloc()
	free(entries);
	
	fclose(input);
	return 0;
}
