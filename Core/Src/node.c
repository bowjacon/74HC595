#include "node.h"
#include <stdio.h>

/**
 * @breif: 链表初始化
 */
void node_init(node *head) {
    for (int i = 0; i < Node_N; i++) {
        head[i].last = (i == 0) ? NULL : &head[i - 1];
        head[i].next = (i == Node_N - 1) ? NULL : &head[i + 1];
        head[i].data = i;
    }
}
/**
 * @breif: 查找指定位置的节点
 */
node *find_node(node head[], node_place palce) {
    for (int i = 0; i < Node_N; i++) {
        if (palce == begin && head[i].last == NULL) {
            return &head[i];
        }
        if (palce == end && head[i].next == NULL) {
            return &head[i];
        }
    }
    return NULL;
}
/**
 * @brief: 跳转到指定位置
 * @param direction: 跳转方向，1 表示向下，-1 表示向上
 */
node *node_jump(node *head, int n, node_up_down direction) {
    if (direction == node_down) {
        for (int i = 0; i < n; i++) {
            if (head->next != NULL) {
                head = head->next;
            } else {
                break;
            }
        }
    } else if (direction == node_up) {
        for (int i = 0; i < n; i++) {
            if (head->last != NULL) {
                head = head->last;
            } else {
                break;
            }
        }
    }
    return head;
}

/**
 * @breif: 在尾节点或者首节点插入数据
 */
void insert_node(double value, node *origin_node, node_place place) {

    node *node_begin = find_node(origin_node, begin);
    node *node_end = find_node(origin_node, end);
    if (place == end) {
        node_begin->data = value;
        node_begin->next->last = NULL;
        node_begin->next = NULL;
        node_end->next = node_begin;
        node_begin->last = node_end;
    } else if (place == begin) {
        node_end->data = value;
        node_end->last->next = NULL;
        node_end->last = NULL;
        node_begin->last = node_end;
        node_end->next = node_begin;
    }
}

/**
 * @breif: 查找最大值或最小值
 */
node *find_Max_Min_node(node *start_node, node *end_node, node_max_min flag) {
    node *target_node;
    int value = start_node->data;
    while (start_node != end_node->next) {
        if ((flag == node_max && start_node->data >= value) ||
            (flag == node_min && start_node->data <= value)) {
            value = start_node->data;
            target_node = start_node;
        }
        start_node = start_node->next;
    }
    return target_node;
}

/**
 * @brief: 计算两个节点之间的距离
 */
int get_node_distance(node *node1, node *node2) {
    node *current = node1;
    int distance = 0;
    while (current != NULL) {
        if (current == node2) {
            return distance;
        }
        current = current->next;
        distance++;
    }
    current = node2;
    distance = 0;
    while (current != NULL) {
        if (current == node1) {
            return distance;
        }
        current = current->next;
        distance++;
    }
    return -1; // nodes are not in the same list
}

/**
 * @brief: 查找指定范围内最大值或者最小值的节点
 */
node *find_Node_Max_Min_Area(node *current, int area, node_max_min flag) {
    node *test_l = node_up_jump(current, area);
    node *test_r = node_down_jump(current, area);
    return find_Max_Min_node(test_l, test_r, flag);
}
