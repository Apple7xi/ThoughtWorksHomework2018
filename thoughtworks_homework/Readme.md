# ThoughtWorks 2018校园招聘作业解题说明
### 题目理解
输入分为两部分：
 * 当前时间
 * 车辆信息

输出要求为三部分：
 * 按时间保养提醒
 * 按里程保养提醒
 * 报废车辆提醒

根据题目分析得出优先级从高至低依次为：
 1. 报废提醒
 2. 里程提醒
 3. 时间提醒

需要注意的点为：
 + 时间保养分为三种情况，且年份判断独立，即无论月份，年份相减即为相差年数，月份处理同理
 + 里程保养以10000为单位，距离500时提醒，则9500～0000尾数时进行提醒
 + 报废提醒中提到6年和3年，根据题目描述，以及测试用例二的结果分析，题目要求按照天数计算，即6年=2190天，3年=1095天，得出报废日期时，需要考虑闰年对日期的影响。
 
 
 ### 代码介绍
程序在ubuntu 17.04操作系统下使用vim进行编写

代码中定义了日期类
 ```c++
 	struct time_class{
    	int year;
        int month;
        int day;
    };
 ```
 用于程序中对日期的存储;
 
 定义了车辆类
 ```c++
 	class car{
    private:
        string number;//车牌号
        string brand;//品牌名称
        time_class time;//购买日期
        int distance;//行驶公里数
        bool fix;//有无大修
    public:
    	string get_number() const;//访问车牌号
        string get_brand() const;//访问品牌名称
        time_class get_time() const;//访问购买日期
        int get_distance() const;//访问行驶公里数
        bool get_fix() const;//访问有无大修
    };
 ```
用于程序中对车辆信息的存储;

主要使用到的函数：
```c++
//对vector<car>进行sort函数排序时，传入的比较函数;
bool camp(const car &car1,const car &car2);

//计算报废的日期，time为车辆购买日期，fix为车辆有无大修，返回车辆报废的日期;
time_class time_fly(const time_class &time,const bool &fix);

//判断是否已经报废或者是否进行报废提醒，w_time为车辆报废日期，n_time为当前日期，返回值分为三种：==1、已经报废;==2、报废提醒;==3、无报废提醒;
int write_off(const car &n_car,const int &n_time);

//判断里程行驶保养，n_car为车辆信息，返回值分为两种：==1、行驶保养提醒；==2、无行驶保养提醒;
int distance_related(const car &n_car);

//判断时间保养，n_car为车辆信息，n_time为当前日期,返回值分为两种：==1、时间保养提醒;==2、无时间保养提醒;
int time_related(const car &n_car,const time_class &n_time);

//对vector<car>按照输出要求进行输出
void print_cars(const vector<car> &n_cars);

```

### 代码运行
在ubuntu 17.04下运行时：

在代码存放目录下进行操作：

```shell
g++ -Wall -std=c++11 main.cpp -o main.out
```
得到执行文件main.out,然后在当前目录下执行：
```shell
./main.out
```
程序会等待测试用例的输入，输入测试用例：
```shell
SubmitDate: 2030/09/01
CAR0001|2025/04/05|Porsche|10000|F
CAR0002|2029/10/14|Porsche|9000|F
CAR0003|2026/08/17|Porsche|13000|F
CAR0004|2027/11/01|BYD|23000|T
CAR0005|2027/01/11|BYD|19500|F
CAR0006|2029/07/01|Audi|10001|T
CAR0007|2028/04/19|Ford|9800|F
CAR0008|2027/07/10|Ford|15000|T
CAR0009|2024/10/22|Ford|90300|F
```

按ctrl+d结束输入，得到输出结果：

```shell
Reminder
==================

* Time-related maintenance coming soon...
Audi: 1 (CAR0006)
Porsche: 1 (CAR0002)

* Distance-related maintenance coming soon...
BYD: 1 (CAR0005)
Ford: 1 (CAR0007)
Porsche: 1 (CAR0001)

* Write-off coming soon...
BYD: 1 (CAR0004)
Ford: 1 (CAR0009)

```

分别对测试用例一、二进行测试：

输入一：
```shell
SubmitDate: 2030/09/01
CAR0001|2025/04/05|Porsche|10000|F
CAR0002|2029/10/14|Porsche|9000|F
CAR0003|2026/08/17|Porsche|13000|F
CAR0004|2027/11/01|BYD|23000|T
CAR0005|2027/01/11|BYD|19500|F
CAR0006|2029/07/01|Audi|10001|T
CAR0007|2028/04/19|Ford|9800|F
CAR0008|2027/07/10|Ford|15000|T
CAR0009|2024/10/22|Ford|90300|F
```
输出一：
```shell
Reminder
==================

* Time-related maintenance coming soon...
Audi: 1 (CAR0006)
Porsche: 1 (CAR0002)

* Distance-related maintenance coming soon...
BYD: 1 (CAR0005)
Ford: 1 (CAR0007)
Porsche: 1 (CAR0001)

* Write-off coming soon...
BYD: 1 (CAR0004)
Ford: 1 (CAR0009)

```

输入二：
```shell
SubmitDate: 2050/05/01
CAR0001|2044/05/01|Volkswagen|65535|F
CAR0002|2044/05/03|BMW|100001|F
CAR0003|2047/05/02|Mercedes-Benz|37789|T
CAR0004|2047/05/03|Honda|59908|T
CAR0005|2049/12/10|Peugeot|49999|F
CAR0006|2046/11/15|Jeep|2000|F
CAR0007|2046/11/16|Jeep|5000|F
```
输出二：
```shell
Reminder
==================

* Time-related maintenance coming soon...
Jeep: 2 (CAR0006, CAR0007)

* Distance-related maintenance coming soon...
Peugeot: 1 (CAR0005)

* Write-off coming soon...
BMW: 1 (CAR0002)
Honda: 1 (CAR0004)

```