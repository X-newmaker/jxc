/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_COMMON_STRING_H_
#define INCLUDE_COMMON_STRING_H_

void* _strcpy(void* dest, void* src);
int   _strlen(const void* str);
int _strncmp(const void* dest, const void* src, u32 size);
int   _strcmp(const void* dest, const void* src);
void* _memset(void* str, int c, u32 len);
void* _memcpy(void* dest, const void* src, u32 size);
int   _memcmp(const void* dest, const void* src, u32 size);

#endif /* INCLUDE_COMMON_STRING_H_ */
