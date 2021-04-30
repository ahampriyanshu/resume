#include "btc.h"

    uint8_t hex_to_dec(uint8_t hex)
    {
        uint8_t decimal = 0;
        if(hex >= '0' && hex <= '9')
            {
                decimal = hex - 48;
            }
        else if (hex >= 'a' && hex <= 'f')
            {
                decimal = hex - 97 + 10;
            }
        else if (hex >= 'A' && hex <= 'F')
            {
                decimal = hex - 65 + 10;
            }
        return decimal;
    }
    
    void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array)
    {
        uint32_t i = 0, j = 0;
        
        for(i = 0, j = 0; j < string_length/2; i+=2, j++)
        {
            byte_array[j] = (hex_to_dec(hex_string[i])*16) + (hex_to_dec(hex_string[i+1]));

        }
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

    void byte_array_to_txn_metadata(uint8_t *btc_txn_metadata_byte_array,txn_metadata *txn_metadata_ptr)
    {

      uint32_t offset = 0, len = 0;

      len = sizeof(txn_metadata_ptr->wallet_index);
      memcpy(txn_metadata_ptr->wallet_index, (btc_txn_metadata_byte_array+offset), len);
      offset += len;

      len = sizeof(txn_metadata_ptr->purpose_index);
      memcpy(txn_metadata_ptr->purpose_index, (btc_txn_metadata_byte_array+offset), len);
      offset += len;

      len = sizeof(txn_metadata_ptr->coin_index);
      memcpy(txn_metadata_ptr->coin_index, (btc_txn_metadata_byte_array+offset), len);
      offset += len;

      len = sizeof(txn_metadata_ptr->account_index);
      memcpy(txn_metadata_ptr->account_index, (btc_txn_metadata_byte_array+offset), len);
      offset += len;

      len = sizeof(txn_metadata_ptr->input_count);
      memcpy(txn_metadata_ptr->input_count, (btc_txn_metadata_byte_array+offset), len);
      offset += len;

      len = (*txn_metadata_ptr->input_count)*sizeof(address_type); 
      txn_metadata_ptr->input = (address_type*)malloc(len);


      for (uint8_t i = 0; i < *txn_metadata_ptr->input_count; i++)
      {
        len = sizeof(txn_metadata_ptr->input[i].chain_index);
        memcpy(txn_metadata_ptr->input[i].chain_index, (btc_txn_metadata_byte_array+offset), len);
        offset += len;

        len = sizeof(txn_metadata_ptr->input[i].address_index);
        memcpy(txn_metadata_ptr->input[i].address_index, (btc_txn_metadata_byte_array+offset), len);
        offset += len;
      }


      len = sizeof(txn_metadata_ptr->output_count);
      memcpy(txn_metadata_ptr->output_count, (btc_txn_metadata_byte_array+offset), len);
      offset += len;

      len = (*txn_metadata_ptr->output_count)*sizeof(address_type); 
      txn_metadata_ptr->output = (address_type*)malloc(len);


      for (uint8_t i = 0; i < *txn_metadata_ptr->output_count; i++)
      {
        len = sizeof(txn_metadata_ptr->output[i].chain_index);
        memcpy(txn_metadata_ptr->output[i].chain_index, (btc_txn_metadata_byte_array+offset), len);
        offset += len;

        len = sizeof(txn_metadata_ptr->output[i].address_index);
        memcpy(txn_metadata_ptr->output[i].address_index, (btc_txn_metadata_byte_array+offset), len);
        offset += len;
      }


      len = sizeof(txn_metadata_ptr->change_count);
      memcpy(txn_metadata_ptr->change_count, (btc_txn_metadata_byte_array+offset), len);
      offset += len;

      len = (*txn_metadata_ptr->change_count)*sizeof(address_type); 
      txn_metadata_ptr->change = (address_type*)malloc(len);


      for (uint8_t i = 0; i < *txn_metadata_ptr->change_count; i++)
      {
        len = sizeof(txn_metadata_ptr->change[i].chain_index);
        memcpy(txn_metadata_ptr->change[i].chain_index, (btc_txn_metadata_byte_array+offset), len);
        offset += len;

        len = sizeof(txn_metadata_ptr->change[i].address_index);
        memcpy(txn_metadata_ptr->change[i].address_index, (btc_txn_metadata_byte_array+offset), len);
        offset += len;
      }


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
          memcpy((btc_serialized_unsigned_txn+offset), 0, len);
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


    uint32_t unsigned_txn_to_signed_txn(unsigned_txn *unsigned_txn_ptr, txn_metadata *txn_metadata_ptr, const char *mnemonic, const char *passphrase, signed_txn *signed_txn_ptr)
    {
    
      uint8_t *byte_array_to_sign;
      byte_array_to_sign = (uint8_t*)malloc(39+41*(*unsigned_txn_ptr->input_count)+34*(*unsigned_txn_ptr->output_count));//39+41*inputcount+34*outputcount
                      
      uint8_t *script_sig;
      uint8_t digest[32];
      uint8_t sig[64];
      uint8_t der_sig[128];
      uint8_t der_sig_len;
                     
      uint8_t bip39seed[512 / 8];
      mnemonic_to_seed(mnemonic, passphrase, bip39seed, 0);   

      uint32_t offset = 0, len = 0;
    
      len = sizeof(unsigned_txn_ptr->network_version);
      memcpy(signed_txn_ptr->network_version, unsigned_txn_ptr->network_version, len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->input_count);
      memcpy(signed_txn_ptr->input_count, unsigned_txn_ptr->input_count, len);
      offset += len;

      signed_txn_ptr->input = (signed_txn_input*)malloc((*signed_txn_ptr->input_count)*sizeof(signed_txn_input));//wholesome memory allocation

      for (uint8_t i = 0; i < *unsigned_txn_ptr->input_count; i++)//all input_count are equal
      {
        serialize_unsigned_txn_to_sign(unsigned_txn_ptr, i, byte_array_to_sign);    

        sha256_Raw(byte_array_to_sign, 39+41*(*unsigned_txn_ptr->input_count)+34*(*unsigned_txn_ptr->output_count), digest);
        sha256_Raw(digest, 32, digest);
        
        HDNode hdnode;
        hdnode_from_seed(bip39seed, 512/8, SECP256K1_NAME, &hdnode);
        hdnode_private_ckd(&hdnode, BYTE_ARRAY_TO_UINT32(txn_metadata_ptr->purpose_index));
        hdnode_private_ckd(&hdnode, BYTE_ARRAY_TO_UINT32(txn_metadata_ptr->coin_index));
        hdnode_private_ckd(&hdnode, BYTE_ARRAY_TO_UINT32(txn_metadata_ptr->account_index));   
        hdnode_private_ckd(&hdnode, BYTE_ARRAY_TO_UINT32(txn_metadata_ptr->input[i].chain_index));
        hdnode_private_ckd(&hdnode, BYTE_ARRAY_TO_UINT32(txn_metadata_ptr->input[i].address_index));
        hdnode_fill_public_key(&hdnode);

        ecdsa_sign_digest(&secp256k1, hdnode.private_key, digest, sig, NULL, NULL);//sig not being matched with the one calculated online, digest and private_key is correct though
        //int verify = ecdsa_verify_digest(&secp256k1,hdnode.public_key, sig, digest);
        der_sig_len = ecdsa_sig_to_der(sig, der_sig); 

        uint8_t script_sig_len = der_sig_len + 36;//PUSHDATA Opcode(1) + der_sig_len + SigHash Code(1) + PUSHDATA Opcode(1) + Public Key(33)
        script_sig = (uint8_t*)malloc(script_sig_len);//check, assuming malloc allocates fresh memory every time.
        
        uint8_t pushdata_opcode_der = der_sig_len + 1;//includes der_sig and SigHash Code(1)
        uint8_t sighash_code = 1;
        uint8_t pushdata_opcode_pub = 33;
        
        memcpy(script_sig, &pushdata_opcode_der, 1);
        memcpy(script_sig+1, der_sig, der_sig_len);
        memcpy(script_sig+1+der_sig_len, &sighash_code, 1);
        memcpy(script_sig+1+der_sig_len+1, &pushdata_opcode_pub, 1);
        memcpy(script_sig+1+der_sig_len+1+1, hdnode.public_key, 33);

        len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
        memcpy(signed_txn_ptr->input[i].previous_txn_hash, unsigned_txn_ptr->input[i].previous_txn_hash, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].previous_output_index);
        memcpy(signed_txn_ptr->input[i].previous_output_index, unsigned_txn_ptr->input[i].previous_output_index, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].script_length);
        memcpy(signed_txn_ptr->input[i].script_length, &script_sig_len, len);
        offset += len;

        len = script_sig_len;
        memcpy(signed_txn_ptr->input[i].script_sig, script_sig, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].sequence);
        memcpy(signed_txn_ptr->input[i].sequence, unsigned_txn_ptr->input[i].sequence, len);
        offset += len;
             
      }
      
      len = sizeof(unsigned_txn_ptr->output_count);
      memcpy(signed_txn_ptr->output_count, unsigned_txn_ptr->output_count, len);
      offset += len;
    
      len = (*unsigned_txn_ptr->output_count)*sizeof(txn_output); 
      signed_txn_ptr->output = (txn_output*)malloc(len);

      for (uint8_t i = 0; i < *signed_txn_ptr->output_count; i++)
      {
        len = sizeof(unsigned_txn_ptr->output[i].value);
        memcpy(signed_txn_ptr->output[i].value, unsigned_txn_ptr->output[i].value, len);
        offset += len;
        
        len = sizeof(unsigned_txn_ptr->output[i].script_length);
        memcpy(signed_txn_ptr->output[i].script_length, unsigned_txn_ptr->output[i].script_length, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_public_key);
        memcpy(signed_txn_ptr->output[i].script_public_key, unsigned_txn_ptr->output[i].script_public_key, len);
        offset += len;
      }

      len = sizeof(unsigned_txn_ptr->locktime);
      memcpy(signed_txn_ptr->locktime, unsigned_txn_ptr->locktime, len);
      offset += len;
      
      return offset;
    }

    void signed_txn_to_byte_array(signed_txn *signed_txn_ptr, uint8_t *generated_signed_txn_byte_array)
    {
      uint32_t offset = 0, len = 0;
    
      len = sizeof(signed_txn_ptr->network_version);
      memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->network_version, len);
      offset += len;

      len = sizeof(signed_txn_ptr->input_count);
      memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->input_count, len);
      offset += len;

      for (uint8_t i = 0; i < *signed_txn_ptr->input_count; i++)
      {
        
        len = sizeof(signed_txn_ptr->input[i].previous_txn_hash);
        memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->input[i].previous_txn_hash, len);
        offset += len;

        len = sizeof(signed_txn_ptr->input[i].previous_output_index);
        memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->input[i].previous_output_index, len);
        offset += len;

        len = sizeof(signed_txn_ptr->input[i].script_length);
        memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->input[i].script_length, len);
        offset += len;

        len = *signed_txn_ptr->input[i].script_length;
        memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->input[i].script_sig, len);
        offset += len;

        len = sizeof(signed_txn_ptr->input[i].sequence);
        memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->input[i].sequence, len);
        offset += len;

        }

      len = sizeof(signed_txn_ptr->output_count);
      memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->output_count, len);
      offset += len;

      for (uint8_t i = 0; i < *signed_txn_ptr->output_count; i++)
      {        
        len = sizeof(signed_txn_ptr->output[i].value);
        memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->output[i].value, len);
        offset += len;

        len = sizeof(signed_txn_ptr->output[i].script_length);
        memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->output[i].script_length, len);
        offset += len;

        len = sizeof(signed_txn_ptr->output[i].script_public_key);
        memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->output[i].script_public_key, len);
        offset += len;
      }
      
      len = sizeof(signed_txn_ptr->locktime);
      memcpy((generated_signed_txn_byte_array+offset), signed_txn_ptr->locktime, len);
      offset += len;
    }