#ifndef _NODE_H
#define _NODE_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Node_N 20
typedef enum { begin, middle, end } node_place;
typedef enum { node_max, node_min } node_max_min;
typedef enum { node_up, node_down } node_up_down;
typedef enum { after, before } node_direct;
typedef struct node_stuct {
    struct node_stuct *next;
    struct node_stuct *last;
    double data;
} node;

node *find_node(node head[], node_place palce);

#define find_begin(head) /*查找链表首节点*/ find_node(head, begin)

#define find_end(head) /*查找链表尾节点*/ find_node(head, end)

void node_init(node head[]);

void insert_node(double value, node *origin_node, node_place place);

#define insert_begin(p, q) /*在链表首节点插入节点*/ insert_node(p, q, begin)

#define insert_end(p, q) /*在链表尾节点插入节点*/ insert_node(p, q, end)
node *find_Max_Min_node(node *start_node, node *end_node, node_max_min flag);
#define find_Max_node(p, q) /*查找最大值*/ find_Max_Min_node(p, q, node_max)
#define find_Min_node(p, q) /*查找最小值*/ find_Max_Min_node(p, q, node_min)
node *node_jump(node *head, int n, node_up_down direction);
#define node_up_jump(head, n) node_jump(head, n, node_up)
#define node_down_jump(head, n) node_jump(head, n, node_down)
int get_node_distance(node *node1, node *node2);
node *find_Node_Max_Min_Area(node *current, int area, node_max_min flag);
#define find_Max_Area(p, q) find_Node_Max_Min_Area(p, q, node_max)
#define find_Min_Area(p, q) find_Node_Max_Min_Area(p, q, node_min)
#endif