#include<stdio.h>
#include<stdlib.h>//malloc用
#define DUMMY -1//ダミーデータ
#define NODATA 0//データ無し
#define EXISTDATA 1//データあり

/*
double型データを保持するセル
スタックで用いる
自己参照構造体
 */
struct doubleCell{
  double data;             //データ部
  struct doubleCell * next;//ポインタ部
};

typedef struct doubleCell DoubleCell ;
typedef DoubleCell* DoubleStack; //スタック型
typedef DoubleCell* Cell_P; //セル型

DoubleStack makeStack();//スタックの作成
void push(DoubleStack stack,double data);//データ挿入
double pop(DoubleStack stack);//データ取り出し
double isEmpty(DoubleStack stack);//空のテスト
void printStack(DoubleStack stack);//リスト表示
void fscanToStack(FILE*fp,DoubleStack stack);//ファイルからのデータ入力
void reverse_fprint(FILE*fp,DoubleStack stack);//ファイルへ逆順に出力
Cell_P makeCell(double n);//セル作成

int main(){
  //スタックの動作
  DoubleStack stack;
  FILE *fp_in,*fp_out;

  stack=makeStack();//スタック生成
  fp_in=fopen("IntData","r");
  fscanToStack(fp_in,stack);
  fclose(fp_in);

  printf("スタックを表示します。\n");
  printStack(stack);

  printf("ファイルへ逆順に出力します。\n");
  fp_out=fopen("IntReverse","w");
  reverse_fprint(fp_out,stack);//ファイルへ逆順に出力
  fclose(fp_in);

  printf("スタックを表示します。\n");
  printStack(stack);

  return 0;
}

DoubleStack makeStack(){
  DoubleStack stack=(DoubleStack)makeCell(DUMMY);//ダミーのセル
}

double isEmpty(DoubleStack stack){
  if(stack->next==NULL){
    return NODATA;
  }else{
    return EXISTDATA;
  }
}


Cell_P makeCell(double n){
  Cell_P new =(Cell_P)malloc(sizeof(DoubleCell));
  new->data=n;
  return new;
}

void push(DoubleStack stack,double data){
  Cell_P new_cell=makeCell(data);
  new_cell->next=stack->next;
  stack->next=new_cell;
  return;
}

double pop(DoubleStack stack){
  Cell_P top=stack->next;
  int data;
  if(top!=NULL){
    data=top->data;
    stack->next=top->next;
    free(top);
    return data;
  }else{
    printf("No data\n");
    return -1;
  }
}

void printStack(DoubleStack stack){
  Cell_P p=stack->next;
  printf("(");
  while(p!=NULL){
    printf("\%3f,",p->data);
    p=p->next;
  }
  printf("]\n");
  return ;
}

void fscanToStack(FILE *fp,DoubleStack stack){
  double idata;
  while(fscanf(fp,"%lf",&idata)!=EOF){
    push(stack,idata);
  }
  return;
}

void reverse_fprint(FILE*fp,DoubleStack stack){
  double idata;
  while(isEmpty(stack)==EXISTDATA){
    idata=pop(stack);
    fprintf(fp,"%3f",idata);
  }
  return ;
}


  
  

