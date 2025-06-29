﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  // fabs 사용을 위해 필요

int main(void) {
    int i;
    float rfp[10000], lfp[10000];  // 오른발, 왼발 충격량 저장
    float max_rfp = 0, max_lfp = 0;
    float sum_rfp = 0, sum_lfp = 0;
    int count = 0;

    char row[1000];
    char* t;

    FILE* f = NULL;
    f = fopen("C:/Users/이보나/Desktop/흠냐링/BLEP/belt19.csv", "r"); // belt 데이터 열기

    if (f != NULL) {
        fgets(row, 1000, f);  // 첫 줄 헤더 무시

        while (fgets(row, 1000, f)) {
            int column = 0;
            float r_value = 0, l_value = 0;

            t = strtok(row, ",");

            while (t != NULL) {
                if (column == 3) {  // 왼발 충격량 (lfp)
                    l_value = atof(t);
                }
                if (column == 4) {  // 오른발 충격량 (rfp)
                    r_value = atof(t);
                }
                t = strtok(NULL, ",");
                column++;
            }

            if (l_value != 0 || r_value != 0) {
                lfp[count] = l_value;
                rfp[count] = r_value;

                sum_lfp += l_value;
                sum_rfp += r_value;

                if (l_value > max_lfp) max_lfp = l_value;
                if (r_value > max_rfp) max_rfp = r_value;

                count++;
            }
        }

        // 평균 계산
        float avg_lfp = sum_lfp / count;
        float avg_rfp = sum_rfp / count;
        float ratio = (avg_lfp != 0) ? (avg_rfp / avg_lfp) : 0;

        // 결과 출력
        printf("왼발 & 오른발 충격 분석\n");
        printf("오른발 최대 충격량: %.2f\n", max_rfp);
        printf("왼발 최대 충격량 : %.2f\n", max_lfp);
        printf("오른발 평균 충격량: %.2f\n", avg_rfp);
        printf("왼발 평균 충격량 : %.2f\n", avg_lfp);
        printf("평균 기준 왼발 대비 오른발 충격 비율: %.2f\n", ratio);

        fclose(f);
    }
    else {
        printf("파일을 열 수 없습니다.\n");
    }

    return 0;
}
