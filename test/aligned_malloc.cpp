#include "../relacy/relacy_std.hpp"

struct aligned_malloc_test_suite
    : rl::test_suite<aligned_malloc_test_suite, 1> {
  void thread(unsigned index) {
    (void)index;

    void *ptr = rl_malloc(128, // size
                          64,  // alignment
                          $);

    // Verify 64-byte alignment
    RL_VERIFY((reinterpret_cast<uintptr_t>(ptr) & 63) == 0);

    // Verify we can write and read
    char *char_ptr = static_cast<char *>(ptr);
    char_ptr[0] = 'a';
    char_ptr[127] = 'z';
    RL_VERIFY(char_ptr[0] == 'a');
    RL_VERIFY(char_ptr[127] == 'z');

    rl_free(ptr, $);
  }
};

int main() {
  rl::test_params p;
  p.iteration_count = 10;
  rl::simulate<aligned_malloc_test_suite>(p);
  return 0;
}
