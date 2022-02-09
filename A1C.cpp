#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
#define ENCRYPT_TYPE_NAME "encrypt"
#define DECRYPT_TYPE_NAME "decrypt"
#define SIMPLE_KIND_NAME "simple"
#define COMPLICATED_KIND_NAME "complicated"
#define CIPHER_BLOCK_DELIM '\n'
#define MAX_RANDOM 11
#define ENCRYPT_OR_DECRYPT 0
#define SIMPLE_OR_COMPLICATED 1
#define KEY 2
#define INPUT_FILE_PATH 3
#define OUTPUT_FILE_PATH 4

vector<string> get_input();
void checking_the_orders(vector<string> orders);
void identify_the_type_of_encrypt(vector<string> orders);
void identify_the_type_of_decrypt(vector<string> orders);
vector<string> reading_unencrypted_input_file_lines(vector<string> orders);
vector<int> reading_encrypeted_input_file_lines(vector<string> orders);
void encrypt_simple(vector<string> orders);
vector<int> create_simple_key_ascii_vector(vector<string> orders);
vector<int> calculate_simple_encryption(vector<string> unencrypted_input_file_lines, vector<int> key_ascii);
void decrypt_simple(vector<string> orders);
vector<char> calculate_simple_decryption(vector<int> encrypeted_input_file_lines, vector<int> key_ascii);
void encrypt_complicated(vector<string> orders);
vector<int> calculate_complicated_encryption(vector<string> orders, vector<string> unencrypted_input_file_lines);
int calculate_srand_number(vector<string> orders);
void decrypt_complicated(vector<string> orders);
vector<char> calculate_complicated_decryption(vector<string> orders, vector<int> encrypeted_input_file_lines);
void writing_the_result_of_decrypt_on_output_file(vector<string> orders, vector<char> encoding_result);
void writing_the_result_of_encrypt_on_output_file(vector<string> orders, vector<int> encoding_result);

int main()
{
	vector<string> orders = get_input();
	checking_the_orders(orders);
	return 0;
}

vector<string> get_input()
{
	vector<string> orders;
	string line;
	while (getline(cin, line))
		orders.push_back(line);
	return orders;
}

void checking_the_orders(vector<string> orders)
{
	if (orders[ENCRYPT_OR_DECRYPT] == ENCRYPT_TYPE_NAME)
		identify_the_type_of_encrypt(orders);
	if (orders[ENCRYPT_OR_DECRYPT] == DECRYPT_TYPE_NAME)
		identify_the_type_of_decrypt(orders);
}

void identify_the_type_of_encrypt(vector<string> orders)
{
	if (orders[SIMPLE_OR_COMPLICATED] == SIMPLE_KIND_NAME)
		encrypt_simple(orders);
	if (orders[SIMPLE_OR_COMPLICATED] == COMPLICATED_KIND_NAME)
		encrypt_complicated(orders);
}

void identify_the_type_of_decrypt(vector<string> orders)
{
	if (orders[SIMPLE_OR_COMPLICATED] == SIMPLE_KIND_NAME)
		decrypt_simple(orders);
	if (orders[SIMPLE_OR_COMPLICATED] == COMPLICATED_KIND_NAME)
		decrypt_complicated(orders);
}

vector<string> reading_unencrypted_input_file_lines(vector<string> orders)
{
	vector<string> unencrypted_input_file_lines;
	string line;
	ifstream myfile(orders[INPUT_FILE_PATH].c_str(), ios::in);
	while (getline(myfile, line))
		unencrypted_input_file_lines.push_back(line);
	return unencrypted_input_file_lines;
}

vector<int> reading_encrypeted_input_file_lines(vector<string> orders)
{
	vector<int> encrypeted_input_file_lines;
	int number;
	ifstream myfile(orders[INPUT_FILE_PATH].c_str(), ios::in);
	while (myfile >> number)
		encrypeted_input_file_lines.push_back(number);
	return encrypeted_input_file_lines;
}

void encrypt_simple(vector<string> orders)
{
	vector<int> key_ascii = create_simple_key_ascii_vector(orders);
	vector<string> unencrypted_input_file_lines = reading_unencrypted_input_file_lines(orders);
	vector<int> simple_encryption_result = calculate_simple_encryption(unencrypted_input_file_lines, key_ascii);
	writing_the_result_of_encrypt_on_output_file(orders, simple_encryption_result);
}

vector<int> create_simple_key_ascii_vector(vector<string> orders)
{
	vector<int> key_ascii;
	for (int current_element = 0; current_element < orders[KEY].size(); current_element++)
		key_ascii.push_back(orders[KEY][current_element]);
	return key_ascii;
}

vector<int> calculate_simple_encryption(vector<string> unencrypted_input_file_lines, vector<int> key_ascii)
{
	vector<int> simple_encryption_result;
	int current_key_element = 0;
	for (int current_line = 0; current_line < unencrypted_input_file_lines.size(); current_line++)
	{
		for (int current_character = 0; current_character < unencrypted_input_file_lines[current_line].size(); current_character++) 
		{
			if (current_key_element >= key_ascii.size())
				current_key_element = 0;
			simple_encryption_result.push_back(unencrypted_input_file_lines[current_line][current_character] + key_ascii[current_key_element]);
			current_key_element++;
		}
		if (current_key_element >= key_ascii.size())
			current_key_element = 0;
		simple_encryption_result.push_back(CIPHER_BLOCK_DELIM + key_ascii[current_key_element]);
		current_key_element++;
	}
	return simple_encryption_result;
}

void decrypt_simple(vector<string> orders)
{
	vector<int> key_ascii = create_simple_key_ascii_vector(orders);
	vector<int> encrypeted_input_file_lines = reading_encrypeted_input_file_lines(orders);
	vector<char> simple_decryption_result = calculate_simple_decryption(encrypeted_input_file_lines, key_ascii);
	writing_the_result_of_decrypt_on_output_file(orders, simple_decryption_result);
}

vector<char> calculate_simple_decryption(vector<int> encrypeted_input_file_lines, vector<int> key_ascii)
{
	vector<char> simple_decryption_result;
	int current_key_element = 0;
	for (int current_line = 0; current_line < encrypeted_input_file_lines.size(); current_line++)
	{
		if (current_key_element >= key_ascii.size())
			current_key_element = 0;
		simple_decryption_result.push_back(encrypeted_input_file_lines[current_line] - key_ascii[current_key_element]);
		current_key_element++;
	}
	return simple_decryption_result;
}

void encrypt_complicated(vector<string> orders)
{
	vector<string> unencrypted_input_file_lines = reading_unencrypted_input_file_lines(orders);
	vector<int> complicated_encryption_result = calculate_complicated_encryption(orders, unencrypted_input_file_lines);
	writing_the_result_of_encrypt_on_output_file(orders, complicated_encryption_result);
}

vector<int> calculate_complicated_encryption(vector<string> orders, vector<string> unencrypted_input_file_lines)
{
	srand(calculate_srand_number(orders));
	vector<int> complicated_encryption_result;
	for (int current_line = 0; current_line < unencrypted_input_file_lines.size(); current_line++)
	{
		for (int current_character = 0; current_character < unencrypted_input_file_lines[current_line].size(); current_character++)
			complicated_encryption_result.push_back(unencrypted_input_file_lines[current_line][current_character] + (rand() % MAX_RANDOM));
		complicated_encryption_result.push_back(CIPHER_BLOCK_DELIM + (rand() % MAX_RANDOM));
	}
	return complicated_encryption_result;
}

int calculate_srand_number(vector<string> orders)
{
	int srand_number = 0;
	for (int current_element = 0; current_element < orders[KEY].size(); current_element++)
		srand_number += int(orders[KEY][current_element]);
	return srand_number;
}

void decrypt_complicated(vector<string> orders)
{
	vector<int> encrypeted_input_file_lines = reading_encrypeted_input_file_lines(orders);
	vector<char> complicated_decryption_result = calculate_complicated_decryption(orders, encrypeted_input_file_lines);
	writing_the_result_of_decrypt_on_output_file(orders, complicated_decryption_result);
}

vector<char> calculate_complicated_decryption(vector<string> orders, vector<int> encrypeted_input_file_lines)
{
	srand(calculate_srand_number(orders));
	int number;
	vector<char> complicated_decryption_result;
	for (int current_line = 0; current_line < encrypeted_input_file_lines.size(); current_line++)
		complicated_decryption_result.push_back(encrypeted_input_file_lines[current_line] - (rand() % MAX_RANDOM));
	return complicated_decryption_result;
}

void writing_the_result_of_decrypt_on_output_file(vector<string> orders, vector<char> encoding_result)
{
	ofstream outfile(orders[OUTPUT_FILE_PATH].c_str(), ios::in | ios::out | ios::trunc);
	for (int current = 0; current < encoding_result.size(); current++)
		outfile << encoding_result[current];
}

void writing_the_result_of_encrypt_on_output_file(vector<string> orders, vector<int> encoding_result)
{
	ofstream outfile(orders[OUTPUT_FILE_PATH].c_str(), ios::in | ios::out | ios::trunc);
	for (int current = 0; current < encoding_result.size() - 1; current++)
		outfile << encoding_result[current] << endl;
}