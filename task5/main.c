#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "secp256k1.h"
#include "RLP.h"
#include "utils.h"
#include "sha3.h"

#define SIGNED_MAX_LEN 3000

struct RawTxStruct
{
    const char *nonce;
    const char *gas_price;
    const char *gas_limit;
    const char *to;
    const char *value;
    const char *data;
    const char *r;
    const char *s;
    uint32_t v;
};

void print_u8(unsigned char *array, uint8_t length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%02x", array[i]);
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

int wallet_ethereum_assemble_tx(EthereumSignTx *msg, EthereumSig *tx, uint64_t *rawTx)
{
    EncodeEthereumSignTx new_msg;
    EncodeEthereumTxRequest new_tx;
    memset(&new_msg, 0, sizeof(new_msg));
    memset(&new_tx, 0, sizeof(new_tx));
    wallet_encode_element(msg->nonce.bytes, msg->nonce.size,
                          new_msg.nonce.bytes, &(new_msg.nonce.size), false);
    wallet_encode_element(msg->gas_price.bytes, msg->gas_price.size,
                          new_msg.gas_price.bytes, &(new_msg.gas_price.size), false);
    wallet_encode_element(msg->gas_limit.bytes, msg->gas_limit.size,
                          new_msg.gas_limit.bytes, &(new_msg.gas_limit.size), false);
    wallet_encode_element(msg->to.bytes, msg->to.size, new_msg.to.bytes,
                          &(new_msg.to.size), false);
    wallet_encode_element(msg->value.bytes, msg->value.size,
                          new_msg.value.bytes, &(new_msg.value.size), false);
    wallet_encode_element(msg->data_initial_chunk.bytes,
                          msg->data_initial_chunk.size, new_msg.data_initial_chunk.bytes,
                          &(new_msg.data_initial_chunk.size), false);
    wallet_encode_int(tx->signature_v, &(new_tx.signature_v));
    wallet_encode_element(tx->signature_r.bytes, tx->signature_r.size,
                          new_tx.signature_r.bytes, &(new_tx.signature_r.size), true);
    wallet_encode_element(tx->signature_s.bytes, tx->signature_s.size,
                          new_tx.signature_s.bytes, &(new_tx.signature_s.size), true);
    int length = wallet_encode_list(&new_msg, &new_tx, rawTx);
    return length;
}

void fill_txn(struct RawTxStruct rts, char *rlpre)
{
    static char rawTx[256];
    EthereumSignTx tx;
    EthereumSig signature;
    uint64_t raw_tx_bytes[24];

    const char *nonce = rts.nonce;
    const char *gas_price = rts.gas_price;
    const char *gas_limit = rts.gas_limit;
    const char *to = rts.to;
    const char *value = rts.value;
    const char *data = rts.data;
    const char *r = rts.r;
    const char *s = rts.s;
    uint32_t v = rts.v;

    tx.nonce.size = size_of_bytes(strlen(nonce));
    hex2byte_arr(nonce, strlen(nonce), tx.nonce.bytes, tx.nonce.size);
    tx.gas_price.size = size_of_bytes(strlen(gas_price));
    hex2byte_arr(gas_price, strlen(gas_price), tx.gas_price.bytes, tx.gas_price.size);
    tx.gas_limit.size = size_of_bytes(strlen(gas_limit));
    hex2byte_arr(gas_limit, strlen(gas_limit), tx.gas_limit.bytes, tx.gas_limit.size);
    tx.to.size = size_of_bytes(strlen(to));
    hex2byte_arr(to, strlen(to), tx.to.bytes, tx.to.size);
    tx.value.size = size_of_bytes(strlen(value));
    hex2byte_arr(value, strlen(value), tx.value.bytes, tx.value.size);
    tx.data_initial_chunk.size = size_of_bytes(strlen(data));
    hex2byte_arr(data, strlen(data), tx.data_initial_chunk.bytes,
                 tx.data_initial_chunk.size);
    signature.signature_v = v;
    signature.signature_r.size = size_of_bytes(strlen(r));
    hex2byte_arr(r, strlen(r), signature.signature_r.bytes, signature.signature_r.size);
    signature.signature_s.size = size_of_bytes(strlen(s));
    hex2byte_arr(s, strlen(s), signature.signature_s.bytes, signature.signature_s.size);
    int length;
    length = wallet_ethereum_assemble_tx(&tx, &signature, raw_tx_bytes);
    int8_to_char((uint8_t *)raw_tx_bytes, length, rawTx);
    sprintf(rlpre, "%s", rawTx);
}

int main()
{

    uint8_t buf[32];
    static secp256k1_context *ctx = NULL;
    ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    unsigned char *privateKeyStr = "e66943565a48c4ef5ab0e69f4e06282ac873d97fb78bf97d9d4b45b210effc9f";
    unsigned char privateKey[32];
    hex2byte_arr(privateKeyStr, 64, privateKey, 32);

    printf("Private Key: ");
    print_u8(privateKey, 32);

    secp256k1_pubkey publicKey;
    secp256k1_ec_pubkey_create(ctx, &publicKey, privateKey); // fill public Key
    unsigned char publicKeyBuf[65];
    size_t clen = 65;
    unsigned char publicKeyStr[64]; // after removing front 04
    secp256k1_ec_pubkey_serialize(ctx, &publicKeyBuf, &clen, &publicKey, SECP256K1_EC_UNCOMPRESSED);
    strncpy(publicKeyStr, publicKeyBuf + 1, 64);

    printf("Pulic Key: ");
    print_u8(publicKeyStr, 32);

    sha3_HashBuffer(256, SHA3_FLAGS_KECCAK, &publicKeyStr, 64, buf, sizeof(buf));
    unsigned char address[20];
    strncpy(address, buf + 12, 20); // last 20 bytes from the hash
    printf("Address: ");
    print_u8(address, 20);


    struct RawTxStruct rts;
    rts.nonce = "02";
    rts.gas_price = "77359400";
    rts.gas_limit = "5208";
    rts.to = "c0095a58489ba23cb5c6808dc0bbbf1cdca32aca";
    rts.value = "2c68af0bb140000";
    rts.data = "";
    rts.r = "0";
    rts.s = "0";
    rts.v = 3; // chainID (Ropsten)
    char unsignedTxn[200];
    fill_txn(rts, unsignedTxn);
    unsigned char rlp[100];
    hex2byte_arr(unsignedTxn, strlen(unsignedTxn), rlp, strlen(unsignedTxn) / 2);
    printf("\nUnsigned Txn: ");
    print_u8(rlp, strlen(unsignedTxn) / 2);

    uint8_t msgHashBuf[32];
    sha3_HashBuffer(256, SHA3_FLAGS_KECCAK, &rlp, strlen(unsignedTxn) / 2, msgHashBuf, sizeof(msgHashBuf));
    printf("\nMsgHash: ");
    print_u8(msgHashBuf, 32);

    unsigned char rs[64];
    secp256k1_ecdsa_signature signature;
    secp256k1_ecdsa_sign(ctx, &signature, msgHashBuf, privateKey, NULL, NULL);
    secp256k1_ecdsa_signature_serialize_compact(ctx, rs, &signature);

    unsigned char r[65];
    unsigned char s[65];

    int index = 0;
    for (int i = 0; i < 32; i++)
    {
        index += sprintf(r + index, "%02x", rs[i]);
    };
    printf("r: %s\n", r);

    index = 0;
    for (int i = 32; i < 64; i++)
    {
        index += sprintf(s + index, "%02x", rs[i]);
    };
    printf("s: %s\n", s);

    rts.r = r;
    rts.s = s;
    rts.v = 28 + rts.v * 2 + 8;
    
    char signedTxn[SIGNED_MAX_LEN];
    fill_txn(rts, signedTxn);
    printf("\nSigned Txn: 0x%s \n", signedTxn);

    return 0;
}
