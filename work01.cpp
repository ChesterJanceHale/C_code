// work01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义待办事项结构体
typedef struct {
    int urgency;
    char title[50];
} TodoItem;

// 定义顺序表结构体
typedef struct {
    TodoItem items[30];
    int size;
} TodoList;

// 创建顺序表
TodoList* createTodoList() {
    TodoList* list = (TodoList*)malloc(sizeof(TodoList));
    if (list) {
        list->size = 0;
    }
    return list;
}

// 销毁顺序表
void destroyTodoList(TodoList* list) {
    free(list);
}

// 增加一项待办事项
int addItem(TodoList* list, int urgency, const char* title) {
    if (list->size < 30) {
        TodoItem newItem;
        newItem.urgency = urgency;
        strncpy(newItem.title, title, sizeof(newItem.title));
        list->items[list->size] = newItem;
        list->size++;
        return 1; // 成功添加
    }
    else {
        return 0; // 顺序表已满
    }
}

// 删除一项指定序号的待办事项
void deleteItem(TodoList* list, int index) {
    if (index >= 0 && index < list->size) {
        for (int i = index; i < list->size - 1; i++) {
            list->items[i] = list->items[i + 1];
        }
        list->size--;
    }
}

// 修改一项指定序号的待办事项
void modifyItem(TodoList* list, int index, int newUrgency, const char* newTitle) {
    if (index >= 0 && index < list->size) {
        list->items[index].urgency = newUrgency;
        strncpy(list->items[index].title, newTitle, sizeof(list->items[index].title));
    }
}

// 列出指定紧急程度的待办事项
void listItemsByUrgency(TodoList* list, int urgency) {
    printf("待办事项列表 (紧急程度 %d):\n", urgency);
    for (int i = 0; i < list->size; i++) {
        if (list->items[i].urgency == urgency) {
            printf("%d. %s\n", i + 1, list->items[i].title);
        }
    }
}

// 列出所有待办事项
void listAllItems(TodoList* list) {
    printf("待办事项列表:\n");
    for (int i = 0; i < list->size; i++) {
        printf("%d. %s (紧急程度 %d)\n", i + 1, list->items[i].title, list->items[i].urgency);
    }
}

int main() {
    TodoList* todoList = createTodoList();
    int choice;
    int index;
    int urgency;
    char title[50];

    while (1) {
        printf("\n请选择操作:\n");
        printf("1. 增加待办事项\n");
        printf("2. 删除待办事项\n");
        printf("3. 修改待办事项\n");
        printf("4. 列出指定紧急程度的待办事项\n");
        printf("5. 列出所有待办事项\n");
        printf("6. 退出\n");
        printf("选择: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("输入紧急程度: ");
            scanf_s("%d", &urgency);
            printf("输入事项标题: ");
            scanf_s("%s", title);
            if (addItem(todoList, urgency, title)) {
                printf("待办事项已添加\n");
            }
            else {
                printf("顺序表已满，无法添加待办事项\n");
            }
            break;
        case 2:
            printf("输入要删除的待办事项序号: ");
            scanf_s("%d", &index);
            deleteItem(todoList, index - 1);
            printf("待办事项已删除\n");
            break;
        case 3:
            printf("输入要修改的待办事项序号: ");
            scanf_s("%d", &index);
            printf("输入新的紧急程度: ");
            scanf_s("%d", &urgency);
            printf("输入新的事项标题: ");
            scanf_s("%s", title);
            modifyItem(todoList, index - 1, urgency, title);
            printf("待办事项已修改\n");
            break;
        case 4:
            printf("输入要列出的紧急程度: ");
            scanf_s("%d", &urgency);
            listItemsByUrgency(todoList, urgency);
            break;
        case 5:
            listAllItems(todoList);
            break;
        case 6:
            destroyTodoList(todoList);
            return 0;
        default:
            printf("无效的选择\n");
        }
    }
}