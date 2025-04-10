#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

// Constants for MD5
#define F(x, y, z) ((x & y) | (~x & z))
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))

#define ROTATE_LEFT(x, n) ((x << n) | (x >> (32 - n)))

#define FF(a, b, c, d, x, s, ac) { a += F(b, c, d) + x + ac; a = ROTATE_LEFT(a, s); a += b; }
#define GG(a, b, c, d, x, s, ac) { a += G(b, c, d) + x + ac; a = ROTATE_LEFT(a, s); a += b; }
#define HH(a, b, c, d, x, s, ac) { a += H(b, c, d) + x + ac; a = ROTATE_LEFT(a, s); a += b; }
#define II(a, b, c, d, x, s, ac) { a += I(b, c, d) + x + ac; a = ROTATE_LEFT(a, s); a += b; }

void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest) {
    uint32_t h0, h1, h2, h3;
    uint8_t *msg = NULL;

    int new_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;
    msg = (uint8_t*)calloc(new_len + 64, 1);
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128;

    uint32_t bits_len = 8 * initial_len;
    memcpy(msg + new_len, &bits_len, 4);

    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;

    for (int offset = 0; offset < new_len; offset += 64) {
        uint32_t *w = (uint32_t *)(msg + offset);
        uint32_t a, b, c, d;
        a = h0; b = h1; c = h2; d = h3;

        FF(a, b, c, d, w[0], 7, 0xd76aa478);
        FF(d, a, b, c, w[1], 12, 0xe8c7b756);
        FF(c, d, a, b, w[2], 17, 0x242070db);
        FF(b, c, d, a, w[3], 22, 0xc1bdceee);

        h0 += a; h1 += b; h2 += c; h3 += d;
    }

    free(msg);
    memcpy(digest, &h0, 4);
    memcpy(digest + 4, &h1, 4);
    memcpy(digest + 8, &h2, 4);
    memcpy(digest + 12, &h3, 4);
}
