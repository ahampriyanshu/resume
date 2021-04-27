#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <inttypes.h>
#include "crypto/bip39.h"
#include "crypto/bip32.h"

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

// Driver Code
int main(void)
{
	const char *mnemonic = "machine ring topic ladder damage stem client cage dust feed attack young audit drum distance lava torch iron absurd female place aisle title gauge";
	const char *passphrase = "";
	int seedlength = 64;
	uint8_t seed[seedlength];
	HDNode node , node1;
	char private[XPUB_MAXLEN];
	char public[XPUB_MAXLEN];
	char address[MAX_ADDR_SIZE];
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
	printf("Bitcoin Coin Version : %x(Private), %x(Public)\n", VERSION_PRIVATE, VERSION_PUBLIC);
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
	printf("Deriviation Path m/44'/1'/0'/0/0 \n");
	hdnode_private_ckd_prime(&node, 0x8000002C);
	hdnode_private_ckd_prime(&node, 0x80000001);
	hdnode_private_ckd_prime(&node, 0);
	hdnode_private_ckd(&node, 0);
	node1 = node;

	hdnode_private_ckd(&node, 1);
	printf("Recieve Derived Public Key: ");
	hdnode_fill_public_key(&node);
	print_u8(node.public_key);
	hdnode_get_address(&node, 0x6F, address, MAX_ADDR_SIZE);
	printf("Recieve Address : %s\n",address);
	hdnode_private_ckd(&node1, 0);
	printf("Change Derived Public Key: ");
	hdnode_fill_public_key(&node1);
	print_u8(node1.public_key);
	hdnode_get_address(&node1, 0x6F, address, MAX_ADDR_SIZE);
	printf("Change Address : %s\n",address);
	printf("\n");
	return 0;
}