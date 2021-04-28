#ifndef BTC_HEADER
#define BTC_HEADER


#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "crypto/bip39.h"
#include "crypto/bip32.h"
#include "crypto/curves.h"
#include "crypto/secp256k1.h"
#include "crypto/sha2.h"
#include "crypto/ecdsa.h"
#include "crypto/ripemd160.h"
#include "crypto/base58.h"


#define BYTE_ARRAY_TO_UINT32(x) x[0]<<24|x[1]<<16|x[2]<<8|x[3]

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




uint8_t hex_to_dec(uint8_t hex);

void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array);

// 2nd step
// Using malloc
void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr);

void byte_array_to_txn_metadata(uint8_t *btc_txn_metadata_byte_array, txn_metadata *txn_metadata_ptr);

// 3rd step Complete this func to generate the serializes unsigned txn to sign corresponding to an input
void serialize_unsigned_txn_to_sign(unsigned_txn *unsigned_txn_ptr, uint8_t input_index, uint8_t *btc_serialized_unsigned_txn);

uint32_t unsigned_txn_to_signed_txn(unsigned_txn *unsigned_txn_ptr, txn_metadata *txn_metadata_ptr, const char *mnemonic, const char *passphrase, signed_txn *signed_txn_ptr);

void signed_txn_to_byte_array(signed_txn *signed_txn_ptr, uint8_t *generated_signed_txn_byte_array);


/*
*/
uint32_t uint8_t_array_to_uint32_t(uint8_t *);


/*
@para para1: byte array, para2: len of array
@return void
*/
void print_byte_array(uint8_t*, uint32_t);

/*
@para para1: hdnode
return void
*/
void print_hdnode(HDNode*);

/*
@para para1: tx meta struct*
@return void
*/
void print_txn_metadata(struct txn_metadata);

/*
*/
void print_unsigned_txn(struct unsigned_txn);

/*
*/
void print_signed_txn(struct signed_txn);

/*
string to byte array
@para para1: string, para2: len of string, para3: byte array
@return len of byte array
*/
uint8_t* string_to_byte_array(int8_t *, uint32_t);


/*
byte array to struct
@para para1: byte array, para2: len of byte array
@return struct
*/
struct unsigned_txn* byte_array_to_unsigned_txn(uint8_t *, uint32_t);


/*
transaction meta data to byte array
@para para1: txn structure, reference to len variable
@return byte array
*/
struct txn_metadata* byte_array_to_txn_meta(uint8_t*, uint16_t);

/*
Unsigned to signed
@para para1: unsigned txn struct, txn_meta struct, signed txn struct
@return void
*/
int8_t* unsigned_to_signed(int8_t*, uint32_t, int8_t*, uint32_t, int8_t*, uint32_t, int8_t*, uint32_t,uint32_t*);


/*
serialise unsigned struct to byte array
@para para1: unsigned struct, para2: index -> input to skip, para3: (ref)len of byte array 
@return byte array
*/
uint8_t* serialise_unsigned_txn(struct unsigned_txn*, int32_t, uint16_t*);

/*
Serialise signed to byte array
*/
uint8_t* serialise_signed_txn(struct signed_txn*, uint32_t);


#endif