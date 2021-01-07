#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node{
  int key;
  int order;
  Node * parent;
  Node * child;
  Node * sibling;
  Node (*make_node)(int);
};

Node * make_node(int k)
{
  Node * node = (Node *) malloc(sizeof(Node));
  node->key = k;
  node->order = 0;
  node->parent = node->child = node->sibling = NULL;
  return node;
}

typedef struct tree_root tree_root;
struct tree_root{
  Node * node;
  tree_root * prev;
  tree_root * next;
};
//Accepts a node of a binomial tree as root and make it a tree_root,
//so that it can be inserted into the linked_list
tree_root* create_tree_root(Node * node)
{
  tree_root * root;
  root = (tree_root *)malloc(sizeof(tree_root));
  root->node = node;
  root->prev = root->next = NULL;
  return root;
}

typedef struct linked_list linked_list;
struct linked_list{
  tree_root * head;
  tree_root * tail;
  int length;
};

//Create an empty linked_list and return it
linked_list * create_linked_list()
{
  linked_list * list = (linked_list *) malloc(sizeof(linked_list));
  list->head = list->tail = NULL;
  list->length = 0;
  return list;
}

//Insert a node as tree_root into a linked_list
void add_first(linked_list * list, tree_root * root)
{
  // tree_root * root = create_tree_root(node);
  // printf("head: %p  tail: %p  root: %p\n",(void*)list->head, (void*)list->tail, (void*)root );
  if(list->head == NULL)
  {
    //make node a tree_root
    //point head-pointer and tail-pointer to it
    list->head = root;
    list->tail = root;
  }
  else
  {
    root->next = list->head;
    list->head->prev = root;
    list->head = root;
  }
  // printf("%d\t%d\n",list->head->node->key, list->tail->node->key );
  list->length++;
}

void add_last(linked_list * list, tree_root * root)
{
  if(list->head == NULL)
  {
    add_first(list, root);
    return;
  }
  // tree_root * root = create_tree_root(node);
  root->prev = list->tail;
  list->tail->next = root;
  list->tail = root;
  list->length++;
}

void remove_first(linked_list * list)
{
  list->head = list->head->next;
  list->head->prev = NULL;
  list->length--;
}

void remove_last(linked_list * list)
{
  list->tail = list->tail->prev;
  list->tail->next = NULL;
  list->length--;
}

void remove_node(linked_list * list, tree_root * root)
{
  tree_root * ptr = list->head;
  //if root is in head
  if(list->head == root)
  {
    remove_first(list);
    return;
  }
  //if root is in tail
  if(list->tail == root)
  {
    remove_last(list);
    return;
  }

  while(ptr != NULL)
  {
    if(ptr == root)
    {
      ptr->prev->next = ptr->next;
      ptr->next->prev = ptr->prev;
      return;
    }
    ptr = ptr->next;
  }
}

//print linked_list
void print_list(linked_list * list)
{
  tree_root * ptr = list->head;
  while(ptr != NULL)
  {
    printf("key = %d\torder = %d\n",ptr->node->key, ptr->node->order);
    ptr = ptr->next;
  }
}


//Functions for binomial heap operations
tree_root * binomial_link(tree_root * root1, tree_root * root2)
{
  //swap root if root2 is smaller.
  if(root2->node->key < root1->node->key)
  {
    tree_root * temp = root1;
    root1 = root2;
    root2 = temp;
  }
  root2->node->parent = root1->node;
  root2->node->sibling = root1->node->child;
  root1->node->child = root2->node;
  root1->node->order++;
  free(root2);
  return root1;
}

linked_list * union_heap(linked_list * heap1, linked_list * heap2)
{
  if(heap1->length == 0 || heap1 == NULL)
  {
    printf("heap1 NULL\n");
    heap1 = NULL;
    free(heap1);
    return heap2;
  }
  if(heap2->length == 0 || heap2 == NULL)
  {
    printf("heap2 NULL\n");
    heap2 = NULL;
    free(heap2);
    return heap1;
  }
  linked_list * heap = create_linked_list();
  tree_root * ptr1 = heap1->head;
  tree_root * ptr2 = heap2->head;
  while(ptr1 != NULL && ptr2 != NULL)
  {
    if(ptr1->node->order == ptr2->node->order)
    {
      add_last(heap, binomial_link(ptr1, ptr2));
      ptr1 = ptr1->next;
      ptr2 = ptr2->next;
    }
    else
    {
      tree_root * ptr = (ptr1->node->order < ptr2->node->order) ? ptr1 : ptr2;
      if(heap->length == 0) add_last(heap, ptr);
      else
      {
        //if tree rooted at ptr and the latest root in the linked list(here, heap)
        //has same order, then link them, remove the latest root and add the newly linked one
        if(heap->tail->node->order == ptr->node->order)
        {
          tree_root * linked_root = binomial_link(heap->tail, ptr);
          remove_last(heap);
          add_last(heap, linked_root);
        }
        else
        {
          add_last(heap, ptr);
        }
      }

      if(ptr == ptr1) ptr1 = ptr1->next;
      else if(ptr == ptr2) ptr2 = ptr2->next;
    }
  }
  heap1 = heap2 = NULL;
  free(heap1);
  free(heap2);
  return heap;
}

linked_list * insert(linked_list * heap, int k)
{
  linked_list * ll = create_linked_list();
  add_last(ll, create_tree_root(make_node(k)));
  printf("before union :  %p\n", (void*)heap);//print_list(heap);
  heap = union_heap(heap, ll);
  printf("after union  :  %p\n",(void*)heap);//print_list(heap);
  if(heap->head == NULL)printf("%s\n","NULL" );
  return heap;
}

void print(Node * node)
{
  while(node)
  {
    printf("\tkey = %d, order = %d\n",node->key, node->order);
    print(node->child);
    node = node->sibling;
  }
}

void print_tree(tree_root * root)
{
  Node * node = root->node;
  print(node);
}
void print_heap(linked_list * heap)
{
  tree_root * ptr = heap->head;
  // if(heap->head == NULL)printf("%s\n","NULL" );
  while(ptr != NULL)
  {
    printf("****root = %d****\n",ptr->node->key);
    print_tree(ptr);
    ptr = ptr->next;
  }
}

/*int main()
{
  linked_list list = create_linked_list();
  // Node n1 = make_node(10);
  // add_first(&list, &n1);
  // Node n2 = make_node(19);
  // add_first(&list, &n2);
  // Node n3 = make_node(25);
  // add_first(&list, &n3);
  // Node n4 = make_node(35);
  // add_first(&list, &n4);
  // print_list(&list);

  // Node n1 = make_node(10);
  // add_last(&list, &n1);
  // Node n2 = make_node(19);
  // add_last(&list, &n2);
  // Node n3 = make_node(25);
  // add_last(&list, &n3);
  // Node n4 = make_node(35);
  // add_last(&list, &n4);
  // tree_root * ptr = list.head;
  // ptr = ptr->next;
  // remove_node(&list, ptr);
  // print_list(&list);

  // Node n1 = make_node(10);
  // Node n2 = make_node(20);
  // Node n3 = make_node(30);
  // Node n4 = make_node(40);
  // tree_root * root1 = create_tree_root(&n1);
  // tree_root * root2 = create_tree_root(&n3);
  // n1.child = &n2;
  // n2.parent = &n1;
  // n3.child = &n4;
  // n4.parent = &n3;
  // print_tree(binomial_link(root1, root2));

}*/
int main()
{
  linked_list * binomial_heap = create_linked_list();
  printf("before calling: %p ......\n",(void*)binomial_heap );
  binomial_heap = insert(binomial_heap, 10);
  printf("after calling : %p ......\n",(void*)binomial_heap );
  print_list(binomial_heap);
  printf("\n");

  printf("before calling: %p ......\n",(void*)binomial_heap );
  binomial_heap = insert(binomial_heap, 20);
  printf("after calling : %p ......\n",(void*)binomial_heap );
  print_list(binomial_heap);
  printf("\n");

  printf("before calling: %p ......\n",(void*)binomial_heap );
  binomial_heap = insert(binomial_heap, 30);
  printf("after calling : %p ......\n",(void*)binomial_heap );
  print_list(binomial_heap);
  printf("\n");

  printf("before calling: %p ......\n",(void*)binomial_heap );
  binomial_heap = insert(binomial_heap, 40);
  printf("after calling : %p ......\n",(void*)binomial_heap );
  print_list(binomial_heap);
  printf("\n");

  printf("before calling: %p ......\n",(void*)binomial_heap );
  binomial_heap = insert(binomial_heap, 50);
  printf("after calling : %p ......\n",(void*)binomial_heap );
  print_list(binomial_heap);
  printf("\n");

  printf("before calling: %p ......\n",(void*)binomial_heap );
  binomial_heap = insert(binomial_heap, 60);
  printf("after calling : %p ......\n",(void*)binomial_heap );
  print_list(binomial_heap);
  printf("\n");

  //print_heap(binomial_heap);
}
