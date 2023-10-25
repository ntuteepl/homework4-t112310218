#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SCHEDULES_COUNT 100

int main()
{
    int driver[MAX_SCHEDULES_COUNT] = {0}; // 用來記錄駕駛狀況 ( 一格代表一位駕駛，其中值 0 為休息，1 為值勤中 )
    int schedule[MAX_SCHEDULES_COUNT][3] = {0}; // 用來儲存計畫排程，格式如下
    /*
    { 發車, 回程, 駕駛 } 駕駛 -1 為無人，人員代號 0 開始計

    {
        { 發車, 回程, 駕駛 },
        { 發車, 回程, 駕駛 },
        { 發車, 回程, 駕駛 },
        { 發車, 回程, 駕駛 }
    }
    */
    int input1, input2; // 用來作為儲存輸入的排程前的暫存
    int schedule_count = 0; // 紀錄有幾個排程，也作為儲存排程時的位置指定
    int driver_count = 0; // 紀錄最多需要調用多少位司機

    // 抓取輸入
    while(scanf("%d%d", &input1, &input2) != EOF){ // 判斷輸入，如果不為 EOF 就儲存並繼續等待下次輸入
        schedule[schedule_count][0] = input1; // 儲存發車時間
        schedule[schedule_count][1] = input2; // 儲存回程時間
        schedule[schedule_count][2] = -1; // 初始化為尚未指派駕駛
        schedule_count++; // 總排程數量 + 1，並可作為下一筆資料的位置代號
    }

    /* 階段狀態1
        driver 陣列所有值皆為 0 ( 尚未有司機值勤 )

        schedule 陣列紀錄了所有排程 (
            { 發車時間, 回程時間, 指派司機 }
            指派司機 皆為 -1 代表皆未有司機執行工作
        )

        schedule_count 儲存排程總數量

        driver_count 為 0 ( 尚未開始派遣司機 )
    */

    // 根據 24 小時，逐個判斷每小時的狀況
    for(int i = 0; i < 24; i++){
        // 判斷回程
        for(int j = 0; j < schedule_count; j++){ // 每個排程逐個判斷
            if(schedule[j][2] != (-1) && schedule[j][1] == i) driver[schedule[j][2]] = 0; // 回收駕駛(設定駕駛為未工作)
            /*
                if(schedule[j][2] != (-1) && schedule[j][1] == i)
                => 如果排程的回程時間對的上，且排程有派遣司機 ( 不等於 -1 )

                driver[schedule[j][2]] = 0;
                => 將對應司機的狀態設為休息中
            */
        }

        // 判斷出發
        for(int k = 0; k < schedule_count; k++){ // 每個排程逐個判斷
            if(schedule[k][2] == (-1) && schedule[k][0] == i){ // 如果排程的出發時間對的上，且排程沒有派遣司機 ( 等於 -1 )
                // 找尋空閒司機
                for(int m = 0; m < MAX_SCHEDULES_COUNT; m++){ // 逐個司機遍歷
                    if(driver[m] == 0){ // 如果司機休息中，執行下面出發程式
                        schedule[k][2] = m; // 設定排程的指派司機為當前司機
                        driver[m] = 1; // 設定當前司機為值勤中
                        driver_count = (m + 1 > driver_count)? m + 1: driver_count;  // 刷新需要調用人數
                        /*
                            m + 1 代表在指派這項工做時，我所需要調用到的人員數量
                            driver_count 代表過去我最多需要調用到多少位

                            如果 m + 1 大於 driver_count 代表過去我所調用的人員數已經不足以應付這項任務了
                            所以要更新需求人數為當前的調用人數 => driver_count = m + 1;

                            driver_count = (m + 1 > driver_count)? m + 1: driver_count;
                            寫法等於
                            if(m + 1 > driver_count){
                                driver_count = m + 1;
                            }else{
                                driver_count = driver_count;
                            }
                            其實else部分可以不用Www
                        */
                        break; // 如果找到司機執行任務了，就跳出迴圈 ( 不用再往下找了 )
                    }
                }
            }
        }
    }

    // 打印模擬結果
    printf("%d\n", (driver_count)); // 輸出需要調用司機數

    // 輸出每個駕駛的行程
    for(int n = 0; n < driver_count; n++){ // 逐個司機執行 ( n < driver_count 限制只有會被調用到的司機才會執行 )
        printf("Driver %d's schedule is", n + 1); // 先打印通用開頭 ( 含司機的代號，陣列編碼從 0 開始，但人數數從 1 開始，所以 +1 )
        for(int o = 0; o < schedule_count; o++) if(schedule[o][2] == n) printf(" %d %d", schedule[o][0], schedule[o][1]); // 逐個排程判斷是否是這個司機駕駛
        /*
            for(int o = 0; o < schedule_count; o++)
            => 逐個排程去遍歷

            if(schedule[o][2] == n)
            => 如果排程的駕駛員是當前司機

            printf(" %d %d", schedule[o][0], schedule[o][1]);
            => 打印出 發車時間 和 回程時間
        */
        printf("\n"); // 換行，為下一位司機行程準備
    }

    return 0;
}
