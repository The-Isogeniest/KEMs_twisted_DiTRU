CC=/usr/bin/cc
LDFLAGS=-lcrypto

CFLAGS = -DCRYPTO_NAMESPACE\(s\)=ntru_\#\#s 

SOURCES = crypto_sort_int32.c poly.c rng.c poly_r.c sample.c   fips202.c ppke.c cca.c pack3_CnC3.c packq_CnC3.c cpucycles.c helper.c uint32.c inverse.c kem.c main_kem.c
HEADERS = crypto_sort_int32.h api.h api_bytes.h params.h poly.h rng.h poly_r.h sample.h inverse.h fips202.h crypto_hash_sha3256.h ppke.h pack3_CnC3.h packq_CnC3.h cca.h kem.h cpucycles.h helper.h uint32.h uint16.h uint64.h int16.h

main: $(HEADERS) $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(LDFLAGS)

.PHONY: clean

clean:
	-rm main