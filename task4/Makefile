src  = crypto/bignum.c crypto/ecdsa.c crypto/curves.c crypto/secp256k1.c crypto/nist256p1.c crypto/rand.c crypto/hmac.c crypto/bip32.c crypto/bip39.c crypto/pbkdf2.c crypto/base58.c crypto/base32.c
src += crypto/address.c
src += crypto/script.c
src += crypto/ripemd160.c
src += crypto/sha2.c
src += crypto/sha3.c
src += crypto/hasher.c
src += crypto/aes/aescrypt.c crypto/aes/aeskey.c crypto/aes/aestab.c crypto/aes/aes_modes.c
src += crypto/ed25519-donna/curve25519-donna-32bit.c crypto/ed25519-donna/curve25519-donna-helpers.c crypto/ed25519-donna/modm-donna-32bit.c
src += crypto/ed25519-donna/ed25519-donna-basepoint-table.c crypto/ed25519-donna/ed25519-donna-32bit-tables.c crypto/ed25519-donna/ed25519-donna-impl-base.c
src += crypto/ed25519-donna/ed25519.c crypto/ed25519-donna/curve25519-donna-scalarmult-base.c crypto/ed25519-donna/ed25519-sha3.c crypto/ed25519-donna/ed25519-keccak.c
src += crypto/monero/base58.c
src += crypto/monero/serialize.c
src += crypto/monero/xmr.c
src += crypto/monero/range_proof.c
src += crypto/blake256.c
src += crypto/blake2b.c crypto/blake2s.c
src += crypto/chacha_drbg.c
src += crypto/groestl.c
src += crypto/chacha20poly1305/chacha20poly1305.c crypto/chacha20poly1305/chacha_merged.c crypto/chacha20poly1305/poly1305-donna.c crypto/chacha20poly1305/rfc7539.c
src += crypto/rc4.c
src += crypto/nem.c
src += crypto/segwit_addr.c crypto/cash_addr.c
src += crypto/memzero.c
src += crypto/shamir.c
src += crypto/hmac_drbg.c
src += crypto/rfc6979.c
src += crypto/slip39.c
src += crypto/schnorr.c

obj = $(src:.c=.o)

all: subfolder main

main: main.o RLP.o utils.o $(obj)
	$(CC) -o $@ $^

main.o: main.c
	gcc -c main.c

RLP.o: RLP.c
	gcc -c RLP.c

utils.o: utils.c
	gcc -c utils.c

subfolder:
	$(MAKE) -C crypto/

clean:
	cd crypto && $(MAKE) clean
	rm -f *.o main