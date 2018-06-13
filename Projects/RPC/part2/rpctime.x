struct twoArgs {
    int arg1;
    float arg2;
};

struct tenArgs {
    double arg_1;
    double arg_2;
    double arg_3;
    double arg_4;
    double arg_5;
    double arg_6;
    double arg_7;
    double arg_8;
    double arg_9;
    double arg_10;
};

struct arrayArg {
    int a[100];
};

program ADD_PROG {
    version ADD_VERS {
        void nullRemote1() = 1;
        int nullRemote2(int) = 2;
        twoArgs nullRemote3(twoArgs) = 3;
        tenArgs nullRemote4(tenArgs) = 4;
        arrayArg nullRemote5(arrayArg) = 5;
    } = 1;
} = 0x20000002;
