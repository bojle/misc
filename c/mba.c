/* https://theses.hal.science/tel-01623849/document
 * Appendix A.2 XOR
 * Mixed Boolean Arithmetic
 */
#include <stdio.h>

int main() {
    unsigned int x = 10;
    unsigned int y = 12;
    printf("Trad: %d\n", x ^ y);
    printf("MBA: %d\n", (x | y) - y + (~x & y));
}
