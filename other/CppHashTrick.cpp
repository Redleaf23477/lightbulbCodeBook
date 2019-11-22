struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
	// size_t operator()(YourType in) const;
	// YourType可以放各種type/struct，只要寫對應到x身上的方法就行
	// (std::hash, non-symmetric function)
    size_t operator()(uint64_t in) const {
		uint64_t x = in;
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
unordered_map<long long, int, custom_hash> ump;
unordered_set<long long, custom_hash> ust;
