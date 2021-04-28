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