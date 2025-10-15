#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// �Լ� ����
void number_to_hangul(unsigned long money);
void check_number(int answer[], int guess[], int length);

// ���� �Լ�
int main(void)
{
    unsigned long money;
    int length, tries;
    int answer[9], guess[9];
    unsigned long answerValue, guessValue;

    srand(time(NULL)); // ���� �õ� �ʱ�ȭ

    // ===== ��Ʈ�� ȭ�� =====
    printf("=====================================\n");
    printf("           ? ���� �߱� ���� ?        \n");
    printf("=====================================\n");
    printf("���ϴ� �ڸ����� �Է��ϼ��� (�ִ� 9�ڸ�): ");
    scanf("%d", &length);

    if (length < 1 || length > 9) {
        printf(" !!!1~9 ������ ���ڸ� �Է� �����մϴ�.!!!\n");
        return 0;
    }

    printf("�õ��� Ƚ���� �Է��ϼ���: ");
    scanf("%d", &tries);

    // ===== ȭ�� ����� (��Ʈ�� ȿ��) =====
    system("cls");

    // ===== ȿ���� =====
    Beep(800, 200);
    Beep(1000, 200);
    Beep(1200, 300);

    printf("������ �����մϴ�! (�ڸ���: %d, �õ� ���� Ƚ��: %d)\n", length, tries);
    printf("=====================================\n\n");

    // ===== ���� ���� ���� (�ߺ� ���� ����) =====
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

    // ===== �õ� ���� =====
    for (int attempt = 1; attempt <= tries; attempt++) {
        printf("[%d��° �õ�] ���� %d�ڸ��� �Է��ϼ���: ", attempt, length);
        scanf("%lu", &guessValue);

        // guess�� �迭�� ��ȯ
        unsigned long temp = guessValue;
        for (int i = length - 1; i >= 0; i--) {
            guess[i] = temp % 10;
            temp /= 10;
        }

        // ��
        check_number(answer, guess, length);

        // ���� Ȯ��
        int correct = 1;
        for (int i = 0; i < length; i++) {
            if (answer[i] != guess[i]) {
                correct = 0;
                break;
            }
        }
        if (correct) {
            system("cls");
            printf("�Է��� �� : ");
            number_to_hangul(guessValue);
            printf("\n");
            printf("\n **** �����Դϴ�! **** \n");
            printf("������ ");
            number_to_hangul(answerValue);
            printf(" �Դϴ�!\n");
            Beep(1500, 300);
            Beep(1800, 400);
            system("pause");
            return 0;
        }

        printf("\n");
    }

    // ===== ���� �� ���� ���� =====
    system("cls");
    printf("�Է��� �� : ");
    number_to_hangul(guessValue);
    printf("\n");
    printf("\n �Ф�...�õ� Ƚ���� ��� �����߽��ϴ�...�Ф� \n");
    printf("������ ");
    number_to_hangul(answerValue);
    printf(" �Դϴ�.\n");
    Beep(400, 500);
    Beep(300, 600);
    system("pause");

    return 0;
}

// ���� �� �Լ�
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
                printf("�� ");
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
   char *unit01[]={"��", "��", "��"};
   char *unit02[]={"õ", "��", "��"};
   char *unit03[]={"", "��", "��", "��", "��", "��", "��", "ĥ", "��", "��"};
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
