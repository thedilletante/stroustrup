void f(char ch) {}
void g(char & ch) {}
void h(const char & ch) {}

int main() {
  char c = 0;
  unsigned char uc = 0;
  signed char sc = 0;

  f('a');
  f(49);
  f(3300);
  f(c);
  f(uc);
  f(sc);

//  g('a');
//  g(49);
//  g(3300);
  g(c);
//  g(uc);
//  g(sc);

  h('a'); // temporary
  h(49);  // temporary
  h(3300); // temporary
  h(c);
  h(uc);
  h(sc);

  return 0;
}