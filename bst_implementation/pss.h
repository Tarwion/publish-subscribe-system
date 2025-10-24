/***************************************************************
 *
 * file: pss.h
 *
 * @Authors  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr), John Petropoulos (johnpetr@csd.uoc.gr)
 * @Version 30-11-2022
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Header file for the Public Subscribe System,
 * with the structures and function prototypes
 *
 ***************************************************************
 */

#ifndef pss_h
#define pss_h
#define MG 64

typedef struct Info{
    struct Info *ip;
    int iId;
    int itm;
    int ipg[64];
    struct Info *ilc;
    struct Info *irc;
} info;
typedef struct Subscription {
    int sId;
    struct Subscription *snext;
}sub;
typedef struct Group {
    int gId;
    struct Subscription *gsub;
    struct Info *groot;
}group;

typedef struct SubInfo{
int sId;
int stm;
struct TreeInfo *tgp[MG];
struct TreeInfo *sgp[MG]; 
struct SubInfo *snext;
}subinfo;

typedef struct TreeInfo{
    struct TreeInfo*tp;
    int tid;
    int ttm;
    struct TreeInfo*next;
    struct TreeInfo*tlc;
    struct TreeInfo*trc;
}treeinfo;

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @param m Size of hash table
 * @param p Prime number for the universal hash function
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(int m, int p);

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(group*groups,subinfo**T);

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
int Insert_Info(group* groups,subinfo**T,int iTM,int iId,int* gids_arr,int size_of_gids_arr);

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
int Subscriber_Registration(subinfo **T,group*groups,int sTM,int sId,int* gids_arr,int size_of_gids_arr);

/**
 * @brief Prune Information from server and forward it to client
 *
 * @param tm Information timestamp of arrival
 * @return 0 on success
 *          1 on failure
 */
int Prune(group*groups,subinfo**T,int tm);

/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(subinfo**T,int sId);

/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(group*groups,subinfo**T,int sId);

/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(group*groups,subinfo**T);

#endif /* pss_h */

