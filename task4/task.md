{ "nonce": "0x00", "gasLimit": "0x5208", "gasPrice": "0x430e2340", "to": "0x7f8f2c6ab110acc28ecd9d2ab19166e455455a07", "value": "2c68af0bb140000", "data": "0x", "chainId": 3 }


0xf86b8084430e2340825208947f8f2c6ab110acc28ecd9d2ab19166e455455a078802c68af0bb1400008029a05b584ffb6b860aa888122d11a0cc009dce8d6cae8efb81bb0823d7e2281a3824a01ff1cbd324fc8a6145a32538bb544e00754449b6d54330dd765fa7bb21a9d621

# task 4

* Search for how ethereum address is generated from public key
* Convert signed trans from my ether wallet to unsigned txn
* Code for RLP encoding
* Hash the unsigned txn 
* Sign the digest using the private key
* Generate V using
* Create RLP encoded signed txn from the derived R and S values
* Broadcast the signed txn using ethers scan
