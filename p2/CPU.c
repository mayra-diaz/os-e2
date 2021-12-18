/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "access.h"

// run this task for the specified time slice
void run(Access *access, int tracks) {
    printf("Accesing %d at position %d with %d tracks traversed.\n", access->id, access->position, tracks);
}
