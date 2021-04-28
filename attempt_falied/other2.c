#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#include "crypto/bip39.h"
#include "crypto/bip32.h"
#include "crypto/ecdsa.h"
#include "crypto/secp256k1.h"
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
    uint8_t input_count[1   ];
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

uint8_t hex_to_dec(uint8_t hex){
	char *ref = "0123456789abcdef";
	int j=0;
    while(hex!=ref[j])
        j++;
	return (uint8_t)j;
}

void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array)
{
	int i=0,j=0;
	char hex[2];
	for(;i<string_length;i+=2,j++)
	{
		hex[0] = hex_string[i];
		hex[1] = hex_string[i+1];
		//printf("%c",hex[0]);
		//printf("%c\t",hex[1]);
		byte_array[j] =  hex_to_dec(hex[0])*16+hex_to_dec(hex[1]);
	}
	/*
	for(;i<string_length;)
		byte_array[i] =  hex_to_dec(hex_string[i]);*/
}

void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr);
void byte_array_to_txn_metadata(uint8_t *btc_txn_metadata_byte_array, txn_metadata *txn_metadata_ptr);

void Masternode_to_addressNode_m_44_1_0_0(HDNode node);

void serialize_unsigned_txn_to_sign(unsigned_txn *unsigned_txn_ptr, uint8_t input_index, uint8_t *btc_serialized_unsigned_txn);

uint32_t unsigned_txn_to_signed_txn(unsigned_txn *unsigned_txn_ptr, txn_metadata *txn_metadata_ptr, const char *mnemonic, const char *passphrase, signed_txn *signed_txn_ptr);

void signed_txn_to_byte_array(signed_txn *signed_txn_ptr, uint8_t *generated_signed_txn_byte_array);

void der_to_signed_txn(uint8_t *pub_key,unsigned_txn *unsigned_txn_ptr, signed_txn *signed_txn_ptr,uint8_t* der,uint8_t input_index);

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


void Masternode_to_addressNode_m_44_1_0_0(HDNode node)
{
    int i=0;
    printf("Master Node\n")    ;
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");

    hdnode_private_ckd(&node,0x8000002C);
    hdnode_fill_public_key(&node);

    printf("Purpose Node 44' \n")    ;
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");
    

    
    hdnode_private_ckd(&node,0x80000001);
    hdnode_fill_public_key(&node);

    
    printf("Coin Node 1' \n")    ;
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");

    hdnode_private_ckd(&node,0x80000000);
    hdnode_fill_public_key(&node);

    
    printf("Account Node 1' \n")    ;
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");

    
    hdnode_private_ckd(&node,0x00000000);
    hdnode_fill_public_key(&node);

    
    printf("Chain Node 0\n");
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");

    hdnode_private_ckd(&node,0x00000000);
    hdnode_fill_public_key(&node);

    
    printf("Address Node 0\n");
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    printf("\n\n");
}

void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr)
{

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

void serialize_unsigned_txn_to_sign(unsigned_txn *unsigned_txn_ptr, uint8_t input_index, uint8_t *btc_serialized_unsigned_txn)
{
      uint32_t offset = 0, len = 0;
    
      len = sizeof(unsigned_txn_ptr->network_version);
      memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->network_version, len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->input_count);
      memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->input_count, len);
      offset += len;
 
      for (uint8_t i = 0; i < *unsigned_txn_ptr->input_count; i++)
      {
        if(i == input_index)
        {
          len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
          memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->input[i].previous_txn_hash, len);
          offset += len;
          
          len = sizeof(unsigned_txn_ptr->input[i].previous_output_index);
          memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->input[i].previous_output_index, len);
          offset += len;

          len = sizeof(unsigned_txn_ptr->input[i].script_length);
          memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->input[i].script_length, len);
          offset += len;

          len = sizeof(unsigned_txn_ptr->input[i].script_public_key);
          memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->input[i].script_public_key, len);
          offset += len;

          len = sizeof(unsigned_txn_ptr->input[i].sequence);
          memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->input[i].sequence, len);
          offset += len;
          continue ;       
        }
        else
        {
        
          len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
          memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->input[i].previous_txn_hash, len);
          offset += len;
        
          len = sizeof(unsigned_txn_ptr->input[i].previous_output_index);
          memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->input[i].previous_output_index, len);
          offset += len;
        
          len = sizeof(unsigned_txn_ptr->input[i].script_length);
          memcpy((btc_serialized_unsigned_txn+offset), "0", len);
          offset += len;
        
          len = sizeof(unsigned_txn_ptr->input[i].sequence);
          memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->input[i].sequence, len);
          offset += len;
        }
    }
    len = sizeof(unsigned_txn_ptr->output_count);
    memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->output_count, len);
    offset += len;
      
    for (uint8_t i = 0; i < *unsigned_txn_ptr->output_count; i++)
    {
      len = sizeof(unsigned_txn_ptr->output[i].value);
      memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->output[i].value, len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->output[i].script_length);
      memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->output[i].script_length, len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->output[i].script_public_key);
      memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->output[i].script_public_key, len);
      offset += len;
    }


    len = sizeof(unsigned_txn_ptr->locktime);
    memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->locktime, len);
    offset += len;

    len = sizeof(unsigned_txn_ptr->sighash);
    memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->sighash, len);
    offset += len;
}

void byte_array_to_txn_metadata(uint8_t *btc_txn_metadata_byte_array, txn_metadata *txn_metadata_ptr){
	uint32_t offset = 0, len = 0;
	
	txn_metadata_ptr->wallet_index[0] = btc_txn_metadata_byte_array[offset++];
	
	len=4;
	memcpy(txn_metadata_ptr->purpose_index, (btc_txn_metadata_byte_array+offset), len);
	offset+=len;
	
	memcpy(txn_metadata_ptr->purpose_index, (btc_txn_metadata_byte_array+offset), len);
	offset+=len;
	
	memcpy(txn_metadata_ptr->purpose_index, (btc_txn_metadata_byte_array+offset), len);
	offset+=len;
	
	txn_metadata_ptr->input_count[0] = btc_txn_metadata_byte_array[offset++];

	len = (*txn_metadata_ptr->input_count)*sizeof(address_type); 
    txn_metadata_ptr->input = (address_type*)malloc(len);
    len =4;
    for (uint8_t i = 0; i < *txn_metadata_ptr->input_count; i++)
    {
    	memcpy(txn_metadata_ptr->input[i].chain_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
		memcpy(txn_metadata_ptr->input[i].address_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
	}
	
	txn_metadata_ptr->output_count[0] = btc_txn_metadata_byte_array[offset++];
	
	len = (*txn_metadata_ptr->output_count)*sizeof(address_type); 
    txn_metadata_ptr->output = (address_type*)malloc(len);
    len =4;
    for (uint8_t i = 0; i < *txn_metadata_ptr->output_count; i++)
    {
    	memcpy(txn_metadata_ptr->output[i].chain_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
		memcpy(txn_metadata_ptr->output[i].address_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
	}
	
	txn_metadata_ptr->change_count[0] = btc_txn_metadata_byte_array[offset++];
	
	len = (*txn_metadata_ptr->change_count)*sizeof(address_type); 
    txn_metadata_ptr->change = (address_type*)malloc(len);
    len =4;
    for (uint8_t i = 0; i < *txn_metadata_ptr->change_count; i++)
    {
    	memcpy(txn_metadata_ptr->change[i].chain_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
		memcpy(txn_metadata_ptr->change[i].address_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
	}
}
void der_to_signed_txn(uint8_t *pub_key,unsigned_txn *unsigned_txn_ptr, signed_txn *signed_txn_ptr,uint8_t* der,uint8_t input_index){
    int offset,len;
    len = sizeof(unsigned_txn_ptr->network_version);
    memcpy(signed_txn_ptr->network_version,unsigned_txn_ptr->network_version,len);
    memcpy(signed_txn_ptr->input_count,unsigned_txn_ptr->input_count,1);

    len = (*unsigned_txn_ptr->input_count)*sizeof(signed_txn_input); 
    signed_txn_ptr->input = (signed_txn_input*)malloc(len);

    for (uint8_t i = 0; i < *unsigned_txn_ptr->input_count; i++)
    {
        len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
        memcpy(signed_txn_ptr->input[i].previous_txn_hash,unsigned_txn_ptr->input[i].previous_txn_hash, len);

        len = sizeof(unsigned_txn_ptr->input[i].previous_output_index);
        memcpy(signed_txn_ptr->input[i].previous_output_index,unsigned_txn_ptr->input[i].previous_output_index, len);


        if(i==input_index){

            printf("%d",i);
            //*signed_txn_ptr->input[i].script_length = 3+sizeof(der)+sizeof(pub_key);
            *signed_txn_ptr->input[i].script_length = 106;
            
            printf("%d  ",*signed_txn_ptr->input[i].script_length);

            uint8_t *scrsig = (uint8_t*)malloc(signed_txn_ptr->input[i].script_length[0]);
            offset = 0;
            scrsig[offset++] = 64+1;
            memcpy(scrsig+offset,der,64);
            offset+=64;

            scrsig[offset++] = 0x01;
            scrsig[offset++] = 33;
            memcpy(scrsig+offset,pub_key,33);
            memcpy(signed_txn_ptr->input[i].script_sig,scrsig,signed_txn_ptr->input[i].script_length[0]);
        }
        else
        {
            signed_txn_ptr->input[i].script_length[0] = 0;
        }
        len = sizeof(unsigned_txn_ptr->input[i].sequence);
        memcpy(signed_txn_ptr->input[i].sequence, unsigned_txn_ptr->input[i].sequence, len);
        offset += len;
      }
      memcpy(signed_txn_ptr->output_count,unsigned_txn_ptr->output_count,1);

      len = (*unsigned_txn_ptr->output_count)*sizeof(txn_output); 
      signed_txn_ptr->output = (txn_output*)malloc(len);

      for(uint8_t i=0;i<signed_txn_ptr->output_count[0];i++)
      {
          len = sizeof(unsigned_txn_ptr->output[i].value);
          memcpy(signed_txn_ptr->output[i].value,unsigned_txn_ptr->output[i].value,len);
          
          signed_txn_ptr->output[i].script_length[0]=unsigned_txn_ptr->output[i].script_length[0];
          
          len = sizeof(unsigned_txn_ptr->output[i].script_public_key);
          memcpy(signed_txn_ptr->output[i].script_public_key,unsigned_txn_ptr->output[i].script_public_key,len);
      }
      len = sizeof(unsigned_txn_ptr->locktime);
      memcpy(signed_txn_ptr->locktime,unsigned_txn_ptr->locktime,len);
}


uint32_t unsigned_txn_to_signed_txn(unsigned_txn *unsigned_txn_ptr, txn_metadata *txn_metadata_ptr, const char *mnemonic, const char *passphrase, signed_txn *signed_txn_ptr){
    uint8_t *byte_array_to_sign, len;
    //printf("here\n");//check
    len = 39+41*(unsigned_txn_ptr->input_count[0])+ 34*(unsigned_txn_ptr->output_count[0]);
    //printf("\n%d\n",unsigned_txn_ptr->input_count[0]);
    //printf("\n%d\n",unsigned_txn_ptr->output_count[0]);
    //printf("\n%d\n",len);
    uint8_t input_index =0;

    byte_array_to_sign = (uint8_t*)malloc(len);
    //39+41*inputcount+34*outputcount    
    
    serialize_unsigned_txn_to_sign(unsigned_txn_ptr, input_index ,byte_array_to_sign);
    
    static uint8_t buff[SHA256_DIGEST_LENGTH];

    printf("byte array to sign :");
    for(int i=0;i<len;i++){
        printf("%02x",byte_array_to_sign[i]);
    }
    printf("\n");
    //Find double hash of byte array to sign
    sha256_Raw (byte_array_to_sign,len,buff);
    sha256_Raw (buff,SHA256_DIGEST_LENGTH,buff);
    printf("double sha256 :     ");
    len =0;
    while(buff[len]!='\0')
        len++;

    for(int i=0;i<len;i++){
        printf("%02x",buff[i]);
    }

    printf("\n");

    //Derive private key of the input 
    HDNode node;
    uint8_t seed[512/8],i;
    uint32_t *index;

    mnemonic_to_seed( mnemonic,passphrase,seed,0 );
    hdnode_from_seed(&seed[0],64,"secp256k1",&node);
    hdnode_fill_public_key(&node);

    index = (uint32_t*)txn_metadata_ptr->purpose_index;
    hdnode_private_ckd(&node,index);
    hdnode_fill_public_key(&node);
    
    index = (uint32_t*)txn_metadata_ptr->coin_index;
    hdnode_private_ckd(&node,index);
    hdnode_fill_public_key(&node);
    
    index = (uint32_t*)txn_metadata_ptr->account_index;
    hdnode_private_ckd(&node,index);
    hdnode_fill_public_key(&node);

    index = (uint32_t*)txn_metadata_ptr->input->chain_index;
    hdnode_private_ckd(&node,index);
    hdnode_fill_public_key(&node);

    index = (uint32_t*)txn_metadata_ptr->input->address_index;
    hdnode_private_ckd(&node,index);
    hdnode_fill_public_key(&node);

    printf("Private Key   :     ");
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);
    printf("\n");
    uint8_t *sig;
    sig = (uint8_t*)malloc(64);
    ecdsa_sign_digest(&secp256k1, node.private_key, buff, sig, NULL, NULL);
    
    uint8_t *der;
    der= (uint8_t*)malloc(64*sizeof(uint8_t));
    ecdsa_sig_to_der(sig,der);

    printf("der : ");
    for(i=0;i<64;i++)
        printf("%02x",der[i]);

    printf("\n");
    der_to_signed_txn(node.public_key,unsigned_txn_ptr,signed_txn_ptr,der,input_index);
    return 0;
}