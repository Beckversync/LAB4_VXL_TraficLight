/////*
//// * scheduler.c
//// *
//// *  Created on: Nov 01, 2024
//// *      Author: Dell
//// */
//#include "scheduler.h"
//#include <stdlib.h>
//#include <stdint.h>
//
//struct sTask{
//	void (* pTask)(void);
//	uint32_t Delay;
//	uint32_t Period;
//	struct sTask *next;
//};
//
//struct container {
//	struct sTask *tail;
//	int numSlot;
//	int emptySlot;
//};
//
//struct container* container;
//
//
//struct sTask* Add_Node(struct sTask** curr, void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
//    struct sTask *temp = (struct sTask*)malloc(sizeof(struct sTask));
//    temp -> pTask = pFunction;
//    temp -> Delay = DELAY;
//    temp -> Period = PERIOD;
//    if (curr == NULL || *curr == NULL) {
//        temp -> next = temp;
//    }
//    else {
//        temp -> next = (*curr) -> next;
//    }
//    return temp;
//}
//
//void SCH_Init(void) {
//    // Cấp phát bộ nhớ cho container trên heap
//    container = (struct container*)malloc(sizeof(struct container));
//    if (container == NULL) {
//        // Kiểm tra lỗi nếu malloc thất bại
//        return;
//    }
//
//    // Khởi tạo các thành viên của container
//    container->tail = NULL; // Không có task nào trong container
//    container->numSlot = 0;  // Số lượng slot ban đầu
//    container->emptySlot = 0; // Số lượng slot trống ban đầu
//}
//
//void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
//	// container empty
//	if (container -> tail == NULL) {
//		container -> tail = Add_Node(NULL, pFunction, DELAY, PERIOD);
//		(container -> numSlot)++;
//	}
//	else {
//		struct sTask* temp = container -> tail;
//		uint32_t sumDelay = 0;
//		uint32_t newDelay = 0;
//		// find first task with bigger delay
//		for (int i = 0; i < container -> numSlot; i++) {
//			sumDelay = sumDelay + temp -> next -> Delay;
//			// add head or middle
//			if (sumDelay > DELAY) {
//                // delay of new task
//				newDelay = DELAY - (sumDelay - temp -> next -> Delay);
//				temp -> next -> Delay = sumDelay - DELAY;
//				// create new node if there is no empty slot
//				if (container -> emptySlot == 0) {
//					temp -> next = Add_Node(&temp, pFunction, newDelay, PERIOD);
//					(container -> numSlot)++;
//                }
//				// if is, move tail to after temp and use it
//				else {
//					container -> tail -> pTask = pFunction;
//					container -> tail -> Delay = newDelay;
//					container -> tail -> Period = PERIOD;
//					struct sTask *newTail = temp -> next;
//					while (newTail -> next != container -> tail) {
//						newTail = newTail -> next;
//					}
//					if (temp == container -> tail) container -> tail = newTail;
//					else {
//						newTail -> next = container -> tail -> next;
//						container -> tail -> next = temp -> next;
//						temp -> next = container -> tail;
//						container -> tail = newTail;
//					}
//                    (container -> emptySlot)--;
//				}
//                break;
//			} else {
//				// add tail
//                if (temp -> next -> pTask == 0x0000) {
//					temp -> next -> pTask = pFunction;
//					temp -> next -> Delay = DELAY - sumDelay;
//					temp -> next -> Period = PERIOD;
//                    (container -> emptySlot)--;
//					break;
//				}
//				else {
//					if (temp -> next == container -> tail) {
//						container -> tail -> next = Add_Node(&(container -> tail), pFunction, DELAY - sumDelay, PERIOD);
//						container -> tail = container -> tail -> next;
//						(container -> numSlot)++;
//						break;
//					}
//				}
//
//			}
//			temp = temp -> next;
//		}
//	}
//
//}
//
//void SCH_Delete_Task(struct sTask** preDel) {
//    struct sTask* del = (*preDel) -> next;
//    if (del != container -> tail) del -> next -> Delay += del -> Delay;
//	del -> pTask = 0x0000;
//	del -> Delay = 0;
//	del -> Period = 0;
//	if (*preDel == container -> tail)
//		container -> tail = container -> tail -> next;
//	else {
//		if (del -> next -> pTask != 0 && del != container -> tail) {
//			(*preDel) -> next = del -> next;
//			del -> next = container -> tail -> next;
//			container -> tail -> next = del;
//			container -> tail = del;
//		}
//	}
//	(container -> emptySlot)++;
//}
//
//
//void SCH_Update(void) {
//	if (container -> tail) {
//		if (container -> tail -> next -> Delay > 0)
//			(container -> tail -> next -> Delay)--;
//	}
//}
//
//
//void SCH_Dispatch_Tasks(void) {
//	while (container -> tail -> next -> Delay <= 0) {
//		(*(container -> tail -> next -> pTask))();
//		struct sTask temp = *(container -> tail -> next);
//		SCH_Delete_Task(&(container -> tail));
//		if (temp.Period != 0) {
//			SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
//		}
//	}
//
//}
//
//

#include "scheduler.h"
#include <stdlib.h>
#include <stdint.h>

struct sTask {
    void (*pTask)(void);    // Con trỏ hàm để thực thi task
    uint32_t Delay;         // Thời gian trễ
    uint32_t Period;        // Chu kỳ lặp lại
};

struct container {
    struct sTask** heap;    // Mảng heap để lưu các task
    int numSlot;            // Số lượng task hiện tại trong heap
    int emptySlot;          // Số lượng slot còn trống trong heap
};

struct container* container;

#define MAX_TASKS 10  // Giới hạn số lượng task tối đa trong heap

// Hàm khởi tạo container và heap
void SCH_Init(void) {
    container = (struct container*)malloc(sizeof(struct container));
    if (container == NULL) {
        return; // Kiểm tra lỗi nếu malloc thất bại
    }

    container->heap = (struct sTask**)malloc(sizeof(struct sTask*) * MAX_TASKS); // Cấp phát mảng heap
    container->numSlot = 0;
    container->emptySlot = MAX_TASKS;
}

// Hàm giúp duy trì tính chất heap sau khi thêm phần tử mới
void heapifyUp(struct container* cont, int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (cont->heap[parentIndex]->Delay <= cont->heap[index]->Delay) {
            break;
        }
        // Hoán đổi vị trí
        struct sTask* temp = cont->heap[parentIndex];
        cont->heap[parentIndex] = cont->heap[index];
        cont->heap[index] = temp;
        index = parentIndex;
    }
}

// Hàm duy trì tính chất heap sau khi xóa task
void heapifyDown(struct container* cont, int index) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int smallest = index;

    // Tìm phần tử con nhỏ hơn
    if (leftChildIndex < cont->numSlot && cont->heap[leftChildIndex]->Delay < cont->heap[smallest]->Delay) {
        smallest = leftChildIndex;
    }

    if (rightChildIndex < cont->numSlot && cont->heap[rightChildIndex]->Delay < cont->heap[smallest]->Delay) {
        smallest = rightChildIndex;
    }

    // Nếu nhỏ hơn, hoán đổi và tiếp tục
    if (smallest != index) {
        struct sTask* temp = cont->heap[index];
        cont->heap[index] = cont->heap[smallest];
        cont->heap[smallest] = temp;
        heapifyDown(cont, smallest);
    }
}

// Thêm task vào heap
void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    if (container->emptySlot <= 0) {
        // Không còn chỗ trống trong heap
        return;
    }

    // Cấp phát bộ nhớ cho task mới
    struct sTask* newTask = (struct sTask*)malloc(sizeof(struct sTask));
    if (newTask == NULL) {
        return; // Kiểm tra lỗi malloc
    }

    newTask->pTask = pFunction;
    newTask->Delay = DELAY;
    newTask->Period = PERIOD;

    // Thêm task vào heap (chèn vào cuối heap)
    container->heap[container->numSlot] = newTask;
    container->numSlot++;
    container->emptySlot--;

    // Duy trì tính chất min-heap
    heapifyUp(container, container->numSlot - 1);
}

// Cập nhật độ trễ của task trong heap
void SCH_Update(void) {
    if (container->numSlot > 0) {
        for (int i = 0; i < container->numSlot; i++) {
            if (container->heap[i]->Delay > 0) {
                container->heap[i]->Delay--;
                heapifyDown(container, i);
            }
        }
    }
}

// Xóa task khỏi heap
void SCH_Delete_Task(int index) {
    if (index >= 0 && index < container->numSlot) {
        struct sTask* taskToDelete = container->heap[index];

        // Di chuyển phần tử cuối cùng lên đầu để giữ lại tính chất heap
        container->heap[index] = container->heap[container->numSlot - 1];
        container->numSlot--;
        container->emptySlot++;

        free(taskToDelete); // Giải phóng bộ nhớ của task đã xóa
        heapifyDown(container, index); // Duy trì tính chất min-heap
    }
}

// Hàm xử lý các task có độ trễ bằng 0
void SCH_Dispatch_Tasks(void) {
    while (container->numSlot > 0 && container->heap[0]->Delay == 0) {
        // Thực thi task
        (*(container->heap[0]->pTask))(); // Thực thi hàm của task

        // Lưu lại thông tin task đã xóa
        struct sTask* taskToDelete = container->heap[0];

        // Nếu task có chu kỳ, thêm lại vào heap với độ trễ là chu kỳ của nó
        if (taskToDelete->Period != 0) {
            SCH_Add_Task(taskToDelete->pTask, taskToDelete->Period, taskToDelete->Period);
        }

        // Xóa task khỏi heap
        container->heap[0] = container->heap[container->numSlot - 1]; // Di chuyển phần tử cuối cùng lên đầu
        container->numSlot--;  // Giảm số lượng task
        container->emptySlot++; // Tăng số lượng slot trống

        free(taskToDelete);  // Giải phóng bộ nhớ của task đã xóa
        heapifyDown(container, 0); // Duy trì tính chất min-heap
    }
}
