#include "poly.h"

#ifdef tDiTRU_HPS
void poly_lift(poly *r, const poly *a)
{
  int i;
  for(i=0; i<ORDER; i++) {
    r->coeffs[i] = a->coeffs[i];
  }
  poly_Z3_to_Zq_tDiTRU(r); //change to tditru
}
#endif
