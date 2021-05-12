#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>
#include"btc.h"
#include "crypto/bip39.h"
#include "crypto/bip32.h"
#include "crypto/ecdsa.h"
#include "crypto/secp256k1.h"

int main(){ 
    int8_t mnemonic[] = "machine ring topic ladder damage stem client cage dust feed attack young audit drum distance lava torch iron absurd female place aisle title gauge";
    int8_t txn_metadata_string[META_LEN] = "8000002c8000000180000000010000000000000000000000000000000000010000000100000000";
    int8_t unsigned_txn_string[UTX_LEN] = "0200000001f5db32c555ba1cb8bc58dfa364e4d476f3f138b5fa854f212273d484be3d5e13010000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88acffffffff0210270000000000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88ac7f761600000000001976a91418b9420d3e7f85d50d150156bc33c1bbe45c748c88ac00000000";
    uint32_t length;
    uint8_t* signed_txn_byte_array = unsigned_to_signed(unsigned_txn_string,UTX_LEN,txn_metadata_string,META_LEN,mnemonic,strlen(mnemonic),&length);
    printf("\nSigned Txn is : ");
    print_uint_8(signed_txn_byte_array,length);
}