/************************************************************/
/*                   FAT操作函数库							*/
/*  环  境:WINCE											*/
/*  原作者:													*/
/*  存在的问题:长文件名目前还不支持，希望大家继续完善跟进	*/
/************************************************************/

//#include <windows.h>
#include "FAT.h"
//#include "stdint.h"
//#include "..//SDMMC_LIB//HSMMCDRV.h"
//#include "debug_frmwrk.h"

uint32_t FirstDirClust;    //first directory cluster
uint32_t FirstDataSector;	// The first sector number of data
uint16_t BytesPerSector;	// uint8_ts per sector
uint32_t FATsectors;		// The amount sector a FAT occupied
uint16_t SectorsPerClust;	// Sector per cluster
uint32_t FirstFATSector;	// The first FAT sector
uint32_t FirstDirSector;	// The first Dir sector
uint32_t RootDirSectors;	// The sector number a Root dir occupied 
uint32_t RootDirCount;		// The count of directory in root dir
uint8_t FAT32_Enable;
uint8_t bpbFATs;

uint8_t TABLE_READ = 0;
uint32_t START_CLUSTER = 0x0ffffff8;	//when the mcu has large ram
//uint8_t FAT_TABLE[512];				//when the mcu has large ram

static uint32_t g_FileSize = 0;//--czx
extern uint8_t sdmmc_write_blocks(uint32_t start_block,uint32_t end_block,uint8_t * buffer);
extern uint8_t sdmmc_read_blocks(uint32_t start_block,uint32_t end_block,uint8_t * buffer);
extern 	uint32_t GetSDCapacity(void);
uint8_t LongNameBuffer[MAX_LONG_NAME_SIZE];
uint8_t LongNameFlag = 0;

//函数指针指向sd卡的读写函数
uint8_t (* FAT_ReadSector)(uint32_t sector, uint32_t dwSector, uint8_t * buffer)=sdmmc_read_blocks;
uint8_t (* FAT_WriteSector)(uint32_t sector, uint32_t dwSector, uint8_t * buffer)=sdmmc_write_blocks;
uint32_t (* FAT_ReadCapacity)()=GetSDCapacity;

struct FileInfoStruct FileInfo;//temporarily buffer for file information

//FAT初始化，不含SD的初始化，用之前应先调用sd的初始化
unsigned char FAT_Init(void)//Initialize of FAT  need initialize SD first
{
	struct bootsector710 *bs  = 0;
	struct bpb710        *bpb = 0;
	//struct partsector    *ps  = 0;
	struct partrecord    *pr  = 0;

	uint8_t buffer[512];
	uint32_t hidsec=0;
	uint32_t Capacity=0;
	int i;

	Capacity = FAT_ReadCapacity();

/*	if(Capacity<0xff)
	{
	_DBG("ERROR -- Capacity<0xff!\n");	
		return 1;
	}
*/
	if(!FAT_ReadSector(0,1,buffer))
	{
		#ifdef DBG
	_DBG("ERROR -- FAT_ReadSector\n");
		#endif
		return 1;
	}
#if FAT_DEBUG
	_DBG("Read Sector succeed!\n");
	for(i=0;i<512;i++)
	{
		if(!(i%16) && i) _DBG("\n");
	_DBH(buffer[i]); _DBG(" ");
	}
	_DBG("\n");
#endif
	bs = (struct bootsector710 *)buffer;

	pr = (struct partrecord *)((struct partsector *)buffer)->psPart;//first partition
	/*(struct partsector *)BUFFER  //将BUFFER转换成结构体指针 

	((struct partsector *)BUFFER)->psPart //结构体指针BUFFER指向的结构体的成员psPart 

	(struct partrecord *)(（struct partsector *)BUFFER)->psPart  //将psPart转换成结构体指针 

	PartInfo = *((struct partrecord *) ((struct partsector *)BUFFER)->psPart);  */
	//读取结构体指针psPart指向的结构体整体，赋值给结构体PartInfo 

	hidsec = pr->prStartLBA;//the hidden sectors

	if((hidsec >= Capacity/512))
	{
		hidsec = 0;
	}
	else 
	{
		if(!FAT_ReadSector(pr->prStartLBA,1,buffer))
		{
			#ifdef DBG
		_DBG("ERROR -- FAT_ReadSector\n");
			#endif
			return 1;//read the bpb sector
		}
		bs = (struct bootsector710 *)buffer;
		if(bs->bsJump[0]!=0xE9 && bs->bsJump[0]!=0xEB)
		{
			hidsec = 0;
			if(!FAT_ReadSector(0,1,buffer))
			{
				#ifdef DBG
			_DBG("ERROR -- FAT_ReadSector\n");
				#endif
				return 1;//read the bpb sector
			}
			bs = (struct bootsector710 *)buffer;	
		}
	}

	if(bs->bsJump[0]!=0xE9 && bs->bsJump[0]!=0xEB)//对付没有bootsect的sd卡	//dead with the card which has no bootsect
	{
		#ifdef DBG
	_DBG("ERROR -- SD card no bootsect!\n");
		#endif
		return 1;
	}
	bpb = (struct bpb710 *)bs->bsBPB;


	if(bpb->bpbFATsecs)//detemine thd FAT type  //do not support FAT12
	{
		FAT32_Enable=0;	//FAT16
		FATsectors		= bpb->bpbFATsecs;//FAT占用的扇区数	//the sectors number occupied by one fat talbe
		FirstDirClust = 2;
		#ifdef DBG
	_DBG("SD card is FAT16\n");
		#endif
	}
	else
	{
		FAT32_Enable=1;	//FAT32
		FATsectors		= bpb->bpbBigFATsecs;//FAT占用的扇区数	//the sectors number occupied by one fat talbe
		FirstDirClust = bpb->bpbRootClust;
		#ifdef DBG
	_DBG("SD card is FAT32\n");
		#endif
	}

	BytesPerSector	= bpb->bpbBytesPerSec;//每扇区字节数
	SectorsPerClust	= (uint8_t)bpb->bpbSecPerClust;//每簇扇区数
	FirstFATSector	= bpb->bpbResSectors+hidsec;//第一个FAT表扇区
	RootDirCount	= bpb->bpbRootDirEnts;//根目录项数
	RootDirSectors	= (RootDirCount*32)>>9;//根目录占用的扇区数
	FirstDirSector	= FirstFATSector+bpb->bpbFATs*FATsectors;//第一个目录扇区
	FirstDataSector	= FirstDirSector+RootDirSectors;//第一个数据扇
	bpbFATs = bpb->bpbFATs;

#if FAT_DEBUG
	_DBG("FirstDirSector:");_DBH16(FirstDirSector);	  _DBG("\n");
	_DBG("RootDirSectors:");_DBH16(RootDirSectors);	  _DBG("\n");
	_DBG("RootDirCount:");_DBH16(RootDirCount);		  _DBG("\n");
	_DBG("FirstFATSector:");_DBH16(FirstFATSector);	  _DBG("\n");
	_DBG("SectorsPerClust:");_DBH16(SectorsPerClust); _DBG("\n");
	_DBG("BytesPerSector:");_DBH16(BytesPerSector);	  _DBG("\n");
	_DBG("FirstDataSector:");_DBH16(FirstDataSector); _DBG("\n");

	_DBG("bpbSectors");_DBH16(bpb->bpbSectors); _DBG("\n");
	_DBG("filesystem version");_DBH16(bpb->bpbFSVers); _DBG("\n");
#endif
#ifdef DBG
	_DBG("FAT Init O.K\n");
	#endif
	return 0;
}

//读一个簇中的一个扇区
unsigned char FAT_LoadPartCluster(uint32_t cluster,unsigned part,uint8_t * buffer)
{
	uint32_t sector;
	sector=(uint32_t)FirstDataSector+(uint32_t)(cluster-2)*(uint32_t)SectorsPerClust;//calculate the actual sector number
	if(!FAT_ReadSector(sector+part,1,buffer))
		return 1;
	else
		return 0;
}



//读下一簇簇号
//Return the cluster number of next cluster of file
//Suitable for system which has limited RAM
uint32_t FAT_NextCluster(uint32_t cluster)
{
	uint8_t buffer[512];
	uint32_t sector;
	uint32_t offset;
	if(FAT32_Enable)offset = cluster/128;
	else offset = cluster/256;
	if(cluster<2)return 0x0ffffff8;
	sector=FirstFATSector+offset;//calculate the actual sector
	if(!FAT_ReadSector(sector,1,buffer))return 0x0ffffff8;//read fat table / return 0xfff8 when error occured

	if(FAT32_Enable)
	{
		offset=cluster%128;//find the position
		sector=((uint32_t *)buffer)[offset];	
	}
	else
	{
		offset=cluster%256;//find the position
		sector=((uint16_t *)buffer)[offset];
	}
	return (uint32_t)sector;//return the cluste number
}

//在FAT表内找空簇
//Find a free cluster return the cluster number
unsigned long FAT_FindFreeCluster(void)
{
	uint8_t buffer[512];
	uint16_t i;
	uint32_t cnt;

	if(FAT32_Enable)
	{
		for(cnt=0;cnt<FATsectors;cnt++)//find in the FAT table
		{
			if(!FAT_ReadSector(FirstFATSector+cnt,1,buffer))return 1;//error
			for(i=0;i<128;i++)
			{
				if(((uint32_t *)buffer)[i]==0x00000000)break;//an unused cluster
			}
			if(i!=128)
			{
				cnt=cnt*128+i;
				return cnt;//return the free cluster number
			}
		}
	}
	else
	{
		for(cnt=0;cnt<FATsectors;cnt++)//find in the FAT table
		{
			if(!FAT_ReadSector(FirstFATSector+cnt,1,buffer))return 1;//error
			for(i=0;i<256;i++)
			{
				if(((uint16_t *)buffer)[i]==0x0000)break;//an unused cluster
			}
			if(i!=256)
			{
				cnt=cnt*256+i;
				return cnt;//return the free cluster number
			}
		}
	}
	
	return 1;//error
}

//在cluster指向的目录下找一个空位置记录文件
//find a position to place a item withe the given directory, the parameter is FileInfo who brought the message
uint16_t FAT_FindFreeItem(uint32_t cluster, struct FileInfoStruct *FileInfo)
{
	//uint8_t *buffer;
	uint8_t buffer[512];
	uint32_t tempclust;
	uint32_t sector;
	uint16_t cnt;
	uint16_t offset;
	//	unsigned char i;
	struct direntry *item = 0;
	if(cluster==0 && FAT32_Enable==0)// root directory//当这个目录是根目录
	{
		//buffer=malloc(512);//apply memory
		if(buffer==0)return 1;//if failed
		for(cnt=0;cnt<RootDirSectors;cnt++)
		{
			if(!FAT_ReadSector(FirstDirSector+cnt,1,buffer))
			{
				//free(buffer);
				return 1;
			}//read sector
			for(offset=0;offset<512;offset+=32)
			{
				item=(struct direntry *)(&buffer[offset]);
				//used item
				if(item->deName[0] == 0x00 || item->deName[0] == 0xe5)
					//unused item
				{

					FileInfo->StartCluster = item->deStartCluster + (((uint32_t)item->deHighClust)<<16);//don't care
					FileInfo->Size         = item->deFileSize;//don't care
					FileInfo->Attr         = item->deAttributes;//don't care
					FileInfo->Sector       = FirstDirSector+cnt;//The key parameter record the secoter nuber which the item stored
					FileInfo->Offset       = offset;			//The key parameter record the offset in the sector
					//free(buffer);//realease
					return 0;//done
				}
			}
		}
		//free(buffer);//release
	}
	else//other folders//当这是一个其它目录时，程序暂且没考虑到目录内没有空余项是需要另找一个簇来记录
	{
		tempclust=cluster;
		while(1)
		{
			sector=(uint32_t)FirstDataSector+(tempclust-2)*(uint32_t)SectorsPerClust;//calculate the actual sector number
			//buffer=malloc(512);//apply memory
			if(buffer==0)return 1;//if failed
			for(cnt=0;cnt<SectorsPerClust;cnt++)
			{
				if(!FAT_ReadSector(sector+cnt,1,buffer))
				{
					//free(buffer);
					return 1;
				}
				for(offset=0;offset<512;offset+=32)
				{
					item=(struct direntry *)(&buffer[offset]);
					if(item->deName[0] == 0x00 || item->deName[0] == 0xe5)
					{
						FileInfo->StartCluster = item->deStartCluster + (((uint32_t)item->deHighClust)<<16);						
						FileInfo->Size         = item->deFileSize;
						FileInfo->Attr         = item->deAttributes;
						FileInfo->Sector       = sector+cnt;
						FileInfo->Offset       = offset;
						//free(buffer);
						return 0;
					}
				}
			}
			//free(buffer);//release
			tempclust=FAT_NextCluster(tempclust);//next cluster
			if( (FAT32_Enable == 0 && tempclust == 0xffff) || tempclust == 0x0ffffff8 || tempclust == 0x0fffffff)return 1;
		}
	}
	return 1;
}

//显示给定路径下的文件
//display the content of a foler , 0 as root directory
uint8_t FAT_DisDir(uint8_t *dir)
{
	//uint8_t *buffer;
	uint8_t buffer[512];
	uint32_t sector;
	uint32_t cluster;
	uint32_t tempclust;
	uint16_t cnt;
	uint16_t offset;
	unsigned char i;
	struct direntry *item = 0;
	cluster = FAT_OpenDir(dir);

	if(cluster == 1)
	{
		#ifdef DBG
		_DBG("ERROR -- FAT_OpenDir");
		#endif
		return 1;
	}
	#ifdef DBG
	_DBG("\r\n==================SD Card File Info=====================");
	#endif
	if(cluster==0 && FAT32_Enable==0)// root directory
	{
		//buffer=malloc(512);//apply memory
		if(buffer==0)return 1;//if failed
		for(cnt=0;cnt<RootDirSectors;cnt++)
		{
			if(!FAT_ReadSector(FirstDirSector+cnt,1,buffer))
			{
				//free(buffer);
				return 1;
			}
			for(offset=0;offset<512;offset+=32)
			{
				item=(struct direntry *)(&buffer[offset]);//pointer convert
				//find a valid item and display it
				if((item->deName[0] != '.') && (item->deName[0] != 0x00) && (item->deName[0] != 0xe5) && (item->deAttributes != 0x0f))
				{
					#ifdef DBG
					_DBG("\r\n");
					#endif
					for(i=0;i<8;i++)//name
					{
						if(item->deName[i] != ' ')
						{
						#ifdef DBG
						_DBC(item->deName[i]);
						#endif
							}
					}
					if((item->deAttributes & 0x10)==0) 
					{
						#ifdef DBG
						_DBG(".");
					#endif
					}
					for(i=0;i<3;i++)//extention
					{
							#ifdef DBG
					_DBC(item->deExtension[i]);
						#endif
					}
				}
			}
		}
		//free(buffer);//release
	}
	else//other folders
	{
		tempclust=cluster;
		while(1)
		{
			sector=(uint32_t)FirstDataSector+(uint32_t)(tempclust-2)*(uint32_t)SectorsPerClust;//calculate the actual sector number
			//buffer=malloc(512);//apply memory
			if(buffer==0)return 1;//if failed
			for(cnt=0;cnt<SectorsPerClust;cnt++)
			{
				if(!FAT_ReadSector(sector+cnt,1,buffer))
				{
					//free(buffer);
					return 1;
				}
				for(offset=0;offset<512;offset+=32)
				{
					item=(struct direntry *)(&buffer[offset]);
					if((item->deName[0] != '.') && (item->deName[0] != 0x00) && (item->deName[0] != 0xe5) && (item->deAttributes != 0x0f))
					{
						#ifdef DBG
						_DBG("\r\n");
						#endif
						for(i=0;i<8;i++)
						{
							if(item->deName[i] != ' ')
							{
								#ifdef DBG
								_DBC(item->deName[i]);
								#endif
							}
						}
						if((item->deAttributes & 0x10)==0)
						{
							#ifdef DBG
							_DBG(".");
							#endif
						}
						for(i=0;i<3;i++)
						{
							#ifdef DBG
							_DBC(item->deExtension[i]);
							#endif
						}
					}
				}
			}
			//free(buffer);//release
			tempclust=FAT_NextCluster(tempclust);//next cluster
			if( tempclust == 0x0ffffff8 )return 1;
			if((FAT32_Enable == 0 && tempclust == 0xffff) || tempclust == 0x0fffffff)break;
		}
	}
	#ifdef DBG
	_DBG("\r\n========================================================\n");
	#endif
	return 0;
}

//在给定目录下查找文件
//Find a item in the directory which specify by the parameter "cluster"
//Return the start cluster number
uint16_t FAT_FindItem(uint32_t cluster, uint8_t *name, struct FileInfoStruct *FileInfo)
{
	//uint8_t *buffer;
	uint8_t buffer[512];
	uint32_t tempclust;
	uint32_t sector;
	uint16_t cnt;
	uint16_t offset;
	unsigned char i;
	struct direntry *item = 0;
	if((cluster==0) && (FAT32_Enable == 0))// root directory
	{
		//buffer=malloc(512);//apply memory
		if(buffer==0) return 1;//if failed
		for(cnt=0;cnt<RootDirSectors;cnt++)
		{
			if(!FAT_ReadSector(FirstDirSector+cnt,1,buffer))
			{
				//free(buffer);
				return 1;
			}
			for(offset=0;offset<512;offset+=32)
			{
				item=(struct direntry *)(&buffer[offset]);
				if((item->deName[0] != 0x00) && (item->deName[0] != 0xe5) && (item->deAttributes != 0x0f))
				{
					for(i=0;i<11;i++)
					{
						if(buffer[offset+i]!=name[i])
							break;
					}
					if(i==11)
					{
						//return the parameter of the item
						FileInfo->StartCluster = item->deStartCluster + (((uint32_t)item->deHighClust)<<16);//don't care
						FileInfo->Size         = item->deFileSize;
						FileInfo->Attr         = item->deAttributes;
						FileInfo->Sector       = FirstDirSector+cnt;
						FileInfo->Offset       = offset;
						//free(buffer);
						return 0;
					}
				}
			}
		}
		//free(buffer);//release
	}
	else//other folders
	{
		tempclust=cluster;
		while(1)
		{
			sector=(uint32_t)FirstDataSector+(uint32_t)(tempclust-2)*(uint32_t)SectorsPerClust;//calculate the actual sector number
			//buffer=malloc(512);//apply memory
			if(buffer==0)return 1;//if failed
			for(cnt=0;cnt<SectorsPerClust;cnt++)
			{
				if(!FAT_ReadSector(sector+cnt,1,buffer))
				{
					//free(buffer);
					return 1;
				}
				for(offset=0;offset<512;offset+=32)
				{
					item=(struct direntry *)(&buffer[offset]);
					if((item->deName[0] != 0x00) && (item->deName[0] != 0xe5) && (item->deAttributes != 0x0f))
					{
						for(i=0;i<11;i++)
						{
							if(buffer[offset+i]!=name[i])break;
						}
						if(i==11)
						{
							FileInfo->StartCluster = item->deStartCluster + (((uint32_t)item->deHighClust)<<16);//don't care
							FileInfo->Size         = item->deFileSize;
							FileInfo->Attr         = item->deAttributes;
							FileInfo->Sector       = sector+cnt;
							FileInfo->Offset       = offset;
							//free(buffer);
							return 0;
						}
					}
				}
			}
			//free(buffer);//release
			tempclust=FAT_NextCluster(tempclust);//next cluster
			if((FAT32_Enable == 0 && tempclust == 0xffff) || tempclust == 0x0ffffff8 || tempclust == 0x0fffffff)break;
		}
	}
	return 1;
}


//挑选一个未使用的记录项
//select the first unsed item in the given cluster
//for delete a foler or a file
unsigned char FAT_SelectOneItem(uint32_t cluster,struct FileInfoStruct *FileInfo)
{
	//uint8_t *buffer;
	uint8_t buffer[512];
	uint32_t tempclust;
	uint32_t sector;
	unsigned int cnt;
	unsigned int offset;
	//	unsigned char i;
	struct direntry *item = 0;
	if(cluster==0 && FAT32_Enable==0)// root directory
	{
		//buffer=malloc(512);//apply memory
		if(buffer==0)return 1;//if failed
		for(cnt=0;cnt<RootDirSectors;cnt++)
		{
			if(!FAT_ReadSector(FirstDirSector+cnt,1,buffer))
			{
				//free(buffer);
				return 1;
			}
			for(offset=0;offset<512;offset+=32)
			{
				item=(struct direntry *)(&buffer[offset]);
				if((item->deName[0] != 0x00) && (item->deName[0] != 0xe5) && (item->deAttributes != 0x0f))
				{
					//return the parameter of the item
					FileInfo->StartCluster = item->deStartCluster + (((uint32_t)item->deHighClust)<<16);//don't care
					FileInfo->Size         = item->deFileSize;
					FileInfo->Attr         = item->deAttributes;
					FileInfo->Sector       = FirstDirSector+cnt;
					FileInfo->Offset       = offset;
					//free(buffer);
					return 0;
				}
			}
		}
		//free(buffer);//release
	}
	else//other folders
	{
		tempclust=cluster;
		while(1)
		{
			sector=(uint32_t)FirstDataSector+(uint32_t)(tempclust-2)*(uint32_t)SectorsPerClust;//calculate the actual sector number
			//buffer=malloc(512);//apply memory
			if(buffer==0)return 1;//if failed
			for(cnt=0;cnt<SectorsPerClust;cnt++)
			{
				if(!FAT_ReadSector(sector+cnt,1,buffer))
				{
					//free(buffer);
					return 1;
				}
				for(offset=0;offset<512;offset+=32)
				{
					item=(struct direntry *)(&buffer[offset]);
					if((item->deName[0] != 0x2e) && (item->deName[0] != 0x00) && (item->deName[0] != 0xe5) & (item->deAttributes != 0x0f))
					{
						FileInfo->StartCluster = item->deStartCluster + (((uint32_t)item->deHighClust)<<16);//don't care
						FileInfo->Size         = item->deFileSize;
						FileInfo->Attr         = item->deAttributes;
						FileInfo->Sector       = sector+cnt;
						FileInfo->Offset       = offset;
						//free(buffer);
						return 0;
					}
				}
			}
			//free(buffer);//release
			tempclust=FAT_NextCluster(tempclust);//next cluster
			if((FAT32_Enable == 0 && tempclust == 0xffff) || tempclust == 0x0ffffff8 || tempclust == 0x0fffffff)break;
		}
	}
	return 1;
}

//修改FAT表中响应的项
//modify the fat table item with "val","cluster" specify the location
unsigned char FAT_ModifyFAT(uint32_t cluster,uint32_t val)
{
	uint8_t buffer[512];
	uint32_t sector;
	uint32_t offset;
	if(FAT32_Enable)offset = cluster/128;
	else            offset = cluster/256;

	sector=FirstFATSector+offset;//calculate the actual sector
	if(!FAT_ReadSector(sector,1,buffer))return 1;//read fat table

	if(FAT32_Enable)
	{
		offset=cluster%128;
		offset<<=2;
		buffer[offset+3]=val>>24;
		buffer[offset+2]=val>>16;
		buffer[offset+1]=val>>8;
		buffer[offset]=val;
	}
	else
	{
		offset=cluster%256;//find the position
		offset<<=1;
		buffer[offset+1] = val>>8;
		buffer[offset]   = val;
	}
	if(!FAT_WriteSector(sector,1,buffer))return 1;//write the first fat table
	if(bpbFATs>1) if(!FAT_WriteSector(sector+FATsectors,1,buffer))return 1;//write the second fat table
	return 0;//return the value
}

// make a dir
uint8_t FAT_MkDir(uint8_t * dir)
{
	uint8_t name[11];
	uint8_t *p=dir;
	uint8_t deep=0;
	uint16_t i,j;
	uint32_t cluster=0;
	uint32_t lastcluster;//cluster number of last directory
	//uint8_t *buffer;
	uint8_t buffer[512];
	uint32_t sector;
	struct direntry *item;
	if(FAT32_Enable)cluster=FirstDirClust;
	if(*p != '\\')return 1;//invalid path

	//Find the same Name file
	if(FAT_OpenDir(p)!=1) //文件存在
	{
	//	RETAILMSG(TRUE, (TEXT("\r\nDir Exist!")));
		return 1;
	}

	while(*p)
	{
		if(*p == '\\')
		{
			deep++;//the deepth of the path
		}
		p++;
	}
	p=dir;
	for(i=0;i<deep-1;i++)
	{
		p++;
		for(j=0;j<11;j++)name[j]=0x20;
		j=0;
		while(*p != '\\')
		{
			if((*p) >= 'a' && (*p) <= 'z')name[j] = (*p++)-0x20;
			else name[j] = *p++;
			j++;
		}
		if(FAT_FindItem(cluster,name, &FileInfo))return 1;//find the location of each directory
		cluster = FileInfo.StartCluster;//point to next directory
	}
	p++;
	for(j=0;j<11;j++)name[j]=0x20;
	j=0;
	while(*p)
	{
		if(*p>='a' && *p<='z')name[j]=(*p++)-0x20;
		else name[j]=*p++;
		j++;
	}
	lastcluster=cluster;//save as last directory
	cluster=FAT_FindFreeCluster();//find a unused cluster
	if(cluster==1) return 1;//error
	if(FAT_FindFreeItem(lastcluster,&FileInfo)) return 1;//find a unused item
	//buffer=malloc(512);
	if(buffer==0)return 1;

	if(!FAT_ReadSector(FileInfo.Sector,1,buffer))
	{
		//free(buffer);
		return 1;
	}//read the sector which the item is in

	item=(struct direntry *)(&buffer[FileInfo.Offset]);//pointer convert

	for(j=0;j<8;j++)item->deName[j] = name[j];
	for(j=0;j<3;j++)item->deExtension[j] = 0x20;

	item->deAttributes = ATTR_DIRECTORY;
	item->deLowerCase = LCASE_BASE | LCASE_EXT;
	item->deCHundredth = 0x00;
	item->deCTime[0] = 0x00;
	item->deCTime[1] = 0x60;
	item->deCDate[0] = 0x5c;
	item->deCDate[1] = 0x09;
	item->deADate[0] = 0x8e;
	item->deADate[1] = 0x35;
	item->deHighClust = cluster>>16;
	item->deMTime[0] = 0x00;
	item->deMTime[1] = 0x60;
	item->deMDate[0] = 0x50;
	item->deMDate[1] = 0x0a;
	item->deStartCluster = cluster;
	item->deFileSize = 0;
	if(!FAT_WriteSector(FileInfo.Sector,1,buffer))
	{
		//free(buffer);
		return 1;
	}//write the item

	for(j=0;j<512;j++)buffer[j]=0x00;
	sector=(uint32_t)FirstDataSector+(uint32_t)(cluster-2)*(uint32_t)SectorsPerClust;

	for(i=0;i<SectorsPerClust;i++)
	{
		if(!FAT_WriteSector(sector+i,1,buffer))
		{
			//free(buffer);
			return 1;
		}//clear the data in the directory
	}

	//create "." directory
	item=(struct direntry *)(&buffer[0]);
	item->deName[0] = '.';
	for(j=1;j<8;j++)item->deName[j] = 0x20;
	for(j=0;j<3;j++)item->deExtension[j] = 0x20;
	item->deAttributes = ATTR_DIRECTORY;
	item->deLowerCase = LCASE_BASE | LCASE_EXT;
	item->deCHundredth = 0x00;
	item->deCTime[0] = 0x00;
	item->deCTime[1] = 0x60;
	item->deCDate[0] = 0x5c;
	item->deCDate[1] = 0x09;
	item->deADate[0] = 0x8e;
	item->deADate[1] = 0x35;
	item->deHighClust = cluster>>16;
	item->deMTime[0] = 0x00;
	item->deMTime[1] = 0x60;
	item->deMDate[0] = 0x50;
	item->deMDate[1] = 0x0a;
	item->deStartCluster = cluster;//the directory itself
	item->deFileSize = 0;

	//creat ".." directory
	item=(struct direntry *)(&buffer[32]);
	item->deName[0] = '.';
	item->deName[1] = '.';
	for(j=2;j<8;j++)item->deName[j] = 0x20;
	for(j=0;j<3;j++)item->deExtension[j] = 0x20;//no extention
	item->deAttributes = ATTR_DIRECTORY;//directory
	item->deLowerCase = LCASE_BASE | LCASE_EXT;
	item->deCHundredth = 0x00;
	item->deCTime[0] = 0x00;
	item->deCTime[1] = 0x60;
	item->deCDate[0] = 0x5c;
	item->deCDate[1] = 0x09;
	item->deADate[0] = 0x8e;
	item->deADate[1] = 0x35;
	item->deHighClust = lastcluster>>16;
	item->deMTime[0] = 0x00;
	item->deMTime[1] = 0x60;
	item->deMDate[0] = 0x50;
	item->deMDate[1] = 0x0a;
	item->deStartCluster = lastcluster;//last directory
	item->deFileSize = 0;

	if(!FAT_WriteSector(sector,1,buffer))
	{
		//free(buffer);
		return 1;
	}//write the data

	//free(buffer);

	if(FAT32_Enable)
	{
		if(FAT_ModifyFAT(cluster,0x0fffffff))return 1;//modify the fat table to sign that the cluster was used 
	}
	else
	{
		if(FAT_ModifyFAT(cluster,0xffff))return 1;//modify the fat table to sign that the cluster was used 
	}
	return 0;//done
}

// remove a directory
uint8_t FAT_RmDir(uint8_t * dir)
{
	if(FAT_OpenDir(dir)==0) return 1;//find the directory
	if(FAT_DelItem(&FileInfo)) return 1;//delete it
	return 0;
}

// creat a file, for convenience we designate the size
// return the start sector of the new file
uint32_t FAT_Create(uint8_t * dir,uint32_t size)
{
	uint8_t name[11];
	uint8_t *p=dir;
	uint8_t deep=0;
	uint8_t i,j;
	uint32_t cluster=0;
	//uint8_t *buffer;
	uint8_t buffer[512];
	struct direntry *item;

	//Find the same Name file
	if(FAT_Open(p)!=1) //文件存在
	{
	//	RETAILMSG(TRUE, (TEXT("\r\nFile Exist!")));
		return 1;
	}

	if(FAT32_Enable) cluster=FirstDirClust;
	if(*p != '\\') return 1;//invalid path
	//Get Dir Deep
	while(*p)
	{
		if(*p == '\\')
		{
			deep++;
		}
		p++;
	}
	//Get LastPath
	p=dir;
	for(i=0;i<deep-1;i++)
	{
		p++;
		for(j=0;j<11;j++) name[j]=0x20;
		j=0;
		while(*p != '\\')
		{
			if((*p) >= 'a' && (*p) <= 'z') name[j] = (*p++)-0x20;
			else name[j] = *p++;
			j++;
		}

		if(FAT_FindItem(cluster,name, &FileInfo)) return 1;
		cluster = FileInfo.StartCluster;
	}
	//Get Current Name
	p++;
	for(j=0;j<11;j++) name[j]=0x20;
	j=0;
	while(*p != '.')
	{
		if(*p>='a' && *p<='z')name[j]=(*p++)-0x20;
		else name[j]=*p++;
		j++;
	}
	j=8;
	p++;
	while(*p)
	{
		if(*p>='a' && *p<='z')name[j]=(*p++)-0x20;
		else name[j]=*p++;
		j++;
	}


	if(FAT_FindFreeItem(cluster,&FileInfo))return 1;
	cluster = FAT_FindFreeCluster();
	if(cluster==1)return 1;
	//buffer=malloc(512);
	if(buffer==0)return 1;
	if(!FAT_ReadSector(FileInfo.Sector,1,buffer))
	{
		//free(buffer);
		return 1;
	}
	item=(struct direntry *)(&buffer[FileInfo.Offset]);

	memcpy(item->deName,name,8);
	memcpy(item->deExtension,&name[8],3);

	item->deAttributes = ATTR_ARCHIVE;//file
	item->deLowerCase = LCASE_BASE | LCASE_EXT;
	item->deCHundredth = 0x00;
	item->deCTime[0] = 0x00;
	item->deCTime[1] = 0x60;
	item->deCDate[0] = 0x5c;
	item->deCDate[1] = 0x09;
	item->deADate[0] = 0x8e;
	item->deADate[1] = 0x35;
	item->deHighClust = cluster>>16;
	item->deMTime[0] = 0x00;
	item->deMTime[1] = 0x60;
	item->deMDate[0] = 0x50;
	item->deMDate[1] = 0x0a;
	item->deStartCluster = cluster;//the cluster number the file was stored
	item->deFileSize = size;//the file size
	if(!FAT_WriteSector(FileInfo.Sector,1,buffer))
	{
		//free(buffer);
		return 1;
	}//write the item
	//free(buffer);
	if(FAT32_Enable)
	{
		if(FAT_ModifyFAT(cluster,0x0fffffff))return 1;//modify the fat table to sign that the cluster was used 
	}
	else
	{
		if(FAT_ModifyFAT(cluster,0xffff))return 1;//modify the fat table
	}
	return cluster;//reutn the first cluster number
}

// find the location with the given path
uint32_t FAT_Open(uint8_t * dir)
{
	uint8_t name[11];
	uint8_t *p=dir;
	uint8_t deep=0;
	uint8_t i,j;
	uint32_t cluster=0;
	if(FAT32_Enable) cluster=FirstDirClust;
	if(*p != '\\') return 1;//invalid path
	while(*p)
	{
		if(*p == '\\')
		{
			deep++;
		}
		p++;
	}
	p=dir;
	for(i=0;i<deep-1;i++)
	{
		p++;
		memset(name,0x20,11);
		j=0;
		while(*p != '\\')
		{
			if((*p) >= 'a' && (*p) <= 'z')name[j] = (*p++)-0x20;
			else name[j] = *p++;
			j++;
		}
		if(FAT_FindItem(cluster,name, &FileInfo)) return 1;//find the directory
		cluster = FileInfo.StartCluster;
	}
	p++;
	memset(name,0x20,11);
	j=0;
	while(*p != '.')//file must have a extention
	{
		if(*p>='a' && *p<='z')name[j]=(*p++)-0x20;
		else name[j]=*p++;
		j++;
	}
	j=8;
	p++;
	while(*p)
	{
		if(*p>='a' && *p<='z')name[j]=(*p++)-0x20;
		else name[j]=*p++;
		j++;
	}
	if(FAT_FindItem(cluster,name, &FileInfo))return 1;//find the file
	cluster = FileInfo.StartCluster;
	return cluster;
}

// find a directory with the given path
uint32_t FAT_OpenDir(uint8_t *dir)
{
	uint8_t name[11];
	uint8_t *p=dir;
	uint8_t deep=0;
	uint8_t i,j;
	uint32_t cluster=0;
	if(FAT32_Enable) cluster = FirstDirClust;
	if(*p != '\\')
	{
		return 1;//invalid path
	}

	while(*p)
	{
		if(*p == '\\')
		{
			deep++;
		}
		p++;
	}
	p=dir;
	for(i=0;i<deep-1;i++)
	{
		p++;
		memset(name,0x20,11);
		j=0;
		while(*p != '\\')
		{
			if((*p) >= 'a' && (*p) <= 'z')name[j] = (*p++)-0x20;
			else name[j] = *p++;
			j++;
		}
		if(FAT_FindItem(cluster,name, &FileInfo))return 1;//find the directory
		cluster = FileInfo.StartCluster;
	}
	p++;
	memset(name,0x20,11);
	j=0;
	while(*p)
	{
		if(*p>='a' && *p<='z')name[j]=(*p++)-0x20;
		else name[j]=*p++;
		j++;
	}
	if(j == 0)return cluster;
	if(FAT_FindItem(cluster,name, &FileInfo))return 1;//find the final directory
	cluster = FileInfo.StartCluster;
	return cluster;
}


uint16_t FAT_Close(uint32_t * p)
{
	*p=1;
	return 0;
}

// Output the data of a file
// size 0 means read all of the file
unsigned char FAT_Read(uint32_t pointer, uint32_t size)
{
	uint32_t sector;
	uint32_t tempclust=pointer;
	//uint8_t *buffer;
	uint8_t buffer[512];
	unsigned int i=0,j=0;
	sector=(uint32_t)FirstDataSector+(uint32_t)(tempclust-2)*(uint32_t)SectorsPerClust;
	if(size==0)size = FileInfo.Size;//whether need to read all
//	RETAILMSG(TRUE, (TEXT("\r\n")));
	while(size)
	{
		//buffer=malloc(512);
		if(!FAT_ReadSector(sector+j,1,buffer))
		{
			//free(buffer);
			return 1;
		}
		if(size<=512)
		{
			for(i=0;i<size;i++)
			{
			//	RETAILMSG(TRUE, (TEXT("%c"),buffer[i]));
			}
			//free(buffer);
			return 0;//file over
		}
		else
		{
			for(i=0;i<512;i++)
			{
			//	RETAILMSG(TRUE, (TEXT("%c"),buffer[i]));
			}
			j++;
			if(j==SectorsPerClust)
			{
				j=0;
				//free(buffer);
				tempclust=FAT_NextCluster(tempclust);//find the next cluster the data was stored
				if((FAT32_Enable == 0 && tempclust == 0xffff) || tempclust == 0x0ffffff8 || tempclust == 0x0fffffff)return 1;
				sector=(uint32_t)FirstDataSector+(uint32_t)(tempclust-2)*(uint32_t)SectorsPerClust;//reculculate the sector
			}
			else 
				;//free(buffer);
			size-=512;

		}
	}
	return 0;
}

// write data to a file
unsigned char FAT_Write(uint32_t cluster,unsigned char *data,uint32_t size)
{
	//uint8_t *buffer=0;
	uint8_t buffer[512];
	uint32_t sector;
	uint16_t  tSize;

	if(buffer==0) return 1; //内存申请失败

	if(size<=512)
	{
		//buffer=malloc(size);
		memcpy(buffer,data,size);
		sector=(uint32_t)FirstDataSector+(uint32_t)(cluster-2)*(uint32_t)SectorsPerClust;
		if(!FAT_WriteSector(sector,1,buffer))
		{
			//free(buffer);
			return 1;//write the data
		}
	}
	else
	{
		//buffer=malloc(512);
		while(size)
		{
			tSize=(size>512?512:size);
			//写入文件,每次512uint8_t
			memcpy(buffer,data,tSize);
			sector=(uint32_t)FirstDataSector+(uint32_t)(cluster-2)*(uint32_t)SectorsPerClust;
			if(!FAT_WriteSector(sector,1,buffer))
			{
				//free(buffer);
				return 1;//write the data
			}
			size-=tSize;
		}
	}
	//free(buffer);
	return 0;
}

//Delete a file
unsigned char FAT_Delete(uint8_t *dir)
{
	if(FAT_Open(dir)==0)return 1;//open the file
	if(FAT_DelItem(&FileInfo))return 1;//delete it
	return 0;
}

//Delete an item
unsigned char FAT_DelItem(struct FileInfoStruct *FileInfo)
{
	//uint8_t *buffer;
	uint8_t buffer[512];
	struct direntry *item;
	uint32_t cluster;
	uint32_t tempclust;

	//buffer=malloc(512);
	if(buffer==0)return 1;
	if(!FAT_ReadSector(FileInfo->Sector,1,buffer))
	{
		//free(buffer);
		return 1;
	}
	item=(struct direntry *)(&buffer[FileInfo->Offset]);
	item->deName[0]=0xe5;//mark it was deleted
	if(!FAT_WriteSector(FileInfo->Sector,1,buffer))
	{
		//free(buffer);
		return 1;
	}
	//free(buffer);
	cluster=FileInfo->StartCluster;
	if(FileInfo->Attr & 0x10)//if the item is a folder
	{
		while(1)
		{
			while(FAT_SelectOneItem(cluster,FileInfo)==0)
			{
				if(FAT_DelItem(FileInfo)) return 1;//nest for deleting folder
			}
			tempclust=FAT_NextCluster(cluster);//if the folder contain many item
			if(tempclust==1)return 1;
			if(FAT_ModifyFAT(cluster,0)) return 1;//release the fat table
			cluster=tempclust;
			if(cluster == 0x0ffffff8) return 1;//error
			if((FAT32_Enable == 0 && tempclust == 0xffff) || tempclust == 0x0fffffff) break;//the end of the directory
		}
	}
	else// the item is a file
	{ 
		while(1)
		{
			tempclust=FAT_NextCluster(cluster);//save the next cluster
			if(tempclust==1) return 1;
			if(FAT_ModifyFAT(cluster,0))return 1;//delete curent cluster
			cluster=tempclust;
			if(cluster == 0x0ffffff8)return 1;//error
			if((FAT32_Enable == 0 && tempclust == 0xffff) || tempclust == 0x0fffffff) break;//the end of the file
		}
	}
	return 0;	//done
}

//Rename a directory or a file
unsigned char FAT_Rename(uint8_t *dir,uint8_t *newname)
{
	uint8_t name[11];
	uint8_t *p=dir;
	uint8_t deep=0;
	uint8_t i,j;
	uint32_t cluster=0;
	//uint8_t *buffer;
	uint8_t buffer[512];
	struct direntry *item;
	if(FAT32_Enable)cluster=FirstDirClust;
	if(*p != '\\')return 1;//invalid path
	while(*p)
	{
		if(*p == '\\')
		{
			deep++;
		}
		p++;
	}
	p=dir;
	for(i=0;i<deep-1;i++)
	{
		p++;
		memset(name,0x20,11);
		j=0;
		while(*p != '\\')
		{
			if((*p) >= 'a' && (*p) <= 'z') name[j] = (*p++)-0x20;
			else name[j] = *p++;
			j++;
		}
		if(FAT_FindItem(cluster,name, &FileInfo))return 1;
		cluster = FileInfo.StartCluster;
	}
	p++;
	memset(name,0x20,11);
	j=0;
	while((*p != '.') && (*p) )//compatalbe for folder and file
	{
		if(*p>='a' && *p<='z')name[j]=(*p++)-0x20;
		else name[j]=*p++;
		j++;
	}
	j=8;
	if(*p == '.')//if it is a file
	{
		p++;
		while(*p)
		{
			if(*p>='a' && *p<='z')name[j]=(*p++)-0x20;
			else name[j]=*p++;
			j++;
		}
	}
	//else ;//It is a directory 
	if(FAT_FindItem(cluster,name, &FileInfo))return 1;//get the file or directory information
	//buffer=malloc(512);
	if(buffer==0)return 1;
	if(!FAT_ReadSector(FileInfo.Sector,1,buffer))
	{
		//free(buffer);
		return 1;
	}//read the item according the information
	item=(struct direntry *)(&buffer[FileInfo.Offset]);

	//modify the name

	p=newname;
	memset(name,0x20,11);
	j=0;
	while((*p != '.') && (*p))
	{
		if(*p>='a' && *p<='z')item->deName[j]=(*p++)-0x20;
		else item->deName[j]=*p++;
		j++;
	}
	j=8;
	if(*p == '.')//if it is a file
	{
		p++;
		while(*p)
		{
			if(*p>='a' && *p<='z')item->deName[j]=(*p++)-0x20;
			else item->deName[j]=*p++;
			j++;
		}
	}
	if(!FAT_WriteSector(FileInfo.Sector,1,buffer))
	{
		//free(buffer);
		return 1;
	}//rewrite the item
	//free(buffer);
	return 0;//done	
}

//复制记录项信息
void CopyDirentruyItem(struct direntry *Desti,struct direntry *Source)
{
	uint8_t i;
	for(i=0;i<8;i++)Desti->deName[i] = Source->deName[i];
	for(i=0;i<3;i++)Desti->deExtension[i] = Source->deExtension[i];
	Desti->deAttributes = Source->deAttributes;
	Desti->deLowerCase = Source->deLowerCase;
	Desti->deCHundredth = Source->deCHundredth;
	for(i=0;i<2;i++)Desti->deCTime[i] = Source->deCTime[i];
	for(i=0;i<2;i++)Desti->deCDate[i] = Source->deCDate[i];
	for(i=0;i<2;i++)Desti->deADate[i] = Source->deADate[i];
	Desti->deHighClust = Source->deHighClust;
	for(i=0;i<2;i++)Desti->deMTime[i] = Source->deMTime[i];
	for(i=0;i<2;i++)Desti->deMDate[i] = Source->deMDate[i];
	Desti->deStartCluster = Source->deStartCluster;
	Desti->deFileSize = Source->deFileSize;
}

//打开指定路径的文件,输出文件信息并返回文件的首簇.
uint32_t FAT_OpenFile(char *dir,struct FileInfoStruct *File_Info)	//1=失败.
{
	uint8_t name[11];
	uint8_t *p=dir;
	uint8_t 	deep=0;
	uint8_t 	i,j;
	uint32_t	cluster=0;

	if(FAT32_Enable)cluster=FirstDirClust;
	//if(*p != '\\')	return 1;//invalid path
	if(*p != '\\')	return 0;//invalid path --czx

	while(*p)
	{
		if(*p == '\\')
		{
			deep++;
		}
		p++;
	}

	p=dir;
	for(i=0;i<deep-1;i++)
	{
		p++;
		memset(name,0x20,11);
		j=0;
		while(*p != '\\')
		{
			if((*p) >= 'a' && (*p) <= 'z')name[j] = (*p++)-0x20;
			else name[j] = *p++;
			j++;
		}

		//printf("(if(FAT_FindItem(cluster,name, File_Info))return 1\n");
		if(FAT_FindItem(cluster,name, File_Info))return 1;//find the directory
		cluster = File_Info->StartCluster;
	}
	p++;
	memset(name,0x20,11);
	j=0;
	while(*p != '.')//file must have a extention
	{
		if(*p>='a' && *p<='z')	name[j]=(*p++)-0x20;
		else name[j]=*p++;
		j++;
	}
	j=8;
	p++;
	while(*p)
	{
		if(*p>='a' && *p<='z')	name[j]=(*p++)-0x20;
		else name[j]=*p++;
		j++;
	}
	//printf("(if(FAT_FindItem(cluster,name, File_Info))return 1\n");
	//if(FAT_FindItem(cluster,name, File_Info))return 1;//find the file
	if(FAT_FindItem(cluster,name, File_Info))return 0;//find the file --czx
	cluster = File_Info->StartCluster;
	return	cluster;
}


//get the content of a foler , 0 as root directory.获取给定目录下所有文件的信息.
uint8_t FAT_GetFile(uint8_t *dir,struct FileInfoStruct *FileInfo)

{
	//uint8_t *buffer;
	uint8_t buffer[512];
	uint32_t sector;
	uint32_t cluster;
	uint32_t tempclust;
	uint32_t cnt;
	uint32_t offset;
	uint8_t i;
	struct direntry *item = 0;
	////
	cluster = FAT_OpenDir(dir);
	if(cluster == 1)
	{
		////打开目录失败.
#if(FAT_DEBUG==1)
		_DBG("FAT_GetFile:);_DBC(dir)；_DBG(Err!\n");
#endif
		return 1;
	}
	////
	if(cluster==0 && FAT32_Enable==0)	// root directory
	{
		//// FAT16 根目录.
		//buffer=malloc(512);//apply memory
		if(buffer==0)return 1;//if failed
		for(cnt=0;cnt<RootDirSectors;cnt++)
		{
			if(!FAT_ReadSector(FirstDirSector+cnt,1,buffer))
			{
				//free(buffer);
				return 1;
			}
			////
			for(offset=0;offset<512;offset+=32)				//1个文件信息占32字节.
			{
				item=(struct direntry *)(&buffer[offset]);	//pointer convert
				//find a valid item and display it
				if((item->deName[0] != '.') && (item->deName[0] != 0x00) && (item->deName[0] != 0xe5) && (item->deAttributes != 0x0f))
				{
					//Uart_Senduint8_t('\n');
					#ifdef DBG
					_DBG("\n");
					#endif
					for(i=0;i<8;i++)//name
					{
						//Uart_Senduint8_t(item->deName[i]);
						if(item->deName[i] != ' ')
						{
							#ifdef DBG
					_DBC(item->deName[i]);
						#endif
						}
					}
					if((item->deAttributes & 0x10)==0)
					{						
						#ifdef DBG
						_DBG(".");
						#endif
					}
					for(i=0;i<3;i++)//extention
					{
						//Uart_Senduint8_t(item->deExtension[i]);
						#ifdef DBG
						_DBC(item->deExtension[i]);
						#endif
					}
				}
			}
		}
		//free(buffer);//release
	}
	else//other folders
	{	
		tempclust=cluster;
		while(1)
		{
			sector=(uint32_t)FirstDataSector+(uint32_t)(tempclust-2)*(uint32_t)SectorsPerClust;//calculate the actual sector number
			//buffer=malloc(512);//apply memory
			if(buffer==0)return 1;//if failed
			for(cnt=0;cnt<SectorsPerClust;cnt++)
			{
				if(!FAT_ReadSector(sector+cnt,1,buffer))
				{
					//free(buffer);
					return 1;
				}
				for(offset=0;offset<512;offset+=32)
				{
					item=(struct direntry *)(&buffer[offset]);
					if((item->deName[0] != '.') && (item->deName[0] != 0x00) && (item->deName[0] != 0xe5) && (item->deAttributes != 

						0x0f))
					{
						//Uart_Senduint8_t(0x0d);
						//Uart_Senduint8_t(0x0a);
						#ifdef DBG
						_DBG("\r\n");
						#endif
						for(i=0;i<8;i++)
						{
							//Uart_Senduint8_t(item->deName[i]);
							if(item->deName[i] != ' ')
							{
								#ifdef DBG
							_DBC(item->deName[i]);
								#endif
							}
						}
						if((item->deAttributes & 0x10)==0)
						{
							#ifdef DBG
							_DBG(".");
								#endif
						}
							for(i=0;i<3;i++)
						{
							//Uart_Senduint8_t(item->deExtension[i]);
							#ifdef DBG
							_DBC(item->deExtension[i]);
							#endif
						}
					}
				}
			}
			//free(buffer);//release
			tempclust=FAT_NextCluster(tempclust);//next cluster
			if( tempclust == 0x0ffffff8 )return 1;
			if((FAT32_Enable == 0 && tempclust == 0xffff) || tempclust == 0x0fffffff)break;
		}
	}
	#ifdef DBG
	_DBG("\r\n");
	#endif
	return 0;
}

//通过目录加载文件到缓冲
uint8_t FAT_DirLoadFile(char *dir,uint8_t *Buf) //0=失败;1=成功.
{
	uint32_t 	cluster,size;
	uint8_t 	part;
//	uint32_t	Cnt = 0;
	struct	FileInfoStruct FileInfo;
#ifdef DBG
	_DBG("Preparing Load File");_DBG("to sdram:");_DBH32((uint32_t)Buf);_DBG("\n");
#endif
	cluster=FAT_OpenFile(dir,&FileInfo);

	if(cluster==0 || FileInfo.Size == 0)
	{
		#ifdef DBG
		_DBG("FAT Load File"); _DBG(" Err!\n");
		#endif
		return 0;
	}
	size=0;
	g_FileSize = FileInfo.Size;
//	_DBG("logo.bmp size is  ");_DBD32(g_FileSize);
//	RETAILMSG(TRUE, (TEXT("Current Load Percent : ")));
/*	if(dir[1] == 'X' || dir[1] == 'x')
	{
//		InitProgressBar(COLOR_BACKGROUND); 
	}*/
	while(size<FileInfo.Size)
	{

		for(part=0;part<SectorsPerClust;part++)
		{
			FAT_LoadPartCluster(cluster,part,(uint8_t *)(Buf+size));	//读一个扇区.
			size+=512;
			
		}
	
		cluster=FAT_NextCluster(cluster);
	}
	#ifdef DBG
	_DBG("\r\n");
	#endif
	
	return 1;
}

//通过簇加载整个文件到Buf.
uint8_t FAT_ClusterLoadFile(uint32_t cluster,uint8_t *Buf)			//0=失败;1=成功.
{
	uint32_t size;
	uint8_t part;

	if(cluster==0)
	{
		#ifdef DBG
	_DBG("FAT Load File Err!\n");
		#endif
		return 0;
	}
	size=0;
	while((cluster&0xffff)<0xfff8)		//0xfff8~0xffff 文件最后一簇.
	{

		for(part=0;part<SectorsPerClust;part++)
		{
			FAT_LoadPartCluster(cluster,part,(uint8_t *)(Buf+size));	//读一个扇区.
			size+=512;
		}
		cluster=FAT_NextCluster(cluster);
	}	
	return 1;
}

uint32_t GetFileSize(void)
{
	return g_FileSize;
}