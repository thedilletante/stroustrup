#include <iostream>

#define PRINT_OP(OP, ARG1, ARG2) std::cout<<#ARG1#OP#ARG2<<" = "<<((ARG1)OP(ARG2))
#define PRINT_UNO(OP, ARG) std::cout<<OP#ARG<<" "<<(OP ARG);
#define EOL std::cout<<"\n"
#define TAB std::cout<<"\t"
#define PRINT_FOR_OP(OP) PRINT_OP(OP, 0, 0); TAB; PRINT_OP(OP, 1, 1); TAB; PRINT_OP(OP, 1, 0); EOL;
#define PRINT_FOR_UNO(OP) PRINT_UNO(OP, 0); TAB; PRINT_UNO(OP, 1); EOL;

int main()
{
  PRINT_FOR_OP(&);
  PRINT_FOR_OP(|);
  PRINT_FOR_OP(^);
  return 0;
} 