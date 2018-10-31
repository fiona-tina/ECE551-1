#include <assert.h>

#include <cstdlib>

#include "il.h"

using namespace std;

//IntList testing()

void testList() {
  // An empty list
  IntList list2;
  assert(list2.size == 0);
  assert(list2.head == NULL);
  assert(list2.tail == NULL);
  assert(list2.getSize() == 0);
  //assert(list2.head->next == NULL);
  //assert(list2.tail->next == NULL);
  //assert(list2.head->prev == NULL);
  //assert(list2.tail->prev == NULL);

  IntList list3 = list2;
  assert(list3.size == 0);
  assert(list3.head == NULL);
  assert(list3.tail == NULL);
  //assert(list3.head->next == NULL);
  //assert(list3.tail->next == NULL);
  //assert(list3.head->prev == NULL);
  //assert(list3.tail->prev == NULL);

  IntList list4(list2);
  assert(list4.size == 0);
  assert(list4.head == NULL);
  assert(list4.tail == NULL);
  //assert(list4.head->next == NULL);
  //assert(list4.tail->next == NULL);
  //assert(list4.head->prev == NULL);
  //assert(list4.tail->prev == NULL);
  //assert(list4.head != list2.head);

  for (int i = 0; i < 10; i++) {
    list2.addBack(i);
  }
  for (int i = 0; i < 10; i++) {
    if (list2[i] != i) {
      assert(0);
    }
  }

  list2[1] = 10;
  assert(list2[1] == 10);
  assert(list2.head->next->data == 10);
  list2[1] = 1;
  assert(list2.size == 10);
  assert(list2.getSize() == 10);
  IntList list1 = list2;
  list1 = list1;
  for (int i = 0; i < 10; i++) {
    if (list1[i] != i) {
      assert(0);
    }
  }

  assert(list1.head != list2.head);
  assert(list1.head->next != list2.head->next);
  assert(list1.tail != list2.tail);
  assert(list1.tail->next == NULL);
  assert(list1.head->data == 0);
  assert(list1.tail->data == 9);

  assert(list1.size == 10);
  assert(list1.head->next != list2.head->next);
  assert(list1.tail->next == NULL);
  assert(list1.head->prev == NULL);
  assert(list1.tail->prev != list2.head->prev);

  assert(list1.head->next->data == 1);
  assert(list1.getSize() == list1.size);
  assert(list1.find(5) == 5);

  IntList list5(list2);

  assert(list5.head != list2.head);
  assert(list5.head->next != list2.head->next);
  assert(list5.tail != list2.tail);
  assert(list5.tail->next == NULL);
  assert(list5.head->data == 0);
  assert(list5.tail->data == 9);

  assert(list5.size == 10);
  assert(list5.head->next != list2.head->next);
  assert(list5.tail->next == NULL);
  assert(list5.head->prev == NULL);
  assert(list5.tail->prev != list2.head->prev);
  assert(list5.head->next->data == 1);
  assert(list5.getSize() == list1.size);
  assert(list5.find(5) == 5);
  //-----------------------------------------------
  IntList list10;
  list10.addFront(1);
  assert(list10.head == list10.tail);
  assert(list10.head->next == NULL);
  assert(list10.tail->prev == NULL);

  list10[0] = 10;
  assert(list10[0] == 10);
  assert(list10.head->data == 10);
  list2[1] = 1;

  IntList list11(list10);
  assert(list10.size == list11.getSize());
  assert(list11.head != list10.head);
  assert(list11.tail != list10.tail);
  assert(list11.head == list11.tail);
  assert(list11.head->next == NULL);
  assert(list11.tail->next == NULL);
  assert(list11.head->prev == NULL);
  assert(list11.tail->prev == NULL);

  IntList list12 = list10;
  assert(list10.size == list12.getSize());
  assert(list12.head != list10.head);
  assert(list12.tail != list10.tail);
  assert(list12.head == list12.tail);
  assert(list12.head->next == NULL);
  assert(list12.tail->next == NULL);
  assert(list12.head->prev == NULL);
  assert(list12.tail->prev == NULL);

  list1 = list10;

  assert(list1[0] == 10);
  assert(list1.size == 1);
  assert(list1.head != list10.head);
  assert(list1.tail != list10.tail);
  assert(list1.head == list1.tail);
  assert(list1.head->next == NULL);
  assert(list1.tail->next == NULL);
  assert(list1.head->prev == NULL);
  assert(list1.tail->prev == NULL);

  //----------------------
  IntList list20;
  list20.addFront(4);
  list20.addFront(3);
  list20.addFront(2);
  list20.addFront(1);
  list20.addFront(0);
  assert(list20.find(3) == 3);
  assert(list20.size == 5);
  assert(list20.head->data == 0);
  assert(list20.tail->data == 4);

  for (int i = 0; i < 5; i++) {
    if (list20[i] != i)
      assert(0);
  }

  list20.remove(3);
  assert(list20.size == 4);
  assert(list20.getSize() == 4);

  //-----------------------
  IntList list30;
  list30.addFront(1);
  list30.addFront(1);
  list30.addFront(1);
  assert(list30.head->next->next == list30.tail);
  assert(list30.find(2) == -1);
  assert(list30.head->data == 1);
  assert(list30.tail->data == 1);

  for (int i = 0; i < 3; i++) {
    if (list30[i] != 1)
      assert(0);
  }

  list30.remove(1);
  assert(list30.size == 2);
  assert(list30.getSize() == 2);
  //----------------------------
  IntList list40;
  list40.addBack(0);
  list40.addBack(1);
  list40.addBack(2);

  list40.remove(1);
  assert(list40.head->data == 0);
  assert(list40.tail->data == 2);
  assert(list40.getSize() == 2);
  assert(list40.size == 2);
  assert(list40.head->next == list40.tail);
  assert(list40.tail->prev == list40.head);

  IntList list50;
  list50.addBack(0);
  list50.addBack(1);
  list50.addBack(2);

  list50.remove(2);
  assert(list50.head->data == 0);
  assert(list50.tail->data == 1);
  assert(list50.getSize() == 2);
  assert(list50.size == 2);
  assert(list50.head->next == list50.tail);
  assert(list50.tail->prev == list50.head);
  assert(list50.head->next->next == NULL);
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
