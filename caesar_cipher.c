/* Author: Chris Garry
//
// Description: A Caesar Cipher
// algorithm to encrypt plaintext
// messages over the ASCII alphabet.
//
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define INVALID -1
#define SIZE_ALPHABET 26

char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

void gettimeofday();

//Returns a random rotation value from the interval [1,25]
int random_rot(){

	//Get time to seed random number generator
	struct timeval start;
	gettimeofday(&start, NULL);

	//Seed the random number generator with seconds*microseconds
	srand(start.tv_usec * start.tv_sec);

	//Return rotation value that encrypts plaintext
	return (rand()%(SIZE_ALPHABET-1) + 1);
}

//Returns the alphabet index of a valid character, -1 otherwise
int alphabet_index(char symbol){

	int i;
	for(i =0; i< SIZE_ALPHABET; i++){
		if(symbol == alphabet[i]) return i;
	}	
	return INVALID;
}

//Returns true if a string is valid within the alphabet
int str_check(char *string){

	int i, is_valid_str = FALSE;
	int length = strlen(string); 

	if(length > 0){

		for(i =0; i<length; i++){

			if(alphabet_index(string[i])==INVALID){
				is_valid_str = FALSE;
				break;
			}
			is_valid_str = TRUE; 
		}
	}
	return is_valid_str;
}

//Shifts plaintext characters over the alphabet by rot on interval [-26, 26]
void rot_plaintext(char *plaintext, int rot){

	int x;
	for(x=0; x<strlen(plaintext); x++){
		plaintext[x] = alphabet[(alphabet_index(plaintext[x])+rot+SIZE_ALPHABET) % SIZE_ALPHABET];
	}
}

//Encrypt the plaintext
char *encrypt(char *plaintext){

	if(str_check(plaintext)==TRUE){
		rot_plaintext(plaintext, random_rot());
	}
	return plaintext;
}

char *decrypt(char *ciphertext, int rot){
	
	if(str_check(ciphertext)==TRUE){
		rot_plaintext(ciphertext, rot);
	}
	return ciphertext;
}

void crack(char *ciphertext){
	int i;
	for(i = 0; i<SIZE_ALPHABET; i++){
		printf("Guess: %s Rot:%d\n", decrypt(ciphertext, -1*i), -1*i);
		decrypt(ciphertext, i);
	}
}

int main(int argc, char *argv[]){

	char string[] = "apples";
	char *encrypted = encrypt(string);
	crack(encrypted);
	return 0;
}