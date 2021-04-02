struct Biguint {
	int a[2000005], len;

	Biguint() {
		memset(a, 0, sizeof a);
		len = 0;
	}

	void read() {
		string str;
		cin >> str;
		memset(a, 0, sizeof a);
		len = str.length();
		for (int i = 0; i < str.size(); i++)
			a[i] = str[str.length() - i - 1] - '0';
	}

	void print() {
		for (int i = len - 1; i >= 0; i--) {
			cout << a[i];
		}
	}

	bool operator < (const Biguint& obj) {
		const int* b = obj.a;
		if (this->len == obj.len) {
			for (int i = len-1; i>=0; --i)
				if (a[i] != b[i]) return a[i] < b[i];
			return false;
		}
		else return this->len < obj.len;
	}

	bool operator > (const Biguint& obj) {
		const int* b = obj.a;
		if (this->len == obj.len) {
			for (int i = len-1; i>=0; --i)
				if (a[i] != b[i]) return a[i] > b[i];
			return false;
		}
		else return this->len > obj.len;
	}

	bool operator != (const Biguint& obj) {
		return (*this < obj) | (*this > obj);
	}

	bool operator == (const Biguint& obj) {
		return !((*this < obj) | (*this > obj));
	}

	bool operator <= (const Biguint& obj) {
		return (*this) < obj || (*this) == obj;
	}

	bool operator >= (const Biguint& obj) {
		return (*this) > obj || (*this) == obj;
	}

	Biguint operator += (const Biguint& obj) {
		const int* b = obj.a;
		if (obj.len > len) len = obj.len;
		for (int i = 0; i < len; i++) {
			a[i] += b[i];
			if (a[i] >= 10) a[i + 1] += a[i] / 10, a[i] %= 10;
		}
		if (a[len]) ++len;
		while (a[len - 1] >= 10)
			a[len] += a[len - 1] / 10, a[len - 1] %= 10, ++len;
		return *this;
	}

	Biguint operator + (const Biguint& obj) {
		Biguint ret;
		ret += *this;
		ret += obj;
		return ret;
	}

	Biguint operator -= (const Biguint& obj) {
		const int* b = obj.a;
		for (int i = 0; i < len; i++) {
			a[i] -= b[i];
			if (a[i] < 0) a[i + 1]--, a[i] += 10;
		}
		while (a[len - 1] == 0 && len > 0) --len;
		return *this;
	}

	Biguint operator -(const Biguint& obj) {
		Biguint ret;
		ret += *this;
		ret -= obj;
		return ret;
	}

	Biguint operator *= (int b) {
		for (int i = 0; i < len; i++)
			a[i] *= b;
		for (int i = 0; i < len; i++)
			a[i + 1] += a[i] / 10, a[i] %= 10;
		++len;
		while (a[len - 1] >= 10)
			a[len] += a[len - 1] / 10, a[len - 1] %= 10, ++len;
		while (a[len - 1] == 0 && len > 0) --len;
		return *this;
	}

	Biguint operator * (int b) {
		Biguint ret;
		ret = *this;
		ret *= b;
		return ret;
	}

	Biguint operator * (const Biguint& obj) {
		const int* b = obj.a;
		Biguint ret;
		for (int i = 0; i < len; i++)
			for (int j = 0; j < obj.len; j++)
				ret.a[i + j] += a[i] * b[j];
		for (int i = 0; i < len + obj.len; i++)
			ret.a[i + 1] += ret.a[i] / 10, ret.a[i] %= 10;
		ret.len = len + obj.len;
		++ret.len;
		while (ret.a[ret.len - 1])
			ret.a[ret.len] += ret.a[ret.len - 1] / 10, ret.a[ret.len - 1] %= 10, ++ret.len;
		while (ret.a[ret.len - 1] == 0 && ret.len > 0) --ret.len;
		return ret;
	}

};


struct Bigint {
	Biguint a;
	bool sign;

	Bigint() {
		sign = 1;
	}

	bool operator < (const Bigint& obj) {
		if (this->sign == 1) {
			if (obj.sign == 1)
				return a < obj.a;
			else
				return 0;
		}
		else {
			if (obj.sign == 0)
				return a > obj.a;
			else
				return 1;
		}
	}

	bool operator > (const Bigint& obj) {
		if (this->sign == 1) {
			if (obj.sign == 1)
				return a > obj.a;
			else
				return 1;
		}
		else {
			if (obj.sign == 0)
				return a < obj.a;
			else
				return 0;
		}
	}

	bool operator != (const Bigint& obj) {
		return (*this < obj) | (*this > obj);
	}

	bool operator == (const Bigint& obj) {
		return !((*this < obj) | (*this > obj));
	}

	bool operator <= (const Bigint& obj) {
		return (*this) < obj || (*this) == obj;
	}

	bool operator >= (const Bigint& obj) {
		return (*this) > obj || (*this) == obj;
	}

	Bigint operator + (const Bigint& obj) {
		Bigint ret;
		if (this->sign == obj.sign) {
			ret.sign = this->sign;
			ret.a = this->a + obj.a;
		}
		else {
			if (this->a == obj.a) return ret;
			if (this->a > obj.a) {
				ret.sign = this->sign;
				ret.a = this->a - obj.a;
			}
			else {
				ret.sign = obj.sign;
				Bigint tmp = obj;
				ret.a = tmp.a - (*this).a;
			}
		}
		while (ret.a.a[ret.a.len - 1] == 0 && ret.a.len > 0) ret.a.len--;
		return ret;
	}

	Bigint operator += (const Bigint& obj) {
		(*this) = (*this) + obj;
	}

	Bigint operator - (const Bigint& obj) {
		Bigint ret, tmp;
		tmp = obj;
		tmp.sign ^= 1;
		ret = *this + tmp;
		return ret;
	}

	Bigint operator -= (const Bigint& obj) {
		(*this) = (*this) - obj;
	}

	Bigint operator * (const Bigint& obj) {
		Bigint ret;
		ret.sign = this->sign == obj.sign;
		ret.a = this->a * obj.a;
		if (ret.a.len == 0) ret.sign = 1;
		return ret;
	}

	Bigint operator *= (const Bigint& obj) {
		(*this) = (*this) * obj;
	}

};


ostream& operator << (ostream& os, Biguint num)
{
	for (int i = num.len - 1; i >= 0; --i)
		os << num.a[i];
	if (num.len == 0) os << "0";
	return os;
}

istream& operator >> (istream& is, Biguint& num)
{
	string str;
	is >> str;
	memset(num.a, 0, sizeof num.a);
	num.len = str.length();
	for (int i = 0; i < str.length(); i++)
		num.a[i] = str[str.length() - i - 1] - '0';
	return is;
}

ostream& operator << (ostream& os, Bigint num) {
	if (num.sign == 0) os << "-";
	os << num.a;
	return os;
}

istream& operator >> (istream& is, Bigint& num) {
	string str;
	is >> str;
	memset(num.a.a, 0, sizeof num.a);
	if (str[0] == '-') {
		num.a.len = str.length() - 1;
		for (int i = 0; i < str.length() - 1; i++)
			num.a.a[i] = str[str.length() - i - 1] - '0';
		num.sign = 0;
	}
	else {
		num.a.len = str.length();
		for (int i = 0; i < str.length(); i++)
			num.a.a[i] = str[str.length() - i - 1] - '0';
		num.sign = 1;
	}
	return is;
}

