#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


const short initial_permutation[64] = {10, 62, 13, 23, 35, 55, 11,  4, 40, 32, 24, 34, 20, 37, 14, 22, 58, 46,  9, 43, 63, 57, 61,  5, 29, 48, 30, 38, 42,  2, 53, 49, 45, 26, 41, 21, 39, 54,  7, 12, 56, 60, 44,  1, 16,  3, 27, 36, 25, 47,  6, 31, 50,  0, 33,  8, 19, 18, 28, 52, 51, 15, 17, 59};

const short final_permutation[64] = {53, 43, 29, 45, 7, 23, 50, 38, 55, 18, 0, 6, 39, 2, 14, 61, 44, 62, 57, 56, 12, 35, 15, 3, 10, 48, 33, 46, 58, 24, 26, 51, 9, 54, 11, 4, 47, 13, 27, 36, 8, 34, 28, 19, 42, 32, 17, 49, 25, 31, 52, 60, 59, 30, 37, 5, 40, 21, 16, 63, 41, 22, 1, 20};

const short parity_drop_table[56] = {41, 6, 55, 46, 44, 39, 29, 24, 7, 11, 27, 1, 25, 23, 28, 30, 16, 8, 9, 48, 31, 36, 14, 33, 43, 10, 53, 42, 45, 54, 13, 12, 51, 34, 52, 47, 21, 15, 32, 35, 18, 50, 38, 5, 4, 40, 26, 17, 49, 2, 19, 37, 3, 22, 20, 0};

const short key_compression_p_box[48] = {1, 5, 30, 16, 28, 12, 37, 21, 2, 26, 29, 18, 17, 22, 34, 15, 8, 33, 0, 43, 40, 32, 44, 10, 38, 23, 24, 6, 47, 14, 13, 42, 31, 27, 45, 4, 35, 25, 7, 9, 19, 36, 11, 20, 3, 39, 46, 41};

const short expansion_p_box[48] = {31, 0, 1, 2, 3, 4, 3, 4, 5,  6, 7, 8, 7, 8, 9, 10, 11, 12, 11, 12, 13, 14, 15, 16, 15, 16, 17, 18, 19, 20, 19, 20, 21, 22, 23, 24, 23, 24, 25, 26, 27, 28, 27, 28, 29, 30, 31, 0};

const short s_box[8][64] = {{10, 1, 8, 6, 2, 5, 11, 13, 15, 9, 12, 3, 7, 0, 14, 4, 9, 14, 11, 0, 13, 7, 15, 3, 6, 5, 4, 2, 1, 8, 10, 12, 10, 1, 6, 0, 7, 11, 14, 12, 15, 2, 5, 8, 9, 13, 3, 4, 4, 9, 11, 0, 1, 10, 7, 8, 15, 12, 3, 13, 5, 14, 6, 2}, {3, 0, 12, 14, 11, 15, 10, 4, 7, 8, 5, 1, 9, 2, 13, 6, 13, 7, 3, 15, 9, 0, 2, 14, 10, 5, 12, 6, 11, 8, 4, 1, 9, 6, 12, 8, 11, 2, 5, 3, 14, 7, 1, 10, 0, 4, 15, 13, 10, 11, 12, 8, 14, 0, 15, 7, 2, 9, 4, 6, 3, 5, 1, 13}, {1, 5, 12, 9, 3, 13, 6, 10, 11, 14, 8, 0, 7, 2, 15, 4, 7, 10, 11, 14, 5, 13, 2, 3, 6, 1, 9, 0, 15, 4, 12, 8, 2, 13, 1, 15, 12, 7, 5, 3, 14, 0, 9, 11, 4, 8, 10, 6, 13, 1, 14, 7, 10, 8, 15, 2, 3, 6, 5, 4, 9, 12, 11, 0}, {2, 14, 9, 10, 13, 3, 5, 4, 8, 0, 1, 11, 12, 7, 15, 6, 0, 2, 12, 11, 4, 7, 6, 9, 14, 13, 3, 5, 10, 8, 1, 15, 0, 8, 15, 6, 5, 7, 13, 2, 12, 14, 4, 11, 3, 10, 1, 9, 11, 6, 13, 1, 9, 3, 12, 2, 0, 7, 5, 8, 14, 10, 4, 15}, {10, 9, 14, 15, 11, 13, 6, 0, 3, 2, 4, 7, 5, 8, 12, 1, 0, 15, 10, 9, 1, 3, 7, 5, 8, 12, 2, 13, 11, 4, 6, 14, 4, 7, 5, 6, 1, 3, 0, 9, 12, 10, 2, 8, 14, 11, 13, 15, 5, 3, 7, 11, 6, 8, 13, 9, 4, 10, 15, 2, 12, 1, 0, 14}, {4, 11, 0, 6, 9, 5, 14, 8, 3, 13, 7, 1, 12, 15, 10, 2, 14, 0, 15, 3, 13, 5, 9, 6, 1, 8, 2, 4, 11, 7, 12, 10, 13, 2, 11, 15, 8, 9, 3, 1, 10, 5, 6, 12, 0, 4, 7, 14, 14, 3, 0, 7, 10, 15, 4, 9, 12, 6, 13, 2, 11, 1, 5, 8}, {3, 4, 5, 10, 12, 2, 9, 0, 6, 7, 14, 13, 15, 11, 1, 8, 7, 8, 13, 5, 6, 12, 10, 15, 11, 1, 3, 9, 4, 2, 14, 0, 7, 14, 9, 5, 11, 12, 10, 3, 15, 2, 13, 8, 4, 0, 1, 6, 15, 10, 8, 13, 5, 3, 4, 9, 1, 2, 7, 0, 14, 12, 11, 6}, {9, 14, 1, 8, 4, 10, 15, 7, 3, 6, 12, 0, 11, 13, 2, 5, 4, 0, 5, 10, 14, 3, 6, 9, 15, 1, 8, 12, 2, 13, 11, 7, 3, 0, 2, 13, 4, 1, 5, 7, 14, 9, 6, 8, 12, 10, 15, 11, 1, 3, 15, 9, 6, 14, 5, 11, 4, 2, 12, 8, 13, 0, 7, 10}};

const short straight_p_box[32] = {3, 22, 27, 29, 31, 14, 11,  7, 23,  4, 21, 24, 25, 19, 20, 12,  9, 18, 10,  1,  2, 15, 28, 16,  0, 13, 17,  8,  5, 26, 30,  6};


// convert binary number to decimal
int binary_to_decimal(char* a, int n){
	int i, j;
	int val = 0;
	for(i=n-1,j=1;i>=0;i--,j*=2) if(a[i]) val += j;
	return val;
}


// convert decimal number to banary string
char *decimal_to_binary(int val, int n){
	int i,j;
	char *a;
	a = (char*) malloc(n*sizeof(char));
	for(i=n-1,j=1;i>=0;i--, j*=2) a[i] = (val&j)==0?0:1;
	return a;
}


void permute(char *block, int n, const short table[]){
	int i;
	char *temp = (char*) malloc(n*sizeof(char));
	memcpy(temp, block, n);
	for(i=0;i<n;i++) block[i] = temp[table[i]];
	free(temp);
}


/**
 * des_function takes a 64 bit block and a 48 bit key to produce a 32 bit output using the rightmost 32 bits of block.
 * This function is made out of 4 sections:
 * 	1. Expansion P box
 * 	2. Whitner (adds the key)
 * 	3. Group of S boxes
 * 	4. Straight P box
 */
void des_function(char* left, char* right, char* key){
	char *temp, *bin, *dec, *output; 
	int i, j, val;
	temp = (char*) malloc(48*sizeof(char));
	memcpy(temp, right, 32);
	permute(temp, 48, expansion_p_box);
	for(i=0;i<48;i++) temp[i] = (temp[i] ^ key[i]);
	
	// substitution
	bin = (char*) malloc(6*sizeof(char));
	output = (char*) malloc(32 * sizeof(char));
	for(i=0;i<8;i++){
		for(j=0;j<6;j++) bin[j] = temp[8*i+j];
		val = binary_to_decimal(bin, 6);
		val = s_box[i][val];
		dec = decimal_to_binary(val, 4);
		for(j=0;j<4;j++) output[4*i+j] = dec[j];
		free(dec);
	}

	// straight permutation
	permute(output, 32, straight_p_box);
	for(i=0;i<32;i++) left[i] = (left[i] ^ output[i]);

	free(output);
	free(temp);
	free(bin);
}


// swap left and right 32 bits of block
void swapper(char *left, char *right, int n){
	char temp;
	for(int i=0;i<n;i++){
		temp = left[i];
		left[i] = right[i];
		right[i] = temp;
	}
}

// left shift k bit 
void shift_left(char *a, int n, int k){
	if(k <= 0) return;
	k = k%n;
	char * temp; int i;

	temp = (char*) malloc(n*sizeof(char));
	memcpy(temp, a, n);
	for(i=0;i<n;i++) a[i] = temp[(i+k)%n];
	free(temp);
}



// encrypt a block of 64 bits using a key of 56 bits
// stores the encrypted block in `block` variable
void encrypt_block(char* block, char **keys){
	int round, i, j, k;
	char *left, *right;
	
	left = block;
	right = left + 32;


	permute(block, 64, initial_permutation);

	// perform the rounds on the block
	
	for(round=0;round<16;round++){
		des_function(left, right, keys[round]);
		if(round != 15) swapper(left, right, 32);
	}
	
	permute(block, 64, final_permutation);
}


// generate 16 round keys of size 48 bit from a 56 bit key
char ** generate_round_keys(char *key_string){
	
	// create round keys from key
	char *left, *right;
	char **round_keys = (char**)malloc(16*sizeof(char*));
	int i, j, k, shift_count;

	// convert 7 byte key string to 56 bit key
	char *key = (char*) malloc(56*sizeof(char));
	for(i=0;i<7;i++) for(j=0, k=128;j<8;j++,k/=2) key[i*8+j] = ((key_string[i]&k)==0)?0:1;

	permute(key, 56, parity_drop_table);
	left = key;
	right = key+28;

	for(i=0;i<16;i++){
		round_keys[i] = (char*)malloc(48*sizeof(char));
		shift_count = (i==0 || i==1 || i==8 || i==15)?1:2;
		shift_left(left, 28, shift_count);
		shift_left(right, 28, shift_count);
		for(k=0;k<8;k++) for(j=0;j<6;j++) round_keys[i][k*6+j] = key[k*7+j];
		permute(round_keys[i], 48, key_compression_p_box);
	}
	
	free(key);

	return round_keys;
}



// This method encrypts a given plain text
// First plain text is converted to the blocks and then each block is encrypted using a given key
char * run_des(char *plain_text, char *key_string, const char type){
	if(type != 'e' && type != 'd') {
		printf("type should be either e(encrypt) or d(decrypt)");
		exit(0);
	}

	int len, number_of_blocks;
	int i, j, k, l;

	char *cipher_text, *block;
	char **round_keys;

	len = strlen(plain_text);
	number_of_blocks = (len + 7)/8;

	// copy plain text to cipher text block then we will encrypt the cipher text blocks
	// padding is applied if necessary
	cipher_text = (char*) malloc(number_of_blocks*8*sizeof(char));
	for(i=0;i<len;i++) cipher_text[i] = plain_text[i];
	for(i=len;i<number_of_blocks*8;i++) cipher_text[i] = ' ';
	cipher_text[i] = '\0';

	
	round_keys = generate_round_keys(key_string);
	if(type == 'd') for(i=0;i<8;i++) swapper(round_keys[i], round_keys[15-i], 48);

	block = (char*) malloc(64*sizeof(char));

	for(i=0;i<number_of_blocks;i++){
		for(j=0;j<8;j++){
			for(k=0,l=128;k<8;k++,l/=2) block[8*j+k] = (cipher_text[8*i+j]&l)==0?0:1;
		}

		encrypt_block(block, round_keys);

		for(j=0;j<8;j++){
			cipher_text[8*i+j] = 0;
			for(k=0,l=128;k<8;k++,l/=2) if(block[8*j+k]) cipher_text[8*i+j] = (cipher_text[8*i+j] | l);
		}
	}

	free(block);
	for(int i=0;i<16;i++) free(round_keys[i]);
	free(round_keys);
	return cipher_text;
}


char * decrypt(){
	return NULL;
}



// print binary of a char array
void print(const char *name, char* value){
	printf("%s : ", name);
	int len = strlen(value);
	int i, j, k;
	char *output = (char*)malloc(len*8*sizeof(char)+1);
	for(i=0;i<len;i++) for(j=0,k=128;j<8;j++,k/=2) output[8*i + j] = (value[i]&k)==0?'0':'1';
	output[len*8*sizeof(char)] = '\0';
	printf("%s\n", output);
	free(output);
}



void command_line(int argc, char ** argv){
	if(argc != 4 ){
		printf("Usage: ./des [OPTION] [KEY] [FILE]\n");
		printf("des encrypts or decrypts the FILE\n");
		printf("[OPTION] is either \'e\' or \'d\' for encryption or decryption respectively.\n");
		printf("[KEY] is a 7 byte string which is used as key for encryption and decryption\n");
		printf("[FILE] is a file present in current directory\n"); 
		printf("\n\n\nAuthor : Qeubd-Bsjso\n"); 
		exit(0);
	}
	if(strcmp(argv[1],"e") && strcmp(argv[1], "d")){
		printf("[OPTION] can only be \'e\' or \'d\'\n");
		exit(0);
	}
	if(strlen(argv[2]) < 7){
		printf("[KEY] size must be 7 (or more. rest will be ignored)\n");
		exit(0);
	}
	char type = strcmp(argv[1], "e")==0?'e':'d';
	FILE* ptr;
	char ch;

	ptr = fopen(argv[3], "rb");
	if(ptr == NULL){
		printf("could not open [FILE]\n");
		exit(0);
	}
	char * block = (char*) malloc(8*sizeof(char));
	char * output;
	int i=0;
	int size = 0;
	ch = fgetc(ptr);
	while(!feof(ptr)){
		size ++;
		//printf("%c", ch);
		block[i++] = ch;
		if(i == 8){
			output = run_des(block, argv[2], type);
			printf("%s", output);
			free(output);
			i=0;
		}
		ch = fgetc(ptr);
	};
	if(i > 0) {
		while(i < 8) block[i++] = ' ';
		output = run_des(block, argv[2], type);
			printf("%s", output);
		free(output);
	}
	free(block);
	fclose(ptr);
}



// main function
int main(int argc, char ** argv){
	command_line(argc, argv);
	/*srand(time(0));
	int len = 10 + rand()%10;
	char * input = (char*)malloc(len*sizeof(char));
	char *key = (char*)malloc(7*sizeof(char));
	for(int i=0;i<len;i++) input[i]='a' + rand()%26;
	for(int i=0;i<7;i++) key[i] = 'a' + rand()%26;
	print("Input", input);
	print("Key", key);

	char * cipher_text = run_des(input, key, 'e');
	print("Cipher", cipher_text);
	
	char * decipher = run_des(cipher_text, key, 'd');
	print("Decipher", decipher);




	free(decipher);
	free(cipher_text);
	free(input);
	free(key);*/
	return 0;
}
