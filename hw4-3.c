#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    // {發車, 回程, 駕駛} 駕駛-1為無人，0開始計

    int driver[100] = {0};
    int schedule[100][3] = {0};
    int input1, input2;
    int schedule_count = 0;
    int driver_count = 0;

    while(scanf("%d%d", &input1, &input2) != EOF){ // 抓取輸入
        schedule[schedule_count][0] = input1;
        schedule[schedule_count][1] = input2;
        schedule[schedule_count][2] = -1;
        schedule_count++;
    }

    for(int i = 0; i < 24; i++){ //一樣24小時逐個判斷
        for(int j = 0; j < schedule_count; j++){ // 判斷回程
            if(schedule[j][2] != (-1) && schedule[j][1] == i) driver[schedule[j][2]] = 0; // 回收駕駛(設定駕駛為未工作)
        }

        for(int k = 0; k < schedule_count; k++){ // 判斷出發
            if(schedule[k][2] == (-1) && schedule[k][0] == i){
                for(int m = 0; m < 100; m++){ // 找尋空閒駕駛
                    if(driver[m] == 0){
                        schedule[k][2] = m;
                        driver[m] = 1;
                        driver_count = (m > driver_count)? m : driver_count;
                        // 重點：driver_count 紀錄的是陣列編號，而非使用人員數
                        // 兩者相差1
                        break;
                    }
                }
            }
        }
    }

    printf("%d\n", (driver_count + 1));

    for(int n = 0; n <= driver_count; n++){ // 輸出每個駕駛的行程
        printf("Driver %d's schedule is", n + 1);
        for(int o = 0; o < schedule_count; o++) if(schedule[o][2] == n) printf(" %d %d", schedule[o][0], schedule[o][1]);
        printf("\n");
    }

    return 0;
}

