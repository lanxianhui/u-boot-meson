/* * \file        amlImage_if.h
 * \brief       Amlogic firmware image interface
 *
 * \version     1.0.0
 * \date        2013/5/21
 * \author      Sam.Wu <yihui.wu@Amlogic.com>
 *
 * Copyright (c) 2013 Amlogic Inc. All Rights Reserved.
 *
 */
#ifndef __AMLIMAGE_IF_H__
#define __AMLIMAGE_IF_H__

typedef void*               __hdle;

#pragma pack(push,4)
typedef struct _AmlFirmwareItem_s
{
    __u32           itemId;
    __u32           fileType;           //image file type, sparse and normal
    __u64           curoffsetInItem;    //current offset in the item
    const __u64     offsetInImage;      //item offset in the image
    const __u64     itemSz;             //item size in the image
    char            itemMainType[32];   //item main type and sub type used to index the item
    char            itemSubType[32];    //item main type and sub type used to index the item
    char            reserve[32];
}ItemInfo;
#pragma pack(pop)


#pragma pack(push,4)
typedef struct _AmlFirmwareImg_s
{
	__u32      crc;             //check sum of the image
    __u32      version;         //firmware version
    __u32      magic;           //magic No. to say it is Amlogic firmware image
    __u64      imageSz;         //total size of this image file
    __u32      itemAlginSize;   //align size for each item
    __u32      itemNum;         //item number in the image, each item a file
    char       reserve[36];
}AmlFirmwareImg_t;
#pragma pack(pop)



typedef void* HIMAGE;
typedef void* HIMAGEITEM;

#define IMAGE_ITEM_TYPE_NORMAL  0
#define IMAGE_ITEM_TYPE_SPARSE  0XFE

//open a Amlogic firmware image
//return value is a handle
HIMAGE image_open(const char* imgPath);

//check the image's crc32
//return 0 when check ok,otherwise return -1
int image_check(HIMAGE hImg);

//close a Amlogic firmware image
int image_close(HIMAGE hImg);

//get item count of specify main type
int image_get_item_count(HIMAGE hImg, const char* mainType);

//open a item in the image
//@hImage: image handle;
//@mainType, @subType: main type and subtype to index the item, such as ["IMAGE", "SYSTEM"]
HIMAGEITEM image_item_open(HIMAGE hImg, const char* mainType, const char* subType);

//close a item
int image_item_close(HIMAGEITEM hItem);

__u64 image_item_get_size(HIMAGEITEM hItem);


//get image item type, current used type is normal or sparse
int image_item_get_type(HIMAGEITEM hItem);

//read item data, like standard fread
int image_item_read(HIMAGE hImg, HIMAGEITEM hItem, void* pBuf, const __u32 wantSz);

//relocate the read pointer to read the item data, like standard fseek
int image_item_seek(HIMAGE , HIMAGEITEM , __s64 , __u32 );

unsigned image_item_get_first_cluster_size(HIMAGEITEM hItem);

int get_item_name(HIMAGE hImg, int itemId, const char** main_type, const char** sub_type);

int get_total_itemnr(HIMAGE hImg);

#endif//ifndef __AMLIMAGE_IF_H__

