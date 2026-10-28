#include <stdio.h>
#include <string.h>
#include "zlib.h"
#include "legacy_1_2_7.h"

#define CHECK(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "line %d: %s\n", __LINE__, #condition); \
        return 1; \
    } \
} while (0)

int main(void) {
    unsigned char expected[2048], decoded[2048], compressed[4096];
    unsigned char damaged[sizeof(legacy_compressed)];
    uLongf decoded_size, compressed_size;
    unsigned i;
    int result;

    CHECK(strcmp(ZLIB_VERSION, "1.3.2") == 0);
    CHECK(strcmp(zlibVersion(), ZLIB_VERSION) == 0);
    CHECK(crc32(0, (const Bytef *)"123456789", 9) == 0xcbf43926UL);
    for (i = 0; i < sizeof(expected); ++i)
        expected[i] = (unsigned char)(i * 37);

    /* Existing database blobs and pack contents must remain readable. */
    decoded_size = sizeof(decoded);
    CHECK(uncompress(decoded, &decoded_size, legacy_compressed,
                     sizeof(legacy_compressed)) == Z_OK);
    CHECK(decoded_size == sizeof(expected));
    CHECK(memcmp(decoded, expected, sizeof(expected)) == 0);

    compressed_size = sizeof(compressed);
    CHECK(compressBound(sizeof(expected)) <= sizeof(compressed));
    CHECK(compress(compressed, &compressed_size, expected, sizeof(expected)) == Z_OK);
    decoded_size = sizeof(decoded);
    CHECK(uncompress(decoded, &decoded_size, compressed, compressed_size) == Z_OK);
    CHECK(decoded_size == sizeof(expected));
    CHECK(memcmp(decoded, expected, sizeof(expected)) == 0);

    /* Preserve the error contracts used by callers handling invalid payloads. */
    decoded_size = sizeof(decoded) - 1;
    CHECK(uncompress(decoded, &decoded_size, legacy_compressed,
                     sizeof(legacy_compressed)) == Z_BUF_ERROR);

    memcpy(damaged, legacy_compressed, sizeof(damaged));
    damaged[sizeof(damaged) - 1] ^= 1; /* Adler-32 mismatch */
    decoded_size = sizeof(decoded);
    CHECK(uncompress(decoded, &decoded_size, damaged, sizeof(damaged)) == Z_DATA_ERROR);

    decoded_size = sizeof(decoded);
    result = uncompress(decoded, &decoded_size, legacy_compressed,
                        sizeof(legacy_compressed) / 2);
    CHECK(result == Z_DATA_ERROR || result == Z_BUF_ERROR);

    printf("zlib %s: legacy data, round trip, checksum and error contracts passed\n",
           zlibVersion());
    return 0;
}
