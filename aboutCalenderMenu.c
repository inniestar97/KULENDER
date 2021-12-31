#define _CRT_SECURE_NO_WARNINGS
// 일정메뉴
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

// 완성
void lookUpCalendar() {
	// 8.1 일정 조회 메뉴
	system("cls");
	printf("-----------일정 조회--------------\n");
	printf("1. 개인 일정 조회\n");
	printf("2. 그룹 일정 조회\n");
	printf("메뉴 선택 : ");
	int result = chooseNumber(1, 2);  //선택지 입력받기
	if (result == 1) {
		// 개인 일정 조회

		int day = checkDay(); // YYMM형식으로 날짜 입력받고 리턴

		showSchedule(0, USER_id, day);
	}
	else if (result == 2) {
		// 그룹 일정 조회

		char groupName[255];
		strcpy(groupName, showGroupList());
		int day = checkDay(); // YYMM형식 
		showSchedule(1, groupName, day);

	}
	else {
		printf("lookUpCalendar()에서 문제가 발생했습니다.");
	}

}

// 완성 
void addSchedule() {
	//8.2 일정 추가 메뉴
	//연월입력 => 시작,종료 시각 입력 => 일정명 입력 => 시작메뉴에서 받은 아이디 파일의 개인일정 부분에 추가=> 일정추가 완료
	system("cls");
	printf("-----------일정 추가--------------\n");
	char path[PATH_LEN] = "";
	char input_data[1024] = "";
	printf("일정추가를 위해 연-월-일을 입력합니다.\n");
	int Date = checkBirth("");

	printf("시작 시각을 입력합니다.\n");
	int start_Time = checkTime();
	
	int finish_Time;
	
	while (1) {
		printf("종료 시각을 입력합니다.\n");
		finish_Time = checkTime();
		if (finish_Time < start_Time) {
			printf("종료시각이 시작시각 보다 빠릅니다. 다시 입력하세요\n");
		}
		else {
			break;
		}
	}

	printf("일정명을 입력합니다.\n");
	char* schedule_name = checkSchedule_Name();

	// 생년월일 예외처리
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
	else { // test 중
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

	// 경로 설정
	strcpy(path, "kulender\\users\\");	//사용자 아이디로 있는 파일
	strcat(path, USER_id);
	strcat(path, ".txt");

	writeFile(input_data, path, 1);
	printf("일정 추가가 완료되었습니다!\n");

	printf("잠시후 일정메뉴로 넘어갑니다.\n");
	Sleep(1500);

	calenderMenu();
}

//8.3 일정 변경 메뉴
void editSchedule() {

	system("cls");
	printf("-----------변경 사항 선택--------------\n");
	printf("1. 연-월-일 변경\n");
	printf("2. 시작-종료 시각 변경\n");
	printf("3. 일정명 변경\n");
	printf("메뉴 선택 : ");
	int result = chooseNumber(1, 3);
	int day = checkBirth("");

	system("cls");
	printf("-----------일정 선택--------------\n");

	//showScheduleList()를 활용하여 일정을 선택받고 이걸로 잘 만들기
	int num = showScheduleList(1, USER_id, day, 0);
	if (num == 0) {
		printf("해당하는 날짜의 일정이 존재하지 않습니다.");
		Sleep(1500);
		editSchedule();
		return;
	}


	fileModifier(result, num);
}

//8.4 일정 삭제 메뉴
void deleteSchedule() {

	system("cls");
	int day = checkBirth("");
	// 날짜입력받고 일정 선택받기
	system("cls");
	printf("-----------일정 선택--------------\n");
	int num = showScheduleList(1, USER_id, day, 0); // 선택한 일정이 파일에서 몇번째줄인지 리턴, 없다면 0 리턴
	if (num == 0) {
		printf("해당하는 날짜의 일정이 존재하지 않습니다.");
		Sleep(1500);
		deleteSchedule();
	}

	FILE* fp; 
	FILE* newfp;
	char path1[PATH_LEN];  //path1 : 기존의 파일
	char path2[PATH_LEN];  //path1 : 새 파일
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
			j--; // 일정 개수 -1
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
		printf("파일 삭제 실패");
		Sleep(1500);
		return;
	}

	if (rename(path2, path1) != 0) {
		printf("파일 이름변경 실패");
		Sleep(1500);
		return;
	}
	printf("일정 삭제 성공");
	Sleep(1500);
}

// 날짜 유효성 검사
int checkDay() {
	char ex[1024] = { 0, };
	while (1) {
		printf("년월 : ");
		gets(ex);
		int Daycheck = GetStringLength(ex);

		//밑의 if문에서 쓸려고 선언
		int year;
		int month;
		int input;

		if (Daycheck == 4) { // YYMM 형식
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
		printf("\n년월을 읽을 수 없습니다. 올바른 형식으로 입력해 주세요.\n");
	}
}

//개인 일정 조회
void showSchedule(int type, char* name, int day) {

	if (!type) {
		int check = showScheduleList(0, name, day, 1);
		if (check == 0) {//해당하는 일정이 없으면 일정조회 메뉴로 돌아간다.
			printf("입력한 날짜에 해당하는 일정이 없습니다.\n");
			printf("일정메뉴로 돌아갑니다.\n");
			Sleep(1500);
			calenderMenu();
		}
		else {
			printf("년/월에 해당하는 일정리스트를 출력했습니다.\n");
			printf("엔터키를 누르면 일정메뉴로 돌아갑니다.\n");
			char ex[1024] = { 0, };
			gets(ex);
			if (strlen(ex) == 0) {
				printf("일정메뉴로 돌아갑니다.");
				Sleep(1500);
				calenderMenu();
			}
		}
	}
	else {
		// 그룹 일정 조회
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

	printf("엔터키를 누르면 일정메뉴로 돌아갑니다.\n");
	char ex[1024] = { 0, };
	gets(ex);
	if (strlen(ex) == 0) {
		printf("일정메뉴로 돌아갑니다.");
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
	int num = atoi(line); // schedule()개수가 있는데 까지 줄 넘기기
	for (i = 0; i < num; i++) {
		fgets(line, sizeof(line), fp);
	}
	fgets(line, sizeof(line), fp);
	num = atoi(line); // 그룹 개수
	printf("-----------그룹 선택--------------\n");
	if (num == 0) {
		printf("속하는 그룹이 없습니다.\n");
		printf("그룹을 생성, 추가하고 다시 시도해주세요.\n");
		printf("일정메뉴로 돌아갑니다.\n");
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
	int num2 = atoi(line); // 그룹 개수
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
		printf("그룹을 선택해 주세요 : ");
		scanf("%d", &result);
		if (result > 0 && result <= num + num2) {
			break;
		}
	}
	getchar(); // 버퍼에 들어가 있는 엔터 지우기
	before = head;
	for (i = 0; i < result; i++) {
		before = before->next;
	}
	strcpy(name, before->data);
	return name;
}

//일정 추가, 변경시 사용할 시각 검사 함수
int checkTime() {
	char ex[1024] = { 0, };
	while (1) {

		printf("시각 입력 : ");
		int len;
		gets(ex);
		len = strlen(ex);

		int hour;
		int minute;
		int input;

		if (len == 4) {	//HHMM 형식
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
		else if (len == 5) {	//HH-MM 형식
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

//일정명 받고 검사할 함수
const char* checkSchedule_Name() {
	while (1) {
		static char ex[1024] = { '0', };
		ex[1024] = "";
		printf("일정명 입력: ");
		gets(ex);
		int nameCheck = GetStringLength(ex);

		if (nameCheck > 500 || nameCheck == 0) {
			printf("일정명의 길이가 문법 형식에 어긋납니다. 1글자 이상 500글자 이하로 입력해주세요.\n");
			continue;
		}

		else {
			return ex;
		}
	}
}

// 일정 목록을 보여주는 함수
// 파라미터
// -type은 1, 0으로 구분   
// -type==0의 경우 chooseNum을 이용한 입력을 받지 않는다. 
// -type==1의 경우 chooseNum을 이용한 입력을 받고 선택된 일정이 텍스트파일에서 위에서 몇번째 줄인지를 return
// -char* id의 일정을 볼 사람의 아이디를 입력 
// -int day의 경우 날짜데이터를 입력
// -EX) day = 2103, day = 210330     YYMM 형태 혹은 YYMMDD형태로 입력한다.
// 이 함수는 순수하게 일정과 입력문구 "일정을 선택하세요 : "만을 출력합니다. 
// -----일정 보기-----   요런 제목이나     "해당하는 날짜에 일정이 없습니다." 이런 안내문구는 따로 출력해야 합니다.
// 해당 월 혹은 날짜에 일정이 하나도 없으면 0을 return합니다. (return 0;)
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

		for (i = 0; i < 4; i++) { //schedule 갯수를 나타내는 줄까지 넘기기
			fgets(line, sizeof(line), fp);
		}
		int num = atoi(line); // shcedule 갯수 받아오기
		int j = 0;
		if (!isGroup) {
			printf("-------------------------------------------------\n");
		}
		for (i = 1; i <= num; i++) {  // schedule리스트 출력
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
			char* s = line;   // 시작 위치로 변경
			int size;
			if (flag) {
				size = 4;
			}
			else {
				size = 6;
			}
			while (size-- > 0 && *s != '\0') {  // size가 0보다 크고, 문자열 끝이 지나지 않은 경우
				 *(buf++) = *(s++);   // 복사 
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
		//일정 리스트 출력
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
		} //schedule 개수를 나타내는 줄까지 넘기기

		num = atoi(line); // shcedule 갯수 받아오기
		struct NODE* head = malloc(sizeof(struct NODE));
		struct NODE* before = malloc(sizeof(struct NODE));
		head->next = before;

		int j = 0;
		printf("-------------------------------------------------\n");
		for (i = 1; i <= num; i++) {  // schedule리스트 출력하고 linked list에 저장
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
			char* s = line;   // 시작 위치로 변경
			int size = 6;
			while (size-- > 0 && *s != '\0') {  // size가 0보다 크고, 문자열 끝이 지나지 않은 경우
				 *(buf++) = *(s++);   // 복사 
			}
			*buf = '\0';    // 끝에 널 문자 처리
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
			printf("일정 선택 : ");
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

//추가 변경메뉴
void additionalEdit() {
	system("cls");
	printf("-----------추가 변경 선택--------------\n");
	printf("1. 추가 변경\n");
	printf("2. 변경 종료");
	int result = chooseNumber(1, 2);
	if (result == 1) {
		editSchedule();
	}
	else {
		calenderMenu();
	}
}

//완성 ============================================================
//type == 1; 날짜 바꾸기
//type == 2; 시각 바꾸기
//type == 3; 일정명 바꾸기
void fileModifier(int type, int num) {

	FILE* fp;
	char temp[256];
	char word[256]; // 추가함
	char* p;
	int cursor_pos;
	char path[PATH_LEN];
	int i;
	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");
	fp = fopen(path, "r+");
	printf("변경할 ");
	if (type == 1) {
		// 생년월일 예외처리
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
			printf("시작 ");
			time1 = checkTime();
			printf("종료 ");
			time2 = checkTime();
			if (time1 / 100 >= time2 / 100 && time1 % 100 > time2 % 100) {
				printf("종료시각이 시작시각 보다 빠릅니다. 일정시각을 다시 입력해 주세요.\n");
				Sleep(1500);
			}
			else if (time1 == -1 || time2 == -1) {
				printf("일정시각을 다시 입력해 주세요\n");
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
			if (i == num) { // 이부분의 일정명을 변경
				fgets(line, sizeof(line), infp);
				
				strcpy(origin, strtok(line, " ")); // origin : 날짜
				strcat(buffer, origin);
				strcat(buffer, " ");
					
				int i;
				for (i = 0; i < 2; i++) { // 시각, 시각
					strcpy(origin, strtok(NULL, " "));
					strcat(buffer, origin);
					strcat(buffer, " ");
				}
				strcat(buffer, name); // buffer -> 모든변경내용

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
			printf("파일 삭제 실패");
			Sleep(1500);
			return;
		}

		if (rename(path2, path1) != 0) {
			printf("파일 이름변경 실패");
			Sleep(1500);
			return;
		}
		printf("일정명이 변경되었습니다.");
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
			if (i == num) { // 이부분의 일정명을 변경
				
				strcpy(origin, strtok(line, " ")); // origin : 날짜
				strcat(buffer, origin);
				strcat(buffer, " ");
					
				int i;
				for (i = 0; i < 2; i++) { // 시각, 시각
					strcpy(origin, strtok(NULL, " "));
					strcat(buffer, origin);
					strcat(buffer, " ");
				}
				strcat(buffer, name); // buffer -> 모든변경내용

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
			printf("파일 삭제 실패");
			Sleep(1500);
			return;
		}

		if (rename(path2, path1) != 0) {
			printf("파일 이름변경 실패");
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
	printf("위와 같이 일정 변경되었습니다.\n");
	Sleep(1500); 
	
}