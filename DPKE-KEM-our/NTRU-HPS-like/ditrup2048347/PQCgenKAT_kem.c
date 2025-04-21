
//
//  PQCgenKAT_kem.c
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rng.h"
#include "api.h"
#include "helper_print.h" 
#include "cpucycles.h"

#define	MAX_MARKER_LEN		50
#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4
#define CPUCYCLES (4.7*1000000000.0);

int		FindMarker(FILE *infile, const char *marker);
int		ReadHex(FILE *infile, unsigned char *A, int Length, char *str);
void	fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L);

int
main()
{
    char                fn_req[32], fn_rsp[32];
    FILE                *fp_req, *fp_rsp;
    unsigned char       seed[48];
    unsigned char       entropy_input[48];
    unsigned char       ct[tDiTRU_CIPHERTEXTBYTES], ss[tDiTRU_SHAREDKEYBYTES], ss1[tDiTRU_SHAREDKEYBYTES];
    int                 count;
    int                 done;
    unsigned char       pk[tDiTRU_PUBLICKEYBYTES], sk[tDiTRU_SECRETKEYBYTES];
    int                 ret_val;

    double execution_time;
    double execution_time_key = 0;
    double encryption_time = 0;
    double decryption_time = 0;
    unsigned long long start_key, end_key;
    unsigned long long start_enc, end_enc;
    unsigned long long start_dec, end_dec;
    unsigned long long start, end;
    unsigned long long timing_overhead;
// Create the polynomial r
    poly r;

    // Initialize the polynomial with some values
    for (int i = 0; i < ORDER; i++) {
        r.coeffs[i] = i;  // You can assign any values here
    }

    // Print the polynomial using the function from helper_print.c
   // print_poly_values(&r);  
    // Create the REQUEST file
    sprintf(fn_req, "PQCkemKAT_%d.req", tDiTRU_SECRETKEYBYTES);
    if ( (fp_req = fopen(fn_req, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }
    sprintf(fn_rsp, "PQCkemKAT_%d.rsp", tDiTRU_SECRETKEYBYTES);
    if ( (fp_rsp = fopen(fn_rsp, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_rsp);
        return KAT_FILE_OPEN_ERROR;
    }

    for (int i=0; i<48; i++)
        entropy_input[i] = i;
    
    timing_overhead = cpucycles_overhead();
    int trials = 1000;
    randombytes_init(entropy_input, NULL, 256);
    for (int i=0; i<trials; i++) {
        fprintf(fp_req, "count = %d\n", i);
        randombytes(seed, 48);
        fprintBstr(fp_req, "seed = ", seed, 48);
        fprintf(fp_req, "pk =\n");
        fprintf(fp_req, "sk =\n");
        fprintf(fp_req, "ct =\n");
        fprintf(fp_req, "ss =\n\n");
    }
    fclose(fp_req);

    //Create the RESPONSE file based on what's in the REQUEST file
    if ( (fp_req = fopen(fn_req, "r")) == NULL ) {
        printf("Couldn't open <%s> for read\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }

    fprintf(fp_rsp, "# %s\n\n", CRYPTO_ALGNAME);
    start = cpucycles_start();
    done = 0;
    do {
        if ( FindMarker(fp_req, "count = ") )
            fscanf(fp_req, "%d", &count);
        else {
            done = 1;
            break;
        }
        fprintf(fp_rsp, "count = %d\n", count);

        if ( !ReadHex(fp_req, seed, 48, "seed = ") ) {
            printf("ERROR: unable to read 'seed' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        fprintBstr(fp_rsp, "seed = ", seed, 48);

        randombytes_init(seed, NULL, 256);
        start_key = cpucycles_start();
        // Generate the public/private keypair
        if ( (ret_val = crypto_kem_keypair(pk, sk)) != 0) {
            printf("crypto_kem_keypair returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }

        end_key = cpucycles_stop();
        execution_time_key += ((double)(end_key - start_key));
        
        fprintBstr(fp_rsp, "pk = ", pk, tDiTRU_PUBLICKEYBYTES);
        fprintBstr(fp_rsp, "sk = ", sk,tDiTRU_SECRETKEYBYTES);
        

        start_enc = cpucycles_start();
        if ( (ret_val = crypto_kem_enc(ct, ss, pk)) != 0) {
            printf("crypto_kem_enc returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        end_enc = cpucycles_stop();
        encryption_time+= ((double)(end_enc - start_enc));

        fprintBstr(fp_rsp, "ct = ", ct, tDiTRU_CIPHERTEXTBYTES);
    
        start_dec = cpucycles_start();
        if ( (ret_val = crypto_kem_dec(ss1, ct, sk)) != 0) {
            printf("crypto_kem_dec returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        end_dec = cpucycles_stop();
        decryption_time+=((double)(end_dec-start_dec));
     
       
        fprintBstr(fp_rsp, "ss = ", ss1, tDiTRU_SHAREDKEYBYTES);

        if ( memcmp(ss, ss1, tDiTRU_SHAREDKEYBYTES) ) {
            printf("crypto_kem_dec returned bad 'ss' value\n");
            return KAT_CRYPTO_FAILURE;
        }

    } while ( !done );

    fclose(fp_req);
    fclose(fp_rsp);
    end = cpucycles_stop();

    unsigned long long total_cpu_cycles = ((end-start))/trials - timing_overhead;
    unsigned long long key_gen_cycles = ((execution_time_key))/trials -timing_overhead;
    unsigned long long encryption_cycles = ((encryption_time))/trials -timing_overhead;
    unsigned long long decryption_cycles = ((decryption_time))/trials - timing_overhead;
    
    execution_time = ((double)(end - start)*1000)/CPUCYCLES;
    execution_time_key = ((double)(execution_time_key)*1000)/CPUCYCLES;
    encryption_time = ((double)(encryption_time)*1000)/CPUCYCLES;
    decryption_time = ((double)(decryption_time)*1000)/CPUCYCLES

    printf("Average CPU cycles for all: %lld \n", total_cpu_cycles);
    printf("Average Time taken to execute in seconds : %f (ms) \n", execution_time/trials);

    printf("Average CPU cycles for key generation: %lld \n", key_gen_cycles);
    printf("Average time for key generation: %f (ms) \n", execution_time_key/trials );

    printf("Average CPU cycles for encryption: %lld \n", encryption_cycles);
    printf("Average time for encryption: %f (ms)\n", encryption_time/trials);
    
    printf("Average cpu cycles for decryption: %lld \n", decryption_cycles);
    printf("Average time for decryption: %f (ms) \n", decryption_time/trials);

    return KAT_SUCCESS;
}



//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
FindMarker(FILE *infile, const char *marker)
{
	char	line[MAX_MARKER_LEN];
	int		i, len;
	int curr_line;

	len = (int)strlen(marker);
	if ( len > MAX_MARKER_LEN-1 )
		len = MAX_MARKER_LEN-1;

	for ( i=0; i<len; i++ )
	  {
	    curr_line = fgetc(infile);
	    line[i] = curr_line;
	    if (curr_line == EOF )
	      return 0;
	  }
	line[len] = '\0';

	while ( 1 ) {
		if ( !strncmp(line, marker, len) )
			return 1;

		for ( i=0; i<len-1; i++ )
			line[i] = line[i+1];
		curr_line = fgetc(infile);
		line[len-1] = curr_line;
		if (curr_line == EOF )
		    return 0;
		line[len] = '\0';
	}

	// shouldn't get here
	return 0;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
ReadHex(FILE *infile, unsigned char *A, int Length, char *str)
{
	int			i, ch, started;
	unsigned char	ich;

	if ( Length == 0 ) {
		A[0] = 0x00;
		return 1;
	}
	memset(A, 0x00, Length);
	started = 0;
	if ( FindMarker(infile, str) )
		while ( (ch = fgetc(infile)) != EOF ) {
			if ( !isxdigit(ch) ) {
				if ( !started ) {
					if ( ch == '\n' )
						break;
					else
						continue;
				}
				else
					break;
			}
			started = 1;
			if ( (ch >= '0') && (ch <= '9') )
				ich = ch - '0';
			else if ( (ch >= 'A') && (ch <= 'F') )
				ich = ch - 'A' + 10;
			else if ( (ch >= 'a') && (ch <= 'f') )
				ich = ch - 'a' + 10;
            else // shouldn't ever get here
                ich = 0;

			for ( i=0; i<Length-1; i++ )
				A[i] = (A[i] << 4) | (A[i+1] >> 4);
			A[Length-1] = (A[Length-1] << 4) | ich;
		}
	else
		return 0;

	return 1;
}

void
fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L)
{
	unsigned long long  i;

	fprintf(fp, "%s", S);

	for ( i=0; i<L; i++ )
		fprintf(fp, "%02X", A[i]);

	if ( L == 0 )
		fprintf(fp, "00");

	fprintf(fp, "\n");
}

