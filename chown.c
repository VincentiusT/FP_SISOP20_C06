#include "types.h"
#include "user.h"

int main(int argc, char* argv[]){
    char owner[100];
    char group[100];
    if(argc > 2){
        int isGroup=0,ownerIdx=0,groupIdx=0;
        const char *temp = argv[1];
        for(int i=0; i< strlen(temp); i++){
            if (temp[i] == ':') {
                isGroup = 1;
                continue;
            }

            if (isGroup==0){ //ubah owner
                owner[ownerIdx]=temp[i];
                ownerIdx++;
            }
            else if (isGroup==1){ //ubah group
                group[groupIdx]=temp[i];
                groupIdx++;
            }
        }
        printf(1, "owner : %s\ngroup : %s\n", owner, group);
        int own = atoi(owner);
        int grp = atoi(group);
        if(own >= 0 && grp >= 0){
            if(chown(argv[2], own, grp) < 0){
                printf(1, "chown %s failed \n", argv[2]);
            }
            else{
                printf(1, "updated..\n");
            }
        }
        else{
            printf(1,"Argumen salah\n");
        }
    }
    else{
      printf(1,"Argumen salah\n");
    }

    exit();
}
