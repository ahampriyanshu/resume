# 1st subTask :

* Derive address from public and private from mnemonics
* The first node derived is the master node
* For master node the index is 0000000 
* For purpose node we have to passed index as 8000002C
* For coin => index => 8000001 (testnet)
* For account node => 00000000
* Chain node :
        00000001 (change address node)
        00000000 (recieve address node)

# 2nd sub task

* To sign an unsigned transaction using crypto library

* 1 Generate unsigned trans using extendended public key of account node
* 2 complete byte_array_to_unsigned_txn() to fill the unsigned txn struct
        2.1 Use malloc for input and ouput struct inside unsigned_strcut
* 3 Complete serialize_unsigned_txn_to_sign() func to generate the serializes unsigned txn to sign corresponding to an input
* 4 Use sha256_raw to generate double hash of the serialize unsigned transation (call the func twice .) (next time kind of recusrive)
* 5 Use ecdsa_sign_digest() to genrate R and S value using private key corresonding to the input (88thline)
* 6 Generate script_sig using ecdsa_sig_to_der() (klmoney article)
* 7 Replace script sig with the script public key for rach input inside the unsigned txn key
* 8 to fill the signed txn strcut (70 line)

0200000001f5db32c555ba1cb8bc58dfa364e4d476f3f138b5fa854f212273d484be3d5e13010000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88acffffffff0210270000000000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88ac7f761600000000001976a91418b9420d3e7f85d50d150156bc33c1bbe45c748c88ac00000000

0200000001f5db32c555ba1cb8bc58dfa364e4d476f3f138b5fa854f212273d484be3d5e13010000006a473044022052ce33ff38e1cd81b64fa122bf7f6910823218a808ec99e2fb9591eebbfd3fba02200508750d0325f08dc9d00293e93afae6f0f33a8420259ef417a4746986470046012103279fc9ed6eb0a7ea81747c4259431d4d1ee35ef8f0cbc7eaa9acd18144550c85ffffffff0210270000000000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88ac077a1600000000001976a91418b9420d3e7f85d50d150156bc33c1bbe45c748c88ac00000000