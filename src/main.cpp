#include "context.hpp"

int main() {
  Context::Init();
  Window* win = new Window();
  Context context(win);

  return 0;
}
