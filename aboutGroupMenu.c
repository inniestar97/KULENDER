#define _CRT_SECURE_NO_WARNINGS
// �׷�޴�
#include "kulender.h"

// 9.1 �׷� ���� 
void joinGroup() {
	char ex[1024] = "";
	char path[PATH_LEN]="";
	FILE* fin;

	
	while (1) {		
		system("cls");
		printf("------------�׷� ����--------------\n");
		printf("�׷�� �Է�: ");
		strcpy(path, "kulender\\groups\\");
		gets(ex);
		strcat(path, ex);
		strcat(path, ".txt");
		fin = fopen(path, "r");
		
		

		//�׷���� ��ȿ���� ������ -> �ٽ� �Է�
		if (!checkGroupName(ex)) {
			continue;
		}
		//�׷�� �̹� �������� ������ -> �ٽ� �Է�
		if(fin == NULL){
			printf("�������� �ʴ� �׷���Դϴ�.\n");
			// ���������� ����
			printf("�׷� �޴��� �̵��Ϸ��� 'y'�� 'Y'�� �Է����ּ���: ");
			gets(ex);
			if (!strcmp(ex, "y")||!strcmp(ex, "Y")) {
				return;
			}
			continue;
		}//���̵� �׷���� ��ȿ�ϰ� �������� ������ -> �ݺ��� Ż��
	
		//if �׷��̹̰��� -> ������ �׷��Դϴ� �� �ٽ�
		
		char inform[50] = "kulender\\users\\";
		strcat(inform, USER_id);
		strcat(inform, ".txt");
		FILE* file = fopen(inform, "r");
		int flag = 0;
		while (feof(file) == 0) {
			char buffer[1024] = "";
			fgets(buffer, sizeof(buffer), file);
			if (strstr(buffer, ex)) {
				printf("�̹� ������ �׷��Դϴ�.\n");
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
	// �׷������ �߰�

	// 1. �׷�.txt�� �ڽ��� id�߰�
	FILE* fin2 = fopen(path, "a");
	if (fin2 == NULL) {
		return;	
	}

	fprintf(fin2, "%s\n", USER_id); 
	fclose(fin2);
	
	path[0] ='\0'; // ��� �ʱ�ȭ

	// 2. id.txt_�׷�� �׷쿡 �߰� 
	addMemberGroup(ex, USER_id);
	printf("�׷�� ���� ������ �����մϴ�.\n");
	Sleep(1500);
}

// 9.2�׷� Ż��
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
	
	//�Ҽӵ� �׷��� ������  -> �޼��� ��� �� ����
	printf("--------------�׷� Ż��--------------\n");
	if(getGroupMemberNum(path) == 0){
		printf("       ������ �׷��� �����ϴ�.\n");	
		printf("-------------------------------------\n");
		Sleep(1500);
		return;
	}
	gnum = readMemberGroup(USER_id);
	printf("-------------------------------------\n");
	printf("Ż���� �׷��� �����ϼ���: ");	
	c = chooseNumber(1,gnum);
	strcpy(groupName,nth_memberGroup(USER_id, c));

	// �׷� Ż��

	// 1. USER_id.txt���� �׷���� �׷� ����
	removeMemberGroup(USER_id,groupName);
	
	// 2. group.txt���� �ڱ� ���̵� ã�Ƽ� ����
	removeID(groupName, USER_id);

	printf("�׷� Ż�� �Ϸ�\n");
	Sleep(1500);
}

// 9.3 �׷� ����
void makeGroup() 
{
	char ex[1024] = "";
	char path[PATH_LEN] = "";
	FILE* fin;
	
	while (1) {
		system("cls");
		printf("------------�׷� ����--------------\n");
		printf("�׷�� �Է�: ");
		gets(ex);
		strcpy(path, "kulender\\groups\\");
		strcat(path, ex);
		strcat(path, ".txt");

		fin = fopen(path, "r");

		//�׷���� ��ȿ���� ������ -> �ٽ� �Է�
		if (!checkGroupName(ex)) {
			continue;
		}
		//�׷��� �̹� �����ϸ� -> �ٽ� �Է�
		if (fin != NULL) {
			printf("�̹� �����ϴ� �׷��Դϴ�.\n");
			Sleep(1500);
		}//���̵� �׷���� ��ȿ�ϰ� �������� ������ -> �ݺ��� Ż��
		else {
			if (fin != 0) {
				fclose(fin);
			}
			break;
		}
	}
	
	// �׷� ����

	//1. �׷�txt�� �ڽ� ���̵� ���� (ù�� - �׷���)
	FILE* fin2 = fopen(path, "a");
	if (fin2 == NULL) {
		return;
	}

	fprintf(fin2, "%s\n", USER_id); 
	fclose(fin2);

	path[0] ='\0'; // ��� �ʱ�ȭ

	// 2. id.txt_�׷�� �׷쿡 �߰� 
	addOwnerGroup(ex, USER_id);

	printf("�׷��� ���������� �����Ǿ����ϴ�.\n");
	Sleep(1500);
}

//9.4 �׷� ����
void manageGroup()
{
	system("cls");
	char path[PATH_LEN]="";
	strcpy(path, "kulender\\users\\");
	strcat(path, USER_id);
	strcat(path, ".txt");
	
	// ������ �׷��� ���� 0�� ��� -> �޼��� ��� �� �׷�޴��� �̵�
	if(getGroupOwnerNum(path)==0){
		printf("------------�׷� ����--------------\n");
		printf("       ������ �׷��� �����ϴ�.\n");
		printf("----------------------------------\n");
		Sleep(1500);
		return;
	}

	printf("------------�׷� ����--------------\n");
	printf("       1. �׷�� ��������\n");
	printf("       2. �׷� ����\n");
	printf("----------------------------------\n");
	printf("���� : ");
	switch(chooseNumber(1,2)){
	case 1:
		expelMember();
		break;
	case 2:
		deleteGroup();
		break;
	}
}

// 9.4.1 �׷�� ��������
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
	printf("--------------���� �׷�--------------\n");
	if(gnum==0){
		printf("       ������ �׷��� �����ϴ�.\n");
		printf("------------------------------------\n");
		Sleep(1500);
		return;
	}
	readOwnerGroup(USER_id);
	printf("------------------------------------\n");
	printf("�׷��� �����ϼ���: ");
	int c = chooseNumber(1, gnum);
	
	strcpy(groupName, nth_ownerGroup(USER_id,c));

	// 1. �׷�� �̸��� ���
	printf("--------------������ �׷�� --------------\n");
	mnum = showGroup(groupName);
	printf("--------------------------------------\n");
	
	// �Ҽ� �׷���� �ڱ� �ڽ� ���� ��
	if(mnum == 1){
		printf("������ �׷���� �����ϴ�. ");
		Sleep(1500);
		return;
	}
	printf("�׷���� �����ϼ��� (�׷����� ������ �� �����ϴ�): ");
	c = chooseNumber(2, mnum);

	strcpy(memberName,nth_idInGroup(groupName, c));
	//printf("������ id: %s\n", memberName); 
	
	// 2. �� ���̵� ���Ͽ��� group.txt�� ���� �̸��� �� ���ڿ��� ����
	removeMemberGroup(memberName,groupName);

	// 3. �׷�.txt���� �ش� �ɹ� ����
	removeID(groupName, memberName);

	printf("%s(��)�� ���������� �����½��ϴ�. ", memberName);
	Sleep(1500);
}

// 9.4.2 �׷� ����
void deleteGroup()
{
	system("cls");
	char pathg[PATH_LEN] = "";
	char groupName[GROUPNAME_LEN] = "";
	int c = 0;
	int gnum = 0;
	printf("--------------�׷� ����--------------\n");
	gnum = readOwnerGroup(USER_id);
	printf("------------------------------------\n");
	printf("������ �׷��� ��ȣ�� �Է��ϼ���: ");
	c = chooseNumber(1, gnum);
	strcpy(groupName, nth_ownerGroup(USER_id, c));

	// 1. �ش� �׷� ������ ����
	strcpy(pathg, "kulender\\groups\\");
	strcat(pathg, groupName);
	strcat(pathg, ".txt");
	FILE* file;
	file = fopen(pathg, "r");

	// 2. ������ ���� �� ���� ���� �� �о

	// 2.1 ù ���� removeOwnerGroup (ù���� �׷���)
	char buffer[1024] = "";
	fgets(buffer, sizeof(buffer), file);
	removeOwnerGroup(USER_id, groupName);
	fgets(buffer, sizeof(buffer), file);
	// 2.2 �� �������� ������ removeMemberGroup (�ι�° ���� �������� �׷� �ɹ�)
	if (buffer[0] != ' ') { 
		while (!feof(file)) {
			if (buffer[strlen(buffer) - 1] == '\n') {
				buffer[strlen(buffer) - 1] = '\0';
			}
			removeMemberGroup(buffer, groupName);
			fgets(buffer, sizeof(buffer), file);
		}
	}

	// 3. �ش� �׷� ���� �� �����.
	fclose(file);
	remove(pathg);

	printf("�׷��� �����Ǿ����ϴ�.\n");
	Sleep(1500);
}

// �׷�� ���� üũ
int checkGroupName(const char* str) {
	
	int len = 0;

	for (size_t i = 0; i < strlen(str); i++) {
		// �ѱ��� �� 2�� �����ϹǷ� i++�ѹ��� ���ְ� �̿��� ��쿡�� �׳� �ǳʶݴϴ�.
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
		printf("�׷�� ���Ŀ� ���� �ʽ��ϴ�.\n");
		Sleep(1500);
		return 0;
	}		
}