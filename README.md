# Efficient Noncommutative KEMs from Twisted Dihedral Group Ring
This repository contains the implementations accompanying the article

## Provide reference implementation in C for the proposed KEMs in our paper: DiTRU $^+$,  E-DiTRU $^+$, and DiTRU $^{\phi+}$. Further, we complete the implemntations of the KEMS for [DiTRU](https://eprint.iacr.org/2024/805) and  [Ei-TRU](https://eprint.iacr.org/2024/1721.pdf).

* The code is written based on NTRU submission to the first and third round of NIST with the required modifications for the new constructions.

# Requirements

* C compilier like GCC


# Description of files
Short description of the content:

* folder `NTRU-revised` contains three sub-folders: `ntru2048587`, `ntru2048886`, and `ntru40961109` completes the implementation for the KEM of NTRU revised parameter sets that target the security levels 1, 3, and 5, respectively.

* folder `DiTRU` completes the implementation for the KEM of DiTRU that target the security levels 1, 3, and 5, respectively.


* folder `Ei-TRU` contains two sub-floders `negligible_decryption_failure` and `no_decrtyption_failure`. The first sub-folder `negligible_decryption_failure` in its turn contains three sub-folders: `Ei_Tru-109_701`, `Ei_Tru_157_1013`, and `Ei_Tru_211_1361` that target the security levels 1, 3, and 5, respectively, and allow for negligible decryption failure.
The second sub-folder `no_decryption_failure` contains three sub-folders: `Ei_TRU_127_2039`, `Ei_TRU_181_2039`, and `Ei_TRU_241_3863` that do not allow decryption failure and target the levels of security 1, 3, and 5.


* folder `NTRU-third-round` contains three sub-folders: `ntruhps2048509`, `ntruhps2048677`, and `ntruhps4096821`: the parameter sets as have been proposed in the third-round submission of NIST.

* folder `DiTRU-plus-our` provides the KEM of our construction and contains five sub-folders `ditru2048293`, `ditru2048421`, `ditru2048443`, `ditru4096547`, and `ditru4096557` and achieve security levels as discussed in the paper.

* folder `Ei-DiTRU-our` provides the KEM of our construction and constains three sub-folders targeting the first, third, and fifth levels of security.

* folder `DPKE-KEM_our` contains two sub-folders `NTRU-HPS-like` and `Standard-Parametersets`. The first sub-folder in its turn contais three sub-folders: `ditru2048269`, `ditru2048347`, and `ditru4096419` that provides KEMs from DPKE targeting security levels similar to those proposed in NTRU-HPS third round. While, the second sub-folder provides the parameter sets that targets the security levels 1, 3, and 5 for the KEM from the DPKE over the twisted-dihedral group.




# How to use

Change the directory to the directory of one of the parameter sets like `ditru2048541`.

Disable Turbo boost and multi-threading to re-produce our results.

Run `make ` and then an executable file will be generated.

Run the executable file by typing in the command line `./main` or `taskset 0x1 ./main` to run the program on a specific core.

The program will be executed, and two files will be generated. 

1. `request file` contains: 
    - `count`: a counter for the generated example.
    - `seed`: a random seet to generate the corresponding key later.
    

2. `response file` for the corresponding request file generates:
    - `sk`: a secret key.
    - `pk`: a public key.
    - `ct`: the ciphertext corresponding to encrypting the message in the request file.
    - `ss`: the shared secret established after running the KEM.

Finally, the average CPU cycles to generate the keypair, encapsulation, and decapsulation of the key are calculated after generating many samples.
