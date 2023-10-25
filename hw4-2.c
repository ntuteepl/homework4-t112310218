
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main()
{
    int data[6][3] = {
        {123, 456, 9000},
        {456, 789, 5000},
        {789, 888, 6000},
        {336, 558, 10000},
        {775, 666, 12000},
        {566, 221, 7000}
    };

    int count, account, password;

    scanf("%d", &count);
    assert(count >= 0 && count <= 10);

    for(int i = 0; i < count; i++){
        bool used = false;
        scanf("%d%d", &account, & password);
        for(int j = 0; j < 6; j++){
            if(data[j][0] == account && data[j][1] == password){
                printf("%d\n", data[j][2]);
                used = true;
            }
        }
        if(!used) printf("error\n");
    }


    return 0;
}
