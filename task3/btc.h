#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "crypto/bip39.h"
#include "crypto/bip32.h"
#include "crypto/curves.h"
#include "crypto/secp256k1.h"
#include "crypto/sha2.h"
#include "crypto/ecdsa.h"
#include "crypto/ripemd160.h"
#include "crypto/base58.h"


#define VERSION_LEN 4
#define NUMBER_OF_INPUTS_LEN 1
#define PREV_TXN_HASH_LEN 32
#define PREV_OUTPUT_INDEX_LEN 4
#define SCRIPT_LENGTH_LEN 1
#define SEQ_LEN 4
#define NUMBER_OF_OUTPUTS_LEN 1
#define VALUE_LEN 8
#define LOCKTIME_LEN 4
#define SIG_HASH_CODE_LEN 4
#define SEED_SIZE 64
#define MAX_SALT_SIZE 256
#define PRIVATE_KEY_LEN 32
#define PUBLIC_KEY_LEN 32
#define CHAIN_CODE_LEN 32
#define INDEX_SIZE 4
#define DEFAULT_UNSIGNED_TXN_SCRIPT_LEN 0x19
#define SIZE_OF_TXN_INPUTS_STRUCT (PREV_TXN_HASH_LEN+PREV_OUTPUT_INDEX_LEN+1+SEQ_LEN)
#define SIZE_OF_TXN_OUTPUTS_STRUCT (VALUE_LEN+1+DEFAULT_UNSIGNED_TXN_SCRIPT_LEN)
#define SIZE_OF_UNSIGNED_TXN_STRUCT(OUTS,SIZE) (VERSION_LEN+1+(SIZE_OF_TXN_INPUTS_STRUCT+(SIZE))+1+((SIZE_OF_TXN_OUTPUTS_STRUCT)*(OUTS))+LOCKTIME_LEN)
#define SIZE_OF_MULTI_INPUT_UNSIGNED_TXN_STRUCT(INS,OUTS,SIZE) (SIZE_OF_UNSIGNED_TXN_STRUCT(OUTS,SIZE)+SIG_HASH_CODE_LEN+(SIZE_OF_TXN_INPUTS_STRUCT+1)*(INS-1))

struct txn_inputs{
    uint8_t prev_txn_hash[PREV_TXN_HASH_LEN];
    uint8_t prev_output_index[PREV_OUTPUT_INDEX_LEN];
    uint8_t script_len;
    uint8_t *script;
    uint8_t squence[SEQ_LEN];
};


struct txn_outputs{
    uint8_t value[VALUE_LEN];
    uint8_t script_len;
    uint8_t *script_public_key;
};


struct unsigned_txn{
    uint8_t version[VERSION_LEN];
    uint8_t no_of_inputs;
    struct txn_inputs* inputs;
    uint8_t no_of_outputs;
    struct txn_outputs* outputs;
    uint8_t lock_time[LOCKTIME_LEN];
    uint8_t sig_hash_code[SIG_HASH_CODE_LEN];
};

struct signed_txn{
    uint8_t version[VERSION_LEN];
    uint8_t no_of_inputs;
    struct txn_inputs* inputs;
    uint8_t no_of_outputs;
    struct txn_outputs* outputs;
    uint8_t lock_time[LOCKTIME_LEN];
};

struct node{
    uint8_t chain_index[INDEX_SIZE];
    uint8_t address_index[INDEX_SIZE];
};


struct txn_metadata{
    
    uint8_t purpose_index[INDEX_SIZE];
    uint8_t coin_index[INDEX_SIZE];
    uint8_t account_index[INDEX_SIZE];
    uint8_t input_count;
    struct node *inputs;
    uint8_t output_count;
    struct node *outputs;
    uint8_t change_count;
    struct node *changes;

};


uint32_t uint8_t_array_to_uint32_t(uint8_t *);


void print_byte_array(uint8_t*, uint32_t);


void print_hdnode(HDNode*);


void print_txn_metadata(struct txn_metadata);


void print_unsigned_txn(struct unsigned_txn);

void print_signed_txn(struct signed_txn);


uint8_t* string_to_byte_array(int8_t *, uint32_t);



struct unsigned_txn* byte_array_to_unsigned_txn(uint8_t *, uint32_t);


struct txn_metadata* byte_array_to_txn_meta(uint8_t*, uint16_t);


int8_t* unsigned_to_signed(int8_t*, uint32_t, int8_t*, uint32_t, int8_t*, uint32_t, int8_t*, uint32_t,uint32_t*);

uint8_t* serialise_unsigned_txn(struct unsigned_txn*, int32_t, uint16_t*);


uint8_t* serialise_signed_txn(struct signed_txn*, uint32_t);