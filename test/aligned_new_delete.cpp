#include "../relacy/relacy_std.hpp"
#include <new>

struct alignas(64) OverAlignedStruct
{
    int value;
    char padding[60];
};

struct aligned_test_suite : rl::test_suite<aligned_test_suite, 1>
{
    void thread(unsigned index)
    {
        (void)index;
        OverAlignedStruct* ptr = new OverAlignedStruct();
        RL_VERIFY((reinterpret_cast<uintptr_t>(ptr) & 63) == 0);
        
        ptr->value = 42;
        delete ptr;
    }
};

int main()
{
    rl::test_params p;
    p.iteration_count = 10;
    rl::simulate<aligned_test_suite>(p);
    return 0;
}
