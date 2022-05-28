#include "quest_graphics.h"
#include "stdlib.h"
#include "stdio.h"

/* Synthesizes a test version of task tree,
 * should be replaced after merging*/
task_tree_mockup_t* synthesizeTest1() {
    task_tree_mockup_t *TreeA = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeB = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeC = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeD = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeE = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeF = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeG = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeH = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));
    task_tree_mockup_t *TreeI = (task_tree_mockup_t*)malloc(sizeof(task_tree_mockup_t));

    TreeA->task_name="A";
    TreeA->rsibling=TreeB;
    TreeA->lmostchild=NULL;
    TreeA->parent=NULL;

    TreeB->task_name="B";
    TreeB->rsibling=TreeC;
    TreeB->lmostchild=TreeE;
    TreeB->parent = NULL;

    TreeC->task_name= "C";
    TreeC->rsibling=TreeD;
    TreeC->lmostchild=TreeG;
    TreeC->parent=NULL;

    TreeD->task_name="D";
    TreeD->rsibling=NULL;
    TreeD->lmostchild=NULL;
    TreeD->parent=NULL;

    TreeE->task_name="E";
    TreeE->rsibling=NULL;
    TreeE->lmostchild=TreeF;
    TreeE->parent=TreeB;

    TreeF->task_name="F";
    TreeF->rsibling=TreeH;
    TreeF->lmostchild=NULL;
    TreeF->parent=TreeE;

    TreeG->task_name="G";
    TreeG->rsibling=NULL;
    TreeG->lmostchild=NULL;
    TreeG->parent=TreeC;

    TreeH->task_name="H";
    TreeH->rsibling=TreeI;
    TreeH->lmostchild=NULL;
    TreeH->parent=TreeE;

    TreeI->task_name="I";
    TreeI->rsibling=NULL;
    TreeI->lmostchild=NULL;
    TreeI->parent=TreeE;

    return TreeA;

}


/* Runs an example of the Quest Graphics*/
int main() {
    task_tree_mockup_t *TreeA = synthesizeTest1();

    quest_graphics_t* quest_graphics=new_quest_graphics((Vector2){80,80},(Vector2){600,400},
                                    (Vector2){50,50},(Vector2){150,150},TreeA,"F",false,30);

    runTaskTreeGraphics(quest_graphics);

    free_quest_graphics(quest_graphics);

    return 0;
}
