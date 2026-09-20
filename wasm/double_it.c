/* The smallest possible C function, compiled to WebAssembly.
   Its only job is to make one mental model concrete: a function written in C
   can be called from JavaScript in a browser. */

__attribute__((export_name("double_it")))
int double_it(int n) {
  return n * 2;
}
