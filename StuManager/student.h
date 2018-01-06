#include <atlstr.h>
class  stu{
public:
	CString stu_no;
	CString name;
	CString age;
	CString gender;
	int grade = 0;
	CString other;

	stu(){
		grade = 0;
	}
	stu(int o){
		grade = o;
	}
	void setGrade(int o){
		grade = o;
	}
	bool operator>(stu o){
		if (grade > o.grade){
			return true;
		}
		return false;
	}
	bool operator>=(stu o){
		if (grade >= o.grade){
			return true;
		}
		return false;
	}
	bool operator<(stu o){
		if (grade < o.grade){
			return true;
		}
		return false;
	}
	bool operator<=(stu o){
		if (grade <= o.grade){
			return true;
		}
		return false;
	}
	bool operator<(int o){
		if (grade < o){
			return true;
		}
		return false;
	}
	bool operator<=(int o){
		if (grade <= o){
			return true;
		}
		return false;
	}
	bool operator>(int o){
		if (grade > o){
			return true;
		}
		return false;
	}
	bool operator>=(int o){
		if (grade >= o){
			return true;
		}
		return false;
	}
	void operator =(int o){
		grade = o;
	}
	void operator =(stu o){
		 stu_no = o.stu_no;
		 name = o.name;
		 age = o.age;
		 gender = o.gender;
		 grade = o.grade;
		 other = o.other;
	}
};