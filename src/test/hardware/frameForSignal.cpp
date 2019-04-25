//#include <cstdio>
//#include <wiringPi.h>
//#include <softPwm.h>
//#include <signal.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//
//void my_handler(int s);
//void ctrl_c_stop_motor_signal_handler();
//
//void my_handler(int s){
//    printf("Caught signal %d\n",s);
//    stop();
//    exit(1);
//
//}
//
//void ctrl_c_stop_motor_signal_handler(){
//    struct sigaction sigIntHandler;
//
//    sigIntHandler.sa_handler = my_handler;
//    sigemptyset(&sigIntHandler.sa_mask);
//    sigIntHandler.sa_flags = 0;
//
//    sigaction(SIGINT, &sigIntHandler, NULL);
//}
//
