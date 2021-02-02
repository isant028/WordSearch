#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DO NOT INCLUDE OTHER LIBRARY!

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);

// Main function, DO NOT MODIFY!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i=0; i<50; i++){
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i=0; i<49; i++){
		*(*(words+i) + strlen(*(words+i))-2) = '\0';	
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i=0; i<50; i++){
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** arr, int n){
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	// Your implementation here
	for(int i=0; i< n; i++){
		for (int j=0; j< n ;j++){
			printf("%c ", *(*(arr+i)+j));
		}
		printf("\n");	
	}
	 printf("\n");
	
}

void upper(int listSize, char** list){
	//change list to upper case char
	for(int i=0; i< listSize; i++){
		for(int j=0; j< listSize; j++){
			if(*(*(list+i)+j) >= 97 && *(*(list+i)+j) <=122){
				*(*(list+i)+j) = *(*(list+i)+j)-32;
			}
		}
	}
};
int forward(char** arr, char** list, int acol, int lcol,int l, int b){
	for(int i=0;i< strlen(*(list+lcol));i++){
		if(*(*(list+lcol)+l+i)!=*(*(arr+acol)+b+i)){
			return 0;
		}
	}	
	return 1;
};
void lowerf(char** arr, int acol, int b, int i){
	if(*(*(arr+acol)+b+i) >= 65 && *(*(arr+acol)+b+i) <=90){
					 *(*(arr+acol)+b+i) = (*(*(arr+acol)+b+i))+32;
					}

};
int down(char** arr, char** list, int acol, int lcol,int l, int b){
	for(int i=0;i< strlen((*(list+lcol)));i++){
		if (acol+i< 15 && l+i< 20 ){
			if( *(*(arr+acol+i)+b) == *(*(list+lcol)+l+i) || *(*(arr+acol+i)+b)== *(*(list+lcol)+l+i)+32){	
			
			}
			else return 0;
		}	
		else return 0;	 
	}
	return 1;
};
void lowerd(char** arr, int acol, int b, int i){
	if(*(*(arr+acol+i)+b) >= 65 && *(*(arr+acol+i)+b) <=90)
		 *(*(arr+acol+i)+b) = (*(*(arr+acol+i)+b))+32;
					
};

int back(char** arr, char** list, int acol, int lcol,int l, int b){
	for(int i=0;i<strlen(*(list+lcol));i++){
			if(*(*(arr+acol)+b-i) == *(*(list+lcol)+l+i) || *(*(arr+acol)+b-i) == *(*(list+lcol)+l+i)+32 ){
			}
			else return 0;
			} 
	return 1;
};
void lowerb(char** arr, int acol, int b, int i){
	if(*(*(arr+acol)+b-i) >= 65 && *(*(arr+acol)+b-i) <=90){
					 *(*(arr+acol)+b-i) = (*(*(arr+acol)+b-i))+32;
					}
}

int dright(char** arr, char** list, int acol, int lcol,int l, int b){
	for(int i=0;i< strlen((*(list+lcol)));i++){
		if (acol+i< 15 && l+i< 20 && b+i <15){
			if(*(*(arr+acol+i)+b+i) == *(*(list+lcol)+l+i)+32 || *(*(arr+acol+i)+b+i) == *(*(list+lcol)+l+i)){
			}
			else return 0;
		}
		else return 0;	
	}
	return 1;
};
void lowerdr(char** arr, int acol, int b, int i){
	if(*(*(arr+acol+i)+b+i) >= 65 && *(*(arr+acol+i)+b+i) <=90){
					 *(*(arr+acol+i)+b+i) = (*(*(arr+acol+i)+b+i))+32;
					}
}
int dleft(char** arr, char** list, int acol, int lcol,int l, int b){
	for(int i=0;i< strlen((*(list+lcol)));i++){
		if (acol+i< 15 && l+i< 20 && b-i> 0 
			&&  *(*(arr+acol+i)+b-i) == *(*(list+lcol)+l+i)){
		}
		else return 0;
		
	}
	return 1;
};
void lowerdl(char** arr, int acol, int b, int i){
	if(*(*(arr+acol+i)+b-i) >= 65 && *(*(arr+acol+i)+b-i) <=90){
					 *(*(arr+acol+i)+b-i) = (*(*(arr+acol+i)+b-i))+32;
					}
}
void searchPuzzle(char** arr, int n, char** list, int listSize){
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here

	upper(listSize, list);
	
	//general: back, forward, down, diag right, diag left
	for(int acol=0;acol< 15; acol++){
	for(int lcol=0;lcol< 50; lcol++){
	for(int arow=0;arow< 15; arow++){
	for(int lrow=0;lrow< strlen(*(list+lcol)); lrow++){
    	if(*(*(arr+acol)+arow) == *(*(list+lcol)+lrow) || *(*(arr+acol)+arow) == *(*(list+lcol)+lrow)+32 ){ 
			
			if(back(arr,list,acol, lcol, lrow, arow)==1){
				printf("\nWord found: ");
				for(int i=strlen(*(list+lcol));i>=0;i--){
					if(i!=strlen(*(list+lcol)))
					printf("%c",*(*(arr+acol+i)+arow+i)+32);
					else 
					printf("%c",*(*(arr+acol)+arow-i));
					lowerb(arr,acol ,arow, i);

				}	
				arow++;			    
			}		

			if(down(arr,  list, acol,  lcol, lrow, arow)==1){
				printf("\nWord found: ");
				for(int i=0;i<strlen(*(list+lcol));i++){
					if(i!=0)
					printf("%c",*(*(arr+acol+i)+arow)+32);
					else 
					printf("%c",*(*(arr+acol+i)+arow));
					lowerd(arr,acol ,arow, i);

				}
			
			}

			if(forward(arr,list,acol, lcol, lrow, arow)==1){
				printf("\nWord found: ");
				for(int i=0;i<strlen(*(list+lcol));i++){
						if(i!=0)
					printf("%c",*(*(arr+acol)+arow+i)+32);
					else 
					printf("%c",*(*(arr+acol)+arow+i));

					lowerf(arr,acol ,arow, i);

				}
				arow++;			    
			}	
			
			if(dright(arr,  list, acol,  lcol, lrow, arow)==1){
				printf("\nWord found: ");
				for(int i=0;i<strlen(*(list+lcol));i++){
					if(i!=0 && *(*(arr+acol+i)+arow+i) >= 65 && *(*(arr+acol+i)+arow+i) <=90)
						printf("%c",*(*(arr+acol+i)+arow+i)+32);
					else if(i==0 && *(*(arr+acol+i)+arow+i) >= 97 && *(*(arr+acol+i)+arow+i) <=122)
						printf("%c",*(*(arr+acol+i)+arow+i)-32);

					else 
					printf("%c",*(*(arr+acol+i)+arow+i));

					lowerdr(arr,acol ,arow, i);
	
				}
			}
			else if(dleft(arr,  list, acol,  lcol, lrow, arow)==1){
				printf("\nWord found: ");
				for(int i=0;i<strlen(*(list+lcol));i++){
					if(i!=0 && *(*(arr+acol+i)+arow+i) >= 65 && *(*(arr+acol+i)+arow+i) <=90)
					printf("%c",*(*(arr+acol+i)+arow+i)+32);
					else 
					printf("%c",*(*(arr+acol+i)+arow-i));

					lowerdl(arr,acol ,arow, i);
				}
			}
			

			else break;
		}	
			}
		} 
	}	
	} 
	

}
