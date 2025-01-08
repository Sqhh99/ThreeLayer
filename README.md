# ThreeLayer
这是我的软件架构实践作业2 三层逻辑架构设计 基于qt，数据库为mysql

1、获取数据集
从附件1的https://www.nationmaster.com/网站中下载了“Wholesale and Retail Trade Services of Computers, Computer Peripherals and Software Turnover in Computer Programming and Consultancy Sector in the UK.xlsx”数据集
 
将该数据集存入mysql数据库中，方便获取

2、设计三层架构
1）数据访问层DataAccessLayer：
定义MysqlConn类（mysqlconn.h/cpp），它拥有两个个方法：bool connMySql()用于连接mysql数据库，QList<QStringList> getTableData(const QString &tableName)用于获取对应表格的数据

2）业务逻辑层BusinessLogicLayer：
1.定义MysqlController类（mysqlcontroller.h/cpp）:用于调用数据访问层的MysqlConn类，读取mysql数据，并通知表示层数据读取完成。

2.定义一个LinearRegressionResult类，用于封装slope，intercept，intercept。

3.定义LinearRegressionHelper类，它拥有一个静态方法，static LinearRegressionResult performLinearRegression(const QList<QList<QString>> &data)用于使用线性回归，并找到相关系数，最佳拟合直线方程，并将结果存储到LinearRegressionResult对象，并返回。

4.定义StatsResult类，用于封装mean，stdDev，Q1，Q3，IQR，percentiles，median，modes

5.定于PointMath类（pointmath.h/cpp），它用于数值计算，它拥有两个静态方法，calculateStats(),用于求得标准差，Q1、Q3、IQR 和百分位数，calculateMeanMedianMode()，用于求得均值、众数和中位数，最后将结果存储到StatsResult并返回。

3）表示层PresentationLayer：
1.定义SqBarChart类（sqbarchart.h/cpp）:用于绘制柱状图
2.定义SqBoxChart类（sqboxchart.h/cpp）：用于绘制箱线图
3.定义SqLineChart类（sqlinechart.h/cpp）：用于绘制折线图
4.定义SqPieChart类（sqpiechart.h/cpp）：用于绘制饼图
5.定义ThreeLayer类（threelayer.h/cpp）:用于展示主界面

画出系统部署结构图
![1](https://github.com/user-attachments/assets/d3f07ba8-6ce4-4465-81f2-3313b767fdea)

1）数据表格
关键代码截图：
 ![2](https://github.com/user-attachments/assets/45d5c503-4bcb-4ed2-88ed-7453c8c931f0)
![3](https://github.com/user-attachments/assets/a4952281-e0aa-4292-8c25-3c60a5252c73)

 
2）折线图以及使用线性回归，并找到相关系数，最佳拟合直线方程：
关键代码截图：
 ![4](https://github.com/user-attachments/assets/3f4bf504-c513-4188-a904-974cc5de15e2)
![5](https://github.com/user-attachments/assets/827e9175-b0f5-4d16-8073-297fa168ad2a)

 
3）饼图以及求得的均值、众数和中位数
关键代码截图：
 ![6](https://github.com/user-attachments/assets/5738e99d-d792-4f71-a39b-26a89273711b)
![7](https://github.com/user-attachments/assets/88a2568e-f392-474c-bf47-b8587e4a4dad)

 


4）箱线图以及求得的标准差，Q1、Q3、IQR 和百分位数
关键代码截图：
![8](https://github.com/user-attachments/assets/128966ba-7137-40e4-8b8d-59ce677934d5)
![9](https://github.com/user-attachments/assets/4fa2db33-7595-4096-9d19-546a7c2b7a4a)

 
 
5）柱状图
关键代码截图：
 ![10](https://github.com/user-attachments/assets/89c7b1f5-58f0-4214-9576-3429b34d952f)
![11](https://github.com/user-attachments/assets/e2671868-488a-4086-ac71-136e1fee19c0)

 

