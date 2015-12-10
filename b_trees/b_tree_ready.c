#include <stdio.h>

#define MAXKEYS 4
#define MINKEYS MAXKEYS/2
#define NIL (-1)
#define NOKEY '@'
#define NO 0
#define YES 1

typedef struct {
 short int keycount; // number of keys in page
 char key[MAXKEYS]; // the actual keys
 short int child[MAXKEYS+1]; // ptrs to rrns of descendants
} BTPAGE;

#define PAGESIZE sizeof(BTPAGE);

short int root; // rrn of root page
int btfd; // file descriptor of btree file
int infd; // file descriptor of input file

/* prototypes */
int btclose ();
int btopen ();
void btread (short rrn, BTPAGE *page_ptr);
void btwrite (short rrn, BTPAGE *page_ptr);
short create_root (char key, short left, short right);
short int create_tree();
short int getpage ();
short int getroot ();
insert (short int rrn, char key, short int *promo_r_child, char *promo_key);
void ins_in_page (char key, short int r_child, BTPAGE *p_page);
void pageinit (BTPAGE *p_page);
putroot(short int root);
int search_node (char key, BTPAGE *p_page, short int *pos);
void split(char key, short int r_child, BTPAGE *p_oldpage, char *promo_key, short int *promo_r_child, BTPAGE *p_newpage);

int main() {

  int promoted; // boolean: tells if a promotion from below
  short int root, // rrn of root page
  short int promo_rrn; // rrn promoted from below
  char promo_key, // key promoted from below
  char key; // next key to insert in tree

  if (btopen()) {
   root = getroot();
  } else {
   root = create_tree();
  }

  while ((key = getchar()) != 'q') {
   promoted = insert(root, key, &promo_rrn, &promo_key);
   if (promoted)
    root = create_root(promo_key, root, promo_rrn);
  }
  btclose();
}

insert(short rrn, char key, short *promo_r_child, char *promo_key){

  BTPAGE page; // current page
  BTPAGE newpage; // new page created if split occurs

  int found, promoted; // boolean values
  short int pos;
  short int p_b_rrn; // rrn promoted from below
  char p_b_key; // key promoted from below

  if (rrn == NIL) {
   *promo_key = key;
   *promo_r_child = NIL;
   return YES;
  }

  btread(rrn, &page);
  found = search_node(key, &page, &pos);
  if (found) {
   printf ("Error: attempt to insert duplicate key: %c \n\007", key);
   return 0;
  }

  promoted = insert(page.child[pos], key, &p_b_rrn, &p_b_key);

  if (!promoted) {
   return NO;
  }

  if (page.keycount < MAXKEYS) {
   ins_in_page(p_b_key, p_b_rrn, &page);
   btwrite(rrn, &page);
   return NO;
  } else {
   split(p_b_key, p_b_rrn, &page, promo_key, promo_r_child, &newpage);
   btwrite(rrn, &page);
   btwrite(*promo_r_child, &newpage);
   return(YES);
  }

}

btopen() {

 btfd = fopen("btree.dat", "r+");
 return (btfd > 0);

}

btclose(){
 close(btfd);
}

short getroot(){
 short root;
 long lseek();
 lseek(btfd, 0L, 0);

 if (read(btfd, &root, 2) == 0){
   printf("Error: Unable to get root. \007\n");
   exit(1);
 }

 return (root);
}

putroot(short root){
 lseek(btfd, 0L, 0);
 write(btfd, &root, 2);
}

short int create_tree(){

 char key;
 btfd = creat("btree.dat",PMODE);
 close (btfd);
 btopen();
 key = getchar();
 return create_root(key, NIL, NIL);
}

short getpage() {
 long lseek(), addr;
 addr = lseek(btfd, 0L, 2) - 2L;
 return ((short) addr / PAGESIZE);
}

void btread (short rrn, BTPAGE *page_ptr){

 long lseek(), add;
 addr = (long)rrn * (long)PAGESIZE + 2L;
 lseek(btfd, addr, 0);
 return read(btfd, page_ptr, PAGESIZE);
}

void btwrite(short rrn, BTPAGE *page_ptr){

 long lseek(), addr;
 addr = (long)rrn * (long)PAGESIZE +2L;
 lseek(btfd, addr, 0);
 return(write(btfd, page_ptr, PAGESIZE));
}

short create_root(char key, short left, short right){

 BTPAGE page;

 short rrn;

 rrn = getpage();

 pageinit (&page);

 page.key[0] = key;

 page.child[0] = left;

 page.child[1] = right;

 page.keycount = 1;

 btwrite(rrn, &page);

 putroot(rrn);

 return(rrn);

}

void pageinit(BTPAGE *p_page){

 int j;
 for (j = 0; j < MAXKEYS; j++){
   p_page->key[j] = NOKEY;
   p_page->child[j] = NIL;
 }
 p_page->child[MAXKEYS] = NIL;
}

int search_node(char key, BTPAGE *p_page, short *pos){

 int i;
 for (i = 0; i < p_page->keycount && key > p_page->key[i]; i++);
 *pos = i;
 if (*pos < p_page->keycount && key == p_page->key[*pos]){
   return YES;
 } else {
   return NO;
 }
}

void ins_in_page(char key,short r_child, BTPAGE *p_page){

 int j;
 for(j = p_page-> keycount; key < p_page->key[j-1] && j > 0; j--){
 p_page->key[j] = p_page->key[j-1];
 p_page->child[j+1] = p_page->child[j];
 }

 p_page->keycount++;
 p_page->key[j] = key;
 p_page->child[j+1] = r_child;
}

void split(char key, short r_child, BTPAGE *p_oldpage, char *promo_key, short *promo_r_child, BTPAGE *p_newpage){

 int j;
 short mid;
 char workkeys[MAXKEYS+1];
 short workchil[MAXKEYS+2];

 for (j = 0; j < MAXKEYS; j++){
 workkeys[j] = p_oldpage->key[j];
 workchil[j] = p_oldpage->child[j];
 }

 workchil[j] = p_oldpage->child[j];

 for (j = MAXKEYS; key < workkeys[j-1] && j > 0; j--){
 workkeys[j] = workkeys[j-1];
 workchil[j+1] = workchil[j];
 }

 workkeys[j] = key;
 workchil[j+1] = r_child;
 *promo_r_child = getpage();

 pageinit(p_newpage);

 for (j = 0; j < MINKEYS; j++){
 p_oldpage->key[j] = workkeys[j];
 p_oldpage->child[j] = workchil[j];
 p_newpage->key[j] = workkeys[j+1+MINKEYS];
 p_newpage->child[j] = workchil[j+1+MINKEYS];
 p_oldpage->key[j+MINKEYS] = NOKEY;
 p_oldpage->child[j+1+MINKEYS] = NIL;
 }

 p_oldpage->child[MINKEYS] = workchil[MINKEYS];
 p_newpage->child[MINKEYS] = workchil[j+1+MINKEYS];
 p_newpage->keycount = MAXKEYS - MINKEYS;
 p_oldpage->keycount = MINKEYS;
 *promo_key = workkeys[MINKEYS];
}
