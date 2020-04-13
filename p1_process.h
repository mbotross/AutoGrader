#ifndef __P1_PROCESS
#define __P1_PROCESS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include<sstream>
#include <string>
#include <string.h>
#include <vector>
#include <sys/wait.h>
#include "p1_threads.h"
#include <iomanip>

void get_statistics(std::string class_name[], int num_processes, int num_threads);
void file_process(std::string class_name[],int i);
#endif
