#define _CRT_SECURE_NO_WARNINGS
// �����޴�
#include "kulender.h"

int checkDay();
int checkTime();
const char* checkSchedule_Name();
void showSchedule(int type, char* name, int day);
char* showGroupList();
int showScheduleList(int type, char* id, int day, int flag);
void additionalEdit();
void fileModifier(int type, int num);

int isGroup = 0;
int jGroup = 0;

struct NODE {
	struct NODE* next;
	char data[255];
	int num;
};

// �ϼ�
void lookUpCalendar() {
	// 8.1 ���� ��ȸ �޴�
	system("cls");
	printf("-----------���� ��ȸ--------------\n");
	printf("1. ���� ���� ��ȸ\n");
	printf("2. �׷� ���� ��ȸ\n");
	printf("�޴� ���� : ");
	int result = chooseNumber(1, 2);  //������ �Է¹ޱ�
	if (result == 1) {
		// ���� ���� ��ȸ

		int day = checkDay(); // YYMM�������� ��¥ �Է¹ް� ����

		showSchedule(0, USER_id, day);
	}
	else if (result == 2) {
		// �׷� ���� ��ȸ

		char groupName[255];
		strcpy(groupName, showGroupList());
		int day = checkDay(); // YYMM���� 
		showSchedule(1, groupName, day);

	}
	else {
		printf("lookUpCalendar()���� ������ �߻��߽��ϴ�.");
	}

}

// �ϼ� 
void addSchedule() {
	//8.2 ���� �߰� �޴�
	//�����Է� => ����,���� �ð� �Է� => ������ �Է� => ���۸޴����� ���� ���̵� ������ �������� �κп� �߰�=> �����߰� �Ϸ�
	system("cls");
	printf("-----------���� �߰�--------------\n");
	char path[PATH_LEN] = "";
	char input_data[1024] = "";
	printf("�����߰��� ���� ��-��-���� �Է��մϴ�.\n");
	int Date = checkBirth("");

	printf("���� �ð��� �Է��մϴ�.\n");
	int start_Time = checkTime();
	
	int finish_Time;
	
	while (1) {
		printf("���� �ð��� �Է��մϴ�.\n");
		finish_Time = checkTime();
		if (finish_Time < start_Time) {
			printf("����ð��� ���۽ð� ���� �����ϴ�. �ٽ� �Է��ϼ���\n");
		}
		else {
			break;
		}
	}

	printf("�������� �Է��մϴ�.\n");
	char* schedule_name = checkSchedule_Name();

	// ������� ����ó��
	char temp[BIRTHDAY_LEN + 1] = "000";
	char user_birth[BIRTHDAY_LEN + 1] = "";

	if (!(Date / 1000)) {
		_itoa(Date, user_birth, 10);
		strcat(temp, user_birth);
	}
	else if (!(Date / 10000)) {
		_itoa(Date, user_birth, 10);
		temp[2] = NULL;
		strcat(temp, user_birth);
	}
	else if (!(Date / 100000)) {
		_itoa(Date, user_birth, 10);
		temp[1] = NULL;
		temp[2] = NULL;
		strcat(temp, user_birth);
	}
	else {
		_itoa(Date, user_birth, 10);
		temp[0] = NULL;
		temp[1] = NULL;
		temp[2] = NULL;
		strcat(temp, user_birth);
	}

	strcpy(input_data, temp);
	strcat(input_data, " ");

	char startTimeString[4] = "";
	char zeros[4] = "000";
	if (!(start_Time / 10)) {
		_itoa(start_Time, startTimeString, 10);
		strcat(zeros, startTimeString);
	}
	else if (!(start_Time / 100)) {
		_itoa(start_Time, startTimeString, 10);
		zeros[2] = NULL;
		strcat(zeros, startTimeString);
	}
	else if (!(start_Time / 1000)) {
		_itoa(start_Time, startTimeString, 10);
		zeros[1] = NULL;
		zeros[2] = NULL;
		strcat(zeros, startTimeString);
	}
	else { // test ��
		zeros[0] = NULL;
		zeros[1] = NULL;
		zeros[2] = NULL;
		_itoa(start_Time, startTimeString, 10);
		strcat(zeros, startTimeString);
	}

	strcat(input_data, zeros);
	strcat(input_data, " ");

	char finishTimeString[4] = "";
	char zeros1[4] = "000";
	if (!(finish_Time / 10)) {
		_itoa(finish_Time, finishTimeString, 10);
		strcat(zeros1, finishTimeString);
	}
	else if (!(finish_Time / 100)) {
		_itoa(finish_Time, finishTimeString, 10);
		zeros1[2] = NULL;
		strcat(zeros1, finishTimeString);
	}
	else if (!(finish_Time / 1000)) {
		_itoa(finish_Time, finishTimeString, 10);
		zeros1[1] = NULL;
		zeros1[2] = NULL;
		strcat(zeros1, finishTimeString);
	}
	else {
		zeros1[0] = NULL;
		zeros1[1] = NULL;
		zeros1[2] = NULL;
		_itoa(finish_Time, finishTimeString, 10);
		strcat(zeros1, finishTimeString);
	}
	strcat(input_data, zeros1);
	strcat(input_data, " ");

	strcat(input_data, schedule_name);

	// ��� ����
	strcpy(path, "kulender\\users\\");	//����� ���̵�� �ִ� ����
	strcat(path, USER_id);
	strcat(path, ".txt");

	writeFile(input_data, path, 1);
	printf("���� �߰��� �Ϸ�Ǿ����ϴ�!\n");

	printf("����� �����޴��� �Ѿ�ϴ�.\n");
	Sleep(1500);

	calenderMenu();
}

//8.3 ���� ���� �޴�
void editSchedule() {

	system("cls");
	printf("-----------���� ���� ����--------------\n");
	printf("1. ��-��-�� ����\n");
	printf("2. ����-���� �ð� ����\n");
	printf("3. ������ ����\n");
	printf("�޴� ���� : ");
	int result = chooseNumber(1, 3);
	int day = checkBirth("");

	system("cls");
	printf("-----------���� ����--------------\n");

	//showScheduleList()�� Ȱ���Ͽ� ������ ���ùް� �̰ɷ� �� �����
	int num = showScheduleList(1, USER_id, day, 0);
	if (num == 0) {
		printf("�ش��ϴ� ��¥�� ������ �������� �ʽ��ϴ�.");
		Sleep(1500);
		editSchedule();
		return;
	}


	fileModifier(result, num);
}

//8.4 ���� ���� �޴�
void deleteSchedule() {

	system("cls");
	int day = checkBirth("");
	// ��¥�Է¹ް� ���� ���ùޱ�
	system("cls");
	printf("-----------���� ����--------------\n");
	int num = showScheduleList(1, USER_id, day, 0); // ������ ������ ���Ͽ��� ���°������ ����, ���ٸ� 0 ����
	if (num == 0) {
		printf("�ش��ϴ� ��¥�� ������ �������� �ʽ��ϴ�.");
		Sleep(1500);
		deleteSchedule();
	}

	FILE* fp; 
	FILE* newfp;
	char path1[PATH_LEN];  //path1 : ������ ����
	char path2[PATH_LEN];  //path1 : �� ����
	char line[255];
	strcpy(path1, "kulender\\users\\");
	strcat(path1, USER_id);
	strcat(path1, ".txt");
	fp = fopen(path1, "r+");
	strcpy(path2, "kulender\\users\\");
	strcat(path2, USER_id);
	strcat(path2, "_new");
	strcat(path2, ".txt");
	newfp = fopen(path2, "w+");

	if (fp == 0) {
		printf("file not opened error\n");
		Sleep(1500);
		return;
	}
	if (newfp == 0) {
		printf("file not opened error\n");
		Sleep(1500);
		return;
	}

	int i = 1;
	while (!feof(fp)) {
		if (i == 4) {
			fgets(line, sizeof(line), fp);
			int j = atoi(line);
			j--; // ���� ���� -1
			char line2[255];
			_itoa(j, line2, 10);
			strcat(line2, "\n");
			fputs(line2, newfp);
		}
		if (i == num - 1) {
			fgets(line, sizeof(line), fp);
		}
		else {
			fgets(line, sizeof(line), fp);
			fputs(line, newfp);
		}
		i++;
	}
	while (fclose(fp) != 0);
	while (fclose(newfp) != 0);

	if (remove(path1) != 0) {
		printf("���� ���� ����");
		Sleep(1500);
		return;
	}

	if (rename(path2, path1) != 0) {
		printf("���� �̸����� ����");
		Sleep(1500);
		return;
	}
	printf("���� ���� ����");
	Sleep(1500);
}

// ��¥ ��ȿ�� �˻�
int checkDay() {
	char ex[1024] = { 0, };
	while (1) {
		printf("��� : ");
		gets(ex);
		int Daycheck = GetStringLength(ex);

		//���� if������ ������ ����
		int year;
		int month;
		int input;

		if (Daycheck == 4) { // YYMM ����
			input = atoi(ex);
			year = input / 100;
			month = input % 100;
			if (month >= 1 && month <= 12) {
				return year * 100 + month;
			}
			else {
				printf("month error 001");
			}
		}
		else if (Daycheck == 5) { // YY-MM
			if (!isdigit(ex[2])) {
				char* context;
				char check[] = { ex[2] };
				char* y = strtok_s(ex, check, &context);
				char* m = strtok_s(NULL, check, &context);

				year = atoi(y);
				month = atoi(m);

				if (month >= 1 && month <= 12) {
					return year * 100 + month;
				}
				else {
					printf("month error 002");
				}
			}
			else {
				printf("year-month error 001");
			}
		}
		else if (Daycheck == 6) { // YYYYMM
			input = atoi(ex);
			year = input / 100;
			month = input % 100;
			if (year >= 1922 && year <= 2021) {
				if (month >= 1 && month <= 12) {
					return (year % 100) * 100 + month;
				}
				else {
					printf("month error 003");
				}
			}
			else {
				printf("year error 001");
			}
		}
		else if (Daycheck == 7) { // YYYY-MM
			if (!isdigit(ex[4])) {
				char* context;
				char check[] = { ex[4] };
				char* y = strtok_s(ex, check, &context);
				char* m = strtok_s(NULL, check, &context);

				year = atoi(y);
				month = atoi(m);

				if (year >= 1922 && year <= 2021) {
					if (month >= 1 && month <= 12) {
						return (year % 100) * 100 + month;
					}
					else {
						printf("month error 004");
					}
				}
				else {
					printf("year error 002");
				}
			}
		}
		printf("\n����� ���� �� �����ϴ�. �ùٸ� �������� �Է��� �ּ���.\n");
	}
}

//���� ���� ��ȸ
void showSchedule(int type, char* name, int day) {

	if (!type) {
		int check = showScheduleList(0, name, day, 1);
		if (check == 0) {//�ش��ϴ� ������ ������ ������ȸ �޴��� ���ư���.
			printf("�Է��� ��¥�� �ش��ϴ� ������ �����ϴ�.\n");
			printf("�����޴��� ���ư��ϴ�.\n");
			Sleep(1500);
			calenderMenu();
		}
		else {
			printf("��/���� �ش��ϴ� ��������Ʈ�� ����߽��ϴ�.\n");
			printf("����Ű�� ������ �����޴��� ���ư��ϴ�.\n");
			char ex[1024] = { 0, };
			gets(ex);
			if (strlen(ex) == 0) {
				printf("�����޴��� ���ư��ϴ�.");
				Sleep(1500);
				calenderMenu();
			}
		}
	}
	else {
		// �׷� ���� ��ȸ
		isGroup = 1;
		char path[PATH_LEN];
		FILE* fp;
		strcpy(path, "kulender\\groups\\");
		name[strlen(name) - 1] = NULL;
		strcat(path, name);
		strcat(path, ".txt");
		fp = fopen(path, "r");
		char line[255] = "";
		printf("-------------------------------------------------\n");
		fgets(line, sizeof(line), fp);
		while (!feof(fp)) {
			if (line[strlen(line) - 1] == '\n') {
				line[strlen(line) - 1] = NULL;
			}

			showScheduleList(0, line, day, 1);
			fgets(line, sizeof(line), fp);
		}
		printf("-------------------------------------------------\n");
		fclose(fp);
	}

	isGroup = 0;
	jGroup = 0;

	printf("����Ű�� ������ �����޴��� ���ư��ϴ�.\n");
	char ex[1024] = { 0, };
	gets(ex);
	if (strlen(ex) == 0) {
		printf("�����޴��� ���ư��ϴ�.");
		Sleep(1500);
		calenderMenu();
	}
}

char* showGroupList() {
	int i;
	char path[PATH_LEN];
	char name[12];

	struct NODE* head = malloc(sizeof(struct NODE));
	struct NODE* before = malloc(sizeof(struct NODE));

	head->next = before;

	FILE* fp;
	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");
	fp = fopen(path, "r");
	char line[255] = "";
	for (i = 0; i < 3; i++) {
		fgets(line, sizeof(line), fp);
	}
	fgets(line, sizeof(line), fp);
	int num = atoi(line); // schedule()������ �ִµ� ���� �� �ѱ��
	for (i = 0; i < num; i++) {
		fgets(line, sizeof(line), fp);
	}
	fgets(line, sizeof(line), fp);
	num = atoi(line); // �׷� ����
	printf("-----------�׷� ����--------------\n");
	if (num == 0) {
		printf("���ϴ� �׷��� �����ϴ�.\n");
		printf("�׷��� ����, �߰��ϰ� �ٽ� �õ����ּ���.\n");
		printf("�����޴��� ���ư��ϴ�.\n");
		Sleep(1500);
		calenderMenu();
	}
	for (i = 1; i <= num; i++) {
		fgets(line, sizeof(line), fp);
		printf("%d. %s", i, line);
		struct NODE* after = malloc(sizeof(struct NODE));
		strcpy(before->data, line);
		before->next = after;
		before = after;
	}
	int j = i;
	fgets(line, sizeof(line), fp);
	int num2 = atoi(line); // �׷� ����
	for (i = j; i < num2+j; i++) {
		fgets(line, sizeof(line), fp);
		printf("%d. %s", i, line);
		struct NODE* after = malloc(sizeof(struct NODE));
		strcpy(before->data, line); 
		before->next = after;
		before = after;
	}
	printf("----------------------------------\n");
	int result;
	while (1) {
		printf("�׷��� ������ �ּ��� : ");
		scanf("%d", &result);
		if (result > 0 && result <= num + num2) {
			break;
		}
	}
	getchar(); // ���ۿ� �� �ִ� ���� �����
	before = head;
	for (i = 0; i < result; i++) {
		before = before->next;
	}
	strcpy(name, before->data);
	return name;
}

//���� �߰�, ����� ����� �ð� �˻� �Լ�
int checkTime() {
	char ex[1024] = { 0, };
	while (1) {

		printf("�ð� �Է� : ");
		int len;
		gets(ex);
		len = strlen(ex);

		int hour;
		int minute;
		int input;

		if (len == 4) {	//HHMM ����
			input = atoi(ex);
			hour = input / 100;
			minute = input % 100;
			if (hour >= 0 && hour <= 23) {
				if (minute >= 0 && minute <= 59) {
					return hour * 100 + minute;
				}
				else {
					printf("minute error");
					break;
				}
			}
			else {
				printf("hour error");
			}
		}
		else if (len == 5) {	//HH-MM ����
			if (!isdigit(ex[2])) {
				char* context;
				char check[] = { ex[2] };
				char* h = strtok_s(ex, check, &context);
				char* m = strtok_s(NULL, check, &context);

				hour = atoi(h);
				minute = atoi(m);
				if (hour >= 0 && hour <= 23) {
					if (minute >= 0 && minute <= 59) {
						return hour * 100 + minute;
					}
					else {
						printf("minute error");
						break;
					}
				}
				else {
					printf("hour error");
					break;
				}
			}
			else {
				printf("hour-minute error");
				break;
			}
		}
		else {
			printf("hour-minute error");
			break;
		}
	}
	return -1;
}

//������ �ް� �˻��� �Լ�
const char* checkSchedule_Name() {
	while (1) {
		static char ex[1024] = { '0', };
		ex[1024] = "";
		printf("������ �Է�: ");
		gets(ex);
		int nameCheck = GetStringLength(ex);

		if (nameCheck > 500 || nameCheck == 0) {
			printf("�������� ���̰� ���� ���Ŀ� ��߳��ϴ�. 1���� �̻� 500���� ���Ϸ� �Է����ּ���.\n");
			continue;
		}

		else {
			return ex;
		}
	}
}

// ���� ����� �����ִ� �Լ�
// �Ķ����
// -type�� 1, 0���� ����   
// -type==0�� ��� chooseNum�� �̿��� �Է��� ���� �ʴ´�. 
// -type==1�� ��� chooseNum�� �̿��� �Է��� �ް� ���õ� ������ �ؽ�Ʈ���Ͽ��� ������ ���° �������� return
// -char* id�� ������ �� ����� ���̵� �Է� 
// -int day�� ��� ��¥�����͸� �Է�
// -EX) day = 2103, day = 210330     YYMM ���� Ȥ�� YYMMDD���·� �Է��Ѵ�.
// �� �Լ��� �����ϰ� ������ �Է¹��� "������ �����ϼ��� : "���� ����մϴ�. 
// -----���� ����-----   �䷱ �����̳�     "�ش��ϴ� ��¥�� ������ �����ϴ�." �̷� �ȳ������� ���� ����ؾ� �մϴ�.
// �ش� �� Ȥ�� ��¥�� ������ �ϳ��� ������ 0�� return�մϴ�. (return 0;)
int showScheduleList(int type, char* id, int day, int flag) {
	if (!type) {
		FILE* fp;
		char path[PATH_LEN];
		int i = 0; 
		char line[255];
		char word[255];

		strcpy(path, "kulender\\users\\");
		strcat(path, id);
		strcat(path, ".txt");
		fp = fopen(path, "r");

		for (i = 0; i < 4; i++) { //schedule ������ ��Ÿ���� �ٱ��� �ѱ��
			fgets(line, sizeof(line), fp);
		}
		int num = atoi(line); // shcedule ���� �޾ƿ���
		int j = 0;
		if (!isGroup) {
			printf("-------------------------------------------------\n");
		}
		for (i = 1; i <= num; i++) {  // schedule����Ʈ ���
			fgets(line, sizeof(line), fp);
			char zeros[255] = "000";
			if (flag) {
				if (!(day / 10)) {
					sprintf(word, "%d", day);
					strcat(zeros, word);
				}
				else if (!(day / 100)) {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					strcat(zeros, word);
				}
				else if (!(day / 1000)) {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					zeros[1] = NULL;
					strcat(zeros, word);
				}
				else {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					zeros[1] = NULL;
					zeros[0] = NULL;
					strcat(zeros, word);
				}
			}
			else {
				char zeros[3] = "000";
				if (!(day / 1000)) {
					sprintf(word, "%d", day);
					strcat(zeros, word);
				}
				else if (!(day / 10000)) {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					strcat(zeros, word);
				}
				else if (!(day / 100000)) {
					zeros[2] = NULL;
					zeros[1] = NULL;
					sprintf(word, "%d", day);
					strcat(zeros, word);
				}
				else {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					zeros[1] = NULL;
					zeros[0] = NULL;
					strcat(zeros, word);
				}
			}
			char line_short[255] = "";
			char* buf = line_short;
			char* s = line;   // ���� ��ġ�� ����
			int size;
			if (flag) {
				size = 4;
			}
			else {
				size = 6;
			}
			while (size-- > 0 && *s != '\0') {  // size�� 0���� ũ��, ���ڿ� ���� ������ ���� ���
				 *(buf++) = *(s++);   // ���� 
			}
			if (strstr(line_short, zeros) != NULL) {
				if (isGroup) {
					jGroup++;
					printf("%d. %s", jGroup, line);
				}
				else {
					j++;
					printf("%d. %s", j, line);
				}
			}
		}
		if (!isGroup) {
			printf("-------------------------------------------------\n");
		}
		fclose(fp);
		return j;
	}
	else {
		//���� ����Ʈ ���
		FILE* fp;
		char path[PATH_LEN];
		char line[255];
		int i;
		int num;
		char word[255];

		strcpy(path, "kulender\\users\\");
		strcat(path, id);
		strcat(path, ".txt");
		fp = fopen(path, "r");

		for (i = 0; i < 4; i++) {
			fgets(line, sizeof(line), fp);
		} //schedule ������ ��Ÿ���� �ٱ��� �ѱ��

		num = atoi(line); // shcedule ���� �޾ƿ���
		struct NODE* head = malloc(sizeof(struct NODE));
		struct NODE* before = malloc(sizeof(struct NODE));
		head->next = before;

		int j = 0;
		printf("-------------------------------------------------\n");
		for (i = 1; i <= num; i++) {  // schedule����Ʈ ����ϰ� linked list�� ����
			fgets(line, sizeof(line), fp);
			char zeros[255] = "000";

			if (flag) {
				if (!(day / 10)) {
					sprintf(word, "%d", day);
					strcat(zeros, word);
				}
				else if (!(day / 100)) {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					strcat(zeros, word);
				}
				else if (!(day / 1000)) {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					zeros[1] = NULL;
					strcat(zeros, word);
				}
				else {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					zeros[1] = NULL;
					zeros[0] = NULL;
					strcat(zeros, word);
				}
			}
			else {
				if (!(day / 1000)) {
					sprintf(word, "%d", day);
					strcat(zeros, word);
				}
				else if (!(day / 10000)) {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					strcat(zeros, word);
				}
				else if (!(day / 100000)) {
					zeros[2] = NULL;
					zeros[1] = NULL;
					sprintf(word, "%d", day);
					strcat(zeros, word);
				}
				else {
					sprintf(word, "%d", day);
					zeros[2] = NULL;
					zeros[1] = NULL;
					zeros[0] = NULL;
					strcat(zeros, word);
				}
			}

			char line_short[255] = "";
			char* buf = line_short;
			char* s = line;   // ���� ��ġ�� ����
			int size = 6;
			while (size-- > 0 && *s != '\0') {  // size�� 0���� ũ��, ���ڿ� ���� ������ ���� ���
				 *(buf++) = *(s++);   // ���� 
			}
			*buf = '\0';    // ���� �� ���� ó��
			if (strstr(line_short, zeros) != NULL) {
				j++;
				printf("%d. %s", j, line);
				struct NODE* after = malloc(sizeof(struct NODE));
				before->next = after;
				strcpy(before->data, line);
				before->num = i;
				before = after;
			}
		}
		printf("-------------------------------------------------\n");
		before->next = head;
		if (head->next == before) {
			return 0;
		}
		fclose(fp);
		int result1;
		while (1) {
			printf("���� ���� : ");
			scanf("%d", &result1);
			if (result1 > 0 && result1 <= j) {
				break;
			}
		}
		getchar();
		before = head;
		for (i = 0; i < result1; i++) {
			before = before->next;
		}
		result1 = before->num;

		return 4 + result1;
	}
}

//�߰� ����޴�
void additionalEdit() {
	system("cls");
	printf("-----------�߰� ���� ����--------------\n");
	printf("1. �߰� ����\n");
	printf("2. ���� ����");
	int result = chooseNumber(1, 2);
	if (result == 1) {
		editSchedule();
	}
	else {
		calenderMenu();
	}
}

//�ϼ� ============================================================
//type == 1; ��¥ �ٲٱ�
//type == 2; �ð� �ٲٱ�
//type == 3; ������ �ٲٱ�
void fileModifier(int type, int num) {

	FILE* fp;
	char temp[256];
	char word[256]; // �߰���
	char* p;
	int cursor_pos;
	char path[PATH_LEN];
	int i;
	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");
	fp = fopen(path, "r+");
	printf("������ ");
	if (type == 1) {
		// ������� ����ó��
		int day = checkBirth("");
		char tempBirth[BIRTHDAY_LEN + 1] = "000";

		if (!(day / 1000)) {
			_itoa(day, word, 10);
			strcat(tempBirth, word);
		}
		else if (!(day / 10000)) {
			_itoa(day, word, 10);
			tempBirth[2] = NULL;
			strcat(tempBirth, word);
		}
		else if (!(day / 100000)) {
			_itoa(day, word, 10);
			tempBirth[1] = NULL;
			tempBirth[2] = NULL;
			strcat(tempBirth, word);
		}
		else {
			_itoa(day, word, 10);
			tempBirth[0] = NULL;
			tempBirth[1] = NULL;
			tempBirth[2] = NULL;
			strcat(tempBirth, word);
		}
		for (i = 0; i < num; i++) {
			fgets(temp, sizeof(temp), fp);
		}
		char origin[255];
		char temp2[255];
		strcpy(temp2, temp);
		strcpy(origin, strtok(temp, " "));
		p = strstr(temp2, origin);
		cursor_pos = strlen(p) + 1;
		fseek(fp, (-1) * cursor_pos, SEEK_CUR);
		fwrite(word, strlen(word), 1, fp);
	}
	else if (type == 2) {
		int time1;
		int time2;
		char ex[255] = { 0, };
		while (1) {
			printf("���� ");
			time1 = checkTime();
			printf("���� ");
			time2 = checkTime();
			if (time1 / 100 >= time2 / 100 && time1 % 100 > time2 % 100) {
				printf("����ð��� ���۽ð� ���� �����ϴ�. �����ð��� �ٽ� �Է��� �ּ���.\n");
				Sleep(1500);
			}
			else if (time1 == -1 || time2 == -1) {
				printf("�����ð��� �ٽ� �Է��� �ּ���\n");
				Sleep(1500);
			}
			else {
				break;
			}
		}

		for (i = 0; i < num; i++) {
			fgets(temp, sizeof(temp), fp);
		}

		char origin1[255];
		char origin2[255];
		char temp2[255];
		strcpy(temp2, temp);
		strcpy(origin1, strtok(temp, " "));
		strcpy(origin1, strtok(NULL, " "));
		strcpy(origin2, strtok(NULL, " "));
		char t1[255];
		char t2[255];
		sprintf(t1, "%d", time1);
		sprintf(t2, "%d", time2);
		char zeros[255] = "000";
		if (!(time1 / 10)) {
			strcat(zeros, t1);
		}
		else if (!(time1 / 100)) {
			zeros[2] = NULL;
			strcat(zeros, t1);
		}
		else if (!(time1 / 1000)) {
			zeros[1] = NULL;
			zeros[2] = NULL;
			strcat(zeros, t1);
		}
		else {
			zeros[0] = NULL;
			zeros[1] = NULL;
			zeros[2] = NULL;
			strcat(zeros, t1);
		}

		char* p1 = strstr(temp2, origin1);
		int cursor_pos1 = strlen(p1) + 1;
		fseek(fp, (-1) * cursor_pos1, SEEK_CUR);
		fwrite(zeros, strlen(zeros), 1, fp);

		char zeros2[255] = "000";
		if (!(time2 / 10)) {
			strcat(zeros2, t2);
		}
		else if (!(time2 / 100)) {
			zeros2[2] = NULL;
			strcat(zeros2, t2);
		}
		else if (!(time2 / 1000)) {
			zeros2[1] = NULL;
			zeros2[2] = NULL;
			strcat(zeros2, t2);
		}
		else {
			zeros2[0] = NULL;
			zeros2[1] = NULL;
			zeros2[2] = NULL;
			strcat(zeros2, t2);
		}

		fseek(fp, 1, SEEK_CUR);
		fwrite(zeros2, strlen(zeros2), 1, fp);
	}
	else if (type == 3) {
	/*
		char* name1 = checkSchedule_Name();
		char name[255];

		FILE* infp;
		FILE* newfp;
		char path1[PATH_LEN];
		char path2[PATH_LEN];
		char line[255];
		strcpy(path1, "kulender\\users\\");
		strcat(path1, USER_id);
		strcat(path1, ".txt");
		infp = fopen(path1, "r+");
		strcpy(path2, "kulender\\users\\");
		strcat(path2, USER_id);
		strcat(path2, "_new");
		strcat(path2, ".txt");
		newfp = fopen(path2, "w+");

		if (infp == 0) {
			printf("file not opened error\n");
			Sleep(1500);
			return;
		}
		if (newfp == 0) {
			printf("file not opened error\n");
			Sleep(1500);
			return;
		}

		strcpy(name, name1);
		char buffer[255] = "";
		char origin[255];

		int i = 1;
		while (!feof(infp)) {
			if (i == num) { // �̺κ��� �������� ����
				fgets(line, sizeof(line), infp);
				
				strcpy(origin, strtok(line, " ")); // origin : ��¥
				strcat(buffer, origin);
				strcat(buffer, " ");
					
				int i;
				for (i = 0; i < 2; i++) { // �ð�, �ð�
					strcpy(origin, strtok(NULL, " "));
					strcat(buffer, origin);
					strcat(buffer, " ");
				}
				strcat(buffer, name); // buffer -> ��纯�泻��

				fputs(buffer, newfp);
			}
			else {
				fgets(line, sizeof(line), infp);
				fputs(line, newfp);
			}
			i++;
		}
		while (fclose(infp) != 0);
		while (fclose(newfp) != 0);

		if (remove(path1) != 0) {
			printf("���� ���� ����");
			Sleep(1500);
			return;
		}

		if (rename(path2, path1) != 0) {
			printf("���� �̸����� ����");
			Sleep(1500);
			return;
		}
		printf("�������� ����Ǿ����ϴ�.");
		while (fclose(fp) != 0);	
		Sleep(1500);

		*/
		

		/*
			char* name1 = checkSchedule_Name();
			char name[255];
			char origin[255];
			char temp2[255];
			strcpy(name, name1);
			strcpy(temp2, temp);
			for (i = 0; i < num; i++) {
				fgets(temp, sizeof(temp), fp);
			}
			strcpy(origin, strtok(temp, " "));
			strcpy(origin, strtok(NULL, " "));
			strcpy(origin, strtok(NULL, " "));
			strcpy(origin, strtok(NULL, " "));
			if (strlen(origin) > strlen(name)) {
				for (int i = strlen(origin) - strlen(name); i > 1; i--) {
					strcat(name, " ");
				}
			}
			char* p1 = strstr(temp2, origin);
			int cursor_pos1 = strlen(p1) + 1; 
			char space[255] = " \0";    
			strcat(space, name);
			fseek(fp, (-1) * cursor_pos1 - 1, SEEK_CUR);
			fwrite(space, strlen(space), 1, fp);

			*/
		
		char* name1 = checkSchedule_Name();
		char name[255];

		FILE* infp;
		FILE* newfp;
		char path1[PATH_LEN];
		char path2[PATH_LEN];
		char line[255];
		strcpy(path1, "kulender\\users\\");
		strcat(path1, USER_id);
		strcat(path1, ".txt");
		infp = fopen(path1, "r+");
		strcpy(path2, "kulender\\users\\");
		strcat(path2, USER_id);
		strcat(path2, "_new");
		strcat(path2, ".txt");
		newfp = fopen(path2, "w+");

		if (infp == 0) {
			printf("file not opened error\n");
			Sleep(1500);
			return;
		}
		if (newfp == 0) {
			printf("file not opened error\n");
			Sleep(1500);
			return;
		}

		strcpy(name, name1);
		char buffer[255] = "";
		char origin[255];

		int i = 1;
		fgets(line, sizeof(line), infp);
		while (!feof(infp)) {
			if (i == num) { // �̺κ��� �������� ����
				
				strcpy(origin, strtok(line, " ")); // origin : ��¥
				strcat(buffer, origin);
				strcat(buffer, " ");
					
				int i;
				for (i = 0; i < 2; i++) { // �ð�, �ð�
					strcpy(origin, strtok(NULL, " "));
					strcat(buffer, origin);
					strcat(buffer, " ");
				}
				strcat(buffer, name); // buffer -> ��纯�泻��

				fputs(buffer, newfp);
				fputs("\n", newfp);
			}
			else {
				fputs(line, newfp);
			}
			i++;
			fgets(line, sizeof(line), infp);
		}
		while (fclose(infp) != 0);
		while (fclose(newfp) != 0);
		while (fclose(fp) != 0);	

		if (remove(path1) != 0) {
			printf("���� ���� ����");
			Sleep(1500);
			return;
		}

		if (rename(path2, path1) != 0) {
			printf("���� �̸����� ����");
			Sleep(1500);
			return;
		}




	}
	else {
			printf("fileModifier error");
	}
	fclose(fp);

	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");
	fp = fopen(path, "r+");
	for (i = 0; i < num; i++) {
		fgets(temp, sizeof(temp), fp);
	}
	printf("%s\n", temp);
	printf("���� ���� ���� ����Ǿ����ϴ�.\n");
	Sleep(1500); 
	
}