#define _CRT_SECURE_NO_WARNINGS
// ���� �޴�
#include "kulender.h"

// ���� txt������ ��й�ȣ, �̸�, ��������� buffer�� ��ȯ�Ѵ�.
// ���ڿ� buffer�� flag������ �ű�� (path: ���ϰ��)
// flag : 0=>��й�ȣ ��ȯ 1=> �̸���ȯ 2=> ������� ��ȯ
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

// ���� id���Ͽ��� ���� owner�� �ִ� �׷��� 1������ ������� ����Ѵ�
// id �� ���� id �� ���ڷ� ������ �ش� ������ Owner�� �׷���� ��µȴ�.
// ��ȯ���� �ش� ������ Owner�� �׷���� ����
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

// ���� id���Ͽ��� ���� Member�� �ִ� �׷��� 1������ ������� ����Ѵ�
// id �� ���� id �� ���ڷ� ������ �ش� ������ Member�� �׷���� ��µȴ�.
// ��ȯ���� �ش� ������ Member�� �׷���� ����
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

// ���� id ���Ͽ��� ���� Owner�� �׷��� �����Ҷ� ������ ������ �����ϴ� �Լ�.
// ù��° ���� char* group -> ���� ������ Owner �׷� �̸�
// �ι�° ���� char* id -> (��) ���� id -> id.txt ���Ͽ� �׷��߰�
void addOwnerGroup(char* group, char* id) {
	char inform[50] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	char newpath[70];
	strcpy(newpath, inform);
	newpath[strlen(newpath) - 4] = '\0';
	strcat(newpath, "_new.txt");

	FILE* newfile = fopen(newpath, "w"); // filename_new.txt ���� ����

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

// ���� id ���Ͽ��� ���� ������ Menber�� �׷��� ������ �����ϴ� �Լ�.
// ù��° ���� char* group -> ���� ������Member �׷� �̸�
// �ι�° ���� char* id -> (��) ���� id -> id.txt ���Ͽ� �׷��߰�
void addMemberGroup(char* group, char* id) {
	char inform[50] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	char newpath[70];
	strcpy(newpath, inform);
	newpath[strlen(newpath) - 4] = '\0';
	strcat(newpath, "_new.txt");

	FILE* newfile = fopen(newpath, "w"); // filename_new.txt ���� ����

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

// �ش� id ������ Owner �׷� ��� ��
// groupName (�׷��̸�) �׸��� �����Ѵ�.
void removeOwnerGroup(const char* id, const char* groupName) {

	char inform[PATH_LEN] = "kulender\\users\\";
	char newpath[PATH_LEN] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	strcpy(newpath, inform);
	strcat(newpath, "_new.txt");
	FILE* file = fopen(inform, "r");
	FILE* newfile = fopen(newpath, "w"); // filename_new.txt ���� ����

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
			// ������ ��

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			number--;
			if (number <= 0)
				number = 0; //������ 0�̸� ���Լ� ���� �ȵ�.
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

// �ش� id ������ Member �׷� ��� ��
// groupName (�׷��̸�) �׸��� �����Ѵ�.
void removeMemberGroup(const char* id, const char* groupName) {
	char inform[PATH_LEN] = "kulender\\users\\";
	char newpath[PATH_LEN] = "kulender\\users\\";
	strcat(inform, id);
	strcat(inform, ".txt");
	strcat(newpath, id);
	strcat(newpath, "_new.txt");
	FILE* file = fopen(inform, "r");
	FILE* newfile = fopen(newpath, "w"); // filename_new.txt ���� ����

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
			// ������ �б� ��

			fgets(buffer, sizeof(buffer), file);
			number = atoi(buffer);
			sprintf(n, "%d", number);
			strcat(n, "\n");
			fputs(n, newfile);

			for (i = 0; i < number; i++) {
				fgets(buffer, sizeof(buffer), file);
				fputs(buffer, newfile);
			}
			// Owner �׷� �б� ��

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

//------------------------- �׷쿡 ���Ե� ������� ��Ƶδ� txt���Ͽ� ���� �ſ�---------
// ���� �׷뿡 �ִ� ��� ���̵� ����Լ�
// ��ȯ -> �׷쿡 �ִ� ��� ����
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

// �׷��� �׷��� Ż���Ұ�� (�߹���Ұܿ�) �ش� ���̵� ����
// �׷��̸���, id �� �����Ѵ�.
void removeID(const char* groupName, const char* id) {
	char inform[PATH_LEN] = "kulender\\groups\\";
	strcat(inform, groupName);
	strcat(inform, ".txt");
	FILE* file = fopen(inform, "r");

	char newpath[PATH_LEN];
	strcpy(newpath, inform);
	newpath[strlen(newpath) - 4] = '\0';
	strcat(newpath, "_new.txt");

	FILE* newfile = fopen(newpath, "w"); // filename_new.txt ���� ����

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

// id.txt ���Ͽ��� member�׷���, idx ��° �׸��� ��ȯ�ϴ� �Լ�
// ��ȯ(���ڿ�) : idx ��° member�׷�
// ���� : Ȯ���� id,  idx(���° member �׷�����) 
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

// id.txt ���Ͽ��� owner�׷���, idx ��° �׸��� ��ȯ�ϴ� �Լ�
// ��ȯ(���ڿ�) : idx ��° owner�׷�
// ���� : Ȯ���� id,  idx(���° owner �׷�����) 
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

//group.txt ���ִ� ����� idx ��° ����� ��ȯ
//��ȯ (���ڿ�)
// ���� ( �׷��̸�, ���° ����� ��ȯ����)
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


// destine -> ���ڿ��� ���� ���� (txt���Ͽ� �߰��� ����)
// path -> � ������ �������� (������ ����)
// flag -> 3���� ������ �ִ�. (1 = "schedules", 2 = "groupOwner", 3 = "groupMember" )
// 1���� ���ý� schedule �� ���� ���� �߰�, 2���ý� groupOwner �� ���� ���� �߰�, 3 ~~ ��������
void writeFile(char* destine, const char* path, int flag) {
	FILE* file = fopen(path, "r"); // filename.txt
	char newpath[70];

	strcpy(newpath, path);
	newpath[strlen(newpath) - 4] = '\0';
	strcat(newpath, "_new.txt");

	FILE* newfile = fopen(newpath, "w"); // filename_new.txt ���� ����

	if (file == NULL) {
		printf("failed to open file 'r'\n");
		return;
	}

	if (newfile == NULL) {
		printf("failed to open file 'w'\n");
		return;
	}

	if (flag == 1) { // schedule �� ���õ� �͸� ǥ���߾��
		int number;
		int count = 0;
		while (!feof(file)) {
			char buffer[1024] = "";
			fgets(buffer, sizeof(buffer), file); // ���ۿ��� �о���°ſ��� �׳�
			count++; // �� ���� ���°ſ���
			if (count == 4) { // 4��°�� (schedule ����) �κп���
				char n[5];
				number = atoi(buffer); // ���ڸ� �����ɴϴ� schedule ������ �����
				number++; // ������ �߰��Ǳ⶧���� schedule ������ �ϳ� �÷����!
				sprintf(n, "%d", number);
				strcat(n, "\n");
				fputs(n, newfile); // �þ ���ڸ� �ٿ��ݴϴ�.

				int i;
				for (i = 0; i < number - 1; i++) { // ������ �ִ� (�þ�� ���̴�) schedule ������ŭ �״�� ����ٿ��ֱ� �մϴ�.
					fgets(buffer, sizeof(buffer), file);
					fputs(buffer, newfile);
				}

				// �̺κ��� ���� �߰��� schedule �� �ٿ��־��ִ°ſ���
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
	else if (flag == 2) {// groupOwner ���õȰ̴ϴ�.
		int number;
		int count = 0;
		while (!feof(file)) {
			char buffer[1024] = "";
			fgets(buffer, sizeof(buffer), file);
			count++;
			if (count == 4) { // ���������� schedule���� ���۵ǿ�
				char n[5];
				number = atoi(buffer);
				sprintf(n, "%d", number);
				strcat(n, "\n");
				fputs(n, newfile); // �̹��� schedule�� ������ ���� �ʾұ⶧���� ������ schedule ������ �״�� �־��ݴϴ�.

				int i;
				for (i = 0; i < number; i++) {
					fgets(buffer, sizeof(buffer), file);
					fputs(buffer, newfile);
				} // ���� schedule ������� �״�� �پ�־����

				fgets(buffer, sizeof(buffer), file);
				number = atoi(buffer); // �� ���� groupOwner �� �÷���߰��� �̺κ��� groupOwner�� �����ϴ� �����̴�
				number++; // groupOwner�� ������ �÷��ݴϴ�
				sprintf(n, "%d", number);
				strcat(n, "\n");
				fputs(n, newfile); // �÷��� ���ڸ�ŭ �״�� �ٿ��־����

				for (i = 0; i < number - 1; i++) { // ������ �ִ� groupOwner ������ �������ݴϴ�
					fgets(buffer, sizeof(buffer), file);
					fputs(buffer, newfile);
				}

				// �̺κ��� groupOwner �߰��� �κ��� ���ִ°ſ���
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

		if ((count == 4 + number + 1) && flag1) { // number ��ŭ �� �������� �����ϱ�
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

		if ((count == 4 + number + number2 + 1 + 1) && flag2) { // number2 ��ŭ �� ��������
			number2 = atoi(buffer);
			while (fclose(file) != 0);
			return number2;
		}

		if ((count == 4 + number + 1) && flag1) { // number ��ŭ �� ��������
			number2 = atoi(buffer);
			flag2 = 1;
		}

		if (count == 4) {
			number = atoi(buffer);
			flag1 = 1;
		}
	}
}