#define _CRT_SECURE_NO_WARNINGS
// 그룹메뉴
#include "kulender.h"

// 9.1 그룹 가입 
void joinGroup() {
	char ex[1024] = "";
	char path[PATH_LEN]="";
	FILE* fin;

	
	while (1) {		
		system("cls");
		printf("------------그룹 가입--------------\n");
		printf("그룹명 입력: ");
		strcpy(path, "kulender\\groups\\");
		gets(ex);
		strcat(path, ex);
		strcat(path, ".txt");
		fin = fopen(path, "r");
		
		

		//그룹명이 유효하지 않으면 -> 다시 입력
		if (!checkGroupName(ex)) {
			continue;
		}
		//그룹명 이미 존재하지 않으면 -> 다시 입력
		if(fin == NULL){
			printf("존재하지 않는 그룹명입니다.\n");
			// 빠져나갈지 묻기
			printf("그룹 메뉴로 이동하려면 'y'나 'Y'를 입력해주세요: ");
			gets(ex);
			if (!strcmp(ex, "y")||!strcmp(ex, "Y")) {
				return;
			}
			continue;
		}//아이디 그룹명이 유효하고 존재하지 않으면 -> 반복문 탈출
	
		//if 그룹이미가입 -> 가입한 그룹입니다 후 다시
		
		char inform[50] = "kulender\\users\\";
		strcat(inform, USER_id);
		strcat(inform, ".txt");
		FILE* file = fopen(inform, "r");
		int flag = 0;
		while (feof(file) == 0) {
			char buffer[1024] = "";
			fgets(buffer, sizeof(buffer), file);
			if (strstr(buffer, ex)) {
				printf("이미 가입한 그룹입니다.\n");
				Sleep(1500);
				flag = 1;
				break;
			}
		}
		fclose(file);
		if (flag == 1)
			continue;
		else { 
			fclose(fin);
			break;
		}
		
	}
	// 그룹원으로 추가

	// 1. 그룹.txt에 자신의 id추가
	FILE* fin2 = fopen(path, "a");
	if (fin2 == NULL) {
		return;	
	}

	fprintf(fin2, "%s\n", USER_id); 
	fclose(fin2);
	
	path[0] ='\0'; // 경로 초기화

	// 2. id.txt_그룹원 그룹에 추가 
	addMemberGroup(ex, USER_id);
	printf("그룹과 나의 일정을 공유합니다.\n");
	Sleep(1500);
}

// 9.2그룹 탈퇴
void exitGroup()
{
	char path[1024] = "";
	char groupName[GROUPNAME_LEN]="";
	int gnum = 0;
	int c = 0;
	system("cls");

	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");
	
	//소속된 그룹이 없으면  -> 메세지 출력 후 종료
	printf("--------------그룹 탈퇴--------------\n");
	if(getGroupMemberNum(path) == 0){
		printf("       가입한 그룹이 없습니다.\n");	
		printf("-------------------------------------\n");
		Sleep(1500);
		return;
	}
	gnum = readMemberGroup(USER_id);
	printf("-------------------------------------\n");
	printf("탈퇴할 그룹을 선택하세요: ");	
	c = chooseNumber(1,gnum);
	strcpy(groupName,nth_memberGroup(USER_id, c));

	// 그룹 탈퇴

	// 1. USER_id.txt에서 그룹원인 그룹 삭제
	removeMemberGroup(USER_id,groupName);
	
	// 2. group.txt에서 자기 아이디 찾아서 삭제
	removeID(groupName, USER_id);

	printf("그룹 탈퇴 완료\n");
	Sleep(1500);
}

// 9.3 그룹 생성
void makeGroup() 
{
	char ex[1024] = "";
	char path[PATH_LEN] = "";
	FILE* fin;
	
	while (1) {
		system("cls");
		printf("------------그룹 생성--------------\n");
		printf("그룹명 입력: ");
		gets(ex);
		strcpy(path, "kulender\\groups\\");
		strcat(path, ex);
		strcat(path, ".txt");

		fin = fopen(path, "r");

		//그룹명이 유효하지 않으면 -> 다시 입력
		if (!checkGroupName(ex)) {
			continue;
		}
		//그룹이 이미 존재하면 -> 다시 입력
		if (fin != NULL) {
			printf("이미 존재하는 그룹입니다.\n");
			Sleep(1500);
		}//아이디 그룹명이 유효하고 존재하지 않으면 -> 반복문 탈출
		else {
			if (fin != 0) {
				fclose(fin);
			}
			break;
		}
	}
	
	// 그룹 생성

	//1. 그룹txt에 자신 아이디 저장 (첫줄 - 그룹장)
	FILE* fin2 = fopen(path, "a");
	if (fin2 == NULL) {
		return;
	}

	fprintf(fin2, "%s\n", USER_id); 
	fclose(fin2);

	path[0] ='\0'; // 경로 초기화

	// 2. id.txt_그룹원 그룹에 추가 
	addOwnerGroup(ex, USER_id);

	printf("그룹이 정상적으로 생성되었습니다.\n");
	Sleep(1500);
}

//9.4 그룹 관리
void manageGroup()
{
	system("cls");
	char path[PATH_LEN]="";
	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");
	
	// 생성한 그룹의 수가 0일 경우 -> 메세지 출력 후 그룹메뉴로 이동
	if(getGroupOwnerNum(path)==0){
		printf("------------그룹 관리--------------\n");
		printf("       생성한 그룹이 없습니다.\n");
		printf("----------------------------------\n");
		Sleep(1500);
		return;
	}

	printf("------------그룹 관리--------------\n");
	printf("       1. 그룹원 내보내기\n");
	printf("       2. 그룹 삭제\n");
	printf("----------------------------------\n");
	printf("선택 : ");
	switch(chooseNumber(1,2)){
	case 1:
		expelMember();
		break;
	case 2:
		deleteGroup();
		break;
	}
}

// 9.4.1 그룹원 내보내기
void expelMember()
{	
	char path[PATH_LEN]="";	
	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");
	
	char groupName[GROUPNAME_LEN]="";
	char memberName[NAME_LEN]="";
	int gnum = getGroupOwnerNum(path);
	int mnum=0;
	printf("--------------관리 그룹--------------\n");
	if(gnum==0){
		printf("       생성한 그룹이 없습니다.\n");
		printf("------------------------------------\n");
		Sleep(1500);
		return;
	}
	readOwnerGroup(USER_id);
	printf("------------------------------------\n");
	printf("그룹을 선택하세요: ");
	int c = chooseNumber(1, gnum);
	
	strcpy(groupName, nth_ownerGroup(USER_id,c));

	// 1. 그룹원 이름을 출력
	printf("--------------내보낼 그룹원 --------------\n");
	mnum = showGroup(groupName);
	printf("--------------------------------------\n");
	
	// 소속 그룹원이 자기 자신 뿐일 때
	if(mnum == 1){
		printf("내보낼 그룹원이 없습니다. ");
		Sleep(1500);
		return;
	}
	printf("그룹원을 선택하세요 (그룹장은 선택할 수 없습니다): ");
	c = chooseNumber(2, mnum);

	strcpy(memberName,nth_idInGroup(groupName, c));
	//printf("삭제할 id: %s\n", memberName); 
	
	// 2. 그 아이디 파일에서 group.txt와 같은 이름을 한 문자열을 삭제
	removeMemberGroup(memberName,groupName);

	// 3. 그룹.txt에서 해당 맴버 삭제
	removeID(groupName, memberName);

	printf("%s(을)를 정상적으로 내보냈습니다. ", memberName);
	Sleep(1500);
}

// 9.4.2 그룹 삭제
void deleteGroup()
{
	system("cls");
	char pathg[PATH_LEN] = "";
	char groupName[GROUPNAME_LEN] = "";
	int c = 0;
	int gnum = 0;
	printf("--------------그룹 삭제--------------\n");
	gnum = readOwnerGroup(USER_id);
	printf("------------------------------------\n");
	printf("삭제할 그룹의 번호를 입력하세요: ");
	c = chooseNumber(1, gnum);
	strcpy(groupName, nth_ownerGroup(USER_id, c));

	// 1. 해당 그룹 파일을 연다
	strcpy(pathg, "kulender\\groups\\");
	strcat(pathg, groupName);
	strcat(pathg, ".txt");
	FILE* file;
	file = fopen(pathg, "r");

	// 2. 파일이 끝날 때 까지 한줄 씩 읽어서

	// 2.1 첫 줄은 removeOwnerGroup (첫줄은 그룹장)
	char buffer[1024] = "";
	fgets(buffer, sizeof(buffer), file);
	removeOwnerGroup(USER_id, groupName);
	fgets(buffer, sizeof(buffer), file);
	// 2.2 그 다음부터 끝까지 removeMemberGroup (두번째 부터 끝까지는 그룹 맴버)
	if (buffer[0] != ' ') { 
		while (!feof(file)) {
			if (buffer[strlen(buffer) - 1] == '\n') {
				buffer[strlen(buffer) - 1] = '\0';
			}
			removeMemberGroup(buffer, groupName);
			fgets(buffer, sizeof(buffer), file);
		}
	}

	// 3. 해당 그룹 파일 을 지운다.
	fclose(file);
	remove(pathg);

	printf("그룹이 삭제되었습니다.\n");
	Sleep(1500);
}

// 그룹명 조건 체크
int checkGroupName(const char* str) {
	
	int len = 0;

	for (size_t i = 0; i < strlen(str); i++) {
		// 한글은 방 2개 차지하므로 i++한번더 해주고 이외의 경우에는 그냥 건너뜁니다.
		if (str[i] & 0x80) {
			i++;	
		}
		len++;
	}

	if(0 <len && len < GROUPNAME_LEN + 1){
		// valid
		return 1;
	}
	else{
		// invalid
		printf("그룹명 형식에 맞지 않습니다.\n");
		Sleep(1500);
		return 0;
	}		
}