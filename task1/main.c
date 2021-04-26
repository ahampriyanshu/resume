#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <inttypes.h>
#include "crypto/bip39.h"

// Do display ongoing porcess
static void progress_callback(uint32_t pos, uint32_t len)
{
	printf("%" PRIu32 " / ", pos);
	printf("%" PRIu32 " ... \n", len);
}

// Driver Code
int main(void)
{
	const char *passphrase = "";
	int seedlength = 64;
	const char *mnemonic = "garden reject beauty inch scissors rifle amazing couch bacon multiply swim poverty impose spray ugly term stamp prevent nothing mutual awful project wrist movie";
	uint8_t seed[seedlength];

	printf("Mnemonic : %s\nGenerating Seed ... \n", mnemonic);

	mnemonic_to_seed(mnemonic, passphrase, seed, progress_callback);

	printf("Your seed is : ");
	for (size_t i = 0; i < seedlength; i++)
	{
		printf("%02x", seed[i]);
	}
	printf("\n");

	return 0;
}