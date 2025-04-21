# An Efficient Noncommutative NTRU from Semi-direct Product
This repository contains the scripts accompanying the article

## Provides reference implementation in C for our construction of a noncommutative analog of NTRU
## The construction utilizes the group ring of a semidirect product of cyclic groups over the ring of Eisenstein integers.


* The code is written based on NTRU submission to the first and third round of NIST with the required modifications for our construction.

# Requirements

* C compilier like GCC


# Description of files
Short description of the content:
* folder 'Ei_TRU_main' two sub-folders: `negligible_decryption_failure` and `no_decryption_failure`; each folder in its turn contains three sub-folders that defines the implementation for this work that targets the security levels 1.3. and 5, respectively.

* folder `Comparasion_to` contains three sub-folders:
`DiTRU`, `NTUR-revised`, and `Ei-TRU-main_com` provides the parameter sets for DiTRU, NTRU, and this work that achieves the same level of security according to the same security evaluation criteria
, we use these implementations to compare the performance of the proposed cryptosystems while encrypting/decrypting messages of the same length.

# How to use

Change the directory to the directory of one of the parameter sets like `Ei_TRU_109_701`.

Run `make,` and then an executable file will be generated.

Run the executable file by typing in the command line `./main` or `taskset 0x1 ./main` to run the program on a specific core.

The program will be executed, and two files will be generated. 

1. `request file` contains: 
    - `count`: a counter for the generated example.
    - `seed`: a random seed to generate the corresponding key later.
    - `original message`: a message to be encrypted according to the CCA encryption scheme.

2. `response file` for the corresponding request file generates:
    - `sk`: a secret key.
    - `pk`: a public key.
    - `ct`: the ciphertext corresponding to encrypting the message in the request file.
    - `decrypted message`: decrypt the message that is supposed to be equal to the original message.

Finally, the average CPU cycles to generate the keypair, encrypt, and decrypt the message are calculated after generating all the examples.


For comparing the running time of this work with DiTRU/NTRU,

change the directory to the scheme you want to compare and similarly run the file as mentioned above. 