#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define PATH_LEN 70

#define ID_LEN 20 // id 길이
#define PASSWORD_LEN 16 // password 길이
#define NAME_LEN 12 // 이름 길이 (한글일경우 2bytes)
#define BIRTHDAY_LEN 8 // 생년월일
#define GROUPNAME_LEN 24 // 그룹명

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


// 사용자 정보------------------------------------------------------
// 마지막은 \0 문자이다
char USER_id[ID_LEN + 1]; // 6 <= length <= 20  
char USER_password[PASSWORD_LEN + 1]; // 8 <= length <= 16
char USER_name[NAME_LEN + 1]; // 한글 2bytes
char USER_birthday[BIRTHDAY_LEN + 1]; // YYYYMMDD
//------------------------------------------------------------------



// menu.c ----------------------------------------------------------
// 메뉴중 번호 고르는 함수
int chooseNumber(int min, int max);

// 메뉴들 
int mainMenu(); // 메인메뉴
int calenderMenu(); // 일정메뉴
void groupMenu(); // 그룹메뉴
int deleteAccount(); // 회원 탈퇴
// -----------------------------------------------------------------


// RW_file.c -------------------------------------------------------
int login(); // 로그인
int checkSpace(char* str); // 공백 확인함수
int reset();
int checkID(char* str);
void checkPass(char* str);
void checkName(char* str);
int checkBirth();
void makeAccount(); // 회원가입
// -----------------------------------------------------------------


// aboutGroupMenu.c ------------------------------------------------
void joinGroup(); // 그룹 가입
void exitGroup(); // 그룹 탈퇴
void makeGroup(); // 그룹 생성
void manageGroup(); // 그룹 관리
void expelMember(); // 멤버 내쫓기
void deleteGroup(); // 그룹 삭제
int checkGroupName(const char* str); //그룹명 확인
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