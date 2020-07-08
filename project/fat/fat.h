/************************************************************/
/*                   FAT操作函数库							*/
/*  环  境:WINCE											*/
/*  原作者:													*/
/*  存在的问题:长文件名目前还不支持，希望大家继续完善跟进	*/
/************************************************************/
#include "stdint.h"

#ifndef __FAT_H__
#define __FAT_H__
/*
#ifndef char
#define char	char
#endif

#ifndef uint8_t
#define uint8_t	unsigned char
#endif
 
#ifndef uint16_t
#define uint16_t	unsigned short
#endif

#ifndef uint32_t
#define uint32_t	unsigned int
#endif

//#define    FALSE	0
//#define    TRUE       	1
#define bool    BOOL;
#define false   FALSE
#define true    TRUE
 */
#define MAX_LONG_NAME_SIZE 80	/* 26*n+2   n=3 */
#define FAT_DEBUG 0		/* FAT debug flag */


#define FIX_DIRECTORY 0		/* 1 means use fix directory, 0 for any directory */


#include <stdlib.h>
#include <string.h>

//extern uint8_t (* FAT_ReadSector)(uint32_t,uint8_t *);
//extern uint8_t (* FAT_WriteSector)(uint32_t,uint8_t *);
//extern uint32_t (* FAT_ReadCapacity)();

//声明外部器件读写函数
//extern uint8_t CH375_ReadOneSector(uint32_t LBA,uint8_t *buffer);
//extern uint8_t CH375_WriteOneSector(uint32_t LBA,uint8_t *buffer);
//extern uint8_t MMC_SD_ReadSingleBlock(uint32_t sector, uint8_t* buffer);
//extern uint8_t MMC_SD_WriteSingleBlock(uint32_t sector, uint8_t* buffer);
//extern uint8_t IDE_ReadOneSector(uint32_t LBA,uint8_t *buffer);
//extern uint8_t IDE_WriteOneSector(uint32_t LBA,uint8_t *buffer);
//extern uint8_t Rd_Block(uint32_t addr,uint8_t* buffer);
//extern uint8_t Wt_Block(uint32_t addr,uint8_t* buffer);

//extern uint32_t MMC_SD_ReadCapacity();



#define MSDOSFSROOT     0               // cluster 0 means the root dir
#define CLUST_FREE      0               // cluster 0 also means a free cluster
#define MSDOSFSFREE     CLUST_FREE
#define CLUST_FIRST     2             	// first legal cluster number
#define CLUST_RSRVD     0xfff6      	// reserved cluster range
#define CLUST_BAD       0xfff7     		// a cluster with a defect
#define CLUST_EOFS      0xfff8     		// start of eof cluster range
#define CLUST_EOFE      0xffff      	// end of eof cluster range

#pragma pack(1)
struct partrecord // length 16 uint8_ts
{			
	uint8_t	prIsActive;					// 0x80 indicates active partition
	uint8_t	prStartHead;				// starting head for partition
	uint16_t	prStartCylSect;				// starting cylinder and sector
	uint8_t	prPartType;					// partition type (see above)
	uint8_t	prEndHead;					// ending head for this partition
	uint16_t	prEndCylSect;				// ending cylinder and sector
	uint32_t	prStartLBA;					// first LBA sector for this partition
	uint32_t	prSize;						// size of this partition (uint8_ts or sectors ?)
};
#pragma pack()

struct partsector
{
	char	psPartCode[446];		// pad so struct is 512b
	uint8_t	psPart[64];					// four partition records (64 uint8_ts)
	uint8_t	psBootSectSig0;				// two signature uint8_ts (2 uint8_ts)
	uint8_t	psBootSectSig1;
#define BOOTSIG0        0x55
#define BOOTSIG1        0xaa
};

struct extboot {
	char	exDriveNumber;				// drive number (0x80)//0x00 for floopy disk 0x80 for hard disk
	char	exReserved1;				// reserved should always set 0
	char	exBootSignature;			// ext. boot signature (0x29)
#define EXBOOTSIG       0x29
	char	exVolumeID[4];				// volume ID number
	char	exVolumeLabel[11];			// volume label "NO NAME"
	char	exFileSysType[8];			// fs type (FAT12 or FAT)
};

struct bootsector50 {
	uint8_t	bsJump[3];					// jump inst E9xxxx or EBxx90
	char	bsOemName[8];				// OEM name and version
	char	bsBPB[25];					// BIOS parameter block
	char	bsExt[26];					// Bootsector Extension
	char	bsBootCode[448];			// pad so structure is 512b
	uint8_t	bsBootSectSig0;				// boot sector signature uint8_t 0x55 
	uint8_t	bsBootSectSig1;				// boot sector signature uint8_t 0xAA
#define BOOTSIG0        0x55
#define BOOTSIG1        0xaa
};


struct bpb50 {
	uint16_t	bpbBytesPerSec; // uint8_ts per sector				//512 1024 2048 or 4096
	uint8_t	bpbSecPerClust; // sectors per cluster			// power of 2
	uint16_t	bpbResSectors;  // number of reserved sectors	//1 is recommend
	uint8_t	bpbFATs;        // number of FATs				// 2 is recommend
	uint16_t	bpbRootDirEnts; // number of root directory entries
	uint16_t	bpbSectors;     // total number of sectors
	uint8_t	bpbMedia;       // media descriptor				//0xf8 match the fat[0]
	uint16_t	bpbFATsecs;     // number of sectors per FAT
	uint16_t	bpbSecPerTrack; // sectors per track
	uint16_t	bpbHeads;       // number of heads
	uint32_t	bpbHiddenSecs;  // # of hidden sectors
	uint32_t	bpbHugeSectors; // # of sectors if bpbSectors == 0
};

struct bootsector710 {
	uint8_t	bsJump[3];					// jump inst E9xxxx or EBxx90
	char	bsOemName[8];				// OEM name and version
	char	bsBPB[53];					// BIOS parameter block
	char	bsExt[26];					// Bootsector Extension
	char	bsBootCode[418];			// pad so structure is 512b
	uint8_t	bsBootSectSig2;				// boot sector signature uint8_t 0x00 
	uint8_t	bsBootSectSig3;				// boot sector signature uint8_t 0x00
	uint8_t	bsBootSectSig0;				// boot sector signature uint8_t 0x55 
	uint8_t	bsBootSectSig1;				// boot sector signature uint8_t 0xAA
#define BOOTSIG0        0x55
#define BOOTSIG1        0xaa
#define BOOTSIG2        0x00
#define BOOTSIG3        0x00
};

#pragma pack(1)
struct bpb710 {
	uint16_t	bpbBytesPerSec;	// uint8_ts per sector
	uint8_t	bpbSecPerClust;	// sectors per cluster
	uint16_t	bpbResSectors;	// number of reserved sectors
	uint8_t	bpbFATs;		// number of FATs
	uint16_t	bpbRootDirEnts;	// number of root directory entries
	uint16_t	bpbSectors;		// total number of sectors
	uint8_t	bpbMedia;		// media descriptor
	uint16_t	bpbFATsecs;		// number of sectors per FAT
	uint16_t	bpbSecPerTrack;	// sectors per track
	uint16_t	bpbHeads;		// number of heads
	uint32_t	bpbHiddenSecs;	// # of hidden sectors
	// 3.3 compat ends here
	uint32_t	bpbHugeSectors;	// # of sectors if bpbSectors == 0
	// 5.0 compat ends here
	uint32_t     bpbBigFATsecs;// like bpbFATsecs for FAT32
	uint16_t      bpbExtFlags;	// extended flags:
#define FATNUM    0xf			// mask for numbering active FAT
#define FATMIRROR 0x80			// FAT is mirrored (like it always was)
	uint16_t      bpbFSVers;	// filesystem version
#define FSVERS    0				// currently only 0 is understood
	uint32_t     bpbRootClust;	// start cluster for root directory
	uint16_t      bpbFSInfo;	// filesystem info structure sector
	uint16_t      bpbBackup;	// backup boot sector
	// There is a 12 uint8_t filler here, but we ignore it
};
#pragma pack()


// Structure of a dos directory entry.
struct direntry {
	uint8_t		deName[8];      	// filename, blank filled
#define SLOT_EMPTY      0x00            // slot has never been used
#define SLOT_E5         0x05            // the real value is 0xE5
#define SLOT_DELETED    0xE5            // file in this slot deleted
#define SLOT_DIR		0x2E			// a directorymmm
	uint8_t		deExtension[3]; 	// extension, blank filled
	uint8_t		deAttributes;   	// file attributes
#define ATTR_NORMAL     0x00            // normal file
#define ATTR_READONLY   0x01            // file is readonly
#define ATTR_HIDDEN     0x02            // file is hidden
#define ATTR_SYSTEM     0x04            // file is a system file
#define ATTR_VOLUME     0x08            // entry is a volume label
#define ATTR_LONG_FILENAME	0x0F		// this is a long filename entry			    
#define ATTR_DIRECTORY  0x10            // entry is a directory name
#define ATTR_ARCHIVE    0x20            // file is new or modified
	uint8_t        deLowerCase;    	// NT VFAT lower case flags  (set to zero)
#define LCASE_BASE      0x08            // filename base in lower case
#define LCASE_EXT       0x10            // filename extension in lower case
	uint8_t        deCHundredth;   	// hundredth of seconds in CTime
	uint8_t        deCTime[2];     	// create time
	uint8_t        deCDate[2];     	// create date
	uint8_t        deADate[2];     	// access date
	uint16_t        deHighClust; 		// high uint8_ts of cluster number
	uint8_t        deMTime[2];     	// last update time
	uint8_t        deMDate[2];     	// last update date
	uint16_t        deStartCluster; 	// starting cluster of file
	uint32_t       deFileSize;  		// size of file in uint8_ts
};


// number of directory entries in one sector
#define DIRENTRIES_PER_SECTOR	0x10	//when the bpbuint8_tsPerSec=512 

// Structure of a Win95 long name directory entry
struct winentry {
	uint8_t			weCnt;			// 
#define WIN_LAST        0x40
#define WIN_CNT         0x3f
	uint8_t		wePart1[10];
	uint8_t		weAttributes;
#define ATTR_WIN95      0x0f
	uint8_t		weReserved1;
	uint8_t		weChksum;
	uint8_t		wePart2[12];
	uint16_t       	weReserved2;
	uint8_t		wePart3[4];
};

#define WIN_ENTRY_CHARS	13      // Number of chars per winentry

// Maximum filename length in Win95
// Note: Must be < sizeof(dirent.d_name)
#define WIN_MAXLEN      255

// This is the format of the contents of the deTime field in the direntry
// structure.
// We don't use bitfields because we don't know how compilers for
// arbitrary machines will lay them out.
#define DT_2SECONDS_MASK        0x1F    // seconds divided by 2
#define DT_2SECONDS_SHIFT       0
#define DT_MINUTES_MASK         0x7E0   // minutes
#define DT_MINUTES_SHIFT        5
#define DT_HOURS_MASK           0xF800  // hours
#define DT_HOURS_SHIFT          11

// This is the format of the contents of the deDate field in the direntry
// structure.
#define DD_DAY_MASK				0x1F	// day of month
#define DD_DAY_SHIFT			0
#define DD_MONTH_MASK			0x1E0	// month
#define DD_MONTH_SHIFT			5
#define DD_YEAR_MASK			0xFE00	// year - 1980
#define DD_YEAR_SHIFT			9



// Stuctures
struct FileInfoStruct
{
	uint32_t StartCluster;			//< file starting cluster for last file accessed
	uint32_t Size;					//< file size for last file accessed
	uint32_t Attr;					//< file attr for last file accessed
	//unsigned short CreateTime;			//< file creation time for last file accessed
	//unsigned short CreateDate;			//< file creation date for last file accessed
	uint32_t Sector;				//<file record place
	uint32_t Offset;				//<file record offset
};

//MP3后添加的函数
/*
#if FIX_DIRECTORY
extern uint8_t Search(uint8_t *dir,struct direntry *MusicInfo,uint16_t *Count,uint8_t *type);//查找音乐文件
extern uint8_t SearchLrc(uint8_t *dir,uint8_t * longnamebuffer,struct direntry *LrcInfo);//serch lrc file
#else
extern uint8_t SearchInit(void);
extern uint8_t Search(uint16_t *music_record_addr,struct direntry *MusicInfo,uint16_t *Count,uint8_t *type);//查找音乐文件
extern uint8_t SearchLrc(uint8_t *dir,uint8_t * longnamebuffer,struct direntry *LrcInfo,uint16_t music_record_addr);//serch lrc file
#endif
*/
extern uint8_t FAT_LoadPartCluster(uint32_t cluster,unsigned part,uint8_t * buffer);//加载文件
extern uint32_t FAT_NextCluster_NEW(uint32_t cluster);//fit system which has large ram

//FAT原有的函数
extern unsigned char FAT_Init(void);//初始化
extern uint32_t FAT_NextCluster(uint32_t cluster);//查找下一簇号
extern unsigned long FAT_FindFreeCluster(void);//查找空簇
extern unsigned char FAT_DisDir(uint8_t *dir);//显示目录内容
extern uint16_t FAT_FindItem(uint32_t cluster, uint8_t *name, struct FileInfoStruct *FileInfo);//查找文件
extern uint32_t FAT_Open(uint8_t * dir);//打开文件
extern uint32_t FAT_OpenDir(uint8_t * dir);//打开目录
extern unsigned char FAT_Read(uint32_t pointer, uint32_t size);//读文件，size=0代表整个文件
extern unsigned char FAT_Rename(uint8_t *dir,uint8_t *newname);//重命名
extern unsigned char FAT_ModifyFAT(uint32_t cluster,uint32_t val);//修改FAT项
extern unsigned char FAT_Delete(uint8_t *dir);//删除文件
extern unsigned char FAT_DelItem(struct FileInfoStruct *FileInfo);//删除记录项
extern uint16_t FAT_FindFreeItem(uint32_t cluster, struct FileInfoStruct *FileInfo);//查找空余项
extern unsigned char FAT_MkDir(uint8_t * dir);//建目录
extern unsigned char FAT_Write(uint32_t cluster,unsigned char *data,uint32_t size);//写文件
extern uint32_t FAT_Create(uint8_t * dir,uint32_t size);//建文件，必须指定文件大小
extern unsigned char FAT_RmDir(uint8_t * dir);//删除目录
extern uint16_t FAT_Close(uint32_t * p);//关闭文件
extern unsigned char FAT_GetFile(uint8_t *dir,struct FileInfoStruct *FileInfo);//获取指定目录下的文件信息
extern uint32_t FAT_OpenFile(char *dir,struct FileInfoStruct *File_Info);//1=失败.//打开指定路径的文件,输出文件信息并返回文件的首簇.
extern uint8_t FAT_DirLoadFile(char *dir,uint8_t *Buf); //0=失败;1=成功.//通过目录加载文件到缓冲
extern uint8_t FAT_ClusterLoadFile(uint32_t cluster,uint8_t *Buf);//0=失败;1=成功.//通过簇加载整个文件到Buf.
extern uint32_t GetFileSize(void);
#endif
