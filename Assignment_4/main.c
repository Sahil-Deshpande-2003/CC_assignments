// C program to calculate the First and
// Follow sets of a given grammar
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTIONS 20
#define MAX_SYMBOLS 100





// Functions to calculate Follow
void followfirst(char, int, int);
void follow(char c);

// Function to calculate First
void findfirst(char, int, int);

int count, n = 0; // count: Will store the number of production rules in the grammar. n : Counter used in the findfirst() function to track the number of symbols added to the First set

// Stores the final result
// of the First Sets
char calc_first[MAX_PRODUCTIONS][MAX_SYMBOLS];

// Stores the final result
// of the Follow Sets
char calc_follow[MAX_PRODUCTIONS][MAX_SYMBOLS];
int m = 0; // Counter used in the follow() function to track the number of symbols added to the Follow set.

// Stores the production rules
char production[MAX_PRODUCTIONS][MAX_SYMBOLS]; // A 2D array to store the production rules of the grammar. Each row represents a production in the form A = B, where A is the left-hand side (LHS) non-terminal and B is the right-hand side (RHS) string.
char f[10]; // store symbols during the calculation of the Follow set.
char first[10]; // store symbols during the calculation of the First set
int k;
char ck;
int e;



void follow(char c)
{
	int i, j;

	// Adding "$" to the follow
	// set of the start symbol
	if (production[0][0] == c) {
		f[m++] = '$'; // start char hence add $
	}
	for (i = 0; i < 10; i++) {
		for (j = 2; j < 10; j++) {
			if (production[i][j] == c) {
				if (production[i][j + 1] != '\0') {
					// Calculate the first of the next
					// Non-Terminal in the production
					followfirst(production[i][j + 1], i,
								(j + 2));
				}

				if (production[i][j + 1] == '\0'
					&& c != production[i][0]) {
					// Calculate the follow of the
					// Non-Terminal in the L.H.S. of the
					// production
					follow(production[i][0]);
				}
			}
		}
	}
}

/*
q1: Represents the index of the production rule in the production[] array. It indicates which production rule is being analyzed.
q2: Represents the position (or index) of the symbol within the right-hand side (RHS) of the production rule. It helps in tracking the current symbol being processed after a non-terminal or terminal.
c: It is the non-terminal symbol whose First set needs to be determined.
*/

void findfirst(char c, int q1, int q2)
{
	int j;

	// The case where we
	// encounter a Terminal
	if (!(isupper(c))) {
		first[n++] = c;
	}
	for (j = 0; j < count; j++) {
		if (production[j][0] == c) {
			if (production[j][2] == '#') {
				if (production[q1][q2] == '\0')
					first[n++] = '#'; /* A → B
										B → #  => # is added to First(A)    
										*/
				else if (production[q1][q2] != '\0'
						&& (q1 != 0 || q2 != 0)) {
					// Recursion to calculate First of New
					// Non-Terminal we encounter after
					// epsilon
					findfirst(production[q1][q2], q1,
							(q2 + 1));
					/*
					
					A → Bc
					B → #

					Here, when analyzing A → Bc and B → #, since c follows B in A → Bc, the function will recursively calculate First(c) and add it to First(A).
					*/
				}
				else
					first[n++] = '#';
			}
			else if (!isupper(production[j][2])) {
				first[n++] = production[j][2]; // Insert the non terminal
			}
			else {
				// Recursion to calculate First of
				// New Non-Terminal we encounter
				// at the beginning
				findfirst(production[j][2], j, 3); 

				/*
				1. A → BC
				2. B → d
				3. C → e
				Analyzing the production A → BC:

				You are calculating First(A), and the first symbol on the RHS is B, which is a non-terminal.
				Recursion on B:

				Since B is a non-terminal, the function will call findfirst(B) to calculate First(B).
				Finding First(B) (B → d):

				For the production B → d, d is a terminal, so First(B) is {d}.

				*/
			}
		}
	}
}

void followfirst(char c, int c1, int c2)
{
	int k;

	// The case where we encounter
	// a Terminal
	if (!(isupper(c)))
		f[m++] = c;
	else {
		int i = 0, j = 1;
		for (i = 0; i < count; i++) {
			if (calc_first[i][0] == c)
				break;
		}

		// Including the First set of the
		// Non-Terminal in the Follow of
		// the original query
		while (calc_first[i][j] != '!') {
			if (calc_first[i][j] != '#') {
				f[m++] = calc_first[i][j]; /*
				This checks if the current element in the First set is not epsilon (#). If the symbol is a terminal or any other non-epsilon symbol, it is added to the Follow set.*/
			}
			else {
				if (production[c1][c2] == '\0') {
					// Case where we reach the
					// end of a production
					follow(production[c1][0]); 
				}
				else {
					// Recursion to the next symbol
					// in case we encounter a "#"
					followfirst(production[c1][c2], c1,
								c2 + 1);  // If the current symbol is epsilon, but it’s not the end of the production, it means there are more symbols after this. In this case, the followfirst() function is called recursively to calculate the First set of the next symbol (production[c1][c2]) after epsilon
				}
			}
			j++;
		}
	}
}

int main(int argc, char** argv)
{
	int jm = 0; // jm and km are counters used for tracking the position in the first and f arrays, respectively
	int km = 0;
	int i, choice;
	char c, ch;
	count = 8;

	// The Input grammar
	strcpy(production[0], "X=TnS");
	strcpy(production[1], "X=Rm");
	strcpy(production[2], "T=q");
	strcpy(production[3], "T=#");
	strcpy(production[4], "S=p");
	strcpy(production[5], "S=#");
	strcpy(production[6], "R=om");
	strcpy(production[7], "R=ST");

	
	
	// count = 5;
	// // Example: Update with new grammar rules
	// strcpy(production[0], "A=BC");
	// strcpy(production[1], "B=DE");
	// strcpy(production[2], "C=a");
	// strcpy(production[3], "D=b");
	// strcpy(production[4], "E=c");


	

	int kay;
	char done[count];
	int ptr = -1;

	// Initializing the calc_first array
	for (k = 0; k < count; k++) {
		for (kay = 0; kay < 100; kay++) {
			calc_first[k][kay] = '!'; // Initializes calc_first with ! to denote uncomputed values.
		}
	}
	int point1 = 0, point2, xxx;

	/*
	Iterates through each non-terminal to compute its First set.
Checks if the First set for a non-terminal is already computed. If not, it calls findfirst() to compute it.
Updates the done list and prints the computed First set.
	*/
	for (k = 0; k < count; k++) { // The outer loop iterates over each production rule to calculate the First set of the non-terminal on the left-hand side (LHS).
		c = production[k][0]; // Extracts the non-terminal from the LHS of the k-th production rule.
		point2 = 0;
		xxx = 0;

		// Checking if First of c has
		// already been calculated
		for (kay = 0; kay <= ptr; kay++)
			if (c == done[kay])
				xxx = 1;

		if (xxx == 1)
			continue;

		// Function call
		findfirst(c, 0, 0);
		ptr += 1;

		// Adding c to the calculated list
		done[ptr] = c;
		printf("\n First(%c) = { ", c);
		calc_first[point1][point2++] = c;

		// Printing the First Sets of the grammar
		for (i = 0 + jm; i < n; i++) {
			int lark = 0, chk = 0;

			for (lark = 0; lark < point2; lark++) {

				if (first[i] == calc_first[point1][lark]) {
					chk = 1;
					break;
				}
			}
			if (chk == 0) {
				printf("%c, ", first[i]);
				calc_first[point1][point2++] = first[i];
			}
		}
		printf("}\n");
		jm = n;
		point1++;
	}
	printf("\n");
	printf("-----------------------------------------------"
		"\n\n");
	char donee[count];
	ptr = -1;

	// Initializing the calc_follow array
	for (k = 0; k < count; k++) {
		for (kay = 0; kay < 100; kay++) {
			calc_follow[k][kay] = '!';
		}
	}
	point1 = 0;
	int land = 0;
	for (e = 0; e < count; e++) {
		ck = production[e][0];
		point2 = 0;
		xxx = 0;

		// Checking if Follow of ck
		// has already been calculated
		for (kay = 0; kay <= ptr; kay++)
			if (ck == donee[kay])
				xxx = 1;

		if (xxx == 1)
			continue;
		land += 1;

		// Function call
		follow(ck);
		ptr += 1;

		// Adding ck to the calculated list
		donee[ptr] = ck;
		printf(" Follow(%c) = { ", ck);
		calc_follow[point1][point2++] = ck;

		// Printing the Follow Sets of the grammar
		for (i = 0 + km; i < m; i++) {
			int lark = 0, chk = 0;
			for (lark = 0; lark < point2; lark++) {
				if (f[i] == calc_follow[point1][lark]) {
					chk = 1;
					break;
				}
			}
			if (chk == 0) {
				printf("%c, ", f[i]);
				calc_follow[point1][point2++] = f[i];
			}
		}
		printf(" }\n\n");
		km = m;
		point1++;
	}
	/*
	
	Iterates through each non-terminal to compute its Follow set.
Checks if the Follow set for a non-terminal is already computed. If not, it calls follow() to compute it.
Updates the donee list and prints the computed Follow set.
	*/
}