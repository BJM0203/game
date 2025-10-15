#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 함수 선언
void number_to_hangul(unsigned long money);
void check_number(int answer[], int guess[], int length);

// 메인 함수
int main(void)
{
    unsigned long money;
    int length, tries;
    int answer[9], guess[9];
    unsigned long answerValue, guessValue;

    srand(time(NULL)); // 랜덤 시드 초기화

    // ===== 인트로 화면 =====
    printf("=====================================\n");
    printf("           ? 숫자 야구 게임 ?        \n");
    printf("=====================================\n");
    printf("원하는 자릿수를 입력하세요 (최대 9자리): ");
    scanf("%d", &length);

    if (length < 1 || length > 9) {
        printf(" !!!1~9 사이의 숫자만 입력 가능합니다.!!!\n");
        return 0;
    }

    printf("시도할 횟수를 입력하세요: ");
    scanf("%d", &tries);

    // ===== 화면 지우기 (인트로 효과) =====
    system("cls");

    // ===== 효과음 =====
    Beep(800, 200);
    Beep(1000, 200);
    Beep(1200, 300);

    printf("게임을 시작합니다! (자릿수: %d, 시도 가능 횟수: %d)\n", length, tries);
    printf("=====================================\n\n");

    // ===== 랜덤 정답 생성 (중복 없는 숫자) =====
    int used[10] = {0};
    answerValue = 0;
    for (int i = 0; i < length; i++) {
        int n;
        do {
            n = rand() % 10;
        } while (used[n]);
        used[n] = 1;
        answer[i] = n;
        answerValue = answerValue * 10 + n;
    }

    // ===== 시도 루프 =====
    for (int attempt = 1; attempt <= tries; attempt++) {
        printf("[%d번째 시도] 숫자 %d자리를 입력하세요: ", attempt, length);
        scanf("%lu", &guessValue);

        // guess를 배열로 변환
        unsigned long temp = guessValue;
        for (int i = length - 1; i >= 0; i--) {
            guess[i] = temp % 10;
            temp /= 10;
        }

        // 비교
        check_number(answer, guess, length);

        // 정답 확인
        int correct = 1;
        for (int i = 0; i < length; i++) {
            if (answer[i] != guess[i]) {
                correct = 0;
                break;
            }
        }
        if (correct) {
            system("cls");
            printf("입력한 값 : ");
            number_to_hangul(guessValue);
            printf("\n");
            printf("\n **** 정답입니다! **** \n");
            printf("정답은 ");
            number_to_hangul(answerValue);
            printf(" 입니다!\n");
            Beep(1500, 300);
            Beep(1800, 400);
            system("pause");
            return 0;
        }

        printf("\n");
    }

    // ===== 실패 시 정답 공개 =====
    system("cls");
    printf("입력한 값 : ");
    number_to_hangul(guessValue);
    printf("\n");
    printf("\n ㅠㅠ...시도 횟수를 모두 소진했습니다...ㅠㅠ \n");
    printf("정답은 ");
    number_to_hangul(answerValue);
    printf(" 입니다.\n");
    Beep(400, 500);
    Beep(300, 600);
    system("pause");

    return 0;
}

// 숫자 비교 함수
void check_number(int answer[], int guess[], int length)
{
    for (int i = 0; i < length; i++) {
        if (guess[i] == answer[i])
            printf("O ");
        else {
            int found = 0;
            for (int j = 0; j < length; j++) {
                if (guess[i] == answer[j]) {
                    found = 1;
                    break;
                }
            }
            if (found)
                printf("△ ");
            else
                printf("X ");
        }
    }
    printf("\n");
}

void number_to_hangul(unsigned long money)
{
   unsigned long num1, num2, temp;
   unsigned long m_unit[]={100000000, 10000, 1};
   unsigned long m_unit01[]={1000, 100, 10};
   int i, j;
   char *unit01[]={"억", "만", "원"};
   char *unit02[]={"천", "백", "십"};
   char *unit03[]={"", "일", "이", "삼", "사", "오", "육", "칠", "팔", "구"};
   printf("$ ");
   for(i=0; i<3; i++)
   {
      num1=money/m_unit[i];
      if(!num1)
          continue;
      temp=num1;
      for(j=0;j<3;j++)
      {
         num2=num1/m_unit01[j];
         if (!num2)
            continue;
        printf("%s%s", unit03[num2], unit02[j]);
        num1=num1-num2*m_unit01[j];
      }
      printf("%s%s ", unit03[num1], unit01[i]);
      printf("$");
      money=money-temp*m_unit[i];
   }
}
