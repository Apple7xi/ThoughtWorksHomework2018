/* 
 * 2017/10/16;
 * by alex;
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*
#define SIX_YEAR 2190
#define THREE_YEAR 1095
*/

using std::vector;using std::cin;using std::cout;using std::string;using std::endl;

//日期类定义
struct time_class{
	int year;
	int month;
	int day;
	time_class(){};
	time_class(const int &yearA,const int &monthA,const int &dayA):year(yearA),month(monthA),day(dayA){};
};

//车辆类定义
class car{
private:	
	string number;
	string brand;
	time_class time; 
	int distance;
	bool fix;
public:
	car(){}
	car(const string &num,const string &brd,const int &yea,const int &mon,const int &da,const int &dis,const bool &fx):number(num),brand(brd),time(yea,mon,da),distance(dis),fix(fx){}
	string get_number() const { return number; }
	string get_brand() const { return brand; }
	int get_distance() const { return distance; }
	bool get_fix() const { return fix; }
	time_class get_time() const { return time;  }
};
//car类比较函数
bool camp(const car &car1,const car &car2){
	if(car1.get_brand() != car2.get_brand())
		return car1.get_brand() < car2.get_brand();
	else
		return car1.get_number() < car2.get_number();
}

//计算报废日期

time_class time_fly(const time_class &time,const bool &fix){
	int temp, decrease = 0, new_year = time.year, new_month = time.month, new_day = time.day;
	if(fix)
		temp = 3;
	else
		temp = 6;
	for(int i = 0;i < temp;i++){
		if(new_month <= 2 ){
			if(new_year % 400 == 0 || (new_year % 4 ==0 && new_year % 100 != 0))
				decrease++;
		}else{
			if((new_year + 1) % 400 == 0 ||((new_year + 1) % 4 ==0 && (new_year + 1 )% 100 != 0))
				decrease++;
		}
		new_year++;
	}
	new_day -= decrease;	
	if(new_day < 0){//回退一个月;
		switch(new_month){
			case 1:new_day = new_day + 31;new_month = 12;new_year--;break;
			case 2:new_day = new_day + 31;new_month --;break;
			case 3:new_day = new_day + ((new_year % 400 == 0||(new_year % 4 == 0&&new_year %100 != 0))?29:28);new_month --;break;
			case 4:new_day = new_day + 31;new_month --;break;
			case 5:new_day = new_day + 30;new_month --;break;
			case 6:new_day = new_day + 31;new_month --;break;
			case 7:new_day = new_day + 30;new_month --;break;
			case 8:new_day = new_day + 31;new_month --;break;
			case 9:new_day = new_day + 31;new_month --;break;
			case 10:new_day = new_day + 30;new_month --;break;
			case 11:new_day = new_day + 31;new_month --;break;
			case 12:new_day = new_day + 30;new_month --;break;
		}
	}
	return time_class(new_year,new_month,new_day);
}

/*
time_class time_fly(const time_class &time,const int &duration){
	int dur = duration;
	int new_year = time.year,new_month = time.month,new_day = time.day;
	dur = dur + new_day - 1;
	new_day = 1;
	while(dur >= 0){
		switch(new_month){	
			case 1:dur -= 31;new_month++;break;
			case 2:dur -= ((new_year % 400 == 0 || (new_year % 4 ==0 && new_year % 100 != 0))?29:28);new_month++;break;
			case 3:dur -= 31;new_month++;break;
			case 4:dur -= 30;new_month++;break;
			case 5:dur -= 31;new_month++;break;
			case 6:dur -= 30;new_month++;break;
			case 7:dur -= 31;new_month++;break;
			case 8:dur -= 31;new_month++;break;
			case 9:dur -= 30;new_month++;break;
			case 10:dur -= 31;new_month++;break;
			case 11:dur -= 30;new_month++;break;
			case 12:dur -= 31;new_month = 1;new_year++;break;
		}
	}
	if(dur < 0){//回退一个月;
		switch(new_month){
			case 1:new_day = new_day + dur + 31;new_month = 12;new_year--;break;
			case 2:new_day = new_day + dur + 31;new_month --;break;
			case 3:new_day = new_day + dur + ((new_year % 400 == 0||(new_year % 4 == 0&&new_year %100 != 0))?29:28);new_month --;break;
			case 4:new_day = new_day + dur + 31;new_month --;break;
			case 5:new_day = new_day + dur + 30;new_month --;break;
			case 6:new_day = new_day + dur + 31;new_month --;break;
			case 7:new_day = new_day + dur + 30;new_month --;break;
			case 8:new_day = new_day + dur + 31;new_month --;break;
			case 9:new_day = new_day + dur + 31;new_month --;break;
			case 10:new_day = new_day + dur + 30;new_month --;break;
			case 11:new_day = new_day + dur + 31;new_month --;break;
			case 12:new_day = new_day + dur + 30;new_month --;break;
		}
	}
	return time_class(new_year,new_month,new_day);
}
*/

//报废判断:1:已报废;2:提醒报废;3:无提醒;
int write_off(const car &n_car,const time_class &n_time){
	time_class w_time;
	if(n_car.get_fix())
		w_time = time_fly(n_car.get_time(),n_car.get_fix());
//		w_time = time_fly(n_car.get_time(),THREEYEAR);	
 	else
		w_time = time_fly(n_car.get_time(),n_car.get_fix());
//		w_time = time_fly(n_car.get_time(),SIXYEAR);
	int temp = (w_time.year - n_time.year) * 12 + w_time.month - n_time.month;
	if(temp < 0)
		return 1;
	else if(temp == 0){
		if(w_time.day <= n_time.day)
			return 1;
		else
			return 2;
	}
	else if(temp == 1)
		return 2;
	else
		return 3;
}

//里程保养判断:1:提醒保养;2:无提醒;
int distance_related(const car &n_car){
	int n_dis = n_car.get_distance();
	int temp = n_dis % 10000;
	if(temp >= 9500 || temp == 0)
		return 1;
	else
		return 2;
}

//时间保养判断:1:提醒保养;2:无提醒;
int time_related(const car &n_car,const time_class &n_time){
	int temp;
	time_class time = n_car.get_time();
	bool fix = n_car.get_fix();
	if(fix)
		temp = (3 - ((n_time.year - time.year) * 12 + n_time.month - time.month) % 3) % 3;
	else{
		if(n_time.year - time.year >= 3)
			temp =(6 - ((n_time.year - time.year) * 12 + n_time.month - time.month) % 6) % 6;
		else
			temp = (12 - ((n_time.year - time.year) * 12 + n_time.month - time.month) % 12) % 12;
	}
	if(temp == 0){
		if(n_time.day < time.day)
			return 1;
		else
			return 2;
	}else if(temp == 1)
		return 1;
	else
		return 2;
}

//输出车辆vector信息;	
void print_cars(const vector<car> &n_cars){	
	for(auto member = n_cars.cbegin();member != n_cars.cend();){
		vector<car> temp;
		unsigned int ix = 1;
		temp.push_back(*member);
	 	member++;
		while(member != n_cars.cend() && member->get_brand() == (member-1)->get_brand()){
			temp.push_back(*member);
			member++;
		}
		cout <<(*(temp.cbegin())).get_brand() << ": " << temp.size() << " ";
		for(auto t_member = temp.cbegin();t_member != temp.cend();t_member++,ix++){
			if(ix == 1)
				cout << "(";
			else
				cout <<", ";
			cout << t_member->get_number();
			if(ix == temp.size())
				cout << ")" << endl;
		}
	}
}

int main(void){
	string input;
	vector<car> cars,w_cars,d_cars,t_cars;
	time_class n_time;

	//当前日期读入;
	getline(cin,input);
	{
		auto pos = input.find_first_of("1234567890");
		int now_year = stoi(input.substr(pos,4));
		int now_month = stoi(input.substr(pos+5,2));
		int now_day = stoi(input.substr(pos+8,2));
		n_time = time_class(now_year,now_month,now_day);
	}

	//车辆信息读入;
	while(getline(cin,input)){
		auto pos1 = input.find('|');
		auto pos2 = input.find('|',pos1+1);
		auto pos3 = input.find('|',pos2+1);
		auto pos4 = input.find('|',pos3+1);
		string num = input.substr(0,pos1-0);
		string time = input.substr(pos1+1,pos2-pos1-1);
		string brand = input.substr(pos2+1,pos3-pos2-1);
		int distance = stoi(input.substr(pos3+1,pos4-pos3-1));
		bool fix = (input.substr(pos4+1,1))=="T"?true:false;
		int year = stoi(time.substr(0,4));
		int month = stoi(time.substr(5,2));
		int day = stoi(time.substr(8,2));
		cars.emplace_back(num,brand,year,month,day,distance,fix);
	}

	 //车辆分类;
	for(auto member = cars.cbegin();member != cars.cend();member++){
		int temp = write_off(*member,n_time);
		if(temp == 1)
			continue;
		else if(temp == 2){
			w_cars.push_back(*member);
			continue;
		}
		temp = distance_related(*member);
		if(temp == 1){
			d_cars.push_back(*member);
			continue;
		}
		temp = time_related(*member,n_time);
		if(temp == 1){
			t_cars.push_back(*member);
			continue;
		}
	}
	
	//各类车辆vector排序，便于输出处理;
	sort(w_cars.begin(),w_cars.end(),camp);
	sort(t_cars.begin(),t_cars.end(),camp);
	sort(d_cars.begin(),d_cars.end(),camp);	

	cout << "Reminder" << endl;
	cout << "==================" << endl << endl;
	cout << "* Time-related maintenance coming soon..." << endl;
	print_cars(t_cars);
	cout << endl;
	cout << "* Distance-related maintenance coming soon..." << endl;
	print_cars(d_cars);
	cout << endl;
	cout << "* Write-off coming soon..." << endl;
	print_cars(w_cars);

	return 0;
}

