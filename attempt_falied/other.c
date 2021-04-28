#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <inttypes.h>
#include "crypto/bip39.h"
#include "crypto/bip32.h"

#define VERSION_PUBLIC 0x043587CF
#define VERSION_PRIVATE 0x04358394
#define XPUB_MAXLEN 112
#define MAX_ADDR_SIZE 130


typedef struct 
{
    uint8_t previous_txn_hash[32];
    uint8_t previous_output_index[4];
    uint8_t script_length[1];
    uint8_t script_public_key[25];
    uint8_t sequence[4];
}unsigned_txn_input;

typedef struct 
{
    uint8_t previous_txn_hash[32];
    uint8_t previous_output_index[4];
    uint8_t script_length[1];
    uint8_t script_sig[128];
    uint8_t sequence[4];
}signed_txn_input;

typedef struct 
{
    uint8_t value[8];
    uint8_t script_length[1];
    uint8_t script_public_key[25];
}txn_output;


typedef struct 
{
    uint8_t network_version[4];
    uint8_t input_count[1];
    unsigned_txn_input *input;
    uint8_t output_count[1];
    txn_output *output;
    uint8_t locktime[4];
    uint8_t sighash[4];

}unsigned_txn;

typedef struct 
{
    uint8_t network_version[4];
    uint8_t input_count[1];
    signed_txn_input *input;
    uint8_t output_count[1];
    txn_output *output;
    uint8_t locktime[4];
}signed_txn;

typedef struct 
{
    uint8_t chain_index[4];
    uint8_t address_index[4];
}address_type;

typedef struct 
{
    uint8_t wallet_index[1];
    uint8_t purpose_index[4];
    uint8_t coin_index[4];
    uint8_t account_index[4];
    
    uint8_t input_count[1];
    address_type *input;
    
    uint8_t output_count[1];
    address_type *output;
    
    uint8_t change_count[1];
    address_type *change;

}txn_metadata;

void print_u8(uint8_t *s) {
    size_t len = strlen((char*)s);
    for(size_t i = 0; i < len; i++) {
        printf("%02x", s[i]);
    }
    printf("\n");
}

int getNum(char ch)
{
    int num=0;
    if(ch>='0' && ch<='9')
    {
        num=ch-0x30;
    }
    else
    {
        switch(ch)
        {
            case 'A': case 'a': num=10; break;
            case 'B': case 'b': num=11; break;
            case 'C': case 'c': num=12; break;
            case 'D': case 'd': num=13; break;
            case 'E': case 'e': num=14; break;
            case 'F': case 'f': num=15; break;
            default: num=0;
        }
    }
    return num;
}

unsigned int hex_to_dec(unsigned char hex[])
{
    unsigned int x=0;
    x=(getNum(hex[0]))*16+(getNum(hex[1]));
}

void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array){

    unsigned char temp[2];    

    for(uint32_t i = 0; i < string_length; i = i + 2){
        for(uint32_t j = 0; j < 2; j++){
            temp[j] = hex_string[i+j];
        }
        byte_array[i/2] = hex_to_dec(temp);
    }

}


void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr){
	uint32_t offset = 0, len = 0;
    
      len = sizeof(unsigned_txn_ptr->network_version);
      memcpy(unsigned_txn_ptr->network_version, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->input_count);
      memcpy(unsigned_txn_ptr->input_count, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = (*unsigned_txn_ptr->input_count)*sizeof(unsigned_txn_input); 
      unsigned_txn_ptr->input = (unsigned_txn_input*)malloc(len);
    
      for (uint8_t i = 0; i < *unsigned_txn_ptr->input_count; i++)
      {
        len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
        memcpy(unsigned_txn_ptr->input[i].previous_txn_hash, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].previous_output_index);
        memcpy(unsigned_txn_ptr->input[i].previous_output_index, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].script_length);
        memcpy(unsigned_txn_ptr->input[i].script_length, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].script_public_key);
        memcpy(unsigned_txn_ptr->input[i].script_public_key, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].sequence);
        memcpy(unsigned_txn_ptr->input[i].sequence, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;
      }

      len = sizeof(unsigned_txn_ptr->output_count);
      memcpy(unsigned_txn_ptr->output_count, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = (*unsigned_txn_ptr->output_count)*sizeof(txn_output); 
      unsigned_txn_ptr->output = (txn_output*)malloc(len);

      for (uint8_t i = 0; i < *unsigned_txn_ptr->output_count; i++)
      {
        len = sizeof(unsigned_txn_ptr->output[i].value);
        memcpy(unsigned_txn_ptr->output[i].value, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_length);
        memcpy(unsigned_txn_ptr->output[i].script_length, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_public_key);
        memcpy(unsigned_txn_ptr->output[i].script_public_key, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;
      }

      len = sizeof(unsigned_txn_ptr->locktime);
      memcpy(unsigned_txn_ptr->locktime, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->sighash);
      memcpy(unsigned_txn_ptr->sighash, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

}

int main(void)
{
	unsigned_txn *uTx;
	uint8_t len;
	const char *received_unsigned_txn_string = "0200000001f5db32c555ba1cb8bc58dfa364e4d476f3f138b5fa854f212273d484be3d5e13010000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88acffffffff0210270000000000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88ac7f761600000000001976a91418b9420d3e7f85d50d150156bc33c1bbe45c748c88ac00000000";

	len = sizeof(received_unsigned_txn_string)/2;
	uint8_t unsigned_txn_byte_array[len];
	hex_string_to_byte_array(received_unsigned_txn_string,len,unsigned_txn_byte_array);


	unsigned_txn *unsigned_txn_ptr;
	byte_array_to_unsigned_txn(unsigned_txn_byte_array, unsigned_txn_ptr);// cast into the unsigned_txn structure
	// print_u8(&unsigned_txn_ptr->input);
	// print_u8(&unsigned_txn_ptr->input_count);
	// print_u8(&unsigned_txn_ptr->output);
	// print_u8(&unsigned_txn_ptr->output_count);
	// print_u8(&unsigned_txn_ptr->sighash);
	// print_u8(&unsigned_txn_ptr->network_version);

	// 	signed_txn *signed_txn_byte_array;
	// len = sizeof(unsigned_txn_input); 
    // signed_txn_byte_array = (signed_txn*)malloc(len);
	return 0;
}