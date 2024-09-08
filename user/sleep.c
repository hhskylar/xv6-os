//
// Created by 曹玉华 on 2024/9/8.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        write(1, "param error\n", 1);
    }
    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}