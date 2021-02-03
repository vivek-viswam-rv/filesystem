#define NAME_SIZE 50
#define DELIMITER "/"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum _node_type{FILE_TYPE,DIR_TYPE};

typedef struct _node_t{
    char name[NAME_SIZE];
    int type;
    char path[NAME_SIZE];
    struct _node_t *parent;
    struct _node_t *child;
    struct _node_t *next;
}node_t;

node_t *ROOT=NULL;

int check_name(node_t *node,char *name){
    if(!strcmp(node->name,name)) return 1;
    return 0;
}

int add_child_n(node_t *parent,node_t *child){
    node_t *temp;
    int flag=0;
    if(parent==NULL) return 0;
    if(parent->child==NULL){
        parent->child=child;
        child->parent=parent;
        return 1;
    }
    temp=parent->child;
    while(temp->next!=NULL){
        if(check_name(temp,child->name)){
            printf("[!] File/Directory already exists\n");
            return 0;
        }
        temp=temp->next;
    }
    if(check_name(temp,child->name)){
        printf("%s and %s", temp->name,child->name);
        printf("%s and %s", temp->name,child->name);
        printf("[!] File/Directory already exists\n");
        return 0;
    }
    child->parent=parent;
    temp->next=child;
    return 1;
}

node_t *get_child(node_t *search_root,char *name){
    node_t *temp;
    if(search_root==NULL) return NULL;
    if(check_name(search_root,name)) return search_root;
    if(search_root->child==NULL) return NULL;
    temp=search_root->child;
    while (temp->next!=NULL){
        if(check_name(temp,name)) return temp;
        temp=temp->next;
    }
    if(check_name(temp,name)) return temp;
    return NULL;
}

node_t *get_loc(char *path){
    node_t *loc=ROOT;
    for(char *dir=strtok(path,DELIMITER);dir!=NULL;dir=strtok(NULL,DELIMITER)){
        loc=get_child(loc,dir);
        if(loc==NULL) return NULL;
    }
    return loc;
}

node_t *create_n(char *name,char *path,int type){
    node_t *new_node;
    new_node=(node_t *)malloc(sizeof(node_t));
    strcpy(new_node->name,name);
    new_node->type=type;
    strcpy(new_node->path,path);
    new_node->parent=NULL;
    new_node->child=NULL;
    new_node->next=NULL;
    return new_node;
}

int insert_n(char *path,node_t *node){
    node_t *loc;
    if(ROOT==NULL){
        ROOT=create_n("root","",DIR_TYPE);
    }
    loc=get_loc(path);
    if(loc==NULL){
        printf("[x] Invalid path\n");
        return 0;
    }
    if(add_child_n(loc,node))
        printf("[!]Added %s to %s successfully\n",node->name,node->path);
        return 1;
    printf("[x] Failed!");
    return 0;
}

int search(node_t *search_root,char *name){
    node_t *temp;
    if(search_root==NULL) return 0;
    if(check_name(search_root,name)){
        printf("path\t: %s\n",search_root->path);
    }
    search(search_root->child,name);
    search(search_root->next,name);
    return 1;
}

int delete(char *path,char *file_name){
    node_t *parent;
    node_t *temp;
    parent=get_loc(path);
    if(parent==NULL){
        printf("[!] Path not found\n");
        return 0;
    }
    if(parent->child==NULL){
        printf("[!] File not found\n");
        return 0;
    }
    if(check_name(parent->child->name,file_name)){
            parent->child=parent->child->next;
            printf("[!]Deleted %s\n",file_name);
            return 1;
    }
    temp=parent->child;
    while(temp->next!=NULL){
        if(check_name(temp->next->name,file_name)){
            temp->next=temp->next->next;
            printf("[!]Deleted %s\n",file_name);
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

int display(node_t *search_root){
    if(search_root==NULL) return 0;
    printf("%s/%s\n",search_root->path,search_root->name);
    display(search_root->next);
    display(search_root->child);
}

int menu(){
    int opt;
    int flag=1;
    char file_name[NAME_SIZE];
    char path[NAME_SIZE];
    node_t *new_node;
    int type;

    while(flag){
        printf("\n\n1.Insert\n");
        printf("2.Search\n");
        printf("3.Delete\n");
        printf("4.Display\n");
        printf("5.Exit\n");
        printf("Option: ");
        scanf("%d",&opt);
        getchar();

        switch(opt){
            case 1:
                printf("Name\t: ");
                gets(file_name);
                printf("Path\t: ");
                gets(path);
                printf("File/Dir (0,1)\t: ");
                scanf("%d",&type);
                getchar();
                new_node=create_n(file_name,path,type);
                if(!insert_n(path,new_node))
                    free(new_node);
                break;
            case 2:
                printf("Name\t: ");
                gets(file_name);
                search(ROOT,file_name);
                break;
            case 3:
                printf("Name\t: ");
                gets(file_name);
                printf("Path\t: ");
                gets(path);
                delete(path,file_name);
                break;
            case 4:
                printf("\nContents\n");
                display(ROOT);
                break;
            case 5:
                flag=0;
                break;
        }
    }

}

int main(){
    menu();
}