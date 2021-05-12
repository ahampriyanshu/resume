#include "btc.h"

uint32_t uint8_t_array_to_uint32_t(uint8_t *arr)
{
    uint32_t temp = 0;
    for (int8_t i = 0; i < 4; i++)
    {
        temp = temp << 8;
        temp = temp | arr[i];
    }
    return temp;
}

void print_uint_8(uint8_t *arr, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
    {
        printf("%02x", arr[i]);
    }
    printf("\n");
}

void print_hex(uint8_t *s)
{
    size_t len = strlen((char *)s);
    for (size_t i = 0; i < len; i++)
    {
        printf("%02x", s[i]);
    }
    printf("\n");
}

void print_signed_txn(struct signed_txn input)
{
    printf("Signed Txn Struct :\n");
    printf("Version: ");
    print_uint_8(input.version, VERSION_LEN);
    printf("\nNo of inputs: %x\n", input.no_of_inputs);
    for (uint8_t i = 0; i < input.no_of_inputs; i++)
    {
        printf("Input Number :%x\n", i + 1);
        printf("Input Prev Hash: ");
        print_uint_8(input.inputs[i].prev_txn_hash, PREV_TXN_HASH_LEN);
        printf("Input Prev Output Index: ");
        print_uint_8(input.inputs[i].prev_output_index, PREV_OUTPUT_INDEX_LEN);
        printf("Input Len: %x\n", input.inputs[i].script_len);
        printf("Input Script: ");
        print_uint_8(input.outputs[i].script_public_key, input.outputs[i].script_len);
        printf("Input Sequence: ");
        print_uint_8(input.inputs[i].squence, SEQ_LEN);
        printf("\n");
    }
    printf("No of outputs: %x\n", input.no_of_outputs);
    for (uint8_t i = 0; i < input.no_of_outputs; i++)
    {
        printf("Output Number :%x\n", i + 1);
        printf("Output Value: ");
        print_uint_8(input.outputs[i].value, VALUE_LEN);
        printf("Output Len: %x\n", input.outputs[i].script_len);
        printf("Output Script: ");
        print_uint_8(input.outputs[i].script_public_key, input.outputs[i].script_len);
        printf("\n");
    }
    printf("Locktime: ");
    print_uint_8(input.lock_time, LOCKTIME_LEN);
}

uint8_t *string_to_byte_array(int8_t *input, uint32_t len)
{
    uint8_t *output = (uint8_t *)malloc(((len + 1) / 2));
    uint32_t o, i;
    o = i = 0;
    while (i < len)
    {
        if (input[i] >= 'a')
        {
            input[i] -= 'a' - 10;
        }
        else if (input[i] >= 'A')
        {
            input[i] -= 'A' - 10;
        }
        else
        {
            input[i] -= '0';
        }
        output[o] = output[o] | input[i];
        if (i % 2 == 0)
        {
            output[o] = output[o] << 4;
        }
        else
        {
            o++;
        }
        i++;
    }
    return output;
}

struct unsigned_txn *byte_array_to_unsigned_txn(uint8_t *input, uint32_t len)
{
    uint32_t offset = 0;
    struct unsigned_txn *output = (struct unsigned_txn *)malloc(sizeof(struct unsigned_txn));
    memcpy(output, input + offset, VERSION_LEN + NUMBER_OF_INPUTS_LEN);
    offset += VERSION_LEN + NUMBER_OF_INPUTS_LEN;
    output->inputs = (struct txn_inputs *)malloc(sizeof(struct txn_inputs) * output->no_of_inputs);

    uint8_t i = 0;
    while (i < output->no_of_inputs)
    {
        memcpy((void *)&output->inputs[i], input + offset, PREV_TXN_HASH_LEN + PREV_OUTPUT_INDEX_LEN + SCRIPT_LENGTH_LEN);
        offset += PREV_TXN_HASH_LEN + PREV_OUTPUT_INDEX_LEN + SCRIPT_LENGTH_LEN;
        output->inputs[i].script = (uint8_t *)malloc(output->inputs[i].script_len);
        memcpy(output->inputs[i].script, input + offset, output->inputs[i].script_len);
        // printf("\n\n\n");
        // print_uint_8( input + offset,i);
        // printf("\n\n\n");
        offset += output->inputs[i].script_len;
        if (output->inputs[i].script_len == 0)
        {
            offset++;
        }
        memcpy((void *)&output->inputs[i].squence, input + offset, SEQ_LEN);
        offset += SEQ_LEN;
        // printf("\n\n\n");
        // print_uint_8( input + offset, SEQ_LEN);
        // printf("\n\n\n");
        i++;
    }
    memcpy((void *)&output->no_of_outputs, input + offset, NUMBER_OF_OUTPUTS_LEN);
    offset += NUMBER_OF_OUTPUTS_LEN;

    output->outputs = (struct txn_outputs *)malloc(sizeof(struct txn_outputs) * output->no_of_outputs);

    i = 0;

    while (i < output->no_of_outputs)
    {
        memcpy((void *)&output->outputs[i], input + offset, VALUE_LEN + SCRIPT_LENGTH_LEN);
        offset += VALUE_LEN + SCRIPT_LENGTH_LEN;
        output->outputs[i].script_public_key = (uint8_t *)malloc(output->outputs[i].script_len);
        memcpy(output->outputs[i].script_public_key, input + offset, output->outputs[i].script_len);
        offset += output->outputs[i].script_len;
        i++;
    }

    memcpy(output->lock_time, input + offset, LOCKTIME_LEN + SIG_HASH_CODE_LEN);
    return output;
}

struct txn_metadata *byte_array_to_txn_meta(uint8_t *input, uint16_t len)
{
    struct txn_metadata *output = (struct txn_metadata *)malloc(sizeof(struct txn_metadata));
    uint16_t offset = 0;

    memcpy((void *)output, input + offset, (INDEX_SIZE * 3) + 1);
    offset += INDEX_SIZE * 3 + 1;

    output->inputs = (struct node *)malloc(sizeof(struct node) * output->input_count);

    memcpy((void *)output->inputs, input + offset, INDEX_SIZE * 2 * output->input_count);
    offset += INDEX_SIZE * 2 * output->input_count;

    memcpy((void *)&output->output_count, input + offset, 1);
    offset += 1;

    output->outputs = (struct node *)malloc(sizeof(struct node) * output->output_count);

    memcpy((void *)output->outputs, input + offset, INDEX_SIZE * 2 * output->output_count);
    offset += INDEX_SIZE * 2 * output->output_count;

    memcpy((void *)&output->change_count, input + offset, 1);
    offset += 1;

    output->changes = (struct node *)malloc(sizeof(struct node) * output->change_count);

    memcpy((void *)output->changes, input + offset, INDEX_SIZE * 2 * output->change_count);
    offset += INDEX_SIZE * 2 * output->change_count;

    return output;
}

uint8_t *serialise_unsigned_txn(struct unsigned_txn *unsigned_txn_in, int32_t index_include, uint32_t *len_out)
{
    uint16_t length;
    uint16_t offset = 0;
    if (unsigned_txn_in->no_of_inputs == 1)
    {
        length = SIZE_OF_UNSIGNED_TXN_STRUCT(unsigned_txn_in->no_of_outputs, unsigned_txn_in->inputs[0].script_len);
    }
    else
    {
        length = SIZE_OF_MULTI_INPUT_UNSIGNED_TXN_STRUCT(unsigned_txn_in->no_of_inputs, unsigned_txn_in->no_of_outputs, unsigned_txn_in->inputs[index_include].script_len);
    }
    uint8_t *unsigned_txn_out = (uint8_t *)malloc(length + 1);
    memcpy(unsigned_txn_out + offset, (void *)unsigned_txn_in->version, VERSION_LEN);
    offset += VERSION_LEN;
    memcpy(unsigned_txn_out + offset, (void *)&unsigned_txn_in->no_of_inputs, 1);
    offset += 1;
    for (int16_t i = 0; i < unsigned_txn_in->no_of_inputs; i++)
    {
        memcpy(unsigned_txn_out + offset, unsigned_txn_in->inputs[i].prev_txn_hash, PREV_TXN_HASH_LEN);
        offset += PREV_TXN_HASH_LEN;
        memcpy(unsigned_txn_out + offset, unsigned_txn_in->inputs[i].prev_output_index, PREV_OUTPUT_INDEX_LEN);
        offset += PREV_OUTPUT_INDEX_LEN;
        if (i == index_include)
        {
            memcpy(unsigned_txn_out + offset, (void *)&unsigned_txn_in->inputs[i].script_len, 1);
            offset += 1;
            memcpy(unsigned_txn_out + offset, unsigned_txn_in->inputs[i].script, unsigned_txn_in->inputs[i].script_len);
            offset += unsigned_txn_in->inputs[i].script_len;
        }
        else
        {
            memset(unsigned_txn_out + offset, 0, 1);
            offset += 1;
        }
        memcpy(unsigned_txn_out + offset, unsigned_txn_in->inputs[i].squence, SEQ_LEN);
        offset += SEQ_LEN;
    }
    memcpy(unsigned_txn_out + offset, (void *)&unsigned_txn_in->no_of_outputs, 1);
    offset += 1;
    for (uint8_t i = 0; i < unsigned_txn_in->no_of_outputs; i++)
    {
        memcpy(unsigned_txn_out + offset, unsigned_txn_in->outputs[i].value, VALUE_LEN);
        offset += VALUE_LEN;
        memcpy(unsigned_txn_out + offset, (void *)&unsigned_txn_in->outputs[i].script_len, SCRIPT_LENGTH_LEN);
        offset += SCRIPT_LENGTH_LEN;
        memcpy(unsigned_txn_out + offset, unsigned_txn_in->outputs[i].script_public_key, unsigned_txn_in->outputs[i].script_len);
        offset += unsigned_txn_in->outputs[i].script_len;
    }
    memcpy(unsigned_txn_out + offset, unsigned_txn_in->lock_time, LOCKTIME_LEN);
    offset += LOCKTIME_LEN;
    memcpy(unsigned_txn_out + offset, unsigned_txn_in->sig_hash_code, SIG_HASH_CODE_LEN);
    offset += SIG_HASH_CODE_LEN;

    *len_out = offset;
    return unsigned_txn_out;
}

uint8_t *serialise_signed_txn(struct signed_txn *signed_txn_struct, uint32_t length)
{
    uint32_t offset = 0;
    uint8_t *signed_txn_byte_array = (uint8_t *)malloc(length + 1);
    memcpy(signed_txn_byte_array + offset, (void *)signed_txn_struct->version, VERSION_LEN);

    offset += VERSION_LEN;
    memcpy(signed_txn_byte_array + offset, (void *)&signed_txn_struct->no_of_inputs, 1);
    offset += 1;

    for (int16_t i = 0; i < signed_txn_struct->no_of_inputs; i++)
    {
        memcpy(signed_txn_byte_array + offset, signed_txn_struct->inputs[i].prev_txn_hash, PREV_TXN_HASH_LEN);
        offset += PREV_TXN_HASH_LEN;

        memcpy(signed_txn_byte_array + offset, signed_txn_struct->inputs[i].prev_output_index, PREV_OUTPUT_INDEX_LEN);
        offset += PREV_OUTPUT_INDEX_LEN;

        memcpy(signed_txn_byte_array + offset, (void *)&signed_txn_struct->inputs[i].script_len, 1);
        offset += 1;

        // printf("\n\n\n");
        // print_uint_8(signed_txn_byte_array,offset);
        // printf("\n\n\n");

        memcpy(signed_txn_byte_array + offset, signed_txn_struct->inputs[i].script, signed_txn_struct->inputs[i].script_len);
        offset += signed_txn_struct->inputs[i].script_len;
        memcpy(signed_txn_byte_array + offset, signed_txn_struct->inputs[i].squence, SEQ_LEN);
        offset += SEQ_LEN;
    }
    memcpy(signed_txn_byte_array + offset, (void *)&signed_txn_struct->no_of_outputs, 1);
    offset += 1;

    for (uint8_t i = 0; i < signed_txn_struct->no_of_outputs; i++)
    {
        memcpy(signed_txn_byte_array + offset, signed_txn_struct->outputs[i].value, VALUE_LEN);
        offset += VALUE_LEN;
        memcpy(signed_txn_byte_array + offset, (void *)&signed_txn_struct->outputs[i].script_len, SCRIPT_LENGTH_LEN);
        offset += SCRIPT_LENGTH_LEN;
        memcpy(signed_txn_byte_array + offset, signed_txn_struct->outputs[i].script_public_key, signed_txn_struct->outputs[i].script_len);
        offset += signed_txn_struct->outputs[i].script_len;
    }
    memcpy(signed_txn_byte_array + offset, signed_txn_struct->lock_time, LOCKTIME_LEN);
    offset += LOCKTIME_LEN;

    return signed_txn_byte_array;
}

int8_t *unsigned_to_signed(int8_t *unsigned_txn_string, uint32_t unsigned_txn_byte_len, int8_t *metadata_txn_string, uint32_t metadata_txn_byte_array_lenght, int8_t *mnemonics_string, uint32_t mnemonics_len, uint32_t *signed_txn_len)
{

    int8_t *passphrase_string = "";
    uint32_t passphrase_len = 0;
    uint32_t offset = 0;
    uint32_t byte_array_length;
    uint8_t *byte_array;
    uint8_t *seed = (uint8_t *)malloc(SEED_SIZE);

    uint8_t *to_sign_byte_array;
    uint32_t to_sign_byte_array_length;

    uint8_t *script_sig;
    uint8_t digest[32];
    uint8_t sig[64];
    uint8_t der_sig[128];
    uint8_t der_sig_len;
    uint8_t sighash_code = 1;
    uint8_t pushdata_opcode_pub = 33;
    uint8_t pushdata_opcode_der;

    uint8_t script_sig_len;
    HDNode *node = (HDNode *)malloc(sizeof(HDNode));
    HDNode *chain_addr_node = (HDNode *)malloc(sizeof(HDNode));

    struct node *current_node;
    struct signed_txn *signed_txn_struct = (struct signed_txn *)malloc(sizeof(struct signed_txn));

    byte_array = string_to_byte_array(unsigned_txn_string, unsigned_txn_byte_len);
    byte_array_length = (unsigned_txn_byte_len + 1) / 2;
    struct unsigned_txn *unsigned_txn_struct = byte_array_to_unsigned_txn(byte_array, byte_array_length);

    byte_array = string_to_byte_array(metadata_txn_string, metadata_txn_byte_array_lenght);
    byte_array_length = (metadata_txn_byte_array_lenght + 1) / 2;
    struct txn_metadata *txn_metadata_struct = byte_array_to_txn_meta(byte_array, byte_array_length);

    mnemonic_to_seed(mnemonics_string, passphrase_string, seed, NULL);
    hdnode_from_seed(seed, SEED_SIZE, SECP256K1_NAME, node);
    //m/44'
    hdnode_private_ckd_prime(node, uint8_t_array_to_uint32_t(txn_metadata_struct->purpose_index));
    hdnode_fill_public_key(node);
    //m/44'/1'
    hdnode_private_ckd_prime(node, uint8_t_array_to_uint32_t(txn_metadata_struct->coin_index));
    hdnode_fill_public_key(node);
    //m/44'/1'/0'
    hdnode_private_ckd_prime(node, uint8_t_array_to_uint32_t(txn_metadata_struct->account_index));
    hdnode_fill_public_key(node);
    memcpy(signed_txn_struct->version, unsigned_txn_struct->version, VERSION_LEN);
    memcpy((void *)&signed_txn_struct->no_of_inputs, (void *)&unsigned_txn_struct->no_of_inputs, 1);
    memcpy((void *)&signed_txn_struct->no_of_outputs, (void *)&unsigned_txn_struct->no_of_outputs, 1);
    offset += VERSION_LEN + 2;
    signed_txn_struct->outputs = (struct txn_outputs *)malloc(sizeof(struct txn_outputs) * signed_txn_struct->no_of_outputs);
    uint16_t i = 0;
    while (i < signed_txn_struct->no_of_outputs)
    {
        memcpy(signed_txn_struct->outputs[i].value, unsigned_txn_struct->outputs[i].value, VALUE_LEN);
        memcpy((void *)&signed_txn_struct->outputs[i].script_len, (void *)&unsigned_txn_struct->outputs[i].script_len, 1);
        signed_txn_struct->outputs[i].script_public_key = (uint8_t *)malloc(signed_txn_struct->outputs[i].script_len);
        memcpy(signed_txn_struct->outputs[i].script_public_key, unsigned_txn_struct->outputs[i].script_public_key, signed_txn_struct->outputs[i].script_len);
        offset += VALUE_LEN + 1 + signed_txn_struct->outputs[i].script_len;
        i++;
    }

    memcpy(signed_txn_struct->lock_time, unsigned_txn_struct->lock_time, LOCKTIME_LEN);
    offset += LOCKTIME_LEN;
    struct unsigned_txn *temp;
    signed_txn_struct->inputs = (struct txn_inputs *)malloc(sizeof(struct txn_inputs) * signed_txn_struct->no_of_inputs);
    i = 0;
    while (i < signed_txn_struct->no_of_inputs)
    {
        memcpy(signed_txn_struct->inputs[i].prev_txn_hash, unsigned_txn_struct->inputs[i].prev_txn_hash, PREV_TXN_HASH_LEN);
        memcpy(signed_txn_struct->inputs[i].prev_output_index, unsigned_txn_struct->inputs[i].prev_output_index, INDEX_SIZE);
        memcpy(signed_txn_struct->inputs[i].squence, unsigned_txn_struct->inputs[i].squence, SEQ_LEN);
        offset += PREV_TXN_HASH_LEN + PREV_OUTPUT_INDEX_LEN + SEQ_LEN;

        memcpy(chain_addr_node, node, sizeof(HDNode));
        hdnode_private_ckd(chain_addr_node, uint8_t_array_to_uint32_t(txn_metadata_struct->inputs[i].chain_index));
        hdnode_fill_public_key(chain_addr_node);

        hdnode_private_ckd(chain_addr_node, uint8_t_array_to_uint32_t(txn_metadata_struct->inputs[i].address_index));
        hdnode_fill_public_key(chain_addr_node);
        to_sign_byte_array = serialise_unsigned_txn(unsigned_txn_struct, i, &to_sign_byte_array_length);
        print_uint_8(to_sign_byte_array, to_sign_byte_array_length);
        sha256_Raw(to_sign_byte_array, to_sign_byte_array_length, digest);
        sha256_Raw(digest, 32, digest);
        printf("Digest: ");
        print_uint_8(digest, 32);
        ecdsa_sign_digest(&secp256k1, chain_addr_node->private_key, digest, sig, NULL, NULL);
        printf("Private Key: ");
        print_uint_8(chain_addr_node->private_key, 32);
        printf("Public Key: ");
        print_uint_8(chain_addr_node->public_key, 32);
        der_sig_len = ecdsa_sig_to_der(sig, der_sig);
        printf("SIG : ");
        print_uint_8(sig, 64);
        uint8_t script_sig_len = der_sig_len + 36;
        script_sig = (uint8_t *)malloc(script_sig_len);
        memset(script_sig, der_sig_len + 1, 1);
        memcpy(script_sig + 1, der_sig, der_sig_len);
        memset(script_sig + 1 + der_sig_len, 0x1, 1);
        memset(script_sig + 1 + der_sig_len + 1, 0x21, 1);
        memcpy(script_sig + 1 + der_sig_len + 1 + 1, chain_addr_node->public_key, 33);
        signed_txn_struct->inputs[i].script = (uint8_t *)malloc(script_sig_len);
        memcpy(signed_txn_struct->inputs[i].script, script_sig, script_sig_len);
        memcpy((void *)&signed_txn_struct->inputs[i].script_len, (void *)&script_sig_len, 1);
        offset += script_sig_len + 1;
        i++;
    }
    uint8_t *signed_txn_byte_array = serialise_signed_txn(signed_txn_struct, offset);
    *signed_txn_len = offset;

    print_signed_txn(*signed_txn_struct);
    return signed_txn_byte_array;
}