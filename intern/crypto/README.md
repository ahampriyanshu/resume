
## Tasks

### Task 1 : To implement ``Shamir Secret Sharing Alogithm`` using C.

![task 1](https://github.com/ahampriyanshu/meta/blob/main/intern/1.png?raw=true)
[Source Code]()

### Task 2 : To understand how ``make`` works and then to calculate a ``BIP39 Seed`` using 24 bip mnemonics.

![task 2](https://github.com/ahampriyanshu/meta/blob/main/intern/2.png?raw=true)
[Source Code]()

### Task 3 : To derive ``public key``, ``private key``, ``chain node`` and ``reciever and change address`` for ``Bitcoin Testnet`` for derivation path ``m/44'/1'/0`/0/``

* Derive address from public and private from mnemonics
* The first node derived is the master node
* For master node the index is 0000000 
* For purpose node we have to passed index as 8000002C
* For coin => index => 8000001 (testnet)
* For account node => 00000000
* Chain node :
  - 00000001 (change address node)
  - 00000000 (recieve address node)

![task 3](https://github.com/ahampriyanshu/meta/blob/main/intern/3.png?raw=true)
[Source Code]()

### Task 4 : To sign an unsigned ``bitcoin testnet`` transaction
* Generate unsigned trans using extendended public key of account node
* complete byte_array_to_unsigned_txn() to fill the unsigned txn struct
        2.1 Use malloc for input and ouput struct inside unsigned_strcut
* Complete serialize_unsigned_txn_to_sign() func to generate the serializes unsigned txn to sign corresponding to an input
* Use sha256_raw to generate double hash of the serialize unsigned transation (call the func twice .) (next time kind of recusrive)
* Use ecdsa_sign_digest() to genrate R and S value using private key corresonding to the input (88thline)
* Generate script_sig using ecdsa_sig_to_der() (klmoney article)
* Replace script sig with the script public key for rach input inside the unsigned txn key
* to fill the signed txn strcut (70 line)

0200000001f5db32c555ba1cb8bc58dfa364e4d476f3f138b5fa854f212273d484be3d5e13010000006a473044022052ce33ff38e1cd81b64fa122bf7f6910823218a808ec99e2fb9591eebbfd3fba02200508750d0325f08dc9d00293e93afae6f0f33a8420259ef417a4746986470046012103279fc9ed6eb0a7ea81747c4259431d4d1ee35ef8f0cbc7eaa9acd18144550c85ffffffff0210270000000000001976a914f03b86b4eb2cacfe0718e28bcb9f00aed168bf4a88ac077a1600000000001976a91418b9420d3e7f85d50d150156bc33c1bbe45c748c88ac00000000

![task 4](https://github.com/ahampriyanshu/meta/blob/main/intern/4.png?raw=true)
[Source Code]()

### Task 5 : To sign a raw ``Ethereum (Ropsten)`` transaction 
* Search for how ethereum address is generated from public key
* Convert signed txn from my ether wallet to unsigned txn
* Code for RLP encoding
* Hash the unsigned txn 
* Sign the digest using the private key
* Generate V using
* Create RLP encoded signed txn from the derived R and S values
* Broadcast the signed txn using ethers scan

#### Transcation Details : 
0xf86b02847735940082520894c0095a58489ba23cb5c6808dc0bbbf1cdca32aca8802c68af0bb140000802aa052975d44a183eff9c495cd1b50aa17ad5536552b2007cb9a2a58c1abf74614d8a051b670142c71b8feadea5e5cfde8c5a0c61c7504f1de4b32e9f8ae50b5eb5afd

0xf86b02847735940082520894c0095a58489ba23cb5c6808dc0bbbf1cdca32aca8802c68af0bb140000802aa052975d44a183eff9c495cd1b50aa17ad5536552b2007cb9a2a58c1abf74614d8a051b670142c71b8feadea5e5cfde8c5a0c61c7504f1de4b32e9f8ae50b5eb5afd


{ "nonce": "0x02", "gasLimit": "0x5208", "gasPrice": "0x77359400", "to": "0xc0095a58489ba23cb5c6808dc0bbbf1cdca32aca", "value": "2c68af0bb140000", "data": "0x", "chainId": 3 }

![task 5](https://github.com/ahampriyanshu/meta/blob/main/intern/5.png?raw=true)
[Source Code]()

* Copy and paste the **crypto** library before executing the Makefile.

## Resources : 
* [https://iancoleman.io/bip39](https://iancoleman.io/bip39)
* [http://bip32.org](http://bip32.org)
* [https://coinb.in/](https://coinb.in/)
* [https://www.blockchain.com/explorer](https://www.blockchain.com/explorer)
* [https://live.blockcypher.com/](https://live.blockcypher.com/)
* [https://bitcoinfaucet.uo1.net/](https://bitcoinfaucet.uo1.net)
* [https://www.myetherwallet.com/](https://www.myetherwallet.com/)
* [https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki)
* [https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki](https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki)
* [https://github.com/bitcoin/bips/blob/master/bip-0044.mediawiki](https://github.com/bitcoin/bips/blob/master/bip-0044.mediawiki)
* [https://learnmeabitcoin.com/technical/derivation-paths#bip-44-m440000](https://learnmeabitcoin.com/technical/derivation-paths#bip-44-m440000)
* [https://galactictalk.org/d/549-secret-key-seed-from-bip39/38](https://galactictalk.org/d/549-secret-key-seed-from-bip39/38)
* [https://lsongnotes.wordpress.com/2018/01/14/signing-an-ethereum-transaction-the-hard-way/](https://lsongnotes.wordpress.com/2018/01/14/signing-an-ethereum-transaction-the-hard-way/)
* [https://medium.com/swlh/understanding-data-payloads-in-ethereum-transactions-354dbe995371](https://medium.com/swlh/understanding-data-payloads-in-ethereum-transactions-354dbe995371)
* [https://lsongnotes.wordpress.com/2017/12/21/ethereum-transaction-structure/](https://lsongnotes.wordpress.com/2017/12/21/ethereum-transaction-structure/)
* [https://eth.wiki/en/fundamentals/rlp](https://eth.wiki/en/fundamentals/rlp)
* [https://github.com/ethereum/EIPs/blob/master/EIPS/eip-155.md](https://github.com/ethereum/EIPs/blob/master/EIPS/eip-155.md)
* [https://www.oreilly.com/library/view/mastering-bitcoin/9781491902639/ch04.html](https://www.oreilly.com/library/view/mastering-bitcoin/9781491902639/ch04.html)
* [https://www.mobilefish.com/services/cryptocurrency/cryptocurrency.html](https://www.mobilefish.com/services/cryptocurrency/cryptocurrency.html)
* [https://ethereum.stackexchange.com/questions/3386/create-and-sign-offline-raw-transactions/3392](https://ethereum.stackexchange.com/questions/3386/create-and-sign-offline-raw-transactions/3392)
* [https://hackernoon.com/how-to-generate-ethereum-addresses-technical-address-generation-explanation-25r3zqo](https://hackernoon.com/how-to-generate-ethereum-addresses-technical-address-generation-explanation-25r3zqo)
* [https://www.cs.utexas.edu/users/moore/acl2/manuals/current/manual/index-seo.php/BITCOIN____BIP32-PATH](https://www.cs.utexas.edu/users/moore/acl2/manuals/current/manual/index-seo.php/BITCOIN____BIP32-PATH)
* [https://medium.com/coinmonks/mnemonic-generation-bip39-simply-explained-e9ac18db9477](https://medium.com/coinmonks/mnemonic-generation-bip39-simply-explained-e9ac18db9477)
* [https://www.soroushjp.com/2014/12/20/bitcoin-multisig-the-hard-way-understanding-raw-multisignature-bitcoin-transactions/](https://www.soroushjp.com/2014/12/20/bitcoin-multisig-the-hard-way-understanding-raw-multisignature-bitcoin-transactions/)
* [http://www.righto.com/2014/02/bitcoins-hard-way-using-raw-bitcoin.html](http://www.righto.com/2014/02/bitcoins-hard-way-using-raw-bitcoin.html)
* [https://github.com/prettymuchbryce/hellobitcoin](https://github.com/prettymuchbryce/hellobitcoin)
* [https://gist.github.com/gavinandresen/3966071](https://gist.github.com/gavinandresen/3966071)
* [https://medium.com/coinmonks/build-p2sh-address-and-spend-its-fund-in-golang-1a03a4131512](https://medium.com/coinmonks/build-p2sh-address-and-spend-its-fund-in-golang-1a03a4131512)