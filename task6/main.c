#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <inttypes.h>
#include "crypto/bip39.h"
#include "crypto/bip32.h"
#include "crypto/ecdsa.h"
#include "crypto/secp256k1.h"

#define VERSION_PUBLIC 0x043587CF
#define VERSION_PRIVATE 0x04358394
#define XPUB_MAXLEN 112
#define MAX_ADDR_SIZE 130

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

void calculate(const char *mnemonic,uint8_t *private[XPUB_MAXLEN], uint8_t *public[XPUB_MAXLEN] ){
	uint8_t sig[64], pub_key33[33], pub_key65[65], priv_key[32], msg[256], hash[32];
	const char *passphrase = "";
	int seedlength = 64;
	uint8_t seed[seedlength];
	HDNode node ;
    uint32_t fingerprint = 0x00000000;
	const char curve[] = "secp256k1";
	const ecdsa_curve * secp256k1;
	mnemonic_to_seed(mnemonic, passphrase, seed, progress_callback);
	hdnode_from_seed(seed, 64, curve, &node);
	printf("Mnemonic Phrase : \n");
	puts(mnemonic);
	// Deriviation Path m/44'/1'/0'/0/0
	hdnode_private_ckd_prime(&node, 0x8000002C);
	hdnode_private_ckd_prime(&node, 0x80000001);
	hdnode_private_ckd_prime(&node, 0);
	hdnode_private_ckd(&node, 0);
	hdnode_private_ckd(&node, 0);
	hdnode_fill_public_key(&node);
	printf("Compressed Public Key : \n");
	print_u8(node.public_key);
	ecdsa_uncompress_pubkey(secp256k1, node.public_key , pub_key65);
	memcpy(private, node.private_key, 33);
	memcpy(public, pub_key65, 65);
	printf("Private Key : \n");
	print_u8(private);
	printf("Uncompressed Public Key : \n");
	print_u8(public);
	printf("\n");
}

// Driver Code
int main(void)
{
	const char *mnemonic1 = "machine ring topic ladder damage stem client cage dust feed attack young audit drum distance lava torch iron absurd female place aisle title gauge";
	const char *mnemonic2 = "approve flight cage rebuild apple garbage tower unlock certain brief tunnel hockey federal couch divert picnic below grief grief feel intact enlist forest talk";
	const char *mnemonic3 = "table planet merry flip tourist stomach spatial hobby tongue dad devote blade assist mobile elephant stove average inspire core matrix poverty fee book canyon";
	uint8_t * private1[XPUB_MAXLEN];
	uint8_t * public1[XPUB_MAXLEN];
	uint8_t * private2[XPUB_MAXLEN];
	uint8_t * public2[XPUB_MAXLEN];
	uint8_t * private3[XPUB_MAXLEN];
	uint8_t * public3[XPUB_MAXLEN];
    uint8_t *redeemScript;
    redeemScript = (uint8_t*)malloc(1024);
	calculate(mnemonic1, private1, public1);
	calculate(mnemonic2, private2, public2);
	calculate(mnemonic3, private3, public3);
    uint8_t OP_2 = 0x52;
	uint8_t OP_3 = 0x53;
	uint8_t OP_CHECKMULTISIG = 0xae;
	uint8_t bytes_to_stack = 0x41;
	uint16_t length;
    uint16_t offset = 0;
    memcpy(redeemScript + offset, &OP_2, 1);
	offset += 1;
	memcpy(redeemScript + offset, &bytes_to_stack, 1);
	offset += 1;
	length = strlen((char*)public1);
	memcpy(redeemScript + offset, public1, length);
	offset += length;
	memcpy(redeemScript + offset, &bytes_to_stack, 1);
	offset += 1;
	length = strlen((char*)public2);
	memcpy(redeemScript + offset, public2, length);
	offset += length;
	memcpy(redeemScript + offset, &bytes_to_stack, 1);
	offset += 1;
	length = strlen((char*)public3);
	memcpy(redeemScript + offset, public3, length);
	offset += length;
	memcpy(redeemScript + offset, &OP_3, 1);
	offset += 1;
	memcpy(redeemScript + offset, &OP_CHECKMULTISIG, 1);
	offset += 1;
	printf("Redeem Script : \n");
	print_u8(redeemScript);
	char address[MAX_ADDR_SIZE];
	printf("P2SH Address : \n");
	ecdsa_get_address(redeemScript, 0x05, HASHER_SHA2_RIPEMD, HASHER_SHA2D, address, sizeof(address));
	puts(address);
	return 0;
}