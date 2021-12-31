#define _CRT_SECURE_NO_WARNINGS
// 메인 메뉴
#include "kulender.h"

// 개인 txt파일의 비밀번호, 이름, 생년월일을 buffer에 반환한다.
// 문자열 buffer에 flag내용을 옮긴다 (path: 파일경로)
// flag : 0=>비밀번호 반환 1=> 이름반환 2=> 생년월일 반환
void readInform(char* buffer, const char* id, int i) {
	char inform[50] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	if (file == NULL) {
		printf("failed to open file\n");
		return;
	}

	int count;
	char destine[1024] = "";
	for (count = 0; count < i; count++) {
		fgets(destine, sizeof(destine), file);
	}
	fgets(destine, sizeof(destine), file);
	destine[strlen(destine) - 1] = '\0';
	strcpy(buffer, destine);

	while (fclose(file) != 0);
	return;
}

// 개인 id파일에서 현재 owner로 있는 그룹을 1번부터 순서대로 출력한다
// id 에 개인 id 를 인자로 넣으면 해당 계정이 Owner인 그룹들이 출력된다.
// 반환값은 해당 계정이 Owner인 그룹들의 개수
int readOwnerGroup(const char* id) {
	char inform[50] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	if (file == NULL) {
		printf("failed to open file\n");
		return;
	}

	int number;
	int count = 0;
	while (!feof(file)) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		count++;
		if (count == 4) {
			char n[5];
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");

			int i;
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
			}

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
				buffer[strlen(buffer) - 1] = '\0';
				printf("%d.\t%s\n", i + 1, buffer);
			}
			while (fclose(file) != 0);
			return number;
		}
	}
}

// 개인 id파일에서 현재 Member로 있는 그룹을 1번부터 순서대로 출력한다
// id 에 개인 id 를 인자로 넣으면 해당 계정이 Member인 그룹들이 출력된다.
// 반환값은 해당 계정이 Member인 그룹들의 개수
int readMemberGroup(const char* id) {
	char inform[50] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	if (file == NULL) {
		printf("failed to open file\n");
		return;
	}

	int number;
	int count = 0;
	while (!feof(file)) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		count++;
		if (count == 4) {
			char n[5];
			number = atoi(buffer);

			int i;
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
			}

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
			}

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
				buffer[strlen(buffer) - 1] = '\0';
				printf("%d.\t%s\n", i + 1, buffer);
			}

			while (fclose(file) != 0);
			return number;
		}
	}
}

// 개인 id 파일에서 내가 Owner인 그룹을 생성할때 파일의 내용을 수정하는 함수.
// 첫번째 인자 char* group -> 내가 생성한 Owner 그룹 이름
// 두번째 인자 char* id -> (나) 계정 id -> id.txt 파일에 그룹추가
void addOwnerGroup(char* group, char* id) {
	char inform[50] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	char newpath[70];
	strcpy(newpath, inform);
	newpath[strlen(newpath) - 4] = '\0';
	strcat(newpath, "_new.txt");

	FILE* newfile = fopen(newpath, "w"); // filename_new.txt 파일 생성

	if (file == NULL) {
		printf("failed to open file 'r'\n");
		return;
	}

	if (newfile == NULL) {
		printf("failed to open file 'w'\n");
		return;
	}

	int number;
	int count = 0;
	while (!feof(file)) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		count++;
		if (count == 4) {
			char n[5];
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			int i;
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
				fputs(buffer, newfile);
			}

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			number++;
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			for (i = 0; i < number - 1; i++) {
				fgets(buffer, sizeof(buffer), file);
				fputs(buffer, newfile);
			}

			char next[1024];
			strcpy(next, group);
			strcat(next, "\n");
			fputs(next, newfile);
			count++;
			continue;
		}
		fputs(buffer, newfile);
	}
	while (fclose(file) != 0);
	while (fclose(newfile) != 0);

	while (remove(inform) != 0);
	if (rename(newpath, inform) != 0) {
		printf("fail to change file!\n");
		return;
	}
}

// 개인 id 파일에서 내가 참여한 Menber인 그룹의 내용을 수정하는 함수.
// 첫번째 인자 char* group -> 내가 참여한Member 그룹 이름
// 두번째 인자 char* id -> (나) 계정 id -> id.txt 파일에 그룹추가
void addMemberGroup(char* group, char* id) {
	char inform[50] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	char newpath[70];
	strcpy(newpath, inform);
	newpath[strlen(newpath) - 4] = '\0';
	strcat(newpath, "_new.txt");

	FILE* newfile = fopen(newpath, "w"); // filename_new.txt 파일 생성

	if (file == NULL) {
		printf("failed to open file 'r'\n");
		exit(0);
	}

	if (newfile == NULL) {
		printf("failed to open file 'w'\n");
		exit(0);
	}

	int number;
	int count = 0;
	while (feof(file) == 0) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		count++;
		if (count == 4) {
			char n[5];
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			int i;
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
				fputs(buffer, newfile);
			}

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
				fputs(buffer, newfile);
			}

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			number++;
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			for (i = 0; i < number - 1; i++) {
				fgets(buffer, sizeof(buffer), file);
				fputs(buffer, newfile);
			}

			char next[1024];
			strcpy(next, group);
			strcat(next, "\n");
			fputs(next, newfile);
			count++;
			continue;
		}
		fputs(buffer, newfile);
	}
	while (fclose(file) != 0);
	while (fclose(newfile) != 0);

	while (remove(inform) != 0);
	if (rename(newpath, inform) != 0) {
		printf("fail to change file!\n");
		return;
	}
}

// 해당 id 계정의 Owner 그룹 목록 중
// groupName (그룸이름) 항목을 삭제한다.
void removeOwnerGroup(const char* id, const char* groupName) {

	char inform[PATH_LEN] = "kulender\\users\\";
	char newpath[PATH_LEN] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	strcpy(newpath, inform);
	strcat(newpath, "_new.txt");
	FILE* file = fopen(inform, "r");
	FILE* newfile = fopen(newpath, "w"); // filename_new.txt 파일 생성

	if (file == NULL) {
		printf("failed to open file 'r'\n");
		return 0;
	}

	if (newfile == NULL) {
		printf("failed to open file 'w'\n");
		return 0;
	}

	int number;
	int count = 0;
	while (feof(file) == 0) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);

		count++;
		if (count == 4) {
			char n[5];
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			int i;
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
				fputs(buffer, newfile);
			}
			// 스케줄 끗

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			number--;
			if (number <= 0)
				number = 0; //어차피 0이면 이함수 실행 안됨.
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			for (i = 0; i < number + 1; i++) {
				buffer[0] = '\0';
				fgets(buffer, sizeof(buffer), file);

				if (buffer[strlen(buffer) - 1] == '\n')
					buffer[strlen(buffer) - 1] = '\0';
				if (strcmp(buffer, groupName) != 0) {
					strcat(buffer, "\n");
					fputs(buffer, newfile);
				}

			}

			count++;
			continue;
		}
		fputs(buffer, newfile);
	}
	while (fclose(file) != 0);
	while (fclose(newfile) != 0);

	while (remove(inform) != 0);
	if (rename(newpath, inform) != 0) {
		printf("fail to change file!\n");
		return;
	}
}

// 해당 id 계정의 Member 그룹 목록 중
// groupName (그룸이름) 항목을 삭제한다.
void removeMemberGroup(const char* id, const char* groupName) {
	char inform[PATH_LEN] = "kulender\\users\\";
	char newpath[PATH_LEN] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	strcat(newpath, id);
	strcat(newpath, "_new.txt");
	FILE* file = fopen(inform, "r");
	FILE* newfile = fopen(newpath, "w"); // filename_new.txt 파일 생성

	if (file == NULL) {
		printf("failed to open file 'r'\n");
		return 0;
	}

	if (newfile == NULL) {
		printf("failed to open file 'w'\n");
		return 0;
	}

	int number;
	int count = 0;
	while (feof(file) == 0) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		count++;
		if (count == 4) {
			char n[5];
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			int i;
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
				fputs(buffer, newfile);
			}
			// 스케줄 읽기 끗

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
				fputs(buffer, newfile);
			}
			// Owner 그룹 읽기 끝

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			sprintf(n, "%d", number - 1);
			strcat(n, "\n");
			fputs(n, newfile);

			for (i = 0; i < number; i++) {
				buffer[0] = '\0';
				fgets(buffer, sizeof(buffer), file);
				if (buffer[strlen(buffer) - 1] == '\n')
					buffer[strlen(buffer) - 1] = '\0';
				if (strcmp(buffer, groupName) != 0) {
					strcat(buffer, "\n");
					fputs(buffer, newfile);
				}
			}

			//count++;
			continue;
		}
		fputs(buffer, newfile);
	}
	while (fclose(file) != 0);
	while (fclose(newfile) != 0);

	while (remove(inform) != 0);
	if (rename(newpath, inform) != 0) {
		printf("fail to change file!\n");
		return;
	}
}

//------------------------- 그룹에 포함된 사람들을 모아두는 txt파일에 쓰면 돼요---------
// 현재 그룸에 있는 모든 아이디 출력함수
// 반환 -> 그룹에 있는 사람 숫자
int showGroup(const char* groupName) {
	char inform[50] = "kulender\\groups\\";
	strcat(inform, groupName);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	if (file == NULL) {
		printf("failed to open file 'r'\n");
		return 0;
	}

	int count = 1;
	while (!feof(file)) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		if (buffer[strlen(buffer) - 1] == '\n') {
			buffer[strlen(buffer) - 1] = '\0';
		}
		if (strlen(buffer) > 0) {
			printf("%d:\t%s\n", count, buffer);
			count++;
		}
	}
	while (fclose(file) != 0);

	return count - 1;
}

// 그룹중 그룹을 탈퇴할경우 (추방당할겨우) 해당 아이디 삭제
// 그룹이름중, id 를 삭제한다.
void removeID(const char* groupName, const char* id) {
	char inform[PATH_LEN] = "kulender\\groups\\";
	strcat(inform, groupName);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	char newpath[PATH_LEN];
	strcpy(newpath, inform);
	newpath[strlen(newpath) - 4] = '\0';
	strcat(newpath, "_new.txt");

	FILE* newfile = fopen(newpath, "w"); // filename_new.txt 파일 생성

	if (file == NULL) {
		printf("failed to open file 'r'\n");
		Sleep(1500);
		return 0;
	}

	if (newfile == NULL) {
		printf("failed to open file 'w'\n");
		Sleep(1500);
		return 0;
	}

	while (!feof(file)) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		if (buffer[strlen(buffer) - 1] == '\n') {
			buffer[strlen(buffer) - 1] = '\0';
		}
		if (strcmp(buffer, id) != 0) {
			strcat(buffer, "\n");
			fputs(buffer, newfile);
		}
	}

	while (fclose(file) != 0);
	while (fclose(newfile) != 0);

	while (remove(inform) != 0);
	if (rename(newpath, inform) != 0) {
		printf("fail to change file!\n");
		return;
	}
}

// id.txt 파일에서 member그룹중, idx 번째 항목을 반환하는 함수
// 반환(문자열) : idx 번째 member그룹
// 인자 : 확인할 id,  idx(몇번째 member 그룹인지) 
const char* nth_memberGroup(const char* id, int idx) {
	char inform[50] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	if (file == NULL) {
		printf("failed to open file\n");
		return;
	}

	int number;
	int count = 0;
	while (!feof(file)) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		count++;
		if (count == 4) {
			char n[5];
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");

			int i;
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
			}
			fgets(buffer, sizeof(buffer), file);


			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");

			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
			}

			fgets(buffer, sizeof(buffer), file);
			for (i = 0; i < idx; i++) {
				fgets(buffer, sizeof(buffer), file);
				buffer[strlen(buffer) - 1] = '\0';
			}
			while (fclose(file) != 0);
			return buffer;
		}
	}
}

// id.txt 파일에서 owner그룹중, idx 번째 항목을 반환하는 함수
// 반환(문자열) : idx 번째 owner그룹
// 인자 : 확인할 id,  idx(몇번째 owner 그룹인지) 
const char* nth_ownerGroup(const char* id, int idx) {
	char inform[50] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	if (file == NULL) {
		printf("failed to open file\n");
		return;
	}

	int number;
	int count = 0;
	while (!feof(file)) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		count++;
		if (count == 4) {
			char n[5];
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");

			int i;
			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
			}

			fgets(buffer, sizeof(buffer), file);
			for (i = 0; i < idx; i++) {
				fgets(buffer, sizeof(buffer), file);
				buffer[strlen(buffer) - 1] = '\0';
			}
			while (fclose(file) != 0);
			return buffer;
		}
	}
}

//group.txt 에있는 멤버중 idx 번째 멤버를 반환
//반환 (문자열)
// 인자 ( 그룹이름, 몇번째 멤버를 반환할지)
const char* nth_idInGroup(const char* groupName, int idx) {
	char inform[49] = "kulender\\groups\\";
	strcat(inform, groupName);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	char buffer[1024] = "";

	if (file == NULL) {
		printf("failed to open file\n");
		return;
	}

	for (int i = 0; i < idx; i++) {
		fgets(buffer, sizeof(buffer), file);
	}

	while (fclose(file) != 0);
	buffer[strlen(buffer) - 1] = '\0';
	return buffer;
}


// destine -> 문자열로 적을 내용 (txt파일에 추가할 내용)
// path -> 어떤 파일을 수정할지 (수정할 파일)
// flag -> 3가지 종류가 있다. (1 = "schedules", 2 = "groupOwner", 3 = "groupMember" )
// 1번을 선택시 schedule 에 대한 나용 추가, 2선택시 groupOwner 에 대한 나용 추가, 3 ~~ 마찬가지
void writeFile(char* destine, const char* path, int flag) {
	FILE* file = fopen(path, "r"); // filename.txt
	char newpath[70];

	strcpy(newpath, path);
	newpath[strlen(newpath) - 4] = '\0';
	strcat(newpath, "_new.txt");

	FILE* newfile = fopen(newpath, "w"); // filename_new.txt 파일 생성

	if (file == NULL) {
		printf("failed to open file 'r'\n");
		return;
	}

	if (newfile == NULL) {
		printf("failed to open file 'w'\n");
		return;
	}

	if (flag == 1) { // schedule 에 관련된 것만 표현했어요
		int number;
		int count = 0;
		while (!feof(file)) {
			char buffer[1024] = "";
			fgets(buffer, sizeof(buffer), file); // 버퍼에서 읽어오는거에요 그냥
			count++; // 줄 수를 새는거에요
			if (count == 4) { // 4번째줄 (schedule 개수) 부분에서
				char n[5];
				number = atoi(buffer); // 숫자를 가져옵니다 schedule 개수가 몇개인지
				number++; // 내용이 추가되기때문에 schedule 개수를 하나 늘려줘요!
				sprintf(n, "%d", number);
				strcat(n, "\n");
				fputs(n, newfile); // 늘어난 숫자를 붙여줍니다.

				int i;
				for (i = 0; i < number - 1; i++) { // 기존에 있던 (늘어나기 전이던) schedule 개수만큼 그대로 복사붙여넣기 합니다.
					fgets(buffer, sizeof(buffer), file);
					fputs(buffer, newfile);
				}

				// 이부분이 새로 추가된 schedule 을 붙여넣어주는거에요
				char next[1024];
				strcpy(next, destine);
				strcat(next, "\n");
				fputs(next, newfile);
				count++;
				continue;
			}
			fputs(buffer, newfile);
		}
	}
	else if (flag == 2) {// groupOwner 관련된겁니다.
		int number;
		int count = 0;
		while (!feof(file)) {
			char buffer[1024] = "";
			fgets(buffer, sizeof(buffer), file);
			count++;
			if (count == 4) { // 마찬가지로 schedule에서 시작되요
				char n[5];
				number = atoi(buffer);
				sprintf(n, "%d", number);
				strcat(n, "\n");
				fputs(n, newfile); // 이번엔 schedule의 개수가 늘지 않았기때문에 기존의 schedule 개수를 그대로 넣어줍니다.

				int i;
				for (i = 0; i < number; i++) {
					fgets(buffer, sizeof(buffer), file);
					fputs(buffer, newfile);
				} // 기존 schedule 내용까지 그대로 붙어넣어줘요

				fgets(buffer, sizeof(buffer), file);
				number = atoi(buffer); // 자 이제 groupOwner 를 늘려줘야겠죠 이부분은 groupOwner를 수정하는 내용이니
				number++; // groupOwner의 개수를 늘려줍니다
				sprintf(n, "%d", number);
				strcat(n, "\n");
				fputs(n, newfile); // 늘려준 숫자만큼 그대로 붙여넣어줘요

				for (i = 0; i < number - 1; i++) { // 기존에 있던 groupOwner 내용을 복붙해줍니다
					fgets(buffer, sizeof(buffer), file);
					fputs(buffer, newfile);
				}

				// 이부분이 groupOwner 추가된 부분을 해주는거에요
				char next[1024];
				strcpy(next, destine);
				strcat(next, "\n");
				fputs(next, newfile);
				count++;
				continue;
			}
			fputs(buffer, newfile);
		}
	}
	else if (flag == 3) {
		int number;
		int count = 0;
		while (feof(file) == 0) {
			char buffer[1024] = "";
			fgets(buffer, sizeof(buffer), file);
			count++;
			if (count == 4) {
				char n[5];
				number = atoi(buffer);
				sprintf(n, "%d", number);
				strcat(n, "\n");
				fputs(n, newfile);

				int i;
				for (i = 0; i < number; i++) {
					fgets(buffer, sizeof(buffer), file);
					fputs(buffer, newfile);
				}

				fgets(buffer, sizeof(buffer), file);
				number = atoi(buffer);
				sprintf(n, "%d", number);
				strcat(n, "\n");
				fputs(n, newfile);

				for (i = 0; i < number; i++) {
					fgets(buffer, sizeof(buffer), file);
					fputs(buffer, newfile);
				}

				fgets(buffer, sizeof(buffer), file);
				number = atoi(buffer);
				number++;
				sprintf(n, "%d", number);
				strcat(n, "\n");
				fputs(n, newfile);

				for (i = 0; i < number - 1; i++) {
					fgets(buffer, sizeof(buffer), file);
					fputs(buffer, newfile);
				}

				char next[1024];
				strcpy(next, destine);
				strcat(next, "\n");
				fputs(next, newfile);
				count++;
				continue;
			}
			fputs(buffer, newfile);
		}
	}
	while (fclose(file) != 0);
	while (fclose(newfile) != 0);

	while (remove(path) != 0);
	if (rename(newpath, path) != 0) {
		printf("fail to change file!\n");
		return;
	}
}

int getGroupOwnerNum(const char* path)
{
	FILE* file = fopen(path, "r");
	int number = 0;
	int count = 0;
	int flag1 = 0;

	while (1) {
		char buffer[1024] = "";

		fgets(buffer, sizeof(buffer), file);
		count++;

		if ((count == 4 + number + 1) && flag1) { // number 만큼 줄 내려가서 리턴하기
			number = atoi(buffer);
			while (fclose(file) != 0);
			return number;
		}

		if (count == 4) {
			number = atoi(buffer);
			flag1 = 1;
		}
	}
}

int getGroupMemberNum(const char* path)
{
	FILE* file = fopen(path, "r");

	int number = 0;
	int number2 = 0;
	int count = 0;
	int flag1 = 0;
	int flag2 = 0;

	while (1) {
		char buffer[1024] = "";
		fgets(buffer, sizeof(buffer), file);
		count++;

		if ((count == 4 + number + number2 + 1 + 1) && flag2) { // number2 만큼 줄 내려가기
			number2 = atoi(buffer);
			while (fclose(file) != 0);
			return number2;
		}

		if ((count == 4 + number + 1) && flag1) { // number 만큼 줄 내려가기
			number2 = atoi(buffer);
			flag2 = 1;
		}

		if (count == 4) {
			number = atoi(buffer);
			flag1 = 1;
		}
	}
}