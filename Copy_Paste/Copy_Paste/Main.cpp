#include<iostream>
#include<vector>

using namespace std;

class Any_Vector {
public:
	Any_Vector() {};

	template<typename T>
	Any_Vector(T elem) {
		values.push_back(new Element<T>(elem));
	}

	Any_Vector(const Any_Vector& vector) {
		this->values.clear();
		this->values = vector.values;
	}

	Any_Vector& operator=(const Any_Vector& elem) {
		if (this != &elem) {
			const_cast<Any_Vector&>(elem).Swap(*this);
		}
		return *this;
	}

	void Swap(Any_Vector& vector) noexcept {
		using std::swap;
		swap(*this, vector);
		swap(vector, *this);
	}

	template<typename T>
	void Push_back(T elem) {
		values.push_back(new Element<T>(elem));
	}

	template<typename T>
	T Pop_back() {
		if (values.empty() != true) {
			if (values.back()->Type() == typeid(T)) {
				Data* e = values.back();
				values.pop_back();
				return static_cast<Element<T>*> (e)->Elem();
			}
			else {
				throw std::invalid_argument("Different types");
			}
		}
		else {
			throw std::invalid_argument("Empty vector");
		}
	}

	template<typename T>
	T Elem(int i) {
		if (values.size() > i) {
			if (values[i]->Type() == typeid(T)) {
				Data* e = values[i];
				return static_cast<Element<T>*> (e)->Elem();
			}
			else {
				throw std::invalid_argument("Different types");
			}
		}
		else {
			throw std::invalid_argument("Not number");
		}
	}

private:

	class Data {
	public:
		~Data() {};
		virtual const type_info& Type() = 0;
	};

	template<typename T>
	class Element : public Data {
	public:
		Element(T elem) {
			data = elem;
		}

		const type_info& Type() {
			return typeid(data);
		}

		T Elem() {
			return data;
		}

		T data;
	};

public:
	vector<Data*> values;
};

int main(void) {
	Any_Vector vector1(10);
	vector1.Push_back(1.1);
	double ans = vector1.Elem<double>(1);
	
	cout << ans << endl;

	Any_Vector vector2 = vector1;

	int num = vector2.Elem<int>(0);
	ans = vector2.Elem<double>(1);

	cout << num << ' ' << ans << endl;

	cout << vector2.Pop_back<double>() << endl;

	return 0;
}