/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr), John Petropoulos (johnpetr@csd.uoc.gr)
 * @Version 30-11-2022
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pss.h"

int randa;
int randb;
int biig;
int hash_table_size;


void freetreeinfo(treeinfo*root){
    if(root!=NULL){
        freetreeinfo(root->tlc);
        freetreeinfo(root->trc);
        free(root);
        root==NULL;
    }
}

void freeinfo(info*root){
    if(root!=NULL){
        freeinfo(root->ilc);
        freeinfo(root->irc);
        free(root);
        root==NULL;
    }
}

sub* L_create(int sid,int stm){
    sub* subhead;
    subhead=(sub*)malloc(sizeof(sub));
    subhead->sId=sid;
    subhead->snext=NULL;
    return subhead;
}

void L_Insert(sub** head,sub*newnode){
    sub* start=*head;
    if(start==NULL){
        *head=newnode;
        return;
    }
    newnode->snext=*head;
    *head=newnode;
}

void L_Print(sub*head){
    while(head!=NULL){
        printf(" %d",head->sId);
        head=head->snext;
    }
}

int L_Delete(sub **head,int sid){
    sub*start=*head;

    if(*head==NULL){
        return 0;
    }
    if(start->sId==sid){
        *head=(*head)->snext;
        free(start);
        return 1;
    }
    while((*head)->snext!=NULL){
        if((*head)->snext->sId==sid){
            sub*temp=(*head)->snext;
            (*head)->snext=(*head)->snext->snext;
            free(temp);
            *head=start;
            return 1;
        }
        *head=(*head)->snext;
    }
    *head=start;
    return 0;
}

int L_LookUp(sub*head,int sid){
    while(head!=NULL){
        if(head->sId==sid){
            return 1;
        }
        head=head->snext;
    }
    return 0;
}

void connect(treeinfo*root){
    treeinfo*temp=root;
    treeinfo*prev=root; 
        while(1){
            prev=root;
            root=root->tp;
            if(root==NULL){
                break;
            }
            if(root->tlc!=NULL && root->tlc!=prev){
                root=root->tlc;
                break;
            }
        }
        if(root!=NULL){
            while(root->trc!=NULL && root->trc!=temp){
            root=root->trc;
        }
        root->next=temp;
        }
        
}

treeinfo* newleaflo(int id,int tm){
    treeinfo*leaf=malloc(sizeof(treeinfo));
    leaf->next=NULL;
    leaf->tid=id;
    leaf->ttm=tm;
    leaf->tp=NULL;
    leaf->tlc=NULL;
    leaf->trc=NULL;
    return leaf;
}

void LO_BST_Insert(treeinfo** root,treeinfo*newleaf){
    if(*root==NULL){
        *root=newleaf;
        return;
    }
    if((*root)->tlc==NULL){
        if((*root)->ttm<=newleaf->ttm){
            treeinfo*lc=newleaflo((*root)->tid,(*root)->ttm);                   
            lc->tlc=*root;
            lc->tp=(*root)->tp;
            (*root)->tp=lc;
            (*root)=lc;
             newleaf->tp=(*root);
             (*root)->trc=newleaf;
             connect((*root)->trc);
             connect((*root)->tlc);
            return;
        }else{
            treeinfo*lc=newleaflo(newleaf->tid,newleaf->ttm);
            treeinfo*temp=(*root);
            newleaf->tp=(*root)->tp;
            *root=newleaf;
            (*root)->trc=temp;
            temp->tp=*root;
            (*root)->tlc=lc;
            lc->tp=(*root);
            connect((*root)->trc);
            connect((*root)->tlc);
            return;
        }
    }
    if((*root)->ttm<=newleaf->ttm){
        LO_BST_Insert(&(*root)->trc,newleaf);
    }else{
        LO_BST_Insert(&(*root)->tlc,newleaf);
    }

}

void LO_BST_Print(treeinfo*root){
    if(root==NULL){
        return;
    }
    printf("%d  ",root->tid);
    LO_BST_Print(root->tlc);
    LO_BST_Print(root->trc);
}


int printsortlist(treeinfo*root){
    if(root==NULL){
        return 0;
    }
    while(root->tlc!=NULL){
        root=root->tlc;
    }

    while(root!=NULL){
        printf("%d ",root->tid);
        root=root->next;
    }
}


 int LO_BST_LookUp(treeinfo*root,int key){
    if(root->tlc==NULL){
        if(root->tid==key){
            return 1;
        }
        return 0;
    }
    if(root->tid>=key){
        return LO_BST_LookUp(root->tlc,key);
    }else{
        return LO_BST_LookUp(root->trc,key);
    }
 }


info* newleaf(int id,int tm){
    info* newleaf=malloc(sizeof(info));
    newleaf->iId=id;
    newleaf->itm=tm;
    newleaf->ip=NULL;
    newleaf->ilc=NULL;
    newleaf->irc=NULL;
    for(int i=0;i<MG;i++){
        newleaf->ipg[i]=0;
    }
    return newleaf;
}

void BST_Insert(info** root,info*newleaf){
    if(*root==NULL){
        *root=newleaf;
        return;
    }
    if((*root)->iId>newleaf->iId){
        newleaf->ip=*root;
        BST_Insert(&(*root)->ilc,newleaf);
    }
    if((*root)->iId<newleaf->iId){
        newleaf->ip=*root;
        BST_Insert(&(*root)->irc,newleaf);
    }
}
info* BST_FindLesser(info* root,int itm){
    info*temp=NULL;
    if(root==NULL){
        return NULL;
    }
    if(root->ilc!=NULL){
        temp=BST_FindLesser(root->ilc,itm);
    }
    if(root->itm<=itm){
        return root;
    }
    if(temp==NULL&&root->irc!=NULL){
        temp=BST_FindLesser(root->irc,itm);
    }

    return temp;
}

void BST_Delete(info** root,int id){
    if(*root==NULL){                     
        return;
    }
    if(id<(*root)->iId){
        BST_Delete(&(*root)->ilc,id);
    }else if(id>(*root)->iId){
        BST_Delete(&(*root)->irc,id);
    }else{
        if((*root)->ilc==NULL){
            info*temp=*root;
            if((*root)->irc!=NULL){
                (*root)->irc->ip=(*root)->ip;
            }
            *root=(*root)->irc;
            free(temp);
        }else if((*root)->irc==NULL){
            info*temp=*root;
            if((*root)->ilc!=NULL){
                (*root)->ilc->ip=(*root)->ip;
            }
            *root=(*root)->ilc;
            free(temp);
        }else{
            info*temp=(*root)->irc; //
            info*temp1;
            while(temp->ilc!=NULL){
                temp=temp->ilc;  //leftmost value of right tree
            }
            if(temp->ip->ilc==temp){
                temp->ip->ilc=NULL;
            }else{
                temp->ip->irc=NULL;
            }
            temp->ip=(*root)->ip;
            temp->ilc=(*root)->ilc;
            temp->irc=(*root)->irc;
            if(temp->irc){
                temp->irc->ip=temp;
            }
            if(temp->ilc){
                temp->ilc->ip=temp;
            }
            temp1=*root;
            *root=temp;
            free(temp1);
            return;
        }
    }
}


int BST_LookUp(info*root,int key){
    while(root!=NULL){
        if(key>(root->iId)){
        }
        if(key<(root->iId)){
            root=root->ilc;
        }else if(key>(root->iId)){
            root=root->irc;
        }else{
            return 1;
        }
    }
    return 0;
}

void BST_Print(info* root){
    if(root==NULL){
        return;
    }
    printf("%d ",root->iId);
    BST_Print(root->ilc);
    BST_Print(root->irc);
}


int Universal_Hash_Function(int key) {
    return (((randa * key) + randb) % biig) % hash_table_size;
}

subinfo* newleafht(int sid,int stm){
    subinfo* newleaf=malloc(sizeof(subinfo));
    newleaf->sId=sid;
    newleaf->stm=stm;
    newleaf->snext=NULL;
    for(int i=0;i<MG;i++){
        newleaf->sgp[i]=1;
        newleaf->tgp[i]=1;
    }
}


void HT_Insert(subinfo**T,subinfo*newnode){
    int index=Universal_Hash_Function(newnode->sId);
    printf("index %d",index);
    if(T[index]==NULL){
        T[index]=newnode;
    }else{
        subinfo*temp=T[index];
        while(temp->snext!=NULL){
            temp=temp->snext;
        }
        temp->snext=newnode;
    }

}

void HT_Delete(subinfo**T,int key){
    int index=Universal_Hash_Function(key);
    subinfo*temp=T[index],*prev=T[index];
    if(temp!=NULL && temp->sId==key){
        for(int i=0;i<MG;i++){
            if(temp->tgp[i]!=1 && temp->tgp[i]!=NULL){
                freetreeinfo(temp->tgp[i]);
            }
        }
        T[index]=T[index]->snext;
        free(temp);
        return;
    }
    while(temp!=NULL){
        if(temp->sId==key){
            subinfo*temp1=temp;
            prev->snext=temp->snext;
            for(int i=0;i<MG;i++){
                
                if(temp1->tgp[i]!=1 && temp1->tgp[i]!=NULL){
                    freetreeinfo(temp1->tgp[i]);
                }
            }
            free(temp1);
            return;
        }
        prev=temp;
        temp=temp->snext;

    }
}

subinfo* HT_LookUp(subinfo**T,int key){
    int index=Universal_Hash_Function(key);
    subinfo*temp=T[index];
    while(temp!=NULL){
        if(temp->sId==key){
            return temp;
        }
        temp=temp->snext;
    }
    return NULL;
}


void HT_Print(subinfo**T){
    for(int i=0;i<hash_table_size;i++){
        subinfo*temp=T[i];
        printf("row: %d  id:",i);
        while(temp!=NULL){
            printf(" %d  subbed groups: ",temp->sId);
            for(int i=0;i<MG;i++){
                if(temp->sgp[i]!=1){
                    printf(" %d",i);
                }
            }
            printf("\n");
            temp=temp->snext;
        }
        printf("\n");
    }
}



/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @param m Size of the hash table.
 * @param p Prime number for the universal hash functions.
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(int m, int p){
    randa=rand()%((m+1)-0) + 0;
    randb=rand()%((m+1)-1) + 1;
    biig=p;
    hash_table_size=m;
    return EXIT_SUCCESS;
}


/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(group*groups,subinfo**T){
    for(int i=0;i<hash_table_size;i++){
        subinfo*head=T[i];
        while(head!=NULL){
            subinfo*temp=head;
            head=head->snext;
            for(int j=0;j<MG;j++){
                if(temp->tgp[i]!=1){
                    freetreeinfo(temp->tgp[i]);
                }
            }
            free(temp);
        }
    }
    free(T);
    for(int i=0;i<MG;i++){
        sub*head=groups[i].gsub;
        while(head!=NULL){
            sub*temp=head;
            head=head->snext;
            free(temp);
        }
        freeinfo(groups[i].groot);
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(group* groups,subinfo**T,int iTM,int iId,int* gids_arr,int size_of_gids_arr){
    for(int i=0;i<size_of_gids_arr-1;i++){
        if(!BST_LookUp(groups[gids_arr[i]].groot,iId)){
            info*temp=newleaf(iId,iTM);
            for(int j=0;j<size_of_gids_arr-1;j++){
                temp->ipg[j]=1;
            }
            BST_Insert(&groups[gids_arr[i]].groot,temp);
            printf("GROUPID= %d,INFOLIST= ",gids_arr[i]);
            info*tempinfo=groups[gids_arr[i]].groot;
            BST_Print(tempinfo);
            printf("\n");
        }
    }
    /*for(int i=0;i<size_of_gids_arr-1;i++){
        sub*temp=groups[gids_arr[i]].gsub;
        while(temp!=NULL){
            subinfo*temp1=HT_LookUp(T,temp->sId);
            if(temp1!=NULL && temp1->sgp[gids_arr[i]]==NULL){
                temp1->sgp[gids_arr[i]]=groups[gids_arr[i]].groot;
            }
            temp=temp->snext;
        }
        
    }*/
    return EXIT_SUCCESS;
}
/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(subinfo **T,group*groups,int sTM,int sId,int* gids_arr,int size_of_gids_arr){
    if(HT_LookUp(T,sId)==NULL){
        subinfo* temp=newleafht(sId,sTM);
        printf("SUBSCRIBERLIST= %d\n",sId);
        for(int i=0;i<size_of_gids_arr-1;i++){
            temp->tgp[gids_arr[i]]=NULL;
            temp->sgp[gids_arr[i]]= temp->tgp[gids_arr[i]];
            L_Insert(&groups[gids_arr[i]].gsub,L_create(sId,sTM));
            printf("GROUPID= %d, SUBLIST= ",gids_arr[i]);
            sub*temp=groups[gids_arr[i]].gsub;
            while(temp!=NULL){
                printf("%d ",temp->sId);
                temp=temp->snext;
            }
            printf("\n");
        }
        HT_Insert(T,temp);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
/**
 * @brief Prune Information from server and forward it to client
 *
 * @param tm Information timestamp of arrival
 * @return 0 on success
 *          1 on failure
 */
int Prune(group*groups,subinfo**T,int tm){
    for(int i=0;i<MG;i++){
        info*temp=BST_FindLesser(groups[i].groot,tm);
        while(temp!=NULL){
            sub*temp1=groups[i].gsub;
            while(temp1!=NULL){
                subinfo* temp3=HT_LookUp(T,temp1->sId);
                LO_BST_Insert(&temp3->tgp[i],newleaflo(temp->iId,temp->itm));
                temp3->sgp[i]=temp3->tgp[i];
                while(temp3->sgp[i]->tlc!=NULL){
                    temp3->sgp[i]=temp3->sgp[i]->tlc;
                }
                temp1=temp1->snext;
            }
            BST_Delete(&groups[i].groot,temp->iId);
            temp=BST_FindLesser(groups[i].groot,tm);
        }
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(subinfo**T,int sId){
    subinfo*temp=HT_LookUp(T,sId);
    
    if(temp!=NULL){
        for(int i=0;i<MG;i++){
            if(temp->sgp[i]!=NULL && temp->sgp[i]!=1){
                while(temp->sgp[i]->next!=NULL){
                    temp->sgp[i]=temp->sgp[i]->next;
                }
            }
        }
        for(int i=0;i<MG;i++){
            if(temp->sgp[i]!=1){
                printf("GROUPID= %d ,TREELIST= ",i);
                printsortlist(temp->tgp[i]);
                if(temp->sgp[i]!=NULL){
                    printf(" ,NEWSGP= %d",temp->sgp[i]->tid);
                }
                printf("\n");
            }
        }
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(group*groups,subinfo**T,int sId){
    subinfo*temp=HT_LookUp(T,sId);
    if(temp!=NULL){
        for(int i=0;i<MG;i++){
            if(temp->sgp[i]!=1){
                L_Delete(&groups[i].gsub,sId);
            }
        }
        HT_Delete(T,sId);
        printf("hello");
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(group*groups,subinfo**T){
    int validgroups=0,subs=0;
    for(int i=0;i<MG;i++){
		printf("GROUPID= %d,INFOLIST= ",i);
        if(groups[i].groot!=NULL){
            validgroups++;
        }
		BST_Print(groups[i].groot);
		printf(",SUBLIST= ");
		sub*temp=groups[i].gsub;
		while(temp!=NULL){
			printf("%d ",temp->sId);
			temp=temp->snext;
		}
		printf("\n");
	}
	for(int i=0;i<hash_table_size;i++){
		subinfo*tempsubinfo=T[i];
		while(tempsubinfo!=NULL){
            subs++;
			printf("id: %d GROUPLIST:\n",tempsubinfo->sId);
			for(int j=0;j<MG;j++){
				if(tempsubinfo->sgp[j]!=1){
					printf("  GID: %d TREELIST: ",j);
					printsortlist(tempsubinfo->tgp[j]);
					printf("\n");
				}
			}
			tempsubinfo=tempsubinfo->snext;
		}
	}
    printf("NO_GROUPS = %d, NO_SUBSCRIBERS = %d\n",validgroups,subs);
    return EXIT_SUCCESS;
}


