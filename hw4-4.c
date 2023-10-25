
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int count;
    scanf("%d", &count);
    assert( count >= 1 && count <= 10);
    int data[count][count];
    for(int i = 0; i < count; i++){
        for(int j = 0; j < count; j++) scanf("%d", &data[i][j]);
    }

    int max, boy, girl, i, j;
    for(int k = 0; k < count; k++){
        max = 0;
        boy = 0;
        girl = 0;
        for(i = 0; i < count; i++){ // 抓最大值
            for(j = 0; j < count; j++) if(data[i][j] > max) max = data[i][j];
        }

        for(i = 0; i < count; i++){ // 用最大值判斷輸出
            for(j = 0; j < count; j++){
                if(data[i][j] == max){
                    boy = i;
                    girl = j;
                    printf("boy %d pair with girl %d\n", (boy + 1), (girl + 1));
                }
            }
        }

        for(i = 0; i < count; i++){ // 清除使用過的
            for(j = 0; j < count; j++) if(i == boy || j == girl) data[i][j] = 0;
        }
    }
}
