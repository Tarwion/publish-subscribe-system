/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
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
#include "pss.h"






void DL_Insert(info** head,int iTM,int iId,int* gids_arr,int size_of_gids_arr){
    info* start=*head;
    info*newnode=malloc(sizeof(info));
    newnode->iId=iId;
    newnode->itm=iTM;
    newnode->inext=NULL;
    newnode->iprev=NULL;
    for(int i=0;i<MG;i++){
        newnode->igp[i]=0;
    }
    for(int i=0;i<size_of_gids_arr-1;i++){
        newnode->igp[gids_arr[i]]=1;
    }
    if(*head==NULL){
        *head=newnode;
        return;
    }
    if(newnode->itm<(*head)->itm){
        newnode->inext=*head;
        if(head!=NULL){
            (*head)->iprev=newnode;
        }
        *head=newnode;
        return;
    }
    while(*head!=NULL){
        if((*head)->inext!=NULL){
            if((newnode->itm)<((*head)->inext->itm)){
                newnode->inext=(*head)->inext;
                newnode->iprev=*head;
                (*head)->inext->iprev=newnode;
                (*head)->inext=newnode;
                break;
            }
        }else{
            newnode->inext=(*head)->inext;
            newnode->iprev=*head;
            (*head)->inext=newnode;
            break;
        }
        *head=(*head)->inext;
    }
    *head=start;
}

void DL_Print(info*head){
    info*temp=head;
    while(head!=NULL){
        printf("%d ",head->iId);
        temp=head;
        head=head->inext;
    }
    /*printf("info list in reverse: ");
    while(temp!=NULL){
        printf("%d ",temp->iId);
        temp=temp->iprev;
    }*/
}

int DL_LookUp(info*head,int iid){
    while(head!=NULL){
        if(head->iId==iid){
            return 1;
        }
        head=head->inext;
    }
    return 0;
}

int DL_Delete(info **head,int iid){
    info*start=*head;

    if(*head==NULL){
        return 0;
    }
    if(start->iId==iid){
        *head=(*head)->inext;
        (*head)->iprev=NULL;
        free(start);
        return 1;
    }
    while((*head)->inext!=NULL){
        if((*head)->inext->iId==iid){
            info*temp=(*head)->inext;
            (*head)->inext=(*head)->inext->inext;
            if((*head)->inext!=NULL){
                (*head)->inext->iprev=(*head);
            }
            free(temp);
            *head=start;
            return 1;
        }
        *head=(*head)->inext;
    }
    *head=start;
    return 0;
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
        printf("%d ",head->sId);
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




subinfo* SL_create(int sid,int stm,info*info,int index){
    subinfo* subhead;
    subhead=(subinfo*)malloc(sizeof(subinfo));
    subhead->sId=sid;
    subhead->stm=stm;
    subhead->snext=NULL;
    subhead->sgp[index]=info;
    for(int i=0;i<MG;i++){
        if(i!=index){
            subhead->sgp[i]=(struct Info *) 1;
        }
    }
    return subhead;
}

void SL_Insert(subinfo** head,subinfo*newnode){
    subinfo* start=*head;
    if(*head==NULL){
        *head=newnode;
        return;
    }
    if(newnode->stm<(*head)->stm){
        newnode->snext=*head;
        *head=newnode;
        return;
    }
    while(*head!=NULL){
        if((*head)->snext!=NULL){
            if((newnode->stm)<((*head)->snext->stm)){
                newnode->snext=(*head)->snext;
                (*head)->snext=newnode;
                break;
            }
        }else{
            newnode->snext=(*head)->snext;
            (*head)->snext=newnode;
            break;
        }
        *head=(*head)->snext;
    }
    *head=start;
}
void SL_Print(subinfo*head){
    while(head!=NULL){
        printf("%d ",head->sId);
        head=head->snext;
    }
}

int SL_Delete(subinfo **head,int sid){
    subinfo*start=*head;

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
            subinfo*temp=(*head)->snext;
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

int SL_LookUp(subinfo*head,int sid){
    while(head!=NULL){
        if(head->sId==sid){
            return 1;
        }
        head=head->snext;
    }
    return 0;
}


/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(group**head){
    for(int i=0;i<64;i++){

    }

    return EXIT_SUCCESS;
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(group*groups,subinfo*S){
    for(int i=0;i<MG;i++){
        while(groups[i].gfirst!=NULL){
            info *temp=groups[i].gfirst;
            groups[i].gfirst=groups[i].gfirst->inext;
            free(temp);
        }
        while(groups[i].ggsub!=NULL){
            sub *temp=groups[i].ggsub;
            groups[i].ggsub=groups[i].ggsub->snext;
            free(temp);
        }
    }
    while(S!=NULL){
            subinfo *temp=S;
            S=S->snext;
            free(temp);
        }
    return EXIT_SUCCESS;
}
void subscriber_update(group* groups,subinfo*s){
    for(int i=0;i<MG;i++){
        if(s->sgp[i]==NULL){
            if(groups[i].gfirst!=NULL){
                s->sgp[i]=groups[i].gfirst;
            }
        }
    }
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
int Insert_Info(group*groups,subinfo*s,int iTM,int iId,int* gids_arr,int size_of_gids_arr){
    for(int i=0;i<size_of_gids_arr-1;i++){
        if(!DL_LookUp(groups[gids_arr[i]].gfirst,iId)){
            DL_Insert(&groups[gids_arr[i]].gfirst,iTM,iId,gids_arr,size_of_gids_arr);
            info *temp1=groups[gids_arr[i]].gfirst;
            while(temp1!=NULL){
                if(temp1->inext==NULL){
                    groups[gids_arr[i]].glast=temp1;
                }
                temp1=temp1->inext;
            }
        }
        if(s!=NULL){
                while(s!=NULL){
                    subscriber_update(groups,s);
                    s=s->snext;
                }
            }
    }
    printf("\n");
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
int Subscriber_Registration(subinfo **S,group*groups,int sTM,int sId,int* gids_arr,int size_of_gids_arr){
    if(!SL_LookUp(*S,sId)){
    subinfo *temp=malloc(sizeof(subinfo));
        temp->sId=sId;
        temp->stm=sTM;
        temp->snext=NULL;
        for(int i=0;i<MG;i++){
            temp->sgp[i]=1;
        }
        for(int i=0;i<size_of_gids_arr-1;i++){
            L_Insert(&groups[gids_arr[i]].ggsub,L_create(sId,sTM));
            temp->sgp[gids_arr[i]]=groups[gids_arr[i]].gfirst;
        }

        SL_Insert(S,temp);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
    
}

/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(subinfo*S,int sId){
    while(S!=NULL){
        if(S->sId==sId){
            for(int i=0;i<MG;i++){
                if(S->sgp[i]!=1 && S->sgp[i]!=NULL){
                    while(S->sgp[i]->inext!=NULL){
                        printf("subscriber %d consumed info %d in group %d\n",sId,S->sgp[i]->iId,i);
                        S->sgp[i]=S->sgp[i]->inext;
                    }
                    printf("subscriber %d consumed info %d in group %d\n",sId,S->sgp[i]->iId,i);
                }
            }
        }
        S=S->snext;
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(subinfo**s,group*groups,int sId){
    subinfo*temp=*s;
    if(SL_LookUp(temp,sId)){
        while(temp!=NULL){
            if(temp->sId==sId){
                for(int i=0;i<63;i++){
                    if(temp->sgp!=1){
                        L_Delete(&groups[i].ggsub,sId);
                    }
                }
            }
            temp=temp->snext;
        }
        SL_Delete(s,sId);
        return EXIT_SUCCESS; 
    }else{
        return EXIT_FAILURE;
    }
    
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(group*groups,subinfo *S){
    for(int i=0;i<64;i++){
            printf("GROUPID =%d INFOLIST= ",groups[i].gId);
            DL_Print(groups[i].gfirst);
            printf("SUBLIST= ");
            L_Print(groups[i].ggsub);
            printf("\n");
    }

    while(S!=NULL){
        printf("SUBSCRIBERID = %d,GROUPLIST=",S->sId);
        for(int i=0;i<MG;i++){
            if(S->sgp[i]!=1 && S->sgp[i]!=NULL){
                printf("%d ",i);
            }
        }
        printf("\n");
        S=S->snext;
    }
    return EXIT_SUCCESS;
}
