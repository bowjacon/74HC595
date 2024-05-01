#ifndef _STEP_H
#define _STEP_H
#include "arm_math.h"
#include <stdint.h>
typedef struct{
  struct node *current;
    struct node *next;
    struct node *last;
    double value;
    uint8_t position;
}node;
typedef struct{
    double value;
    uint8_t position;
}max_info;
#define STEP_SIZE 20
#define STEP_CHECK_SIZE 10
#endif