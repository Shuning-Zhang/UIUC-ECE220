#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
/*
in this mp through the functions and tuplesread the list, and put things in order
and then print and safe teh value
*/




sp_tuples * load_tuples(char* input_file)
{
  FILE *reader = fopen(input_file,"r");

  sp_tuples*list =(sp_tuples*) malloc(sizeof(sp_tuples));
  //char enter;
  int row,col;
  double value;
  fscanf(reader,"%d %d",&list->m,&list->n);//read the dimension into the list
  list->nz = 0;//set the value for nz and tuples_head
  list->tuples_head = NULL;

  while(fscanf(reader,"%d %d %lf",&row,&col,&value) != EOF){//loop through the file
    set_tuples(list,row,col,value);//put the value in correct place
  }
  fclose(reader);
  return list;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
  if(mat_t == NULL){
    return 0;
  }
    sp_tuples_node*cNode = mat_t->tuples_head;//set up the pointer
    while(cNode != NULL){//check if reached end
      if((cNode->row == row)&&(cNode->col ==col)){//find the correct cell
        return cNode->value;//return the value
      }
        cNode = cNode->next;//check the next node for correct space

    }
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  if(mat_t == NULL){
    return;
  }
  sp_tuples_node *node = mat_t->tuples_head;
  sp_tuples_node *pre = NULL;
  sp_tuples_node *NewNode = NULL;
  if(value == 0){//if value is zero, delete node and free pointer
    while(node != NULL){//loop
      if(node->row == row && node->col == col){//found in list
        if(pre == NULL)
        {//node at start of the list
          mat_t->tuples_head = node->next;
          free(node);
        }else
        {
          pre->next = node->next;
          free(node);
        }
        mat_t->nz--;
      }
      pre = node;//increase the pointer
      node = node->next;
    }//end loop
    return;
  }
  if(node == NULL){//nothing in list
    node =(sp_tuples_node*) malloc(sizeof(sp_tuples_node));
    node->row = row;
    node->col = col;
    node->value = value;
    node->next = NULL;
    mat_t->tuples_head = node;
    mat_t->nz++;
    return;
  }
  node = mat_t->tuples_head;
  while(node != NULL){//loop to find if the node exist
    if(node->row == row && node->col == col){//node exist
      node->value = value;
      return;
    }
    node = node->next;//increase the node
  }

  node = mat_t->tuples_head;
  while(node != NULL){//end when reach the end of the loop
    if((node->row > row)||(node->row == row && node->col > col)){
      NewNode =(sp_tuples_node*) malloc(sizeof(sp_tuples_node));
      NewNode->row = row;
      NewNode->col = col;
      NewNode->value = value;
      NewNode->next = node;
      mat_t->nz++;

      if(pre == NULL){//newnode at start of the list
        mat_t->tuples_head = NewNode;
        return;
      }else{
        pre->next = NewNode;
        return;
      }
    }
    pre = node;//increase node
    node = node->next;
  }
  //add node at the end
  node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
  node->row = row;
  node->col = col;
  node->value = value;
  node->next = NULL;
  pre->next = node;
  mat_t->nz++;

  return;

}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    if(mat_t == NULL){
      return;
    }
    FILE *reader = fopen(file_name,"w");

    sp_tuples_node*node = mat_t->tuples_head;//get the value stored in node
    fprintf(reader,"%d %d\n",mat_t->m,mat_t->n);//print dimension
    while(node != NULL){
      fprintf(reader,"%d %d %lf\n",node->row,node->col,node->value);//print the node value
      //cNode++;
      node = node->next;//go to next node
    }
    fclose(reader);

  return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  //int i,j;
  //double v;
  if(matA == NULL || matB == NULL){
    return NULL;
  }
  if(matA->m != matB->m || matA->n != matB->n){
    return NULL;
  }
  sp_tuples *matAdd = (sp_tuples*)malloc(sizeof(sp_tuples));//set up the list
  matAdd->m = matA->m;
  matAdd->n = matA->n;
  matAdd->nz=0;
  sp_tuples_node *nodeA = matA->tuples_head;//setup th ehead node
  sp_tuples_node *nodeB = matB->tuples_head;// set up the end node

  while(nodeA != NULL){//add the value of matA into the add list using set_tuples function
    //i = nodeA->row;
    //j = nodeA->col;
    //v = nodeA->value + gv_tuples(matAdd,i,j);
    //set_tuples(matAdd,i,j,v);
    set_tuples(matAdd,nodeA->row,nodeA->col,(nodeA->value+gv_tuples(matAdd,nodeA->row,nodeA->col)));
    nodeA = nodeA->next;
  }
  while(nodeB != NULL){//add the value of matB into the add list using set_tuples function
    //i = nodeB->row;
    //j = nodeB->col;
    //v = nodeB->value + gv_tuples(matAdd,i,j);
    //set_tuples(matAdd,i,j,v);
    set_tuples(matAdd,nodeB->row,nodeB->col,(nodeB->value+gv_tuples(matAdd,nodeB->row,nodeB->col)));
    //get the value at node b and add the already stored value in list add(which is the value of matA)
    nodeB = nodeB->next;
  }
  return matAdd;
}


// Optional (not graded)
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
  return NULL;
}



void destroy_tuples(sp_tuples * mat_t){

    if(mat_t != NULL){//free the pointer first
      sp_tuples_node*cNode = mat_t->tuples_head;
      sp_tuples_node*temp = NULL;//the node use for free;
      while(cNode != NULL){
        temp = cNode;
        cNode = cNode->next; //get the next node
        free(temp);//free the current node
      }
      free(mat_t);//free the whole thing
    }
    return;
}

/*
if(mat_t->tuples_head == NULL){//if nothing in the list
  if(value == 0){return;}

  mat_t->nz++; //update the nz
  sp_tuples_node*create =(sp_tuples_node*)malloc(sizeof(sp_tuples_node));//create a new space
  create->row = row;//updte the row value
  create->col = col;//update the col value
  create->value = value;//update the value of the node
  create->next = NULL;//end the list
  mat_t->tuples_head = create;//point the head pointer to the start of the list
  return;
}else{//add a node in
  sp_tuples_node*pNode = NULL;//set the pNode
  sp_tuples_node*cNode = mat_t->tuples_head; //set the cNode
  //pNode->next = cNode;
//loop begins
  while(cNode != NULL){

    if((cNode->row == row) && (cNode->col ==col)){ //find the spot is in the list
      if(value == 0){//if value is 0, delete and free the node
        if(cNode == mat_t->tuples_head){
          pNode = cNode;
          mat_t->tuples_head=cNode->next;
        }
        else{//if not the start of the list
          pNode=cNode;
          cNode->next = cNode->next->next;
        }
        free(pNode);
        mat_t->nz--;//update the nz value
        return;
      }

      else{
        cNode->value = value;//value is not zero update the list
        return;
      }
    }//above is if the space already exits eith delete or replace the node depend on value


    if((cNode->row >= row) && (value != 0)){//add a node in
      if((row == cNode->row) && (col < cNode->col)){//at the right row
        sp_tuples_node*create =(sp_tuples_node*)malloc(sizeof(sp_tuples_node));//create a new space
        create->row = row;
        create->col = col;
        create->value = value;
        create->next = cNode;
        if(cNode != mat_t->tuples_head){//same as earlier
          pNode->next = create;
        }else{
          mat_t->tuples_head = create;
        }
        mat_t->nz++;
        return;
      }else if(row < cNode->row){//add the case where the row number are not the same
        sp_tuples_node*create =(sp_tuples_node*)malloc(sizeof(sp_tuples_node));//create a new space
        create->row = row;
        create->col = col;
        create->value = value;
        create->next = cNode;
        if(cNode != mat_t->tuples_head){//same as earlier
          pNode->next = create;
        }else{
          mat_t->tuples_head = create;
        }
        mat_t->nz++;
        return;
      }
    }
    pNode = cNode;//loop
    cNode = cNode->next;//increase the node
  }



//loop ends
  if(value != 0){//if value is not zero add to the end of list

    mat_t->nz++; //update the nz
    sp_tuples_node*create =(sp_tuples_node*)malloc(sizeof(sp_tuples_node));//create a new space
    create->row = row;//updte the row value
    create->col = col;//update the col value
    create->value = value;//update the value of the node
    create->next = NULL;//end the list
    mat_t->tuples_head = create;//point the head pointer to the start of the list
  }
  return;
}
*/
