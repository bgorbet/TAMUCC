struct output {
	int v;
	float t;
};

program ADD_PROG {
	version ADD_VERS {
		output prime(int) = 1;
		output fibonacci(int) = 2;
	} = 1;
} = 0x20000001;
