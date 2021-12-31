#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define PATH_LEN 70

#define ID_LEN 20 // id ����
#define PASSWORD_LEN 16 // password ����
#define NAME_LEN 12 // �̸� ���� (�ѱ��ϰ�� 2bytes)
#define BIRTHDAY_LEN 8 // �������
#define GROUPNAME_LEN 24 // �׷��

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <io.h> 
#include <Windows.h>
#include <direct.h>
#include <conio.h>
#include <errno.h>


// ����� ����------------------------------------------------------
// �������� \0 �����̴�
char USER_id[ID_LEN + 1]; // 6 <= length <= 20  
char USER_password[PASSWORD_LEN + 1]; // 8 <= length <= 16
char USER_name[NAME_LEN + 1]; // �ѱ� 2bytes
char USER_birthday[BIRTHDAY_LEN + 1]; // YYYYMMDD
//------------------------------------------------------------------



// menu.c ----------------------------------------------------------
// �޴��� ��ȣ ���� �Լ�
int chooseNumber(int min, int max);

// �޴��� 
int mainMenu(); // ���θ޴�
int calenderMenu(); // �����޴�
void groupMenu(); // �׷�޴�
int deleteAccount(); // ȸ�� Ż��
// -----------------------------------------------------------------


// RW_file.c -------------------------------------------------------
int login(); // �α���
int checkSpace(char* str); // ���� Ȯ���Լ�
int reset();
int checkID(char* str);
void checkPass(char* str);
void checkName(char* str);
int checkBirth();
void makeAccount(); // ȸ������
// -----------------------------------------------------------------


// aboutGroupMenu.c ------------------------------------------------
void joinGroup(); // �׷� ����
void exitGroup(); // �׷� Ż��
void makeGroup(); // �׷� ����
void manageGroup(); // �׷� ����
void expelMember(); // ��� ���ѱ�
void deleteGroup(); // �׷� ����
int checkGroupName(const char* str); //�׷�� Ȯ��
// -----------------------------------------------------------------


// aboutCalenderMenu.c ---------------------------------------------
void lookUpCalendar();
void addSchedule();
void editSchedule();
void deleteSchedule();
int checkDay();
void showSchedule(int type, char* name, int day);
char* showGroupList();
int checkTime();
const char* checkSchedule_Name();
int showScheduleList(int type, char* id, int day, int flag);
void additionalEdit();
void fileModifier(int type, int num);
// -----------------------------------------------------------------


// filetool.c ------------------------------------------------------
void readInform(char* buffer, const char* id, int i);
int readOwnerGroup(const char* id);
int readMemberGroup(const char* id);
void addOwnerGroup(char* group, char* id);
void addMemberGroup(char* group, char* id);
void removeOwnerGroup(const char* id, const char* groupName);
void removeMemberGroup(const char* id, const char* groupName);
int showGroup(const char* groupName);
void removeID(const char* groupName, const char* id);
void writeFile(char* destine, const char* path, int flag);
int getGroupOwnerNum(const char* path);
int getGroupMemberNum(const char* path);
const char* nth_ownerGroup(const char* id, int idx);
const char* nth_memberGroup(const char* id, int idx);
const char* nth_idInGroup(const char* id, int idx);
int GetStringLength(const char* string);
// -----------------------------------------------------------------