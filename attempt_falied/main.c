#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#include "crypto/bip39.h"
#include "crypto/bip32.h"
#include "crypto/ecdsa.h"
#include "crypto/secp256k1.h"

#include "btc.h"

int main()
{
    char* mnemonic = "machine ring topic ladder damage stem client cage dust feed attack young audit drum distance lava torch iron absurd female place aisle title gauge";
	char* address ;
  	char *passphrase = "";
  	uint8_t seed[512/8];
    int i,len;

    const char *received_unsigned_txn_string = "0200000001f5db32c555ba1cb8bc58dfa364e4d476f3f138b5fa854f212273d484be3d5e13010000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88acffffffff0210270000000000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88ac7f761600000000001976a91418b9420d3e7f85d50d150156bc33c1bbe45c748c88ac00000000";    
	const char *received_txn_metadata_string = "8000002c8000000180000000010000000000000000000000000000000000010000000100000000";
    
	
    len=0;
	while(received_unsigned_txn_string[len]!='\0')
		len++;
	uint8_t unsigned_txn_byte_array[len/2];

	hex_string_to_byte_array(received_unsigned_txn_string,len,&unsigned_txn_byte_array[0]);// converting string to byte array
	

	unsigned_txn *unsigned_txn_ptr;
    unsigned_txn_ptr = (unsigned_txn*)malloc(sizeof(unsigned_txn));
	byte_array_to_unsigned_txn(unsigned_txn_byte_array, unsigned_txn_ptr);// cast into the unsigned_txn structure

	len=0;
	while(received_txn_metadata_string[len]!='\0')
		len++;
	uint8_t txn_metadata_byte_array[len/2];
	hex_string_to_byte_array(received_txn_metadata_string,len,&txn_metadata_byte_array[0]);// converting string to byte array
	
	txn_metadata *txn_metadata_ptr;
    txn_metadata_ptr = (txn_metadata*)malloc(sizeof(txn_metadata));
	byte_array_to_txn_metadata(txn_metadata_byte_array, txn_metadata_ptr);// cast into the txn_metadata structure
	
	signed_txn *signed_txn_byte_array;

	len = sizeof(unsigned_txn_input); 
    signed_txn_byte_array = (signed_txn*)malloc(len);
	
	mnemonic_to_seed( mnemonic,passphrase,seed,0 );

    HDNode node;

    hdnode_from_seed(&seed[0],64,"secp256k1",&node);
    hdnode_fill_public_key(&node);
    
    unsigned_txn_to_signed_txn(unsigned_txn_ptr,"",mnemonic,"",signed_txn_byte_array);
    for(i=0;i<(uint8_t)signed_txn_byte_array->input[0].script_length;i++)
    {
        printf("%02x ",signed_txn_byte_array->input[0].script_sig[i]);
    }

    return 0;
}