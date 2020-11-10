#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

class Fraction {
protected:
	int r, n, d;
public:
	Fraction() {
		r = 0;
		n = 0;
		d = 1;
	}

	Fraction(int line) {
		this->r = line;
		n = 0;
		d = 1;
	}

	Fraction(double line) {
		EuAlg(line * pow(10, 3), pow(10, 3));
	}

	Fraction(int r, int n, int d) {
		this->r = r;
		this->n = n;
		this->d = d;
	}

	 friend istream& operator>>(istream& in, Fraction& frac) {
        int n;
        in >> n;

        if (in.peek() == '.') {
            in.get();
            int u;
            in >> u;
            if (in.peek() == '/') {
                in.get();
                int h;
                in >> h;
                frac = Fraction(n, u, h);
            }
            else {
                string b = to_string(n) + '.' + to_string(u);
                double e = stod(b);
                int l = e * int(1e9);
                frac.EuAlg(l, int(1e9));
            }
        }

        else if (in.peek() == '/') {
            in.get();
            int u;
            in >> u;
            frac.EuAlg(n, u);
        }

        else if (in.peek() == '\n' || in.peek() == ' ') {
            frac = Fraction(n);
        }

        return in;
    }


	friend ostream& operator<<(ostream& out, const Fraction& frac) {
		if (frac.n == 0) {
			out << frac.r;
		}
		else if (frac.r == 0) {
			out << frac.n << '/' << frac.d;
		}
		else {
			out << frac.r << ' ' << frac.n << '/' << frac.d;
		}
		return out;
	}

	int WholePart(string s) {
		int parts = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == ' ') {
				parts = 2;
				break;
			}

			if (s[i] == '/') {
				parts = 1;
				break;
			}

			if (s[i] == '.') {
				parts = 3;
				break;
			}
		}
		return parts;
	}

	void EuAlg(int num, int den) {
		if (num % den == 0) {
			num /= den;
			r += num;
			n = 0;
			d = 1;
		}

		else {
			int a = abs(num);
			int b = abs(den);
			n = num;
			d = den;
			while (a != b)
				if (a > b) {
					a -= b;
				}
				else {
					b -= a;
				}
			n /= b;
			d /= b;

			if (abs(n) > abs(d)) {
				r = n / d;
				n = n % d;
			}
			else {
				r = 0;
			}
		}
	}

	Fraction operator+(Fraction a) {
		Fraction f;
		int num = (r * d + n) * a.d + (a.r * a.d + a.n) * d;
		int den = d * a.d;
		f.EuAlg(num, den);
		return f;
	}

	Fraction operator-(Fraction a) {
		Fraction f;
		int num = (r * d + n) * a.d - (a.r * a.d + a.n) * d;
		int den = d * a.d;
		f.EuAlg(num, den);
		return f;
	}

	Fraction operator*(Fraction a) {
		Fraction f;
		int num = (r * d + n) * (a.r * a.d + a.n);
		int den = d * a.d;
		f.EuAlg(num, den);
		return f;
	}

	Fraction operator/(Fraction a) {
		Fraction f;
		int num = (r * d + n) * a.d;
		int den = d * (a.r * a.d + a.n);
		f.EuAlg(num, den);
		return f;
	}

	Fraction& operator=(const Fraction& a) {
		Fraction f;
		f.r = a.r;
		f.n = a.n;
		f.d = a.d;
		return f;
	}

	friend Fraction operator-(Fraction a) {
		Fraction f;
		if (a.r != 0) {
			f.r = -a.r;
			f.n = a.n;
			f.d = a.d;
		}
		else {
			f.n = -a.n;
			f.d = a.d;
		}

		return f;
	}

	operator int() {
		int result;
		int num = r * d + n;
		result = num / d;
		return result;
	}

	operator double() {
		double result;
		double num = r * d + n;
		result = num / d;
		return result;
	}

	bool operator==(Fraction a) {
		if (r == a.r && n == a.n && d == a.d) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator!=(Fraction a) {
		if (r == a.r || n == a.n || d == a.d) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator<(Fraction a) {
		int num1 = (r * d + n) * a.d;
		int num2 = (a.r * a.d + a.n) * d;

		if (num1 < num2) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator<=(Fraction a) {
		int num1 = (r * d + n) * a.d;
		int num2 = (a.r * a.d + a.n) * d;

		if (num1 <= num2) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator>(Fraction a) {
		int num1 = (r * d + n) * a.d;
		int num2 = (a.r * a.d + a.n) * d;

		if (num1 > num2) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator>=(Fraction a) {
		int num1 = (r * d + n) * a.d;
		int num2 = (a.r * a.d + a.n) * d;

		if (num1 >= num2) {
			return true;
		}
		else {
			return false;
		}
	}
};

int main()
{
	int step;
	std::cin >> step;
	while (step != 0) {
		if (step == 1) {
			int num;
			std::cin >> num;
			Fraction f(num);
			cout << f << endl;
		}

		else if (step == 2) {
			Fraction f;
			std::cin >> f;
			cout << int(f) << endl;
		}

		else if (step == 3) {
			double num;
			std::cin >> num;
			Fraction f(num);
			cout << f << endl;
		}

		else if (step == 4) {
			Fraction f;
			std::cin >> f;
			cout << fixed << setprecision(2) << double(f) << endl;
		}

		else if (step == 5) {
			Fraction a;
			Fraction b;
			std::cin >> a;
			std::cin >> b;
			cout << a + b << endl;
		}

		else if (step == 6) {
			Fraction a;
			Fraction b;
			std::cin >> a;
			std::cin >> b;
			cout << a - b << endl;
		}

		else if (step == 7) {
			Fraction a;
			Fraction b;
			std::cin >> a;
			std::cin >> b;
			cout << a * b << endl;
		}

		else if (step == 8) {
			Fraction a;
			Fraction b;
			std::cin >> a;
			std::cin >> b;
			cout << a / b << endl;
		}

		else if (step == 9) {
			Fraction f;
			std::cin >> f;
			cout << -f << endl;
		}

		else if (step == 10) {
			Fraction a;
			Fraction b;
			std::cin >> a;
			std::cin >> b;
			if (a < b) {
				cout << a << " is less than " << b << endl;
			}

			else if (a > b) {
				cout << a << " is greater than " << b << endl;
			}

			else if (a == b) {
				cout << a << " is equal to " << b << endl;
			}
		}

		std::cin >> step;
	}
}
