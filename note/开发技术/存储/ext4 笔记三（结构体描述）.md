```cpp


Super block
只是在ext3的基础上扩展了一些字段，可以支持更大的硬盘和更大的文件。
如：s_blocks_count  修改为s_blocks_count_lo和s_blocks_count_hi
结构体如下：

[plain] view plaincopyprint?
	1. 
/*  
	2. 
 *Structure of the super block  
	3. 
 */  
	4. 
struct ext4_super_block {  
	5. 
/*00*/ __le32  s_inodes_count;         /* Inodes count文件系统中inode的总数*/  
	6. 
       __le32  s_blocks_count_lo;      /* Blocks count文件系统中块的总数*/  
	7. 
       __le32  s_r_blocks_count_lo;    /* Reserved blocks count保留块的总数*/  
	8. 
       __le32  s_free_blocks_count_lo; /*Free blocks count未使用的块的总数（包括保留块）*/  
	9. 
/*10*/ __le32  s_free_inodes_count;    /* Free inodes count未使用的inode的总数*/  
	10. 
       __le32  s_first_data_block;     /* First Data Block第一块块ID，在小于1KB的文件系统中为0，大于1KB的文件系统中为1*/  
	11. 
       __le32  s_log_block_size;       /* Block size用以计算块的大小（1024算术左移该值即为块大小）(0=1K, 1=2K, 2=4K) */  
	12. 
       __le32  s_obso_log_frag_size;   /* Obsoleted fragment size用以计算段大小（为正则1024算术左移该值，否则右移）*/  
	13. 
/*20*/ __le32  s_blocks_per_group;     /* # Blocks per group每个块组中块的总数*/  
	14. 
       __le32  s_obso_frags_per_group; /*Obsoleted fragments per group每个块组中段的总数*/  
	15. 
       __le32  s_inodes_per_group;     /* # Inodes per group每个块组中inode的总数*/  
	16. 
       __le32  s_mtime;                /* Mount time POSIX中定义的文件系统装载时间*/  
	17. 
/*30*/ __le32  s_wtime;                /* Write time POSIX中定义的文件系统最近被写入的时间*/  
	18. 
       __le16  s_mnt_count;            /* Mount count最近一次完整校验后被装载的次数*/  
	19. 
       __le16  s_max_mnt_count;        /* Maximal mount count在进行完整校验前还能被装载的次数*/  
	20. 
       __le16  s_magic;                /* Magic signature文件系统标志*/  
	21. 
       __le16  s_state;                /* File system state文件系统的状态*/  
	22. 
       __le16  s_errors;               /* Behaviour when detectingerrors文件系统发生错误时驱动程序应该执行的操作*/  
	23. 
       __le16  s_minor_rev_level;      /* minor revision level局部修订级别*/  
	24. 
/*40*/ __le32  s_lastcheck;            /* time of last check POSIX中定义的文件系统最近一次检查的时间*/  
	25. 
       __le32  s_checkinterval;        /* max. time between checks POSIX中定义的文件系统最近检查的最大时间间隔*/  
	26. 
       __le32  s_creator_os;           /* OS生成该文件系统的操作系统*/  
	27. 
       __le32  s_rev_level;            /* Revision level修订级别*/  
	28. 
/*50*/ __le16  s_def_resuid;           /* Default uid for reserved blocks报留块的默认用户ID */  
	29. 
       __le16  s_def_resgid;           /* Default gid for reserved blocks保留块的默认组ID */  
	30. 
       /*  
	31. 
        * These fields are for EXT4_DYNAMIC_REV superblocks only.  
	32. 
        *  
	33. 
        * Note: the difference between the compatible feature set and  
	34. 
        * the incompatible feature set is that if there is a bit set  
	35. 
        * in the incompatible feature set that the kernel doesn't  
	36. 
        * know about, it should refuse to mount the filesystem.  
	37. 
        *  
	38. 
        * e2fsck's requirements are more strict; if it doesn't know  
	39. 
        * about a feature in either the compatible or incompatible  
	40. 
        * feature set, it must abort and not try to meddle with  
	41. 
        * things it doesn't understand...  
	42. 
        */  
	43. 
       __le32  s_first_ino;            /* First non-reserved inode标准文件的第一个可用inode的索引（非动态为11）*/  
	44. 
       __le16  s_inode_size;           /* size of inode structure inode结构的大小（非动态为128）*/  
	45. 
       __le16  s_block_group_nr;       /* block group # of this superblock保存此超级块的块组号*/  
	46. 
       __le32  s_feature_compat;       /* compatible feature set兼容特性掩码*/  
	47. 
/*60*/ __le32  s_feature_incompat;     /* incompatible feature set不兼容特性掩码*/  
	48. 
       __le32  s_feature_ro_compat;    /* readonly-compatible feature set只读特性掩码*/  
	49. 
/*68*/ __u8    s_uuid[16];             /* 128-bit uuid for volume卷ID，应尽可能使每个文件系统的格式唯一*/  
	50. 
/*78*/ char    s_volume_name[16];      /* volume name卷名（只能为ISO-Latin-1字符集，以'\0'结束）*/  
	51. 
/*88*/ char    s_last_mounted[64];     /* directory where last mounted最近被安装的目录*/  
	52. 
/*C8*/ __le32  s_algorithm_usage_bitmap;/* For compression文件系统采用的压缩算法*/  
	53. 
       /*  
	54. 
        * Performance hints.  Directorypreallocation should only  
	55. 
        * happen if the EXT4_FEATURE_COMPAT_DIR_PREALLOC flag is on.  
	56. 
        */  
	57. 
       __u8    s_prealloc_blocks;      /* Nr of blocks to try to preallocate预分配的块数*/  
	58. 
       __u8   s_prealloc_dir_blocks;  /* Nr topreallocate for dirs给目录预分配的块数*/  
	59. 
       __le16 s_reserved_gdt_blocks;  /* Pergroup desc for online growth */  
	60. 
       /*  
	61. 
        * Journaling support valid if EXT4_FEATURE_COMPAT_HAS_JOURNAL set.  
	62. 
        */  
	63. 
/*D0*/ __u8    s_journal_uuid[16];     /* uuid of journal superblock日志超级块的卷ID */  
	64. 
/*E0*/ __le32  s_journal_inum;         /* inode number of journal file日志文件的inode数目*/  
	65. 
       __le32  s_journal_dev;          /* device number of journal file日志文件的设备数*/  
	66. 
       __le32  s_last_orphan;          /* start of list of inodes to delete要删除的inode列表的起始位置*/  
	67. 
       __le32  s_hash_seed[4];         /* HTREE hash seed HTREE散列种子*/  
	68. 
       __u8    s_def_hash_version;     /* Default hash version to use默认使用的散列函数*/  
	69. 
       __u8    s_jnl_backup_type;  
	70. 
       __le16  s_desc_size;            /* size of group descriptor */  
	71. 
/*100*/ __le32  s_default_mount_opts;  
	72. 
       __le32  s_first_meta_bg;        /* First metablock block group块组的第一个元块*/  
	73. 
        __le32 s_mkfs_time;            /* Whenthe filesystem was created */  
	74. 
       __le32  s_jnl_blocks[17];       /* Backup of the journal inode */  
	75. 
       /* 64bit support valid if EXT4_FEATURE_COMPAT_64BIT */  
	76. 
/*150*/ __le32  s_blocks_count_hi;      /* Blocks count */  
	77. 
       __le32  s_r_blocks_count_hi;    /* Reserved blocks count */  
	78. 
       __le32  s_free_blocks_count_hi; /*Free blocks count */  
	79. 
       __le16  s_min_extra_isize;      /* All inodes have at least # bytes */  
	80. 
       __le16  s_want_extra_isize;     /* New inodes should reserve # bytes */  
	81. 
       __le32  s_flags;                /* Miscellaneous flags */  
	82. 
       __le16  s_raid_stride;          /* RAID stride */  
	83. 
       __le16 s_mmp_update_interval;  /* #seconds to wait in MMP checking */  
	84. 
        __le64 s_mmp_block;            /* Blockfor multi-mount protection */  
	85. 
       __le32  s_raid_stripe_width;    /* blocks on all data disks (N*stride)*/  
	86. 
       __u8   s_log_groups_per_flex;  /* FLEX_BGgroup size */  
	87. 
       __u8    s_reserved_char_pad;  
	88. 
       __le16  s_reserved_pad;  
	89. 
       __le64  s_kbytes_written;       /* nr of lifetime kilobytes written */  
	90. 
       __le32  s_snapshot_inum;        /* Inode number of active snapshot */  
	91. 
       __le32  s_snapshot_id;          /* sequential ID of active snapshot*/  
	92. 
       __le64  s_snapshot_r_blocks_count;/* reserved blocks for active  
	93. 
                                             snapshot's future use */  
	94. 
       __le32  s_snapshot_list;        /* inode number of the head of the  
	95. 
                                           on-disk snapshot list */  
	96. 
#define EXT4_S_ERR_START offsetof(structext4_super_block, s_error_count)  
	97. 
       __le32  s_error_count;          /* number of fs errors */  
	98. 
       __le32  s_first_error_time;     /* first time an error happened */  
	99. 
       __le32  s_first_error_ino;      /* inode involved in first error */  
	100. 
       __le64  s_first_error_block;    /* block involved of first error */  
	101. 
       __u8    s_first_error_func[32]; /*function where the error happened */  
	102. 
       __le32  s_first_error_line;     /* line number where error happened */  
	103. 
       __le32  s_last_error_time;      /* most recent time of an error */  
	104. 
       __le32  s_last_error_ino;       /* inode involved in last error */  
	105. 
       __le32  s_last_error_line;      /* line number where error happened */  
	106. 
       __le64  s_last_error_block;     /* block involved of last error */  
	107. 
       __u8   s_last_error_func[32];  /*function where the error happened */  
	108. 
#define EXT4_S_ERR_END offsetof(structext4_super_block, s_mount_opts)  
	109. 
       __u8    s_mount_opts[64];  
	110. 
       __le32  s_reserved[112];        /* Padding to the end of the block */  
	111. 
};  




/*
*Structure of the super block
*/
struct ext4_super_block {
/*00*/ __le32 s_inodes_count; /* Inodes count文件系统中inode的总数*/
__le32 s_blocks_count_lo; /* Blocks count文件系统中块的总数*/
__le32 s_r_blocks_count_lo; /* Reserved blocks count保留块的总数*/
__le32 s_free_blocks_count_lo; /*Free blocks count未使用的块的总数（包括保留块）*/
/*10*/ __le32 s_free_inodes_count; /* Free inodes count未使用的inode的总数*/
__le32 s_first_data_block; /* First Data Block第一块块ID，在小于1KB的文件系统中为0，大于1KB的文件系统中为1*/
__le32 s_log_block_size; /* Block size用以计算块的大小（1024算术左移该值即为块大小）(0=1K, 1=2K, 2=4K) */
__le32 s_obso_log_frag_size; /* Obsoleted fragment size用以计算段大小（为正则1024算术左移该值，否则右移）*/
/*20*/ __le32 s_blocks_per_group; /* # Blocks per group每个块组中块的总数*/
__le32 s_obso_frags_per_group; /*Obsoleted fragments per group每个块组中段的总数*/
__le32 s_inodes_per_group; /* # Inodes per group每个块组中inode的总数*/
__le32 s_mtime; /* Mount time POSIX中定义的文件系统装载时间*/
/*30*/ __le32 s_wtime; /* Write time POSIX中定义的文件系统最近被写入的时间*/
__le16 s_mnt_count; /* Mount count最近一次完整校验后被装载的次数*/
__le16 s_max_mnt_count; /* Maximal mount count在进行完整校验前还能被装载的次数*/
__le16 s_magic; /* Magic signature文件系统标志*/
__le16 s_state; /* File system state文件系统的状态*/
__le16 s_errors; /* Behaviour when detectingerrors文件系统发生错误时驱动程序应该执行的操作*/
__le16 s_minor_rev_level; /* minor revision level局部修订级别*/
/*40*/ __le32 s_lastcheck; /* time of last check POSIX中定义的文件系统最近一次检查的时间*/
__le32 s_checkinterval; /* max. time between checks POSIX中定义的文件系统最近检查的最大时间间隔*/
__le32 s_creator_os; /* OS生成该文件系统的操作系统*/
__le32 s_rev_level; /* Revision level修订级别*/
/*50*/ __le16 s_def_resuid; /* Default uid for reserved blocks报留块的默认用户ID */
__le16 s_def_resgid; /* Default gid for reserved blocks保留块的默认组ID */
/*
* These fields are for EXT4_DYNAMIC_REV superblocks only.
*
* Note: the difference between the compatible feature set and
* the incompatible feature set is that if there is a bit set
* in the incompatible feature set that the kernel doesn't
* know about, it should refuse to mount the filesystem.
*
* e2fsck's requirements are more strict; if it doesn't know
* about a feature in either the compatible or incompatible
* feature set, it must abort and not try to meddle with
* things it doesn't understand...
*/
__le32 s_first_ino; /* First non-reserved inode标准文件的第一个可用inode的索引（非动态为11）*/
__le16 s_inode_size; /* size of inode structure inode结构的大小（非动态为128）*/
__le16 s_block_group_nr; /* block group # of this superblock保存此超级块的块组号*/
__le32 s_feature_compat; /* compatible feature set兼容特性掩码*/
/*60*/ __le32 s_feature_incompat; /* incompatible feature set不兼容特性掩码*/
__le32 s_feature_ro_compat; /* readonly-compatible feature set只读特性掩码*/
/*68*/ __u8 s_uuid[16]; /* 128-bit uuid for volume卷ID，应尽可能使每个文件系统的格式唯一*/
/*78*/ char s_volume_name[16]; /* volume name卷名（只能为ISO-Latin-1字符集，以'\0'结束）*/
/*88*/ char s_last_mounted[64]; /* directory where last mounted最近被安装的目录*/
/*C8*/ __le32 s_algorithm_usage_bitmap;/* For compression文件系统采用的压缩算法*/
/*
* Performance hints. Directorypreallocation should only
* happen if the EXT4_FEATURE_COMPAT_DIR_PREALLOC flag is on.
*/
__u8 s_prealloc_blocks; /* Nr of blocks to try to preallocate预分配的块数*/
__u8 s_prealloc_dir_blocks; /* Nr topreallocate for dirs给目录预分配的块数*/
__le16 s_reserved_gdt_blocks; /* Pergroup desc for online growth */
/*
* Journaling support valid if EXT4_FEATURE_COMPAT_HAS_JOURNAL set.
*/
/*D0*/ __u8 s_journal_uuid[16]; /* uuid of journal superblock日志超级块的卷ID */
/*E0*/ __le32 s_journal_inum; /* inode number of journal file日志文件的inode数目*/
__le32 s_journal_dev; /* device number of journal file日志文件的设备数*/
__le32 s_last_orphan; /* start of list of inodes to delete要删除的inode列表的起始位置*/
__le32 s_hash_seed[4]; /* HTREE hash seed HTREE散列种子*/
__u8 s_def_hash_version; /* Default hash version to use默认使用的散列函数*/
__u8 s_jnl_backup_type;
__le16 s_desc_size; /* size of group descriptor */
/*100*/ __le32 s_default_mount_opts;
__le32 s_first_meta_bg; /* First metablock block group块组的第一个元块*/
__le32 s_mkfs_time; /* Whenthe filesystem was created */
__le32 s_jnl_blocks[17]; /* Backup of the journal inode */
/* 64bit support valid if EXT4_FEATURE_COMPAT_64BIT */
/*150*/ __le32 s_blocks_count_hi; /* Blocks count */
__le32 s_r_blocks_count_hi; /* Reserved blocks count */
__le32 s_free_blocks_count_hi; /*Free blocks count */
__le16 s_min_extra_isize; /* All inodes have at least # bytes */
__le16 s_want_extra_isize; /* New inodes should reserve # bytes */
__le32 s_flags; /* Miscellaneous flags */
__le16 s_raid_stride; /* RAID stride */
__le16 s_mmp_update_interval; /* #seconds to wait in MMP checking */
__le64 s_mmp_block; /* Blockfor multi-mount protection */
__le32 s_raid_stripe_width; /* blocks on all data disks (N*stride)*/
__u8 s_log_groups_per_flex; /* FLEX_BGgroup size */
__u8 s_reserved_char_pad;
__le16 s_reserved_pad;
__le64 s_kbytes_written; /* nr of lifetime kilobytes written */
__le32 s_snapshot_inum; /* Inode number of active snapshot */
__le32 s_snapshot_id; /* sequential ID of active snapshot*/
__le64 s_snapshot_r_blocks_count;/* reserved blocks for active
snapshot's future use */
__le32 s_snapshot_list; /* inode number of the head of the
on-disk snapshot list */
#define EXT4_S_ERR_START offsetof(structext4_super_block, s_error_count)
__le32 s_error_count; /* number of fs errors */
__le32 s_first_error_time; /* first time an error happened */
__le32 s_first_error_ino; /* inode involved in first error */
__le64 s_first_error_block; /* block involved of first error */
__u8 s_first_error_func[32]; /*function where the error happened */
__le32 s_first_error_line; /* line number where error happened */
__le32 s_last_error_time; /* most recent time of an error */
__le32 s_last_error_ino; /* inode involved in last error */
__le32 s_last_error_line; /* line number where error happened */
__le64 s_last_error_block; /* block involved of last error */
__u8 s_last_error_func[32]; /*function where the error happened */
#define EXT4_S_ERR_END offsetof(structext4_super_block, s_mount_opts)
__u8 s_mount_opts[64];
__le32 s_reserved[112]; /* Padding to the end of the block */
};group descriptor
块组描述信息。
包含了blockbitmap、inode bitmap、inode table等存放的块地址。
结构体如下：

[plain] view plaincopyprint?
	1. 
/*  
	2. 
 *Structure of a blocks group descriptor  
	3. 
 */  
	4. 
struct ext4_group_desc  
	5. 
{  
	6. 
       __le32  bg_block_bitmap_lo;     /* Blocks bitmap block块位图所在的第一个块的块ID */  
	7. 
       __le32  bg_inode_bitmap_lo;     /* Inodes bitmap block inode位图所在的第一个块的块ID */  
	8. 
       __le32  bg_inode_table_lo;      /* Inodes table block inode表所在的第一个块的块ID */  
	9. 
       __le16  bg_free_blocks_count_lo;/*Free blocks count块组中未使用的块数*/  
	10. 
       __le16  bg_free_inodes_count_lo;/*Free inodes count块组中未使用的inode数*/  
	11. 
       __le16 bg_used_dirs_count_lo;  /*Directories count块组分配的目录的inode数*/  
	12. 
       __le16  bg_flags;               /* EXT4_BG_flags (INODE_UNINIT,etc) */  
	13. 
       __u32   bg_reserved[2];         /* Likely block/inode bitmap checksum*/  
	14. 
       __le16  bg_itable_unused_lo;    /* Unused inodes count */  
	15. 
       __le16  bg_checksum;            /* crc16(sb_uuid+group+desc) */  
	16. 
       __le32  bg_block_bitmap_hi;     /* Blocks bitmap block MSB */  
	17. 
       __le32  bg_inode_bitmap_hi;     /* Inodes bitmap block MSB */  
	18. 
       __le32  bg_inode_table_hi;      /* Inodes table block MSB */  
	19. 
       __le16  bg_free_blocks_count_hi;/*Free blocks count MSB */  
	20. 
       __le16  bg_free_inodes_count_hi;/*Free inodes count MSB */  
	21. 
       __le16 bg_used_dirs_count_hi;  /*Directories count MSB */  
	22. 
       __le16  bg_itable_unused_hi;    /* Unused inodes count MSB */  
	23. 
       __u32   bg_reserved2[3];  
	24. 
};  




/*
*Structure of a blocks group descriptor
*/
struct ext4_group_desc
{
__le32 bg_block_bitmap_lo; /* Blocks bitmap block块位图所在的第一个块的块ID */
__le32 bg_inode_bitmap_lo; /* Inodes bitmap block inode位图所在的第一个块的块ID */
__le32 bg_inode_table_lo; /* Inodes table block inode表所在的第一个块的块ID */
__le16 bg_free_blocks_count_lo;/*Free blocks count块组中未使用的块数*/
__le16 bg_free_inodes_count_lo;/*Free inodes count块组中未使用的inode数*/
__le16 bg_used_dirs_count_lo; /*Directories count块组分配的目录的inode数*/
__le16 bg_flags; /* EXT4_BG_flags (INODE_UNINIT,etc) */
__u32 bg_reserved[2]; /* Likely block/inode bitmap checksum*/
__le16 bg_itable_unused_lo; /* Unused inodes count */
__le16 bg_checksum; /* crc16(sb_uuid+group+desc) */
__le32 bg_block_bitmap_hi; /* Blocks bitmap block MSB */
__le32 bg_inode_bitmap_hi; /* Inodes bitmap block MSB */
__le32 bg_inode_table_hi; /* Inodes table block MSB */
__le16 bg_free_blocks_count_hi;/*Free blocks count MSB */
__le16 bg_free_inodes_count_hi;/*Free inodes count MSB */
__le16 bg_used_dirs_count_hi; /*Directories count MSB */
__le16 bg_itable_unused_hi; /* Unused inodes count MSB */
__u32 bg_reserved2[3];
};inode
保存了每个节点的信息。
该节点的属性、所占的块地址。
结构体如下：

[plain] view plaincopyprint?
	1. 
/*  
	2. 
 *Structure of an inode on the disk  
	3. 
 */  
	4. 
struct ext4_inode {  
	5. 
       __le16  i_mode;         /* File mode文件格式和访问权限*/  
	6. 
       __le16  i_uid;          /* Low 16 bits of Owner Uid文件所有者ID的低16位*/  
	7. 
       __le32  i_size_lo;      /* Size in bytes文件字节数*/  
	8. 
       __le32  i_atime;        /* Access time文件上次被访问的时间*/  
	9. 
       __le32  i_ctime;        /* Inode Change time文件创建时间*/  
	10. 
       __le32  i_mtime;        /* Modification time文件被修改的时间*/  
	11. 
       __le32  i_dtime;        /* Deletion Time文件被删除的时间（如果存在则为0）*/  
	12. 
       __le16  i_gid;          /* Low 16 bits of Group Id文件所有组ID的低16位*/  
	13. 
       __le16  i_links_count;  /* Links count此inode被连接的次数*/  
	14. 
       __le32  i_blocks_lo;    /* Blocks count文件已使用和保留的总块数（以512B为单位）*/  
	15. 
       __le32  i_flags;        /* File flags */  
	16. 
       union {  
	17. 
                struct {  
	18. 
                        __le32  l_i_version;  
	19. 
                } linux1;  
	20. 
                struct {  
	21. 
                        __u32  h_i_translator;  
	22. 
                } hurd1;  
	23. 
                struct {  
	24. 
                        __u32  m_i_reserved1;  
	25. 
                } masix1;  
	26. 
       } osd1;                         /*OS dependent 1 */  
	27. 
       __le32  i_block[EXT4_N_BLOCKS];/*Pointers to blocks定位存储文件的块的数组*/  
	28. 
       __le32  i_generation;   /* File version (for NFS) 用于NFS的文件版本*/  
	29. 
       __le32  i_file_acl_lo;  /* File ACL包含扩展属性的块号，老版本中为0*/  
	30. 
       __le32  i_size_high;  
	31. 
       __le32  i_obso_faddr;   /* Obsoleted fragment address */  
	32. 
       union {  
	33. 
                struct {  
	34. 
                        __le16  l_i_blocks_high; /* were l_i_reserved1 */  
	35. 
                        __le16  l_i_file_acl_high;  
	36. 
                        __le16  l_i_uid_high;   /* these 2 fields */  
	37. 
                        __le16  l_i_gid_high;   /* were reserved2[0] */  
	38. 
                        __u32   l_i_reserved2;  
	39. 
                } linux2;  
	40. 
                struct {  
	41. 
                        __le16  h_i_reserved1;  /* Obsoleted fragment number/size which areremoved in ext4 */  
	42. 
                        __u16   h_i_mode_high;  
	43. 
                        __u16   h_i_uid_high;  
	44. 
                        __u16   h_i_gid_high;  
	45. 
                        __u32   h_i_author;  
	46. 
                } hurd2;  
	47. 
                struct {  
	48. 
                        __le16  h_i_reserved1;  /* Obsoleted fragment number/size which areremoved in ext4 */  
	49. 
                        __le16  m_i_file_acl_high;  
	50. 
                        __u32   m_i_reserved2[2];  
	51. 
                } masix2;  
	52. 
       } osd2;                         /*OS dependent 2 */  
	53. 
       __le16  i_extra_isize;  
	54. 
       __le16  i_pad1;  
	55. 
       __le32  i_ctime_extra;  /* extra Change time      (nsec << 2 | epoch) */  
	56. 
       __le32  i_mtime_extra;  /* extra Modification time(nsec << 2 |epoch) */  
	57. 
       __le32  i_atime_extra;  /* extra Access time      (nsec << 2 | epoch) */  
	58. 
       __le32  i_crtime;       /* File Creation time */  
	59. 
       __le32  i_crtime_extra; /* extraFileCreationtime (nsec << 2 | epoch) */  
	60. 
       __le32  i_version_hi;   /* high 32 bits for 64-bit version */  
	61. 
};  




/*
*Structure of an inode on the disk
*/
struct ext4_inode {
__le16 i_mode; /* File mode文件格式和访问权限*/
__le16 i_uid; /* Low 16 bits of Owner Uid文件所有者ID的低16位*/
__le32 i_size_lo; /* Size in bytes文件字节数*/
__le32 i_atime; /* Access time文件上次被访问的时间*/
__le32 i_ctime; /* Inode Change time文件创建时间*/
__le32 i_mtime; /* Modification time文件被修改的时间*/
__le32 i_dtime; /* Deletion Time文件被删除的时间（如果存在则为0）*/
__le16 i_gid; /* Low 16 bits of Group Id文件所有组ID的低16位*/
__le16 i_links_count; /* Links count此inode被连接的次数*/
__le32 i_blocks_lo; /* Blocks count文件已使用和保留的总块数（以512B为单位）*/
__le32 i_flags; /* File flags */
union {
struct {
__le32 l_i_version;
} linux1;
struct {
__u32 h_i_translator;
} hurd1;
struct {
__u32 m_i_reserved1;
} masix1;
} osd1; /*OS dependent 1 */
__le32 i_block[EXT4_N_BLOCKS];/*Pointers to blocks定位存储文件的块的数组*/
__le32 i_generation; /* File version (for NFS) 用于NFS的文件版本*/
__le32 i_file_acl_lo; /* File ACL包含扩展属性的块号，老版本中为0*/
__le32 i_size_high;
__le32 i_obso_faddr; /* Obsoleted fragment address */
union {
struct {
__le16 l_i_blocks_high; /* were l_i_reserved1 */
__le16 l_i_file_acl_high;
__le16 l_i_uid_high; /* these 2 fields */
__le16 l_i_gid_high; /* were reserved2[0] */
__u32 l_i_reserved2;
} linux2;
struct {
__le16 h_i_reserved1; /* Obsoleted fragment number/size which areremoved in ext4 */
__u16 h_i_mode_high;
__u16 h_i_uid_high;
__u16 h_i_gid_high;
__u32 h_i_author;
} hurd2;
struct {
__le16 h_i_reserved1; /* Obsoleted fragment number/size which areremoved in ext4 */
__le16 m_i_file_acl_high;
__u32 m_i_reserved2[2];
} masix2;
} osd2; /*OS dependent 2 */
__le16 i_extra_isize;
__le16 i_pad1;
__le32 i_ctime_extra; /* extra Change time (nsec << 2 | epoch) */
__le32 i_mtime_extra; /* extra Modification time(nsec << 2 |epoch) */
__le32 i_atime_extra; /* extra Access time (nsec << 2 | epoch) */
__le32 i_crtime; /* File Creation time */
__le32 i_crtime_extra; /* extraFileCreationtime (nsec << 2 | epoch) */
__le32 i_version_hi; /* high 32 bits for 64-bit version */
};Dir
用于保存所有目录的信息。
根目录总是在inode表的第二项，而其子目录则在根目录文件的内容中定义。
结构体如下：

[plain] view plaincopyprint?
	1. 
struct ext4_dir_entry {  
	2. 
       __le32  inode;                  /* Inode number文件入口的inode号，0表示该项未使用*/  
	3. 
       __le16  rec_len;                /* Directory entry length目录项长度*/  
	4. 
       __le16  name_len;               /* Name length文件名包含的字符数*/  
	5. 
       char    name[EXT4_NAME_LEN];    /* File name文件名*/  
	6. 
};  




struct ext4_dir_entry {
__le32 inode; /* Inode number文件入口的inode号，0表示该项未使用*/
__le16 rec_len; /* Directory entry length目录项长度*/
__le16 name_len; /* Name length文件名包含的字符数*/
char name[EXT4_NAME_LEN]; /* File name文件名*/
};
```