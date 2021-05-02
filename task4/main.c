#include "utils.h"
#include "RLP.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <inttypes.h>
#include "crypto/bip39.h"
#include "crypto/bip32.h"
#include "keccak.h"

#define VERSION_PUBLIC 0x0488b21e
#define VERSION_PRIVATE 0x0488ade4
#define XPUB_MAXLEN 112
#define BN256_STR_LEN 64

// Do display ongoing porcess
static void progress_callback(uint32_t pos, uint32_t len)
{
	// printf("%" PRIu32 " / ", pos);
	// printf("%" PRIu32 " ... \n", len);
}

void print_u8(uint8_t *s) {
    size_t len = strlen((char*)s);
    for(size_t i = 0; i < len; i++) {
        printf("%02x", s[i]);
    }
    printf("\n");
}

int wallet_ethereum_assemble_tx(EthereumSignTx *msg, EthereumSig *tx, uint64_t *rawTx) {
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

void assembleTx() {
    static char rawTx[256];
    EthereumSignTx tx;
    EthereumSig signature;
    uint64_t raw_tx_bytes[24];
    const char *nonce = "00";
    const char *gas_price = "430e2340";
    const char *gas_limit = "5208";
    const char *to = "7f8f2c6ab110acc28ecd9d2ab19166e455455a07";
    const char *value = "2c68af0bb140000";
    const char *data = "00";
    const char *r = "09ebb6ca057a0535d6186462bc0b465b561c94a295bdb0621fc19208ab149a9c";
    const char *s = "440ffd775ce91a833ab410777204d5341a6f9fa91216a6f3ee2c051fea6a0428";
    uint32_t v = 27;

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

    signature.signature_v = 27;

    signature.signature_r.size = size_of_bytes(strlen(r));
    hex2byte_arr(r, strlen(r), signature.signature_r.bytes, signature.signature_r.size);

    signature.signature_s.size = size_of_bytes(strlen(s));
    hex2byte_arr(s, strlen(s), signature.signature_s.bytes, signature.signature_s.size);

    int length = wallet_ethereum_assemble_tx(&tx, &signature, raw_tx_bytes);
    int8_to_char((uint8_t *) raw_tx_bytes, length, rawTx);
    printf("raw transaction: %s\n", rawTx);
}

int main() {
    const char *mnemonic = "machine ring topic ladder damage stem client cage dust feed attack young audit drum distance lava torch iron absurd female place aisle title gauge";
	const char *passphrase = "";
	int seedlength = 64;
	uint8_t seed[seedlength];
	HDNode node , node1;
	char private[XPUB_MAXLEN];
	char public[XPUB_MAXLEN]; 
    uint8_t address[20];
    uint32_t fingerprint = 0x00000000;
	const char curve[] = "secp256k1";
	mnemonic_to_seed(mnemonic, passphrase, seed, progress_callback);
	hdnode_from_seed(seed, 64, curve, &node);
	printf("\n");
	printf("BIP39 Mnemonic: ");
	puts(mnemonic);
	printf("BIP39 Seed: ");
	for (size_t i = 0; i < seedlength; i++)
	{
		printf("%02x", seed[i]);
	}
	printf("\n"); 
	printf("Fingerprint : %08x\n", fingerprint);
	printf("Master Private Key: ");
	print_u8(node.private_key);
	printf("Master Chain Code: ");
	for (size_t i = 0; i < 31; i++)
	{
		printf("%02x", node.chain_code[i]);
	}
	printf("\n");
	printf("Master Public Key: ");
	hdnode_fill_public_key(&node);
	print_u8(node.public_key);
	printf("BIP32 Root Key: ");
	hdnode_serialize_private(&node, fingerprint, VERSION_PRIVATE, private,sizeof(private));
	puts(private);
	hdnode_deserialize_private(private, VERSION_PRIVATE, curve, &node, NULL);
	printf("Deriviation Path m/44'/60'/0'/0/0 \n");
	hdnode_private_ckd_prime(&node, 44);
	hdnode_private_ckd_prime(&node, 60);
	hdnode_private_ckd_prime(&node, 0);
	hdnode_private_ckd(&node, 0); 
	hdnode_private_ckd(&node, 0);
    printf("Private Key: ");
	print_u8(node.private_key);
	printf("Public Key: ");
	hdnode_fill_public_key(&node);
    print_u8(node.public_key); 
    printf("Wallet Address: ");
    hdnode_get_ethereum_pubkeyhash(&node, address);
    print_u8(address);
    return 0;
}
