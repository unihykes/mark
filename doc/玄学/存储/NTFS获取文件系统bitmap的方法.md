1、查询卷的引导扇区，获取到主MFT的地址、每个簇size，卷length等信息

2、查询主MFT，根据MFT编号，找到第6号MFT（$BITMAP）

3、查询6号MFT,通过0x14-0x15确认第一个属性的偏移地址(例如0x38)

4、查询第1个属性，获取属性类型以及属性长度，

5、通过属性长度进行计算，按偏移量依次查询其他属性，直到找到数据属性($DATA)，属性类型编号是0x80

6、计算0x80属性的长度，判断是否为非常驻属性

7、非常驻属性：获取簇流的起始VCN以及结束VCN

8、获取簇流列表的偏移量（例如0x40）

9、【可选】还可以获取属性内容的分配空间，实际占用空间、初始化大小 等其他信息

10、通过簇流列表偏移量，找到簇流列表

11、计算簇流列表，找到存放数据的簇的起始位置（相对于卷的lcn），以及长度；，找到该簇流，读取其中数据，即为bitmap的真是数据；

12、如果簇流列表包含多个簇流，则依次计算其他簇流信息，并读取bitmap数据内容；

~~end~~