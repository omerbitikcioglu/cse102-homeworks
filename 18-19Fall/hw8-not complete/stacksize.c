//include

#include <sys/resource.h>

//insert the following in main:

int main()
{

    const rlim_t kStackSize = 16 * 1024 * 1024; // min stack size = 16 MB
struct rlimit rl;
int result;

result = getrlimit(RLIMIT_STACK, &rl);
if (result == 0)
{
if (rl.rlim_cur < kStackSize)
{
rl.rlim_cur = kStackSize;
result = setrlimit(RLIMIT_STACK, &rl);
if (result != 0)
{
fprintf(stderr, "setrlimit returned result = %d\n", result);
}
}
}
