#include <stdio.h>
#include <limits.h>

int main (void) {
   printf ("sizeof (unsigned): %lu\n", 
            sizeof (unsigned));        
   printf ("UINT_MAX: %u, ou %x\n",
            UINT_MAX, UINT_MAX);
   printf ("sizeof (int) = %lu, ou %x\n",  
            sizeof (int), (int) sizeof (int));        
   printf ("INT_MIN: %d, ou %x\nINT_MAX: %d, ou %x\n",
            INT_MIN, INT_MIN, INT_MAX, INT_MAX);
   return 0;
}
