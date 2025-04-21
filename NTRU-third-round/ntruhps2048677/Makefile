
CC=/usr/bin/cc
LDFLAGS=-lcrypto
CFLAGS = -DCRYPTO_NAMESPACE\(s\)=ntru_\#\#s -O3

SOURCES = cmov.c crypto_sort_int32.c fips202.c kem.c owcpa.c pack3.c packq.c poly.c poly_lift.c poly_mod.c poly_r2_inv.c poly_rq_mul.c poly_s3_inv.c PQCgenKAT_kem.c rng.c sample.c sample_iid.c cpucycles.c
HEADERS = api_bytes.h api.h cmov.h crypto_hash_sha3256.h crypto_sort_int32.h fips202.h kem.h owcpa.h params.h poly.h rng.h sample.h cpucycles.h

main: $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) -DCRYPTO_NAMESPACE\(s\)=ntru_\#\#s -o $@ $(SOURCES) $(LDFLAGS)

.PHONY: clean

clean:
	-rm main
