// 返回右起第一個1的位置(1起算)，否則返回0
int __builtin_ffs(unsigned int);
int __builtin_ffsll(unsigned long long);
// 返回左起第一個1之前的0的個數
int __builtin_clz(unsigned int);
int __builtin_clzll(unsigned long long);
// 返回右起第一個1之後的0的個數
int __builtin_ctz(unsigned int);
int __builtin_ctzl(unsigned long long);
// 返回1的個數
int __builtin_popcount(unsigned int);
int __builtin_popcountll(unsigned long long);
