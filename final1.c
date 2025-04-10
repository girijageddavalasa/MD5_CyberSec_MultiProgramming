#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "md5.h" // Custom MD5 header file (included below)

#define PASSWORD_LENGTH 4
#define NUM_THREADS 8

void md5_hash(const char *str, char *output)
{
    unsigned char digest[16];
    md5((unsigned char *)str, strlen(str), digest);

    for (int i = 0; i < 16; i++)
    {
        sprintf(&output[i * 2], "%02x", digest[i]);
    }
    output[32] = '\0'; // Null-terminate string
}

// Parallel Brute-force function
void brute_force_md5(const char *target_hash)
// MD5 hash we're trying to crack.
{
    char attempt[PASSWORD_LENGTH + 1]; // Stores the current password guess.
    char hash_output[33];              // Stores the generated MD5 hash of the guess.
    int found = 0;

    // Uses OpenMP (#pragma omp parallel for) to split brute-force attempts among NUM_THREADS threads.

#pragma omp parallel for num_threads(NUM_THREADS) private(attempt, hash_output) shared(found)
    for (int i = 0; i < 10000; i++)
    { // Try from "0000" to "9999"
        if (found)
            continue; // Stop early if password is found

        snprintf(attempt, PASSWORD_LENGTH + 1, "%04d", i); //0002
        md5_hash(attempt, hash_output);

        if (strcmp(hash_output, target_hash) == 0)
        {
#pragma omp critical // Prevent race conditions in output ie ensures that only one thread prints the output.
            {
                printf("✅ Password found: %s\n", attempt);
                found = 1;
            }
        }
    }
}

int main()
{
    char password[PASSWORD_LENGTH + 1] = "3456"; // Target password
    char target_hash[33];

    md5_hash(password, target_hash); // Convert to MD5 hash
    printf("🔒 MD5 Hash of password: %s\n", target_hash);

    printf("🚀 Starting parallel brute-force attack...\n");
    brute_force_md5(target_hash);

    return 0;
}
